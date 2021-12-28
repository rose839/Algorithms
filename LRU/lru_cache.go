package lru

const (
	// identify host bit of current system
	HOSTBIT = uint64(^uint(0)) == ^uint64(0)

	// hash bucket length
	LENGTH = 100
)

type lruNode struct {
	prev *lruNode
	next *lruNode

	hnext *lruNode

	key   int
	value int
}

type LRUCache struct {
	node []lruNode // hash list, for quick search

	head *lruNode
	tail *lruNode

	capacity int
	used     int
}

func Constructor(cap int) *LRUCache {
	return &LRUCache{
		node:     make([]lruNode, LENGTH),
		head:     nil,
		tail:     nil,
		capacity: cap,
		used:     0,
	}
}

func (this *LRUCache) Get(key int) int {
	if this.tail == nil {
		return -1
	}

	if tmp := this.searchNode(key); tmp != nil {
		this.moveToTail(tmp)
		return tmp.value
	}
	return -1
}

func (this *LRUCache) Put(key int, value int) {
	if tmp := this.searchNode(key); tmp != nil {
		tmp.value = value
		this.moveToTail(tmp)
		return
	}
	this.addNode(key, value)

	if this.used > this.capacity {
		this.delNode()
	}
}

func (lru *LRUCache) addNode(key int, value int) {
	newNode := &lruNode{
		key:   key,
		value: value,
	}

	tmp := &lru.node[hash(key)]
	newNode.hnext = tmp.hnext
	tmp.hnext = newNode
	lru.used++

	if lru.tail == nil {
		lru.tail, lru.head = newNode, newNode
		return
	}

	lru.tail.next = newNode
	newNode.prev = lru.tail
	lru.tail = newNode
}

func (lru *LRUCache) delNode() {
	if lru.head == nil {
		return
	}
	prev := &lru.node[hash(lru.head.key)]
	tmp := prev.hnext

	for tmp != nil && tmp.key != lru.head.key {
		prev = tmp
		tmp = tmp.hnext
	}
	if tmp == nil {
		return
	}
	prev.hnext = tmp.hnext
	lru.head = lru.head.next
	lru.head.prev = nil
	lru.used--
}

func (lru *LRUCache) searchNode(key int) *lruNode {
	if lru.tail == nil {
		return nil
	}

	tmp := lru.node[hash(key)].hnext
	for tmp != nil {
		if tmp.key == key {
			return tmp
		}
		tmp = tmp.hnext
	}

	return nil
}

func (lru *LRUCache) moveToTail(node *lruNode) {
	if lru.tail == node {
		return
	}

	if lru.head == node {
		lru.head = node.next
		lru.head.prev = nil
	} else {
		node.next.prev = node.prev
		node.prev.next = node.next
	}

	node.next = nil
	lru.tail.next = node
	node.prev = lru.tail

	lru.tail = node
}

func hash(key int) int {
	if HOSTBIT {
		return (key ^ (key >> 32)) & (LENGTH - 1)
	}

	return (key ^ key>>16) & (LENGTH - 1)
}
