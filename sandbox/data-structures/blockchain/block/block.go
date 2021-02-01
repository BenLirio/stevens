package block

import (
	"crypto/sha256"
	"bytes"
	"math/rand"
)

type Block struct {
	id [256]byte
	parent [256]byte
	nonce [256]byte
}

func randomBytes(size int) []byte {
	randB := make([]byte, size)
	rand.Read(randB)
	return randB
}

func newBlock() *Block {
	block := &Block{}
	return block
}

func (block *Block) getBytes() []byte {
	buffer := bytes.NewBuffer([]byte{})
	buffer.Write(block.id[:])
	buffer.Write(block.parent[:])
	buffer.Write(block.nonce[:])
	return buffer.Bytes()
}

func (block *Block) GetWork() uint32 {
	var work uint32
	for i, b := range block.Hash() {
		if i > 28 {
			continue
		}
		work += uint32(b) << (28-i)
	}
	return work
}

func (block *Block) Hash() [sha256.Size]byte {
	hash := sha256.New()
	hash.Write(block.getBytes())
	var sum [sha256.Size]byte
	copy(sum[:], hash.Sum(nil)[:sha256.Size])
	return sum
}
