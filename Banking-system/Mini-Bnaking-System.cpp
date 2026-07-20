#include <iostream>
using namespace std;
long long account_number, deposit = 0, withdrawal = 0, balance, pin, mobile_number;
int age;
char name[20];
bool account_Created = false;
void main_menu(){
    cout << "\n" << "    ====================\n" << "        MAIN MENU   \n " << "   ====================\n";
    cout << endl << "1. Create Account\n" << "2. Login\n" << "3. Exit\n";
}
void account(){
    if (account_Created)
        {
            cout << "\nAccount already exists.\n";
            cout << "Please login.\n";
            return;
        }
    else{
        cout << endl << "Enter your name : ";
        cin >> name;
        cout << "Enter your age : ";
        cin >> age;
        cout << "Enter your account number : ";
        cin >> account_number;
        cout << "Enter your initial deposit : ";
        cin >> balance;
        cout << "Enter your PIN code : ";
        cin >> pin;
        cout << "Enter your Mobile Number : ";
        cin >> mobile_number;
        long long temp = mobile_number;
        while (temp >= 10){
            temp = temp / 10;
        } 
        if (balance <= 0){
            cout << endl << "Enter valid balance\n";
            cout << endl << "   Account NOT created \n" << "============================= \n";
            account_Created = false;
        }
        else if(pin<1000 || pin>10000){
            cout << endl << "Enter valid PIN\n";
            cout << endl << "   Account NOT created \n" << "============================= \n";
            account_Created = false;        
        }
        else if(mobile_number<1000000000 || mobile_number>10000000000){
            cout << endl << "Enter valid Mobile Number\n";
            cout << endl << "   Account NOT created \n" << "============================= \n";
            account_Created = false;        
        }
        else if(temp<=5){
            cout << endl << "Enter valid Mobile Number\n";
            cout << endl << "   Account NOT created \n" << "============================= \n";
            account_Created = false;
        }
        else{
            cout << endl << "Account created successfully \n" << "============================= \n";
            account_Created = true;
        }
    }
}

void banking_menu(){
    cout << endl << "============================== \n" << "         Banking menu \n" << "============================== \n";
    cout << endl << "1. Deposit Money\n";
    cout << "2. Withdraw Money\n";
    cout << "3. Check Balance\n";
    cout << "4. Account Details\n";
    cout << "5. Change PIN\n";
    cout << "6. Interest Calculator\n";
    cout << "7. Loan Eligibility Checker\n";
    cout << "8. Logout\n";
}

void deposits(){
    cout << endl << "enter amount to be deposited : ";
    cin >> deposit;
    if(deposit<=0){
        cout << endl << "invalid amount. \n" << "==================================== \n";
    }
    else{
        balance = balance + deposit;
        cout << endl << deposit << " : deposited successfully \n" << "current balance : " << balance << endl << "===========================" << endl;
     }
}

void withdraw(){
    cout << endl <<"enter amount of withdrawal : ";
    cin >> withdrawal;
    if(withdrawal < 0){
        cout << endl << "invalid amount. \n" << "==================================== \n";
    }
    else if( balance < withdrawal){
        cout << endl << "not enough balance \n" << "============================= \n";
    }
    else{
        balance = balance - withdrawal;
        cout << endl << "withdrawal was successful \n" << "remaining balance : " << balance << endl << "=========================== \n";  
    } 
}

void change_PIN(){
    int old_pin, new_pin;
    cout << "Enter PIN : ";
    cin >> old_pin;
    if (old_pin == pin){
        cout << "Enter new PIN : ";
        cin >> new_pin;
        if(new_pin<1000 || new_pin>10000){
            cout << endl << "Enter valid PIN\n";
            cout << endl << " PIN not updated\n";                   
        }
        else{
            pin = new_pin;
            cout << endl << "PIN successfully changed : " << pin << endl;
        }
    }
    else{
        cout << "Invalid PIN";
    }
}

void interest_calculator(){
    float rate = 6.0f;
    int year ;
    cout << "Enter time period (in years) : ";
    cin >> year;
    cout << endl << "Your balance is : " << balance << endl;
    cout << "Rate of Interest of Bank is 6%\n";
    cout << endl << "Total Interest : " << (balance*rate*year)/100 << endl;
    cout << "Total Amount : " << balance+(balance*rate*year)/100 << endl;
}

void loan(){
    int salary, loan;
    cout << "Enter amount of loan : ";
    cin >> loan;
    cout << "Enter your Monthly Salary : ";
    cin >> salary;
    if (age<18){
        cout << endl << "Loan Rejected\n" << "Reason : Applicant must be at least 18 years old.\n";
    }
    else if(salary<25000){
        cout << endl << "Loan Rejected\n" << "Reason : Salary too low.\n";
    }
    else if(balance<10000){
        cout << endl << "Loan Rejected\n" << "Reason : Minimum balance not maintained.\n"; 
    }
    else if(loan>salary*12){
        cout << endl << "Loan Rejected\n" << "Reason : Requested amount exceeds eligibility.\n";
    }
    else{
        cout << endl << "Loan Approved\n" << "Maximum Eligible Loan : " << salary*12 << endl; 
    }
}

int main(){
    long long entered_account_no, entered_pin;
    int c, choice;
    cout << "      ===================================== \n" << "                     MINI BANK \n" << "      ===================================== \n";
    cout << endl << " Thank You for coming to our bank \n";
    
    while(true){
        main_menu();
        cout << endl << "Enter choice : ";
        cin >> choice;
        if (choice == 1){
            account();
        }
        else if (choice == 2){

            if(account_Created == false){
                cout << endl << "  Create an account first\n" << "============================= \n";
                break;
            }
            cout << "Enter Account Number : ";
            cin >> entered_account_no;
            if(entered_account_no != account_number){                    cout << endl << "Account number does not exist \n" << "============================= \n";
                break;
            }
            else{
                while(true){
                    cout << "Enter PIN : ";
                    cin >> entered_pin;
                    if (entered_pin == pin){
                        cout << endl << "==============================\n" << "       WELCOME " << name << endl << "==============================\n"; 
                        while(true){
                            banking_menu();
                            cout << endl << "enter your choice : ";
                            cin >> c;
                            if(c==1){
                                deposits();
                            }
                            else if(c==2){
                                withdraw(); 
                            }
                            else if(c==3){
                                cout << endl << "Your balance is " << balance << endl << "================================= \n";
                            }
                            else if(c==4){
                                cout << endl << "account holder : " << name << "\n" << "age : " << age << endl << "account number : " << account_number << endl << "current balance : " << balance << endl << "=============================== \n";
                            }
                            else if(c==5){
                                change_PIN();
                            }  
                            else if(c==6){
                                interest_calculator();
                            }  
                            else if(c==7){
                                loan();
                            }        
                            else if(c==8){
                                cout << endl << "         Thank you \n" << "================================ \n";
                                break;
                            }
                            else{
                                cout << endl << "invalid choice.\n" << "Please try again" << endl;
                            }
                            }
                            break;
                        }
                    else {
                        cout << endl << "     Invalid PIN\n" << "============================= \n";
                        break;
                    }
                }
            }       
        }
        
        else if (choice == 3){
            cout << "You are now exiting\n";
            break;
        }
    }    
    return 0;
} 