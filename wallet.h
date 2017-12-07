#ifndef WALLET_H_INCLUDED
#define WALLET_H_INCLUDED

#include "block.h"

class Wallets
{
public:
    int id;
    double balance;
};

class Transactions
{
public:
        string from;
        string to;
        double svota;
        time_t timestamp;
        struct tm *ptm;
};

std::unordered_map<string,Wallets> new_wallet(string username,std::unordered_map<string,Wallets> &map_wallets);
std::unordered_map<string,Wallets> izmjena_wallet(std::unordered_map<string,Wallets> &map_wallets);
void ispis_wallet(std::unordered_map<string,Wallets> map_wallets);

std::unordered_map<string,Wallets> new_wallet(string username,std::unordered_map<string,Wallets> &map_wallets)
{
    double novac;

    Wallets *wallet=new Wallets;

    //wallet->id=i;
    cout <<"Unesite bitcoine: "<<endl;
    cin>>wallet->balance;
    cout << endl;
    map_wallets[username]=*wallet;

    return map_wallets;
}

std::unordered_map<string,Wallets> izmjena_wallet(std::unordered_map<string,Wallets> &map_wallets, string ime, string ime_a, double novac )
{
    map_wallets[ime_a].balance+=novac;
    map_wallets[ime].balance-=novac;

    return map_wallets;
}

void ispis_wallet(std::unordered_map<string,Wallets> map_wallets)
{
    for (auto& x: map_wallets)
    {
        std::cout << x.first<<":" << endl <<"\tbalance: " << x.second.balance <<endl<< "\tID: " << x.second.id << std::endl;
    }
}

#endif // WALLET_H_INCLUDED
