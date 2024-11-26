#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ACCOUNTS 100
#define MAX_TRANSACTIONS 100
#define MAX_LOANS 10
#define MAX_SAVINGS_GOALS 5

typedef enum { CHECKING, SAVINGS } AccountType;

// Contains transaction information
typedef struct {
    char description[100];
    float amount;
} Transaction;

// Contains loan information
typedef struct {
    float amount;
    float interestRate;
    int term;
    int isApproved;
} Loan;

// Contains savings goal information
typedef struct {
    char goalName[50];
    float targetAmount;
    float currentAmount;
} SavingsGoal;

// Contains account information
typedef struct {
    int accountNumber;
    char name[50];
    char password[20];
    float balance;
    AccountType type;
    Transaction transactions[MAX_TRANSACTIONS];
    int transactionCount;
    Loan loans[MAX_LOANS];
    int loanCount;
    SavingsGoal savingsGoals[MAX_SAVINGS_GOALS];
    int savingsGoalCount;
} Account;

Account accounts[MAX_ACCOUNTS];
int totalAccounts = 0;

// Function declarations start here
void createAccount();
void login();
void depositMoney(Account* account);
void withdrawMoney(Account* account);
void checkBalance(Account* account);
void viewTransactions(Account* account);
void transferMoney(Account* account);
void calculateInterest(Account* account);
void mobileRecharge(Account* account);
void payBill(Account* account);
void applyForLoan(Account* account);
void viewLoans(Account* account);
void setSavingsGoal(Account* account);
void viewSavingsGoals(Account* account);
void menu();
Account* findAccount(int accountNumber, char* password);

int main() {
    int choice;

    while (1) {
        menu();
        printf("Select your option : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                login();
                break;
            case 3:
                printf("Thank you for using our survice. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid!!! Please try again.\n");
        }
    }

    return 0;
}

void menu() {
    printf("\n_--ABC Online Bank--_\n");
    printf("Press 1. Create Your Account\n");
    printf("Press 2. Login Here\n");
    printf("Press 3. Exit\n");
}

void createAccount() {
    if (totalAccounts >= MAX_ACCOUNTS) {
        printf("Account limit reached. Cannot create more accounts.\n");
        return;
    }

    Account newAccount;
    newAccount.accountNumber = totalAccounts + 1;

    printf("\nEnter your name: ");
    scanf(" %[^\n]", newAccount.name);

    printf("Create a password: ");
    scanf("%s", newAccount.password);

    printf("Select account type :\nPress 0 for Checking Account. \nPress 1 for Savings Account.\n");
    printf("Enter : ");
    int type;
    scanf("%d", &type);
    newAccount.type = (AccountType)type;

    newAccount.balance = 0.0f;
    newAccount.transactionCount = 0;
    newAccount.loanCount = 0;
    newAccount.savingsGoalCount = 0;

    accounts[totalAccounts++] = newAccount;

    printf("\nAccount created successfully!\n Your account number is: %d\n", newAccount.accountNumber);
}

void login() {
    int accountNumber;
    char password[20];
    Account* account;

    printf("\nEnter account number: ");
    scanf("%d", &accountNumber);

    printf("Enter password: ");
    scanf("%s", password);

    account = findAccount(accountNumber, password);

    if (account != NULL) {
        printf("\nLogin successful. Welcome, %s!\n", account->name);
        int choice;

        while (1) {
            printf("\n--- Account Menu ---\n");
            printf("1. Check Balance\n");
            printf("2. Deposit Money\n");
            printf("3. Withdraw Money\n");
            printf("4. Transfer Money\n");
            printf("5. View Transactions\n");
            printf("6. Calculate Interest\n");
            printf("7. Mobile Recharge\n");
            printf("8. Pay Bill\n");
            printf("9. Apply for Loan\n");
            printf("10. View Loans\n");
            printf("11. Set Savings Goal\n");
            printf("12. View Savings Goals\n");
            printf("13. Logout\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    checkBalance(account);
                    break;
                case 2:
                    depositMoney(account);
                    break;
                case 3:
                    withdrawMoney(account);
                    break;
                case 4:
                    transferMoney(account);
                    break;
                case 5:
                    viewTransactions(account);
                    break;
                case 6:
                    calculateInterest(account);
                    break;
                case 7:
                    mobileRecharge(account);
                    break;
                case 8:
                    payBill(account);
                    break;
                case 9:
                    applyForLoan(account);
                    break;
                case 10:
                    viewLoans(account);
                    break;
                case 11:
                    setSavingsGoal(account);
                    break;
                case 12:
                    viewSavingsGoals(account);
                    break;
                case 13:
                    printf("Logging out...\n");
                    return;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }
    } else {
        printf("Invalid account number or password.\n");
    }
}

void depositMoney(Account* account) {
    float amount;

    printf("Enter amount to deposit: ");
    scanf("%f", &amount);

    if (amount > 0) {
        account->balance += amount;
        snprintf(account->transactions[account->transactionCount].description, sizeof(account->transactions[account->transactionCount].description), "Deposited: %.2f", amount);
        account->transactions[account->transactionCount].amount = amount;
        account->transactionCount++;
        printf("Amount successfully deposited. Your new balance is: %.2f\n", account->balance);
    } else {
        printf("Invalid amount. Please try again.\n");
    }
}

void withdrawMoney(Account* account) {
    float amount;

    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);

    if (amount > 0 && amount <= account->balance) {
        account->balance -= amount;
        snprintf(account->transactions[account->transactionCount].description, sizeof(account->transactions[account->transactionCount].description), "Withdrew: %.2f", amount);
        account->transactions[account->transactionCount].amount = -amount;
        account->transactionCount++;
        printf("Amount successfully withdrawn. Your new balance is: %.2f\n", account->balance);
    } else if (amount > account->balance) {
        printf("Insufficient funds. Your current balance is: %.2f\n", account->balance);
    } else {
        printf("Invalid amount. Please try again.\n");
    }
}

void checkBalance(Account* account) {
    printf("Your current balance is: %.2f\n", account->balance);
}

void viewTransactions(Account* account) {
    printf("\n--- Transaction History for Account %d ---\n", account->accountNumber);
    for (int i = 0; i < account->transactionCount; i++) {
        printf("%s: %.2f\n", account->transactions[i].description, account->transactions[i].amount);
    }
}

void transferMoney(Account* account) {
    int targetAccountNumber;
    float amount;

    printf("Enter target account number: ");
    scanf("%d", &targetAccountNumber);
    Account* targetAccount = findAccount(targetAccountNumber, account->password);

    if (targetAccount == NULL) {
        printf("Target account not found.\n");
        return;
    }

    printf("Enter amount to transfer: ");
    scanf("%f", &amount);

    if (amount > 0 && amount <= account->balance) {
        account->balance -= amount;
        targetAccount->balance += amount;

        snprintf(account->transactions[account->transactionCount].description, sizeof(account->transactions[account->transactionCount].description), "Transferred to Account %d: %.2f", targetAccountNumber, amount);
        account->transactions[account->transactionCount].amount = -amount;
        account->transactionCount++;

        snprintf(targetAccount->transactions[targetAccount->transactionCount].description, sizeof(targetAccount->transactions[targetAccount->transactionCount].description), "Received from Account %d: %.2f", account->accountNumber, amount);
        targetAccount->transactions[targetAccount->transactionCount].amount = amount;
        targetAccount->transactionCount++;

        printf("Amount successfully transferred. Your new balance is: %.2f\n", account->balance);
    } else if (amount > account->balance) {
        printf("Insufficient funds. Your current balance is : %.2f\n", account->balance);
    } else {
        printf("Invalid amount. Please try again.\n");
    }
}

void calculateInterest(Account* account) {
    if (account->type == SAVINGS) {
        float interestRate = 0.05; // 5% interest rate for savings accounts
        float interest = account->balance * interestRate;
        account->balance += interest;
        snprintf(account->transactions[account->transactionCount].description, sizeof(account->transactions[account->transactionCount].description), "Interest Added: %.2f", interest);
        account->transactions[account->transactionCount].amount = interest;
        account->transactionCount++;
        printf("Interest calculated and added. Your new balance is: %.2f\n", account->balance);
    } else {
        printf("Interest calculation is only applicable for savings accounts.\n");
    }
}

void mobileRecharge(Account* account) {
    char mobileNumber[15];
    float amount;

    printf("Enter mobile number: ");
    scanf("%s", mobileNumber);
    printf("Enter amount to recharge: ");
    scanf("%f", &amount);

    if (amount > 0 && amount <= account->balance) {
        account->balance -= amount;
        snprintf(account->transactions[account->transactionCount].description, sizeof(account->transactions[account->transactionCount].description), "Mobile Recharge: %s - %.2f", mobileNumber, amount);
        account->transactions[account->transactionCount].amount = -amount;
        account->transactionCount++;
        printf("Recharge successful! Your new balance is: %.2f\n", account->balance);
    } else {
        printf("Insufficient funds or invalid amount. Your current balance is: %.2f\n", account->balance);
    }
}

void payBill(Account* account) {
    char billType[50];
    float amount;

    printf("Enter bill type (e.g., Electricity, Water): ");
    scanf(" %[^\n]", billType);
    printf("Enter amount to pay: ");
    scanf("%f", &amount);

    if (amount > 0 && amount <= account->balance) {
        account->balance -= amount;
        snprintf(account->transactions[account->transactionCount].description, sizeof(account->transactions[account->transactionCount].description), "Bill Payment (%s): %.2f", billType, amount);
        account->transactions[account->transactionCount].amount = -amount;
        account->transactionCount++;
        printf("Bill payment successful! Your new balance is: %.2f\n", account->balance);
    } else {
        printf("Insufficient funds or invalid amount. Your current balance is: %.2f\n", account->balance);
    }
}

void applyForLoan(Account* account) {
    if (account->loanCount >= MAX_LOANS) {
        printf("Loan limit reached. Cannot apply for more loans.\n");
        return;
    }

    Loan newLoan;
    printf("Enter loan amount: ");
    scanf("%f", &newLoan.amount);
    printf("Enter interest rate (in percentage): ");
    scanf("%f", &newLoan.interestRate);
    printf("Enter loan term (in months): ");
    scanf("%d", &newLoan.term);
    newLoan.isApproved = 0;

    account->loans[account->loanCount++] = newLoan;
    printf("Loan application submitted successfully!\n");
}

void viewLoans(Account* account) {
    printf("\n--- Loan Information for Account %d ---\n", account->accountNumber);
    for (int i = 0; i < account->loanCount; i++) {
        printf("Loan %d: Amount: %.2f, Interest Rate: %.2f%%, Term: %d months, Approved: %s\n", 
               i + 1, account->loans[i].amount, account->loans[i].interestRate, account->loans[i].term, 
               account->loans[i].isApproved ? "Yes" : "No");
    }
}

void setSavingsGoal(Account* account) {
    if (account->savingsGoalCount >= MAX_SAVINGS_GOALS) {
        printf("Savings goal limit reached. Cannot set more goals.\n");
        return;
    }

    SavingsGoal newGoal;
    printf("Enter savings goal name: ");
    scanf(" %[^\n]", newGoal.goalName);
    printf("Enter target amount: ");
    scanf("%f", &newGoal.targetAmount);
    newGoal.currentAmount = 0.0f;

    account->savingsGoals[account->savingsGoalCount++] = newGoal;
    printf("Savings goal set successfully!\n");
}

void viewSavingsGoals(Account* account) {
    printf("\n--- Savings Goals for Account %d ---\n", account->accountNumber);
    for (int i = 0; i < account->savingsGoalCount; i++) {
        printf("Goal %d: %s, Target Amount: %.2f, Current Amount: %.2f\n", 
               i + 1, account->savingsGoals[i].goalName, 
               account->savingsGoals[i].targetAmount, 
               account->savingsGoals[i].currentAmount);
    }
}

Account* findAccount(int accountNumber, char* password) {
    for (int i = 0; i < totalAccounts; i++) {
        if (accounts[i].accountNumber == accountNumber && strcmp(accounts[i].password, password) == 0) {
            return &accounts[i];
        }
    }
    return NULL;
}