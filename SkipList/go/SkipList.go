/*
 * @Author: your name
 * @Date: 2022-02-15 12:17:41
 * @LastEditTime: 2022-02-15 13:32:30
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /SkipList/go/SkipList.go
 */

package SkipList

import "math/rand"

const (
	maxLevel int     = 16 // Should be enough for 2^16 elements
	p        float32 = 0.25
)

// Element is an Element of a skiplist.
type Element struct {
	Score   float64
	Value   interface{}
	forward []*Element
}

func newElement(score float64, value interface{}, level int) *Element {
	return &Element{
		Score:   score,
		Value:   value,
		forward: make([]*Element, level),
	}
}

// SkipList represents a skiplist.
// The zero value from SkipList is an empty skiplist ready to use.
type SkipList struct {
	header *Element // header is a dummy element
	len    int      // current skiplist length，header not included
	level  int      // current skiplist level，header not included
}

// New returns a new empty SkipList.
func New() *SkipList {
	return &SkipList{
		header: &Element{forward: make([]*Element, maxLevel)},
	}
}

func randomLevel() int {
	level := 1
	for rand.Float32() < p && level < maxLevel {
		level++
	}

	return level
}

// Front returns first element in the skiplist which maybe nil.
func (sl *SkipList) Front() *Element {
	return sl.header.forward[0]
}

// Next returns first element after e.
func (e *Element) Next() *Element {
	if e != nil {
		return e.forward[0]
	}

	return nil
}

// Search the skiplist to findout element with the given score.
// Returns *Element if the given score present, otherwise returns nil.
func (sl *SkipList) Search(score float64) *Element {
	x := sl.header
	for i := sl.level - 1; i >= 0; i-- {
		for x.forward[i] != nil && x.Score < score {
			x = x.forward[i]
		}
	}

	x = x.forward[0]
	if x != nil && x.Score == score {
		return x
	}
	return nil
}

// Insert (score, value) pair to the skiplist and returns pointer of element.
func (sl *SkipList) Insert(score float64, value interface{}) *Element {
	update := make([]*Element, maxLevel)
	x := sl.header
	for i := sl.level - 1; i >= 0; i-- {
		for x.forward[i] != nil && x.Score < score {
			x = x.forward[i]
		}

		update[i] = x
	}

	// Score already presents, replace with new value then return
	if x != nil && x.Score == score {
		x.Value = value
		return x
	}

	level := randomLevel()
	if level > sl.level {
		level = sl.level + 1
		update[level] = sl.header
		sl.level = level
	}

	e := newElement(score, value, level)
	for i := 0; i < level; i++ {
		e.forward[i] = update[i].forward[i]
		update[i].forward[i] = e
	}
	sl.len++
	return e
}

// Delete remove and return element with given score, return nil if element not present
func (sl *SkipList) Delete(score float64) *Element {
	update := make([]*Element, maxLevel)
	x := sl.header
	for i := sl.level - 1; i >= 0; i-- {
		for x.forward[i] != nil && x.forward[i].Score < score {
			x = x.forward[i]
		}
		update[i] = x
	}
	x = x.forward[0]

	if x != nil && x.Score == score {
		for i := 0; i < sl.level; i++ {
			if update[i].forward[i] != x {
				return nil
			}
			update[i].forward[i] = x.forward[i]
		}
		sl.len--
	}
	return x
}
