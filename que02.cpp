#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;


class Bank{
    public: 
    Bank(int numAccounts, int initialBalance)
        : accounts(numAccounts, initialBalance){}


    void transfer(int from, int to, int amount){
        lock_guard<mutex> lock(mtx);

        if(accounts[from] >= amount){
            accounts[from] -= amount;
            accounts[to] += amount;
            cout<<"Transferred Amount "<<amount
            <<" from account "<<from<<" to account "<<to<<endl;
        }
        else{
            cout<<"Insufficient funds in account "<<from 
            <<" to transfer "<<amount<<" funds"<<endl;
        }
    }

    int getTotalBalance(){
        lock_guard<mutex> lock(mtx);
        int totalBalance = 0;
        for(int i = 0; i < accounts.size(); i++){
            totalBalance += accounts[i];
        }
        return totalBalance;
    }


private:
    vector<int> accounts;
    mutable mutex mtx;
};


void simulateTransactions(
                            Bank &bank, int from, 
                            int to, int amount, int numTransactions
                        ){

    for(int i=0; i<numTransactions; ++i){
        bank.transfer(from, to, amount);
    }
}


int main(){

    // Account Details
    int numAccounts = 3;
    int initialBalance = 1000;
    int numberOfTransactionsPerThread = 2;

    int numThreads = 2;
    
    // create the bank and its threads
    Bank bank(numAccounts,initialBalance);

    vector<thread> t;

    // Create threads and launch them
    for (int i = 0; i < numThreads; ++i) {
        t.emplace_back(
                       simulateTransactions, ref(bank), 
                       i % numThreads, (i + 1) % numAccounts,
                       50,numberOfTransactionsPerThread
                       );

        
    }

    // Join Threds
    for(int i=0; i<numThreads; ++i){
        t[i].join();
    }

    // print total balance of bank
    cout<< "Total Bank Balance: "<< bank.getTotalBalance() <<endl;
    

    return 0;
}


