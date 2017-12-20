#ifndef BLOCKCHAIN_H_INCLUDED
#define BLOCKCHAIN_H_INCLUDED

#include "Block.h"
#include <vector>

class Blockchain
{
private:
    int difficulty;

public:
    Blockchain();
    void addBlock(Block newBlock);
    vector<Block> chain;
    int getDifficulty()
    {
        return difficulty;
    }
};

#endif // BLOCKCHAIN_H_INCLUDED
