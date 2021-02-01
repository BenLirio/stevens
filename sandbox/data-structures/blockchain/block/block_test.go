package block

import (
	"testing"
	"math/rand"
)

const Size = 32

func TestBlockHash(t *testing.T) {
	block0 := newBlock()
	block0.id[0] = 0
	if len(block0.Hash()) != Size {
		t.Errorf("Block hash should be %d bytes\n", Size)
	}
	if block0.Hash() != block0.Hash() {
		t.Errorf("Block hash should be unique\n")
	}

	block1 := newBlock()
	block1.id[0] = 1
	if block1.Hash() == block0.Hash() {
		t.Errorf("Block 1 and 0 should have different hashes\n")
	}

	block0copy := newBlock()
	block0copy.id[0] = 0
	if block0copy.Hash() != block0.Hash() {
		t.Errorf("Blocks with the same ID should have the same hash\n")
	}
	var nonce [256]byte
	nonce[0] = 1
	block0copy.nonce = nonce
	if block0copy.Hash() == block0.Hash() {
		t.Errorf("Block nonce should change the hash\n")
	}

}
func TestWork(t *testing.T) {
	t.Skip()
	var maxWork uint32 = 0
	block := newBlock()
	for {
		r := make([]byte, 256)
		rand.Read(r)
		copy(block.nonce[:], r[:256])
		work := block.GetWork()
		if work > maxWork {
			maxWork = work
		}
	}
}
func TestGenBlock(t *testing.T) {
	block := newBlock()
	nextBlock := block.GenerateNextBlock()
	if block.id != nextBlock.parent {
		t.Error("Next Block should have the same parent id as the block that generated it")
	}
}
func TestRandomNonce(t *testing.T) {
	block := newBlock()
	block.RandomizeNonce()
	nonceBefore := block.nonce
	block.RandomizeNonce()
	nonceAfter := block.nonce
	if nonceBefore == nonceAfter {
		t.Error("Randomize nonce should change the block nonce\n")
	}
}
