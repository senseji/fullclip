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

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

void ispis(block *vrh);
void promjena_bloka(block *vrh, bool provjera);
block* new_block(block* &vrh, bool provjera, std::stack<block> mystack);
void fun_nonce(block *vrh);
void fun_transaction(block* & vrh, std::unordered_map<string,Wallets> &map_wallets, string username, int i);
void ispis_transakcija(block *vrh);

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
        cout <<"Hash bloka: " << vrh->hash_podatka << endl;
        cout <<"Prošli hash: " << vrh->prev_hash_podatka <<endl;
        cout <<"Vrijeme bloka: " << vrh->ptm->tm_hour << ":" << vrh->ptm->tm_min<< ":" << vrh->ptm->tm_sec << endl;
        cout <<"Datum: " << (vrh->ptm->tm_year+1900) << "-" << (vrh->ptm->tm_mon+1) << "-" << vrh->ptm->tm_mday << endl;
        cout <<"Nonce: " << vrh->nonce <<endl;

        return ispis(vrh->veza);
    }
}
/*
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
}*/
/*
void fun_nonce(block *vrh)
{
    block *tmp=new block;
    tmp=vrh;
    tmp->hash_podatka=hashing(tmp->prev_hash_podatka+char(tmp->nonce)+char(tmp->timestamp));
    char n_hash[tmp->hash_podatka.length()+1];
    strncpy(n_hash, tmp->hash_podatka.c_str(),sizeof(n_hash));


    while(n_hash[0]!='0' || n_hash[1]!='0' || n_hash[2]!='0' || n_hash[3]!='0')
    {
        tmp->nonce++;
        tmp->hash_podatka=hashing(tmp->prev_hash_podatka+char(tmp->nonce));
        strncpy(n_hash, tmp->hash_podatka.c_str(),sizeof(n_hash));
    }
}*/

void fun_transaction(block* &vrh, std::unordered_map<string,Wallets> &map_wallets,string username)
{
    Transactions transaction;

    bool pro_login=false;
    string provjera_za_username;

    transaction.from=username;

    cout <<"S kim zelite razmjeniti novac "<<endl;

    ifstream provjera_logina;
    provjera_logina.open("account.txt");

    do
    {
        cin >> transaction.to;
        provjera_logina.clear();
        provjera_logina.seekg(0, ios::beg);

        while(!provjera_logina.eof() && pro_login==false)
        {
            provjera_logina>>provjera_za_username;
            if(provjera_za_username==transaction.to)
            {
                pro_login=true;
            }
            else{pro_login=false;}
        }
        if(pro_login==false){cout <<"Ne postoji taj username. Unesi ponovno!!!!"<<endl;}
    }while(pro_login==false);
    provjera_logina.close();

    cout << "Koliko: "<<endl;
    cin >> transaction.svota;
    transaction.timestamp=time(0);

    transaction.hash_transaction=hashing(transaction.from+transaction.to+patch::to_string(transaction.svota)+patch::to_string(transaction.timestamp));

    vrh->transaction_vec.emplace(vrh->transaction_vec.end(),transaction);

    vrh->timestamp=time(0);

    vrh->hash_podatka=hashing(vrh->hash_podatka+transaction.hash_transaction+vrh->prev_hash_podatka+patch::to_string(vrh->nonce)+patch::to_string(vrh->timestamp));

    //izmjena_wallet(map_wallets,transaction.from, transaction.to, transaction.svota);

    //ispis_wallet(map_wallets);
}

void ispis_transakcija(block* vrh)
{
    cout <<"\nISPIS TRANSAKCIJA"<<endl;
    for(int i=0; i<vrh->transaction_vec.size(); i++)
    {
        vrh->transaction_vec[i].ptm=localtime(&(vrh->transaction_vec[i].timestamp));
        cout <<"Vrijeme: " << vrh->transaction_vec[i].ptm->tm_hour << ":" << vrh->transaction_vec[i].ptm->tm_min<< ":" << vrh->transaction_vec[i].ptm->tm_sec;
        cout << "\tDatum: " << (vrh->transaction_vec[i].ptm->tm_year+1900) << "-" << (vrh->transaction_vec[i].ptm->tm_mon+1) << "-" << vrh->transaction_vec[i].ptm->tm_mday<<"\t";
        std::cout <<"From " <<vrh->transaction_vec[i].from<<" to "<<vrh->transaction_vec[i].to<<" + "<<vrh->transaction_vec[i].svota;
        cout <<"\tHash transakcije: "<<vrh->transaction_vec[i].hash_transaction<<endl;
    }
}
#endif // BLOCK_H_INCLUDED
