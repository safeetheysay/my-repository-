#include <iostream>
#include <string>
using namespace std;

const int MAX_ACCOUNTS = 100;

class Account{
	protected:
		static int accountCounter;
		int accountNumber;
		string owner;
		double balance;
	public:
	    Account(const string &owner,double initialBalance)
		: owner(owner), balance(initialBalance) {
			accountNumber = ++accountCounter;
		}	
		virtual ~Account(){}
		
		int getAccountNumber() const{
			return accountNumber;
		}
		
		double getBalance() const{
			return balance;
		}
		const string &getowner() const{
			return owner;
		}
		
		virtual void deposit(double amount) {
			balance +=amount;
		}
		
		virtual void withdraw(double amount){
			if (amount<= balance) {
			
			balance -= amount;
		} else {
			cout<<"Insufficient Balance!" <<endl;
			}
		}
		
		virtual void display() const {
			cout<<"Account Number is: "<< accountNumber<<endl;
			cout<<"Owner Name is: "<< owner<<endl;;
			cout<<"Your Balance is: Rs. "<< balance<<endl;
		}

	    static int getAccountCounter(){
	    	return accountCounter;
		}
};

int Account::accountCounter = 0;
class SavingsAccount : public Account {
       public:
	   SavingsAccount(const string &owner,double initialBalance)	
	   : Account(owner,initialBalance) {}	  
	   
	   void deposit(double amount) override {
	   	balance+= amount;
	   }
	   
	   void withdraw(double amount) override {
	   	if (amount <= balance){
	   		balance -=amount;
		   }
		   else {
		   	cout<<" Insufficient Balance!"<<endl;
		   }
	   } 
	   void display() const override{
	   
	   cout<<"Savings ";
	   Account::display();
	   }
	   
};

class Bank {
	private:
		Account* accounts[MAX_ACCOUNTS];
		int accountCount;
	
	public:
	     Bank(): accountCount(0){}
		 
		 ~Bank() {
		 	for (int i=0; i< accountCount; i++){
		 		delete accounts[i];
			 }
		 }
		
		void createAccount (const string &owner, double initialBalance){
			if (accountCount < MAX_ACCOUNTS){
				accounts[accountCount++] = new SavingsAccount(owner, initialBalance);
			} else {
			  cout<<"Cannot Create More Accounts. Maximum Number of Accounts Already Exist."<<endl;
			}
		}
		
		void deleteAccount(int accountNumber) {
			for (int i=0; i<accountCount; ++i){
				if (accounts[i]->getAccountNumber() == accountNumber){
					delete accounts[i];
					for (int j = i; j < accountCount - 1; ++j){
						accounts[j] = accounts[j + 1];
					}
					--accountCount;
					cout<<"Account "<< accountNumber <<" Deleted."<<endl;
					return;
				}
			}
			cout<<"Account "<<accountNumber<<" Not Found. "<<endl;
		}
		
		Account* findAccount (int accountNumber) {
			for (int i=0; i < accountCount; ++i ){
				if (accounts[i]->getAccountNumber() == accountNumber){
					return accounts[i];
				}
			}
			return nullptr;
			}
		
		void deposit(int accountNumber,double amount) {
			Account* account = findAccount(accountNumber);
			if (account) {
				account->deposit(amount);
				cout<<" Deposited Rs " << amount << " to Account Number: " <<accountNumber<<"."<<endl;
			} else {
				cout<< "Account "<< accountNumber<< " Not Found." <<endl;
			}
		}
			
			
 void withdraw(int accountNumber, double amount) {
        Account* account = findAccount(accountNumber);
        if (account) {
            account->withdraw(amount);
            cout << "Withdrew Rs : " << amount << " from account " << accountNumber << "." << endl;
        } else {
            cout << "Account " << accountNumber << " not found." << endl;
        }
    }

    void displayAccount(int accountNumber) const {
        for (int i = 0; i < accountCount; ++i) {
            if (accounts[i]->getAccountNumber() == accountNumber) {
                accounts[i]->display();
                return;
            }
        }
        cout << "Account " << accountNumber << " not found." << endl;
    }

    void displayAllAccounts() const {
        for (int i = 0; i < accountCount; ++i) {
            accounts[i]->display();
        }
    }
};

int main() {
    Bank bank;
    int choice;
    int accountNumber;
    double amount;
    string owner;
    double initialBalance;

    do {
        cout << "\n                       ------------- Bank Management System ---------------\n";
        cout << "                       |                                                   |"<<endl;
        cout << "                       |            Choose an option from the Menu.        |"<<endl;
        cout << "                       |                 1. Create Account                 |"<<endl;
        cout << "                       |                 2. Delete Account                 |"<<endl;
        cout << "                       |                 3. Deposit                        |"<<endl;
        cout << "                       |                 4. Withdraw                       |"<<endl;
        cout << "                       |                 5. Display Account                |"<<endl;
        cout << "                       |                 6. Display All Accounts           |"<<endl;
        cout << "                       |                 7. Exit                           |"<<endl;
        cout << "                       -----------------------------------------------------"<<endl;
        cout<<" "<<endl;
		cout << "|----------------------|"<<endl;
		cout << "|  Enter your choice:  |"<<endl;
        cout << "|----------------------|"<<endl;
		cout<<"      ";
		cin >> choice;

        switch (choice) {
            case 1:
                cout << "|---------------------|"<<endl;
			    cout << "|  Enter owner name:  | "<<endl;
			    cout << "|---------------------|"<<endl;
			    cout<<" "<<endl;
                cout<<"      ";cin.ignore();
                getline(cin, owner);
                cout<<" "<<endl;
                cout << "|--------------------------|"<<endl;
                cout << "|  Enter initial balance:  |"<<endl;
                cout << "|--------------------------|"<<endl;
                cout<<"      "<<endl;
				cout<<"      ";cin >> initialBalance;
				cout<<" "<<endl;
                bank.createAccount(owner, initialBalance);
              cout <<" |--------------------------------|"<<endl;
              cout<< " |  Account Created Succesfully.  |"<<endl;
              cout <<" |--------------------------------|"<<endl;
                break;
            case 2:
            	cout <<" |-----------------------------------|"<<endl;
                cout <<" |  Enter account number to delete:  |"<<endl;
                cout <<" |-----------------------------------|"<<endl;
				cout<< " "<<endl;
				cout<<"      ";cin >> accountNumber;
                bank.deleteAccount(accountNumber);
                break;
            case 3:
                cout << "|-----------------------------------------|"<<endl;
				cout << "|  Enter account number to deposit into:  |"<<endl;
                cout << "|-----------------------------------------|"<<endl;
				cout<< " "<<endl;
                cout<<"      ";cin >> accountNumber;
                cout<< " "<<endl;
				cout << "|----------------------------|"<<endl;
                cout << "|  Enter amount to deposit:  |"<<endl;
                cout << "|----------------------------|"<<endl;
                cout<< " "<<endl;
				cout<<"      ";cin >> amount;
                bank.deposit(accountNumber, amount);
                break;
            case 4:
            	cout << "|------------------------------------------|"<<endl;
                cout << "|  Enter account number to withdraw from:  |"<<endl;
                cout << "|------------------------------------------|"<<endl;
                cout<< " "<<endl;
				cout<<"      ";cin >> accountNumber;
                cout<< " "<<endl;
				cout << "|------------------------------|"<<endl;
                cout << "|   Enter amount to withdraw:  |"<<endl;
                cout << "|------------------------------|"<<endl;
                cout<< " "<<endl;
				cout<<"      ";cin >> amount;
                bank.withdraw(accountNumber, amount);
                break;
            case 5:
            	cout <<" |------------------------------------|"<<endl;
                cout <<" |  Enter account number to display:  |"<<endl;
                cout <<" |------------------------------------|"<<endl;
                cout<< " "<<endl;
				cout<<"      ";cin >> accountNumber;
                bank.displayAccount(accountNumber);
                break;
            case 6:
                bank.displayAllAccounts();
                break;
            case 7:
                cout << "Exiting...GoodBye!"<<endl;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
