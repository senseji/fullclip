#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#include <iostream>
#include <stack>
#include <string>
#include <stdio.h>
#include <time.h>
#include <vector>
#include "hasha.h"
#include "wallet.h"

using namespace std;

class block
{
public:
    //std::string podatak;
    std::vector<Transactions> transaction_vec;
    string hash_podatka;
    string prev_hash_podatka;
    int r_br;
    int nonce=0;
    time_t timestamp;
    struct tm *ptm;
    block *veza;
    block *next;
};

void ispis(block *vrh);
void promjena_bloka(block *vrh, bool provjera);
block* new_block(block* &vrh, bool provjera, std::stack<block> mystack);
void fun_nonce(block *vrh);
void fun_transaction(block* & vrh, std::unordered_map<string,Wallets> &map_wallets, string username, int i);


block* new_block(block* &vrh, bool provjera, std::stack<block> mystack)
{
    block *tmp=new block;
    tmp->next=NULL;
    /*cout << "Unesi podatak \n";
    if(provjera)
    {
        provjera=false;
    }
    else
    {
        cin.ignore();
    }
    std::getline (std::cin,tmp->podatak);*/
    tmp->timestamp=time(0);
    tmp->r_br=vrh->r_br+1;
    tmp->prev_hash_podatka=vrh->hash_podatka;
    //fun_nonce(tmp);
    tmp->hash_podatka='0';
    tmp->veza=vrh;
    vrh->next=tmp;
    mystack.push(*tmp);
    vrh=tmp;

    return vrh;
}

void ispis(block *vrh)
{
    while (vrh->r_br>0)
    {
        vrh->ptm=localtime(&(vrh->timestamp));
        cout <<"\nRedni broj bloka: " << vrh->r_br << endl;
        //cout <<"Podatak bloka: " << vrh->podatak << endl;
        cout <<"Hash bloka: " << vrh->hash_podatka << endl;
        cout <<"Prošli hash: " << vrh->prev_hash_podatka <<endl;
        cout <<"Vrijeme bloka: " << vrh->ptm->tm_hour << ":" << vrh->ptm->tm_min<< ":" << vrh->ptm->tm_sec << endl;
        cout <<"Datum: " << (vrh->ptm->tm_year+1900) << "-" << (vrh->ptm->tm_mon+1) << "-" << vrh->ptm->tm_mday << endl;
        cout <<"Nonce: " << vrh->nonce <<endl;
        //vrh=vrh->veza;
        return ispis(vrh->veza);
    }
}

void promjena_bloka(block *vrh, bool provjera)
{
    int a;
    provjera=true;
    block *tmp1=new block;
    tmp1=vrh;
    cout << "\nUnesite redni broj bloka kojemu zelite promjeniti podatak: " << endl;
    cin >> a;
    while(provjera)
    {
        if(tmp1->r_br==a)
        {
            //tmp1->podatak.erase();
            cin.ignore();
            cout << "Unesite novi podatak: "<<endl;
            //std::getline (std::cin,tmp1->podatak);
            while(provjera)
            {
                block *tmp=new block;
                tmp=tmp1->veza;
                tmp1->prev_hash_podatka=tmp->hash_podatka;
                tmp1->timestamp=time(0);
                fun_nonce(tmp1);
                if(tmp1->r_br!=vrh->r_br)
                {
                    tmp=tmp1;
                    tmp1=tmp1->next;
                }
                else{provjera=false;}
            }
        }
        tmp1=tmp1->veza;
    }
}

void fun_nonce(block *vrh)
{
    block *tmp=new block;
    tmp=vrh;
    tmp->hash_podatka=hashing(/*tmp->podatak+*/tmp->prev_hash_podatka+char(tmp->nonce)+char(tmp->timestamp));
    char n_hash[tmp->hash_podatka.length()+1];
    strncpy(n_hash, tmp->hash_podatka.c_str(),sizeof(n_hash));


    while(n_hash[0]!='0' || n_hash[1]!='0' || n_hash[2]!='0' || n_hash[3]!='0')
    {
        tmp->nonce++;
        tmp->hash_podatka=hashing(/*tmp->podatak+*/tmp->prev_hash_podatka+char(tmp->nonce));
        strncpy(n_hash, tmp->hash_podatka.c_str(),sizeof(n_hash));
    }
}

void fun_transaction(block* &vrh, std::unordered_map<string,Wallets> &map_wallets,string username, int i)
{
    Transactions transaction;
    string hash_vec_podatka;

    transaction.from=username;

    cout <<"S kim zelite razmjeniti novac, koliko i kako(+ ili -): "<<endl;
    cin >> transaction.to >> transaction.svota>>transaction.operacija;

    vrh->transaction_vec.emplace(vrh->transaction_vec.end(),transaction);

    std::stringstream ss;
    for(size_t i = 0; i < vrh->transaction_vec.size(); ++i)
    {
        if(i != 0)
            ss << ",";
        ss << vrh->transaction_vec[i].svota;
    }
    std::string s = ss.str();

    hash_vec_podatka=hashing(vrh->transaction_vec[i].from+vrh->transaction_vec[i].operacija+vrh->transaction_vec[i].to+s);
    vrh->hash_podatka=hashing(hash_vec_podatka+vrh->hash_podatka+vrh->prev_hash_podatka+char(vrh->nonce)+char(vrh->timestamp));

    izmjena_wallet(map_wallets,transaction.from, transaction.to, transaction.svota, transaction.operacija);

    ispis_wallet(map_wallets);
}
#endif // BLOCK_H_INCLUDED
