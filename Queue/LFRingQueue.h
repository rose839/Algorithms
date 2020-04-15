#ifndef LFRINGQUEUE_H
#define LFRINGQUEUE_H

/* Lock free ring queue */

#include <mutex>
#include <atomic>
#include <chrono>

template <typename _TyData, long _lCount = 100000>
class LFRingQueue {
public:
	LFRingQueue(long lCount = _lCount) :
		m_lHeadIterator(0), m_lTailIterator(0), m_lCount(lCount) {

		m_queue = new _TyData*[m_lCount];
		memset(m_queue, 0, sizeof(_TyData*) * m_lCount);
	}

	~LFRingQueue() {
		if (m_queue) {
			delete [] m_queue;
		}
	}

	bool enqueue(_TyData *pData, unsigned int uiRetries = 1000) {
		if (nullptr == pData) {
			return false;
		}

		unsigned int uiCurrRetries = 0;
		while (uiCurrRetries < uiRetries) {
			long lHeadIterator = m_lHeadIterator.load();

			if (nullptr == m_queue[lHeadIterator]) {
				long lHeadIteratorOrig = lHeadIterator;

				lHeadIterator++;
				if (lHeadIterator >= m_lCount) { // head iterator reset to 0
					lHeadIterator = 0;
				}

				/* m_lHeadIterator doesn't changed */
				if (std::atomic_compare_exchange_strong(&m_lHeadIterator, 
					                    &lHeadIteratorOrig, lHeadIterator)) {
					m_queue[lHeadIteratorOrig] = pData;

					if (!m_bEventSet.test_and_set()) {
                        m_bHasItem.test_and_set();
                    }
					
                    return true;
				}
			} else { // retry
				// The queue is full.  Spin a few times to check to see if an item is popped off.
            	++uiCurrRetries;
			}
		}

		return false;
	}

	bool dequeue(_TyData **ppData) {
		if (!ppData) {
			return false;
		}

		bool bDone = false;
		while (!bDone) {
			long lTailIterator = m_lTailIterator;
			volatile _TyData *pData = m_queue[lTailIterator];

			if (nullptr != pData  {
                long lTailIteratorOrig = lTailIterator;

                ++lTailIterator;
                if (lTailIterator >= m_lCount) {
                        lTailIterator = 0;
                }

                if (std::atomic_compare_exchange_strong( &m_lTailIterator, &lTailIteratorOrig, lTailIterator)) {
                        m_queue[lTailIteratorOrig] = nullptr;
                        *ppdata = (_TyData*)pdata;

                        return true;
                }
            } else { // no item
                bDone = true;
                m_bEventSet.clear();
            }
		}

		*ppData = nullptr;
		return false;
	}

	long get_count() const {
        long lCount = count();

        if (0 != lCount) {
        	return lCount;
        }

        // If the queue is full then the item right before the tail item will be valid.  If it
        // is empty then the item should be set to NULL.
        long lLastInsert = m_lTailIterator - 1;
        if (lLastInsert < 0)
                lLastInsert = m_lCount - 1;

        volatile _TyData *pdata = m_queue[lLastInsert];
        if ( pdata != nullptr ) {
        	return m_lCount;
        }

        return 0;
    }

    long get_maxsize() const {
        return m_lCount;
    }

    bool has_item() {
        return m_bHasItem.test_and_set();
    }

    void set_item_flag_back() {
        m_bHasItem.clear();
    }

private:
    long count() const {
        volatile long lHeadIterator = m_lHeadIterator;
        volatile long lTailIterator = m_lTailIterator;

        if (lTailIterator > lHeadIterator)
                return m_lCount - lTailIterator + lHeadIterator;

        // This has a bug where it returns 0 if the queue is full.
        return lHeadIterator - lTailIterator;
    }

private:
	std::atomic<long> m_lHeadIterator; // enqueue index
	std::atomic<long> m_lTailIterator; // dequeue index
	_TyData **m_queue;                 // array of pointers to the data
	long m_lCount;                     // size of the queue
	std::atomic_flag m_bEventSet = ATOMIC_FLAG_INIT; // a flag to use whether we should change the item flag
	std::atomic_flag m_bHasItem  = ATOMIC_FLAG_INIT; // a flag to indicate whether there is an item enqueued
};

#endif