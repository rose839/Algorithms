package bigmap

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestBitMap(t *testing.T) {
	bitmap := New(80)
	assert.Equal(t, len(bitmap), 11)

	bitmap.Set(77)
	assert.Equal(t, bitmap.Get(77), true)

	assert.Equal(t, bitmap.Get(78), false)
	assert.Equal(t, bitmap.Get(100), false)
}
