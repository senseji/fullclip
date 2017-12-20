#include "Blockchain.h"
#include <stack>

Blockchain::Blockchain()
{
    chain.emplace_back(Block(0));
    difficulty=2;
}

void Blockchain::addBlock(Block newBlock)
{
    newBlock.prev_hash=chain.back().getHash();
    chain.push_back(newBlock);
}

