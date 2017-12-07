#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED

std::unordered_map<string,Wallets> new_account(std::unordered_map<string,Wallets> &map_wallets);
void login(block* &vrh,std::unordered_map<string,Wallets> &map_wallets);

static int brojac_vec=0;

std::unordered_map<string,Wallets> new_account(std::unordered_map<string,Wallets> &map_wallets)
{
    bool pro_user;
    string username, password, provjera_za_username;

    ifstream provjera_username;
    provjera_username.open("account.txt");

    do
    {
        pro_user=true;
        cout <<"Unesite novi username: "<<endl;
        cin >>username;
        provjera_username.clear();
        provjera_username.seekg(0, ios::beg);
        while(!provjera_username.eof() && pro_user==true)
        {
            provjera_username>>provjera_za_username;
            if(provjera_za_username==username)
            {
                cout <<"Username vec postoji!"<<endl;
                pro_user=false;
            }
        }
    }while(pro_user==false);
    provjera_username.close();
    cout << "Unesite novi password: "<<endl;
    cin >> password;

    ofstream account("account.txt",ios::app);

    account << username<<"\t"<<password<<"\n";
    account.close();

    new_wallet(username, map_wallets);

    return map_wallets;
}

void login(block* &vrh, std::unordered_map<string,Wallets> &map_wallets)
{
    string username, password,provjera_za_username,provjera_za_password;
    bool pro_login=false;

    ifstream provjera_logina;
    provjera_logina.open("account.txt");

    do
    {
        cout <<"Unesite svoj username: "<<endl;
        cin >>username;
        cout <<"Unesite svoj password: "<<endl;
        cin >>password;

        provjera_logina.clear();
        provjera_logina.seekg(0, ios::beg);

        while(!provjera_logina.eof() && pro_login==false)
        {
            provjera_logina>>provjera_za_username>>provjera_za_password;
            if(provjera_za_username==username && provjera_za_password==password)
            {
                cout <<"bravo!"<<endl;
                pro_login=true;
            }
            else{pro_login=false;}
        }
        if(pro_login==false){cout <<"Krivi username ili password!!!!"<<endl;}
    }while(pro_login==false);
    provjera_logina.close();

    char n;
    do
    {
        fun_transaction(vrh, map_wallets, username, brojac_vec);
        brojac_vec++;
        cout << "Ako zelite jos transakcija unesite 1:\n";
        cin >> n;
    }while(n=='1');
}

#endif // LOGIN_H_INCLUDED
