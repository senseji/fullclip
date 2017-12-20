#ifndef TRANSACTION_H_INCLUDED
#define TRANSACTION_H_INCLUDED

#include <iostream>

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

#endif // TRANSACTION_H_INCLUDED
