#include <iostream>
using namespace std;
int main(){
    char name[20];
    long long account_number, initial_deposit, deposit = 0, withdrawal = 0, balance;
    int age, c;
    cout << "=========================== \n" << "         MINI BANK \n" << "=========================== \n";
    cout << endl << "enter your name : ";
    cin >> name;
    cout << "enter your age : ";
    cin >> age;
    cout << "enter your account number : ";
    cin >> account_number;
    cout << "enter your initial deposit : ";
    cin >> initial_deposit;
    balance = initial_deposit;
    cout << endl << "Account created successfully \n" << "============================= \n";
    cout << endl << "Operations \n" << "============================== \n" << "enter 1 to deposit a sum of money \n" << "enter 2 to withdraw money \n" << "enter 3 to check balance \n" << "enter 4 to check bank details \n" << "enter 5 to exit \n";

    for(int i=1; i>0; i++){
        cout << endl << "enter your choice : ";
        cin >> c;
        if(c==1){
            cout << endl << "enter amount to be deposited : ";
            cin >> deposit;
            if(deposit<0){
                cout << endl << "invalid amount. \n" << "==================================== \n";
            }
            else{
                balance = balance + deposit;
            cout << endl << deposit << "deposited successfully \n" << "current balance : " << balance << endl << "===========================" << endl;
            }
        }
        else if(c==2){
            cout << endl <<"enter amount of withrawal : ";
            cin >> withdrawal;
            if(withdrawal<0){
                cout << endl << "invalid amount. \n" << "==================================== \n";
            }
            else if(balance<withdrawal){
                cout << endl << "not enough balance \n" << "============================= \n";
            }
            else{
                balance = balance - withdrawal;
                cout << endl << "withdrawal was successful \n" << "remainig balance : " << balance << endl << "=========================== \n";  
            } 
        }
        else if(c==3){
            cout << endl << "Your balance is " << balance << endl << "================================= \n";
        }
        else if(c==4){
            cout << endl << "account holder : " << name << "\n" << "age : " << age << endl << "account number : " << account_number << endl << "current balance : " << balance << endl << "=============================== \n";
        }
        else if(c==5){
            cout << endl << "         Thank you \n" << "================================ \n";
            break;
        }
        else{
            cout << endl << "invalid choice.\n" << "Please try again" << endl;
        }
    }
    return 0;
}