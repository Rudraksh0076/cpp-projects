# 🏦 Mini Banking System

> A console-based banking management system built in **C++** to apply Object-Oriented Programming, STL, binary file handling, persistent data storage, authentication, transaction management, savings interest, and loan processing in a single practical application.

---

## 📌 Overview

**Mini Banking System** is a command-line banking application developed in C++ as a practical demonstration of core programming and Object-Oriented Programming concepts.

The system simulates essential banking operations such as account creation, secure login, deposits, withdrawals, transaction history, savings interest, loan management, and persistent account storage.

Unlike a basic in-memory banking program, this project maintains its data between executions through **custom binary serialization**, allowing accounts, transactions, loans, security states, and other account information to be restored when the application starts again.

The project was designed with a focus on applying C++ concepts to a larger, interconnected system rather than implementing isolated examples.

---

## ✨ Key Features

### 👤 Account Management

* Create Saving or Current accounts
* Automatic account-number generation
* Account holder information management
* Initial balance validation
* Age validation
* Mobile-number validation
* Four-digit PIN validation
* Account details display

### 🔐 Authentication & Account Security

* Login using Account Number and PIN
* Three-attempt PIN protection
* Permanent account locking after three failed attempts
* Failed-attempt count persistence
* PIN change functionality
* Successful authentication resets the failed-attempt counter

### 💰 Banking Operations

* Deposit funds
* Withdraw funds
* Check account balance
* Prevent invalid or negative transactions
* Prevent withdrawals exceeding available balance
* Record successful financial operations in transaction history

### 📜 Transaction Management

The system maintains transaction history for each account.

Each transaction records:

| Information | Description                                          |
| ----------- | ---------------------------------------------------- |
| Type        | Deposit, withdrawal, loan, repayment, interest, etc. |
| Amount      | Transaction amount                                   |
| Date        | Date of transaction                                  |
| Time        | Time of transaction                                  |

Transaction data is stored as part of the corresponding `Account` object and persists across program executions.

### 💵 Savings Interest

Saving accounts support an annual interest mechanism.

* Saving account interest rate: **5%**
* Current account interest rate: **0%**
* Interest is applied based on elapsed time
* Calculated interest is added directly to the account balance
* Interest is recorded in transaction history
* Last interest-calculation time is persisted

### 🏦 Loan Management

The application includes a dedicated loan-management system.

Users can:

* Apply for a loan
* View active loan details
* Make loan repayments
* View remaining loan amount
* Track amount paid
* Track loan status

#### Loan Eligibility

The current implementation applies the following simplified rules:

* Applicant must be at least 18 years old
* Monthly salary must be at least ₹25,000
* Account balance must be at least ₹10,000
* Requested loan must not exceed `salary × 12`
* An account cannot have more than one active loan

The current loan implementation uses a **13.1% annual interest rate** for EMI calculation.

### 💾 Persistent Storage

The application stores its data locally using **binary file handling**.

The following information is persisted:

* Account information
* Account balance
* PIN
* Account type
* Interest information
* Interest timestamp
* Account lock status
* Failed login attempts
* Transaction history
* Loan information
* Account-number sequence

Data is stored in:

```text
accounts.dat
```

The application automatically loads existing data when started and saves the current banking state when the user exits through the main menu.

---

# 🧱 System Architecture

The project is organized around five core classes:

```text
                         ┌─────────────────┐
                         │      Bank       │
                         └────────┬────────┘
                                  │
                           manages Accounts
                                  │
                                  ▼
                         ┌─────────────────┐
                         │     Account     │
                         └───────┬─┬───────┘
                                 │ │
                   contains      │ │      contains
                                 │ │
                    ┌────────────┘ └────────────┐
                    ▼                           ▼
           ┌─────────────────┐         ┌─────────────────┐
           │   Transaction   │         │      Loan       │
           └─────────────────┘         └─────────────────┘

                         ┌─────────────────┐
                         │   FileManager   │
                         └────────┬────────┘
                                  │
                           Binary Persistence
                                  │
                                  ▼
                         ┌─────────────────┐
                         │   accounts.dat  │
                         └─────────────────┘
```

---

## 🧩 Class Responsibilities

### `Account`

The central domain class representing a customer's bank account.

It manages:

* Account information
* Balance
* Authentication
* Security state
* Deposits
* Withdrawals
* PIN changes
* Transaction history
* Savings interest
* Loan operations

An `Account` owns collections of:

```cpp
vector<Transaction>
vector<Loan>
```

This allows transactions and loans to remain associated with their respective account.

---

### `Transaction`

Represents an individual banking transaction.

Stores:

```text
Transaction Type
Amount
Date
Time
```

It also provides methods for binary serialization and deserialization:

```cpp
save()
load()
```

Transaction timestamps are generated using C++ date/time facilities.

---

### `Loan`

Represents a customer's loan.

Stores:

```text
Principal
Interest Rate
Duration
Salary
EMI
Total Amount
Amount Paid
Active Status
```

Responsibilities include:

* EMI calculation
* Repayment tracking
* Remaining amount calculation
* Active/inactive loan status
* Binary persistence

---

### `Bank`

Acts as the account collection manager.

Responsibilities include:

* Maintaining all accounts
* Generating account numbers
* Searching for accounts
* Returning account references/pointers
* Maintaining the account-number sequence

Internally, the bank stores:

```cpp
vector<Account> accounts;
```

---

### `FileManager`

Responsible for persistent storage.

It handles:

```text
Saving application state
Loading application state
```

The class serializes the bank's accounts and their associated transactions and loans into the binary data file.

---

# 🔄 Application Flow

```text
                    START
                      │
                      ▼
              Load saved data
                      │
                      ▼
                 Main Menu
                /    |     \
               /     |      \
              ▼      ▼       ▼
          Create   Login    Exit
          Account    │        │
                     │        ▼
                     │    Save Data
                     │        │
                     │        ▼
                     │       END
                     ▼
              PIN Authentication
                     │
              ┌──────┴──────┐
              │             │
           Success         Failure
              │             │
              ▼             ▼
        Account Menu    Attempt Count
              │             │
       ┌──────┼──────┐      │
       ▼      ▼      ▼      ▼
    Banking  Loans  Account  Lock
   Operations       Services
```

---

# 🖥️ User Interface

## Main Menu

```text
====================
     MAIN MENU
====================

1. Create Account
2. Login
3. Exit
```

## Account Menu

```text
================================
          ACCOUNT MENU
================================

1. Deposit
2. Withdraw
3. Check Balance
4. Account Details
5. Transaction History
6. Change PIN
7. Apply Interest
8. Loan
9. Logout
```

## Loan Menu

```text
================================
           LOAN MENU
================================

1. Apply for Loan
2. Loan Details
3. Make Repayment
4. Back
```

---

# 🛠️ Technical Stack

| Category                  | Technology                  |
| ------------------------- | --------------------------- |
| Language                  | C++                         |
| Interface                 | Console / CLI               |
| Data Structure            | `vector`                    |
| Strings                   | `std::string`               |
| File Storage              | Binary file I/O             |
| Date & Time               | `<chrono>`, `<ctime>`       |
| Mathematical Calculations | `<math.h>`                  |
| Persistence File          | `accounts.dat`              |
| Paradigm                  | Object-Oriented Programming |

---

# 🧠 C++ Concepts Demonstrated

This project brings together several C++ concepts in one application:

* Classes and objects
* Encapsulation
* Constructors
* Access specifiers
* Member functions
* Object composition
* STL `vector`
* STL `string`
* References
* Pointers
* Object collections
* Binary file handling
* Serialization and deserialization
* Input validation
* Stream-state handling
* Date and time handling
* Mathematical calculations
* Nested menus
* Loops and conditional logic
* Persistent application state

---

# 📁 Project Structure

The current implementation is maintained as a single C++ source file:

```text
cpp-projects/
│
└── Banking-system/
    │
    ├── Mini-Bnaking-System.cpp
    │
    └── accounts.dat       # Generated at runtime
```

> `accounts.dat` is generated by the application and stores persistent banking data locally.

---

# ⚙️ Installation & Usage

## Prerequisites

You need a C++ compiler supporting standard C++ features, such as:

* GCC / MinGW
* Clang
* Visual Studio C++ compiler

---

## 1. Clone the Repository

```bash
git clone https://github.com/Rudraksh0076/cpp-projects.git
```

## 2. Navigate to the Project

```bash
cd cpp-projects/Banking-system
```

## 3. Compile

Using `g++`:

```bash
g++ Mini-Bnaking-System.cpp -o banking
```

## 4. Run

### Windows

```bash
banking.exe
```

### Linux / macOS

```bash
./banking
```

---

# 💾 Data Persistence

One of the major components of the project is persistent storage.

The program does not simply keep accounts in memory. Before termination, the `FileManager` serializes the banking data into:

```text
accounts.dat
```

When the program starts again, the file is read and the previous application state is reconstructed.

The persistence hierarchy can be represented as:

```text
Bank
│
├── Account
│   ├── Personal Information
│   ├── Security Information
│   ├── Transaction History
│   │   ├── Transaction
│   │   ├── Transaction
│   │   └── ...
│   │
│   └── Loans
│       ├── Loan
│       └── ...
│
└── Account
    └── ...
```

This was implemented using custom `save()` and `load()` functions rather than relying on a database.

---

# 🔐 Security Considerations

This application demonstrates **basic account-level security**, but it is not intended for real-world banking.

The project currently provides:

* PIN authentication
* Three-attempt protection
* Permanent account locking
* Persistent security state

However, sensitive information is stored in a local binary file without encryption or cryptographic hashing.

Therefore:

> **This project should be considered an educational banking simulation, not production banking software.**

Never use real banking credentials, PINs, or sensitive financial information while testing it.

---

# ⚠️ Current Limitations

The current version intentionally remains a standalone C++ console application.

### Architecture

* All classes currently reside in one source file
* No separate header/source architecture
* No database layer
* No networking layer

### Security

* PINs are not cryptographically hashed
* Binary storage is not encrypted
* No secure authentication protocol

### Banking Logic

* Interest and loan rules are simplified
* Loan eligibility is based on predefined conditions
* No real-world banking regulations or financial policies are implemented

### Application

* Console-based interface
* No graphical interface
* No administrator interface
* No concurrent users
* No online transactions
* No external banking APIs

---

# 🚀 Future Improvements

Possible future versions could introduce:

### Architecture

* [ ] Separate `.h` and `.cpp` files
* [ ] Dedicated service classes
* [ ] Improved separation of concerns
* [ ] Unit testing

### Security

* [ ] PIN hashing
* [ ] Encryption for stored data
* [ ] Improved authentication
* [ ] Session management

### Banking Features

* [ ] Account-to-account transfers
* [ ] Beneficiary management
* [ ] Account statements
* [ ] Transaction IDs
* [ ] Transaction filtering
* [ ] Multiple loan management
* [ ] More realistic interest calculations

### Storage

* [ ] Database integration
* [ ] Automated backups
* [ ] Data versioning

### Interface

* [ ] GUI
* [ ] Web-based interface
* [ ] REST API

---

# 🎯 Project Goals

The primary goal of this project was to move beyond small C++ exercises and build a complete application where multiple concepts work together.

The project provided practical experience with:

```text
C++
 │
 ├── Object-Oriented Programming
 │
 ├── STL
 │
 ├── File Handling
 │
 ├── Data Persistence
 │
 ├── Input Validation
 │
 ├── Authentication
 │
 ├── Date & Time
 │
 ├── Financial Calculations
 │
 └── System Design
```

---

# 📈 Project Status

**Status: Completed**

This project represents a major C++ application developed as part of my learning journey before moving toward **Data Structures & Algorithms and Java development**.

---

# 👨‍💻 Author

### Rudraksh

GitHub: [@Rudraksh0076](https://github.com/Rudraksh0076)

---

# ⚠️ Disclaimer

This project is developed strictly for **educational and demonstration purposes**.

It is a simulation of basic banking operations and is **not affiliated with or intended to represent an actual bank or financial institution**.

Do not use real personal, banking, authentication, or financial information while testing the application.

---

## ⭐ If you find this project useful

Feel free to explore the repository, review the implementation, and use the project as a reference for learning C++ Object-Oriented Programming and file handling.
