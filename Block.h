#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#include <iostream>
#include <vector>
//#include "Transaction.h"

using namespace std;

class Transaction
{
private:
    string from;
    string to;
    int amount;
    string transaction_hash;
public:
    Transaction(string nFrom, string nTo, int nAmount);
    int getAmount(){return amount;}
    string getFrom(){return from;}
    string getTo(){return to;}
    string getHash(){return transaction_hash;}
};

class Block
{
private:
    int index;
    int nonce;
    string _hash;
    vector <Transaction> vector_transaction;
public:
    time_t _time;
    string prev_hash;
    Block(int nIndex);
    void addTransaction(Transaction newTransaction);
    string getHash()
    {
        return _hash;
    }
    int getIndex()
    {
        return index;
    }
    int getNonce()
    {
        return nonce;
    }
    vector<Transaction> getTransaction()
    {
        return vector_transaction;
    }
    void MineBlock(int difficulty);
};


#endif // BLOCK_H_INCLUDED
