package block

func (block *Block) GenerateNextBlock() *Block {
	nextBlock := &Block{}
	copy(nextBlock.id[:], randomBytes(256))
	copy(nextBlock.parent[:], block.id[:])
	return block
}

func (block *Block) RandomizeNonce() {
	copy(block.nonce[:], randomBytes(256))
}
