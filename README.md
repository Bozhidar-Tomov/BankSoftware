
# Bank Software

Course Project № 9

Course - *Introduction to programming*, Winter Semester 2022, Year 1

## Introduction

Program simulating a set of basic functionalities in a bank.

### Features

Initial functionalities

* **L** -  Login to the system
* **R** -  Register new user
* **Q** -  Quit

- - -
After the user is successfully logged in they can:

* **C** -  Cancel their account
* **D** -  Deposit money to their account
* **W** -  Withdraw money from their account
* **T** -  Transfer money to another user by passing the name of the recipient party
* **L** -  Logout from the system

### Account limits

* Overdraft limit - 10,000.00 BGN
* Maximum balance limit - 1,000,000,000.00 BGN (1 billion)
* Withdraw / Deposit amount limit per time - 5000.00 BGN

### Validations

User Name should consist of:

* *First Name* and *SurName* with minimum of **3** and maximum of **20** letters [A-Z, a-z]

Password should consist of at least:

* 1 lowercase letter
* 1 uppercase letter
* 1 symbol - `! @ # $ % ^ & *`
* minimum length - **5**
* maximum length - **20**

## ⚠️ Build And Run the program

First, ake sure you have GCC Compiler installed on your machine by running this command:

```bash
g++ --version
```

Then, in the directory where all the source files are located run:

```bash
g++ -o program.exe main.cpp accountOperations.cpp onStart.cpp userInfo.cpp utils.cpp
```

An executable file `program.exe` should be created in the same directory.

**Note:** If there is any problem building the project, you could run the pre-built executable in this repository.

## Compatibility

The software is cross-platform, not invoking any OS-specific functionalities.

The software is tested and guaranteed to run on:

* **OS:** Windows 10 64-bit, version 22H2
* **Compiler:** MINGW64 GCC version: (Rev4, Built by MSYS2 project) 12.2.0

### License

The MIT License ([MIT](https://choosealicense.com/licenses/mit/)) 2023 - Bozhidar Tomov - student Year 1, Semester 1, FMI, Sofia.
