//hash popraviti
// id napraviti
//datoteke

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

    cout <<"Za novi account unesi 1, za login unesi 2: "<<endl;
    cin >> acc_log;
    do
    {
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
                    ispis_wallet(map_wallets);
                    break;
                }
            case 2:
                {
                    do
                    {
                        cout <<"LOGIN"<<endl;
                        login(vrh, map_wallets);
                        cout << "Ako se zeli jos neko ulogirati nek unese 1:\n";
                        cin >> n;
                    }while(n=='1');
                    ispis_wallet(map_wallets);
                    break;
                }
            case 3:
                break;
            default:
                cout <<"debilu unesi 1 ili 2"<<endl;
        }
        cout <<"Za novi account unesi 1, za login unesi 2, za kraj unesi 3: "<<endl;
        cin >> acc_log;
    }while(acc_log==1 || acc_log==2);

    cin.ignore();

    ispis(vrh);


    cout <<"ISPIS TRANSAKCIJA"<<endl;
    for(int i=0; i<vrh->transaction_vec.size(); i++)
    {
        std::cout <<"From " <<vrh->transaction_vec[i].from<<" to "<<vrh->transaction_vec[i].to<<" "<<vrh->transaction_vec[i].operacija<<" "<<vrh->transaction_vec[i].svota<<endl;
    }

    /*
    do
    {
        promjena_bloka(vrh, provjera);
        cout << "Ako ne zelite vise mjenjati podatke unesite 0: " <<endl;
        cin >> n;
    }while(n!=0);

    ispis(vrh);
    */

    return 0;
}

