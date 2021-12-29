package heap

type Heap struct {
	h       []int
	capcity int
	used    int
}

// init heap
func NewHeap(capacity int) *Heap {
	return &Heap{
		h:       make([]int, capacity+1),
		capcity: capacity,
		used:    0,
	}
}

// top-max-heap, heapify from down to up
func (heap *Heap) insert(data int) {
	if heap.used >= heap.capcity {
		return
	}

	heap.used++
	heap.h[heap.used] = data

	// compare with parent data
	i := heap.used
	parent := i / 2
	for parent > 0 && heap.h[parent] < heap.h[i] {
		swap(heap.h, parent, i)
		i = parent
		parent = i / 2
	}
}

func (heap *Heap) removeMax() {
	if heap.used == 0 {
		return
	}

	// swap max and down
	swap(heap.h, 1, heap.used)
	heap.used--

	// heapify from up to down
	heapfyUpToDown(heap.h, heap.used)
}

func heapfyUpToDown(h []int, count int) {
	for i := 1; i < count/2; {
		maxIndex := i
		if h[i] < h[i*2] {
			maxIndex = i * 2
		}
		if i*2+1 <= count && h[maxIndex] < h[i*2+1] {
			maxIndex = i*2 + 1
		}
		if maxIndex == i {
			break
		}

		swap(h, i, maxIndex)
		i = maxIndex
	}
}

// swap tow element
func swap(h []int, i int, j int) {
	h[i], h[j] = h[j], h[i]
}
