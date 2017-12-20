//time nije privatan
//transakcije u poseban cpp i header
#include <iostream>
#include <time.h>
#include "blockchain.h"

using namespace std;

struct tm *ptm;

int main()
{
    char odg='1';
    string from, to;
    int amount,counter=0, n=0;

    Blockchain FullCoin=Blockchain();

    while(odg=='1')
    {
        cout <<"unesit od koga, kome i koliko: "<<endl;
        cin >> from >> to >> amount;
        FullCoin.chain[n].addTransaction(Transaction(from,to,amount));

        counter++;
        if(counter==2)
        {
            FullCoin.chain[n].MineBlock(FullCoin.getDifficulty());
            cout <<"Mining..."<<endl;
            FullCoin.addBlock(Block(n));
            n++;
            counter=0;
        }

        cout <<"Ako zelis jos unesi 1: " <<endl;
        cin >> odg;
    }

    for(int j=0; j<n+1; j++)
    {
        tm *ptm=localtime(&(FullCoin.chain[j]._time));
        cout<<endl<<"Block " << j<<":"<<endl;
        cout <<"TRANSAKCIJE:"<<endl;
        for(int i=0; i<FullCoin.chain[j].getTransaction().size();i++)
            {
            cout <<"\t"<<FullCoin.chain[j].getTransaction()[i].getFrom();
            cout <<"\t"<<FullCoin.chain[j].getTransaction()[i].getTo();
            cout <<"\t"<<FullCoin.chain[j].getTransaction()[i].getAmount()<<endl;
            }
        cout <<"BLOCK:"<<endl;
        cout <<"\tHahh: "<<FullCoin.chain[j].getHash()<<endl;
        cout <<"\tRedni broj bloka: " << FullCoin.chain[j].getIndex() << endl;
        cout <<"\tProšli hash: " << FullCoin.chain[j].prev_hash <<endl;
        cout <<"\tNonce: " << FullCoin.chain[j].getNonce() <<endl;
        cout <<"\tVrijeme bloka: " << ptm->tm_hour << ":" << ptm->tm_min<< ":" << ptm->tm_sec << endl;
        cout <<"\tDatum: " << (ptm->tm_year+1900) << "-" << (ptm->tm_mon+1) << "-" << ptm->tm_mday << endl;
    }

    return 0;
}
