package heap

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestHeap_insert(t *testing.T) {
	h := NewHeap(80)

	h.insert(10)
	h.insert(20)
	h.insert(15)

	assert.Equal(t, h.h[1], 20)
}

func TestHeap_removeMax(t *testing.T) {
	h := NewHeap(80)

	h.insert(10)
	h.insert(20)
	h.insert(15)

	h.removeMax()
	assert.Equal(t, h.h[1], 15)
}
