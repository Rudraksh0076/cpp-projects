#include<iostream>
#include<string> 
#include<fstream>
#include<math.h>
#include<vector>
#include <chrono>
#include <ctime>
using namespace std;
class Transaction{
private:
    string type;
    long long amount;
    string date;
    string time;
    
public:
    Transaction(string type, long long amount, string date, string time){
        this->type=type;
        this->amount=amount;
        this->date=date;
        this->time=time;
    }
    Transaction() {}

    string getType(){
        return type;
    }
    long long getAmount(){
        return amount;
    }
    Transaction(string type, long long amount) {

        this->type = type;
        this->amount = amount;

        auto now = chrono::system_clock::now();

        time_t currentTime =
            chrono::system_clock::to_time_t(now);

        tm* localTime = localtime(&currentTime);

        date = to_string(localTime->tm_mday) + "/" +
               to_string(localTime->tm_mon + 1) + "/" +
               to_string(localTime->tm_year + 1900);

        time = to_string(localTime->tm_hour) + ":" +
               to_string(localTime->tm_min) + ":" +
               to_string(localTime->tm_sec);
    }
    string getDate(){
    return date;
    }

    string getTime(){
        return time;
    }
    void save(ofstream& file) const {

        size_t length;

        // Type
        length = type.size();
        file.write((char*)&length, sizeof(length));
        file.write(type.c_str(), length);

        // Amount
        file.write((char*)&amount, sizeof(amount));

        // Date
        length = date.size();
        file.write((char*)&length, sizeof(length));
        file.write(date.c_str(), length);

        // Time
        length = time.size();
        file.write((char*)&length, sizeof(length));
        file.write(time.c_str(), length);
    }
    void load(ifstream& file) {

        size_t length;

        // Type
        file.read((char*)&length, sizeof(length));
        type.resize(length);
        file.read(&type[0], length);

        // Amount
        file.read((char*)&amount, sizeof(amount));

        // Date
        file.read((char*)&length, sizeof(length));
        date.resize(length);
        file.read(&date[0], length);

        // Time
        file.read((char*)&length, sizeof(length));
        time.resize(length);
        file.read(&time[0], length);
    }
};
class Loan{
private:
    long long principal;
    float rate;
    int month;
    long long salary;
    long long EMI;
    long long amount;
    long long paid;
    bool active;

public:
    Loan() {};
    Loan(long long principal, int month, int salary){
        this->principal = principal;
        this->rate = 13.1;
        this->month = month;
        this->salary = salary;

        EMI = (principal * (rate / 12.0 / 100.0) *
               pow(1 + (rate / 12.0 / 100.0), month)) /
              (pow(1 + (rate / 12.0 / 100.0), month) - 1);

        amount = EMI * month;
        paid = 0;
        active = true;
    }
    void save(ofstream& file) const {

        file.write((char*)&principal, sizeof(principal));
        file.write((char*)&rate, sizeof(rate));
        file.write((char*)&month, sizeof(month));
        file.write((char*)&salary, sizeof(salary));
        file.write((char*)&EMI, sizeof(EMI));
        file.write((char*)&amount, sizeof(amount));
        file.write((char*)&paid, sizeof(paid));
        file.write((char*)&active, sizeof(active));
    }
    void load(ifstream& file) {
        file.read((char*)&principal, sizeof(principal));
        file.read((char*)&rate, sizeof(rate));
        file.read((char*)&month, sizeof(month));
        file.read((char*)&salary, sizeof(salary));
        file.read((char*)&EMI, sizeof(EMI));
        file.read((char*)&amount, sizeof(amount));
        file.read((char*)&paid, sizeof(paid));
        file.read((char*)&active, sizeof(active));
    }
    long long getPrincipal(){
        return principal;
    }

    int getMonth(){
        return month;
    }

    float getRate(){
        return rate;
    }

    long long getEMI(){
        return EMI;
    }

    long long getsalary(){
        return salary;
    }

    bool isActive(){
        return active;
    }

    void repayment(long long p){
        paid += p;

        if(paid >= amount){
            paid = amount;
            active = false;
        }
    }

    long long getRemaining(){
        return amount - paid;
    }
    void getinfo(){
        cout << "Principal : " << principal << endl << "Interest Rate" << rate << endl << "Duration :" << month << endl << "Total Amount : " << amount << endl << "Paid : " << paid << endl << "Remaining : " << getRemaining() << endl << "Status" << active << endl ;
    }
};
class Account{
private:
    long long balance;
    int pin;
    long long account_number;
    int age;
    string name;
    string mobile_number;
    vector<Transaction> transaction_safe;
    vector<Loan> loans;
    string Account_type;
    double interestRate;
    time_t lastInterestTime;
    bool locked_status=false;
    int failedAttempts=0;
public:
    Account() {}
    void setinterestrate(){
        if(Account_type=="saving"){
            interestRate=5;
        }
        else{
            interestRate=0;
        }
        
    }
    Account(long long account_number, long long balance, int age,int pin ,string name, string mobile_number, string type){
        this->account_number=account_number;
        this->balance=balance;
        this->age=age;
        this->pin=pin;
        this->name=name;
        this->mobile_number=mobile_number;
        locked_status=false;
        Account_type= type;
        auto now = chrono::system_clock::now();

        lastInterestTime =
            chrono::system_clock::to_time_t(now);
        setinterestrate();
    }
    void save(ofstream& file) const {
        file.write((char*)&account_number, sizeof(account_number));
        file.write((char*)&balance, sizeof(balance));
        file.write((char*)&pin, sizeof(pin));
        file.write((char*)&age, sizeof(age));

        size_t length = name.size();
        file.write((char*)&length, sizeof(length));
        file.write(name.c_str(), length);

        length = mobile_number.size();
        file.write((char*)&length, sizeof(length));
        file.write(mobile_number.c_str(), length);

        length = Account_type.size();
        file.write((char*)&length, sizeof(length));
        file.write(Account_type.c_str(), length);

        file.write((char*)&interestRate, sizeof(interestRate));
        file.write((char*)&lastInterestTime, sizeof(lastInterestTime));
        file.write((char*)&locked_status, sizeof(locked_status));
        file.write((char*)&failedAttempts, sizeof(failedAttempts));

        size_t transactionCount = transaction_safe.size();
        file.write((char*)&transactionCount, sizeof(transactionCount));

        for(const auto& transaction : transaction_safe){
            transaction.save(file);
        }

        size_t loanCount = loans.size();
        file.write((char*)&loanCount, sizeof(loanCount));

        for(const auto& loan : loans){
            loan.save(file);
        }
    }

    void load(ifstream& file) {
        file.read((char*)&account_number, sizeof(account_number));
        file.read((char*)&balance, sizeof(balance));
        file.read((char*)&pin, sizeof(pin));
        file.read((char*)&age, sizeof(age));

        size_t length;

        file.read((char*)&length, sizeof(length));
        name.resize(length);
        file.read(&name[0], length);

        file.read((char*)&length, sizeof(length));
        mobile_number.resize(length);
        file.read(&mobile_number[0], length);

        file.read((char*)&length, sizeof(length));
        Account_type.resize(length);
        file.read(&Account_type[0], length);

        file.read((char*)&interestRate, sizeof(interestRate));
        file.read((char*)&lastInterestTime, sizeof(lastInterestTime));
        file.read((char*)&locked_status, sizeof(locked_status));
        file.read((char*)&failedAttempts, sizeof(failedAttempts));

        size_t transactionCount;
        file.read((char*)&transactionCount, sizeof(transactionCount));

        transaction_safe.clear();

        for(size_t i = 0; i < transactionCount; i++){
            Transaction transaction;
            transaction.load(file);
            transaction_safe.push_back(transaction);
        }

        size_t loanCount;
        file.read((char*)&loanCount, sizeof(loanCount));

        loans.clear();

        for(size_t i = 0; i < loanCount; i++){
            Loan loan;
            loan.load(file);
            loans.push_back(loan);
        }
    }
    long long getBalance(){
        return balance;
    }
    long long getAccount_no(){
        return account_number;
    }
    int getAge(){
        return age;
    }
    string getName(){
        return name;
    }
    string getMobile_number(){
        return mobile_number;
    }
    void transaction_secure(string t, long long a){
        Transaction n(t,a);
        transaction_safe.push_back(n);
    }
    bool hasActiveLoan(){
        for(int i = 0; i < loans.size(); i++){
            if(loans[i].isActive()){
                return true;
            }
        }
        return false;
    }
    bool security(int enteredPin){

        if(locked_status){
            cout << "Account is permanently locked.\n";
            return false;
        }

        if(enteredPin == pin){

            failedAttempts = 0;

            return true;
        }

        failedAttempts++;

        cout << "Incorrect PIN.\n";
        cout << "Attempts used: "
            << failedAttempts << "/3\n";

        if(failedAttempts >= 3){

            locked_status = true;

            cout << "Account permanently locked.\n";
        }

        return false;
    }   
    void loan_apply(long long p,int m, long long salary){
        if(hasActiveLoan()){
            cout << "You already have an active loan.\n";
            return;
        }
        Loan l( p ,m,salary);
        if (age<18){
            cout << endl << "Loan Rejected\n" << "Reason : Applicant must be at least 18 years old.\n";
        }
        else if(salary<25000){
               cout << endl << "Loan Rejected\n" << "Reason : Salary too low.\n";
           }
           
        else if(balance<10000){
            cout << endl << "Loan Rejected\n" << "Reason : Minimum balance not maintained.\n"; 
        }
       else if(p>salary*12){
            cout << endl << "Loan Rejected\n" << "Reason : Requested amount exceeds eligibility.\n";
        }
        else{
            loans.push_back(l);
            cout << endl << "Loan Approved\n" << "Maximum Eligible Loan : " << salary*12 << endl; 
            balance+=p;
            transaction_secure("Loan", p);
        }
        
    }
    void loan_repayment(long long p){

        if(!hasActiveLoan()){
            cout << "No active loan found.\n";
            return;
        }

        if(p <= 0){
            cout << "Invalid repayment amount.\n";
            return;
        }

        // Find the actual active Loan object
        Loan* activeLoan = nullptr;

        for(int i = 0; i < loans.size(); i++){
            if(loans[i].isActive()){
                activeLoan = &loans[i];
                break;
            }
        }

        if(p > balance){
            cout << "Insufficient balance.\n";
            return;
        }

        if(p > activeLoan->getRemaining()){
            cout << "Repayment exceeds remaining loan amount.\n";
            return;
        }

        // Deduct repayment from account
        balance -= p;

        // Update actual Loan object
        activeLoan->repayment(p);

        // Record transaction
        transaction_secure("Loan Repayment", p);

        cout << endl;
        cout << "Loan repayment successful.\n";
        cout << "Amount Paid : " << p << endl;
        cout << "Remaining Loan : "
            << activeLoan->getRemaining() << endl;

        if(!activeLoan->isActive()){
            cout << "Loan fully repaid.\n";
        }

        cout << "Current Balance : "
            << balance << endl;
    }
    void loan_details(){
        if(!hasActiveLoan()){
            cout << "No active loan found.\n";
            return;
        }
        Loan* activeLoan = nullptr;
        for(int i = 0; i < loans.size(); i++){
            if(loans[i].isActive()){
                activeLoan = &loans[i];
                break;
            }
        }
        activeLoan->getinfo();
    }
    void transaction_details(){

        if(transaction_safe.empty()){
            cout << "No transactions found.\n";
            return;
        }

        cout << "\n========== TRANSACTION HISTORY ==========\n";

        for(int i = 0; i < transaction_safe.size(); i++){

            cout << "Transaction " << i + 1 << endl;
            cout << "Type   : " << transaction_safe[i].getType() << endl;
            cout << "Amount : " << transaction_safe[i].getAmount() << endl;
            cout << "Date : " << transaction_safe[i].getDate() << endl;
            cout << "Time : " << transaction_safe[i].getTime() << endl;
            cout << "-----------------------------------------\n";
        }
    }
    void applyInterest(){
        int interest=0;
        auto now = chrono::system_clock::now();

        time_t currentTime =
            chrono::system_clock::to_time_t(now);
        
            auto elapsed = currentTime - lastInterestTime;
            
        if(Account_type=="saving"){
            if (elapsed >= chrono::duration_cast<chrono::seconds>(
                    chrono::hours(24 * 365)).count()) {
                interest=balance*interestRate*1/100;
                balance+=interest;
                lastInterestTime = currentTime;
                transaction_secure("interest",interest);
            }
        }
    }
    void deposits(long long deposit){
        if(deposit<=0){
            cout << endl << "invalid amount. \n" << "==================================== \n";
        }
        else{
            balance = balance + deposit;
            cout << endl << deposit << " : deposited successfully \n" << "current balance : " << balance << endl << "===========================" << endl;
            transaction_secure("deposit", deposit);
        }
    }
    
    void withdraw(long long withdrawal){
        if(withdrawal <= 0){
            cout << endl << "invalid amount. \n" << "==================================== \n";
        }
        else if( balance < withdrawal){
            cout << endl << "not enough balance \n" << "============================= \n";
        }
        else{
            balance = balance - withdrawal;
            cout << endl << "withdrawal was successful \n" << "remaining balance : " << balance << endl << "=========================== \n";
            transaction_secure("withdrawal", withdrawal);  
        } 
    }
    void change_PIN(){
        int old_pin,new_pin;
       
        cout << "Enter PIN : ";
        cin >> old_pin;

        if(cin.fail()){
            cout << "Invalid PIN input.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            return;
        }

        if(cin.fail()){
            cout << "Invalid PIN input.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            return;
        }
        if (old_pin == pin){
            cout << "Enter new PIN : ";
            cin >> new_pin;

            if(cin.fail()){
                cout << "Invalid PIN input.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                return;
            }
            if(new_pin<1000 || new_pin>9999){
                cout << endl << "Enter valid PIN\n";
                cout << endl << " PIN not updated\n";                   
            }
            else{
                pin = new_pin;
                cout << endl << "PIN successfully changed " ;
            }
        }
        else{
            cout << "Invalid PIN";
        }
    }
    void account_details(){
         cout << endl << "account holder : " << name << "\n" << "age : " << age << endl << "account number : " << account_number << endl << "current balance : " << balance << endl << "=============================== \n";
                            
    }
};
class Bank{
private:
    vector<Account> accounts;
    int branch_code=235; // code for saving 200 & normal 300
    int nextAccountNumber = 0;

public:

    long long account_no(string type){

        nextAccountNumber++;

        if(type == "saving"){
            return branch_code * 1000 + 200 + nextAccountNumber;
        }
        else{
            return branch_code * 1000 + 300 + nextAccountNumber;
        }
    }
    void setaccounts(Account n){
        accounts.push_back(n);
    }
    bool search_accounts(long long n){
        for(int i=0;i<accounts.size();i++){
            if(accounts[i].getAccount_no() == n){
                cout << "S.No." << i << endl;
                return true;
            }
        }
        return false;
    }
    Account* findAccount(long long accountNumber){

        for(int i = 0; i < accounts.size(); i++){

            if(accounts[i].getAccount_no() == accountNumber){
                return &accounts[i];
            }
        }

        return nullptr;
    } 
    vector<Account>& getAccounts(){
        return accounts;
    }
    int getNextAccountNumber(){
        return nextAccountNumber;
    }

    void setNextAccountNumber(int n){
        nextAccountNumber = n;
    }
    
};
class FileManager{
private:
    string filename = "accounts.dat";

public:

    // =========================
    // SAVE DATA
    // =========================
    void save(Bank& bank){

        ofstream file(filename, ios::binary | ios::trunc);

        if(!file){
            cout << "Error opening file for saving.\n";
            return;
        }

        vector<Account>& accounts = bank.getAccounts();

        // Save number of accounts
        size_t accountCount = accounts.size(); 

        file.write(
            (char*)&accountCount,
            sizeof(accountCount)
        );
        int nextNumber = bank.getNextAccountNumber();

        file.write((char*)&nextNumber, sizeof(nextNumber));

        // Save every account
        for(const auto& account : accounts){
            account.save(file);
        }

        file.close();

        cout << "Data saved successfully.\n";
    }


    // =========================
    // LOAD DATA
    // =========================
    void load(Bank& bank){

        ifstream file(filename, ios::binary);

        // File doesn't exist
        if(!file){
            cout << "No existing data found. Starting fresh.\n";
            return;
        }

        size_t accountCount;

        // Read number of accounts
        file.read(
            (char*)&accountCount,
            sizeof(accountCount)
        );
        int nextNumber;

        file.read((char*)&nextNumber, sizeof(nextNumber));

        bank.setNextAccountNumber(nextNumber);

        // Read every account
        for(size_t i = 0; i < accountCount; i++){

            Account account;

            account.load(file);

            bank.setaccounts(account);
        }

        file.close();

        cout << "Data loaded successfully.\n";
    }
};
void main_menu(){
    cout << "\n" << "    ====================\n" << "        MAIN MENU   \n " << "   ====================\n";
    cout << endl << "1. Create Account\n" << "2. Login\n" << "3. Exit\n";
}
int main(){
    Bank bank;
    int c, choice;
    FileManager fileManager;
    fileManager.load(bank);
    bool Continue = true;
    while(Continue){
        main_menu();
        cout << "Enter your choice : ";
        cin >> choice;

        if(cin.fail()){
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        switch (choice){
            case 1: {
                long long balance;
                int pin;
                int age;
                string name;
                string mobile_number;
                string Account_type;

                cout << endl << "Enter your name : ";
                cin >> name;

                // Age validation
                cout << "Enter your age : ";
                cin >> age;

                if(age < 18) {
                    cout << "Account cannot be created.\n";
                    cout << "You must be at least 18 years old.\n";
                    break;
                }

                // Initial deposit validation
                cout << "Enter your initial deposit : ";
                cin >> balance;

                if(balance <= 0) {
                    cout << "Invalid initial deposit.\n";
                    break;
                }

                // PIN validation
                cout << "Enter your PIN code : ";
                cin >> pin;

                if(pin < 1000 || pin > 9999) {
                    cout << "Invalid PIN.\n";
                    cout << "PIN must contain exactly 4 digits.\n";
                    break;
                }

                // Mobile number validation
                cout << "Enter your Mobile Number : ";
                cin >> mobile_number;

                if(mobile_number.length() != 10) {
                    cout << "Invalid mobile number.\n";
                    cout << "Mobile number must contain exactly 10 digits.\n";
                    break;
                }

                bool validMobile = true;

                for(int i = 0; i < mobile_number.length(); i++) {
                    if(mobile_number[i] < '0' || mobile_number[i] > '9') {
                        validMobile = false;
                        break;
                    }
                }

                if(!validMobile) {
                    cout << "Invalid mobile number.\n";
                    cout << "Mobile number must contain only digits.\n";
                    break;
                }

                // Account type validation
                cout << "Enter your Account Type (saving/current) : ";
                cin >> Account_type;

                if(Account_type != "saving" && Account_type != "current") {
                    cout << "Invalid account type.\n";
                    cout << "Please enter saving or current.\n";
                    break;
                }

                // Generate account number
                long long account_number = bank.account_no(Account_type);

                // Create account
                Account account(
                    account_number,
                    balance,
                    age,
                    pin,
                    name,
                    mobile_number,
                    Account_type
                );

                // Store account inside Bank
                bank.setaccounts(account);

                cout << "\n====================================\n";
                cout << "      ACCOUNT CREATED SUCCESSFULLY\n";
                cout << "====================================\n";
                cout << "Account Number : " << account_number << endl;
                cout << "Account Type   : " << Account_type << endl;
                cout << "Initial Balance: " << balance << endl;

                break;
            }
            case 2:{
                long long account_number;
                cout << "Enter Account Number :";
                cin >>  account_number;
                Account* acc = bank.findAccount(account_number);
                if(acc== nullptr){
                    cout << "The Account is not created " <<endl;
                }else{
                    int pin;
                    cout << "Enter PIN : ";
                    cin >> pin;
                    if(acc->security(pin)){
                        int choice;           

                        do {

                            cout << "\n================================\n";
                            cout << "          ACCOUNT MENU\n";
                            cout << "================================\n";
                            cout << "1. Deposit\n";
                            cout << "2. Withdraw\n";
                            cout << "3. Check Balance\n";
                            cout << "4. Account Details\n";
                            cout << "5. Transaction History\n";
                            cout << "6. Change PIN\n";
                            cout << "7. Apply Interest\n";
                            cout << "8. Loan\n";
                            cout << "9. Logout\n";
                            cout << "Enter your choice : ";
                            cin >> choice;

                            switch(choice) {

                                case 1: {
                                    long long amount;

                                    cout << "Enter deposit amount : ";
                                    cin >> amount;

                                    acc->deposits(amount);

                                    break;
                                }

                                case 2: {
                                    long long amount;

                                    cout << "Enter withdrawal amount : ";
                                    cin >> amount;

                                    acc->withdraw(amount);

                                    break;
                                }

                                case 3: {
                                    cout << "\nCurrent Balance : "
                                        << acc->getBalance() << endl;

                                    break;
                                }

                                case 4: {
                                    acc->account_details();

                                    break;
                                }

                                case 5: {
                                    acc->transaction_details();

                                    break;
                                }

                                case 6: {
                                    acc->change_PIN();

                                    break;
                                }

                                case 7: {
                                    acc->applyInterest();

                                    cout << "Interest check completed.\n";

                                    break;
                                }

                                case 8: {
                                    int loanChoice;

                                    do {

                                        cout << "\n================================\n";
                                        cout << "           LOAN MENU\n";
                                        cout << "================================\n";
                                        cout << "1. Apply for Loan\n";
                                        cout << "2. Loan Details\n";
                                        cout << "3. Make Repayment\n";
                                        cout << "4. Back\n";
                                        cout << "Enter your choice : ";
                                        cin >> loanChoice;

                                        switch(loanChoice) {

                                            case 1: {
                                                long long principal;
                                                int months;
                                                long long salary;

                                                cout << "Enter loan amount : ";
                                                cin >> principal;

                                                if (cin.fail() || principal <= 0) {
                                                    cout << "Invalid loan amount.\n";
                                                    cin.clear();
                                                    cin.ignore(10000, '\n');
                                                    break;
                                                }

                                                cout << "Enter loan duration (months) : ";
                                                cin >> months;

                                                if (cin.fail() || months <= 0) {
                                                    cout << "Invalid loan duration.\n";
                                                    cin.clear();
                                                    cin.ignore(10000, '\n');
                                                    break;
                                                }

                                                cout << "Enter monthly salary : ";
                                                cin >> salary;

                                                if (cin.fail() || salary <= 0) {
                                                    cout << "Invalid salary.\n";
                                                    cin.clear();
                                                    cin.ignore(10000, '\n');
                                                    break;
                                                }

                                                acc->loan_apply(principal, months, salary);

                                                break;
                                            }

                                            case 2: {
                                                acc->loan_details();

                                                break;
                                            }

                                            case 3: {
                                                long long amount;

                                                cout << "Enter repayment amount : ";
                                                cin >> amount;

                                                acc->loan_repayment(amount);

                                                break;
                                            }

                                            case 4:
                                                cout << "Returning to Account Menu...\n";
                                                break;

                                            default:
                                                cout << "Invalid loan choice.\n";
                                        }

                                    } while(loanChoice != 4);

                                    break;
                                }

                                case 9:
                                    cout << "\nLogged out successfully.\n";
                                    break;

                                default:
                                    cout << "Invalid choice.\n";
                            }

                        } while(choice != 9);                    

                    }
                }
                break;

            }
            case 3:{
                fileManager.save(bank);
                Continue = false;
                break;
            }
            default:
                cout << "Enter a valid choice";;
        }
    }
}