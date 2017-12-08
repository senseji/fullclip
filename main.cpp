// id napraviti

#include <iostream>
#include <stack>
#include <string>
#include <stdio.h>
#include <time.h>
#include <unordered_map>
#include <fstream>
#include "block.h"
#include "wallet.h"
#include "login.h"

using namespace std;

std::unordered_map<string,Wallets> map_wallets;
std::stack<block> mystack;

int main()
{
    block *vrh = new block;
    vrh->veza=NULL;
    vrh->next=NULL;
    vrh->r_br=0;

    bool provjera=true;

    new_block(vrh, provjera, mystack);

    char n;
    int acc_log;
    string username;

    do
    {
    cout <<"\n1--Novi account\n2--Login\n3--Azuriranje walleta\n4--Ispis walleta\n5--Ispis mojih transakcija\n6--Ispis bloka\n7--Ispis svih transakcija\n8--EXIT\n"<<endl;
    cin >> acc_log;
        switch(acc_log)
        {
            case 1:
            {
                do
                {
                    cout <<"NOVI ACCOUNT"<<endl;
                    new_account(map_wallets);
                    cout << "Ako zelite unjeti jos accouta unesite 1:\n";
                    cin >> n;
                }while(n=='1');
                break;
            }
            case 2:
            {
                do
                {
                    cout <<"LOGIN"<<endl;
                    username=login();
                    do
                    {
                        fun_transaction(vrh, map_wallets, username);
                        cout << "Ako zelite jos transakcija unesite 1:\n";
                        cin >> n;
                    }while(n=='1');
                    cout << "Ako se zeli jos neko ulogirati nek unese 1:\n";
                    cin >> n;
                }while(n=='1');
                break;
            }
            case 3:
            {
                cout <<"Unesi username walleta koji zelis azurirati: "<<endl;
                username=login();
                for(int i=0; i<vrh->transaction_vec.size(); i++)
                {
                    if(username==vrh->transaction_vec[i].to)
                    {
                        map_wallets[vrh->transaction_vec[i].to].balance+=vrh->transaction_vec[i].svota;
                    }
                    else if(username==vrh->transaction_vec[i].from)
                    {
                        map_wallets[vrh->transaction_vec[i].from].balance-=vrh->transaction_vec[i].svota;
                    }
                }
                break;
            }
            case 4:
            {
                ispis_wallet(map_wallets);
                break;
            }
            case 5:
            {
                username=login();
                for(int i=0; i<vrh->transaction_vec.size(); i++)
                {
                    if(username==vrh->transaction_vec[i].to || username==vrh->transaction_vec[i].from)
                    {
                        vrh->transaction_vec[i].ptm=localtime(&(vrh->transaction_vec[i].timestamp));
                        cout <<"Vrijeme: " << vrh->transaction_vec[i].ptm->tm_hour << ":" << vrh->transaction_vec[i].ptm->tm_min<< ":" << vrh->transaction_vec[i].ptm->tm_sec;
                        cout << "\tDatum: " << (vrh->transaction_vec[i].ptm->tm_year+1900) << "-" << (vrh->transaction_vec[i].ptm->tm_mon+1) << "-" << vrh->transaction_vec[i].ptm->tm_mday<<"\t";
                        std::cout <<"From " <<vrh->transaction_vec[i].from<<" to "<<vrh->transaction_vec[i].to<<" + "<<vrh->transaction_vec[i].svota;
                        cout <<"\tHash transakcije: "<<vrh->transaction_vec[i].hash_transaction<<endl;
                    }
                }
                break;
            }
            case 6:
            {
                ispis(vrh);
                break;
            }
            case 7:
            {
                ispis_transakcija(vrh);
                break;
            }
            default:
                break;
        }
    }while(acc_log==1 || acc_log==2 || acc_log==3 || acc_log==4 || acc_log==5 || acc_log==6 || acc_log==7 );

    return 0;
}

