#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_ACCOUNTS 100
#define MAX_TRANSACTIONS 100

struct Transaction {
    char type[20];
    float amount;
};

struct BankAccount {
    int accountNumber;
    char name[100];
    float balance;
    int pin;

    struct Transaction transactions[MAX_TRANSACTIONS];
    int transactionCount;

    float loanAmount;
    float loanInterestRate;
    int loanTermYears;
    int hasLoan;
    float loanRemaining;
};

void addTransaction(struct BankAccount *acc, const char *type, float amount) {
    if (acc->transactionCount < MAX_TRANSACTIONS) {
        strcpy(acc->transactions[acc->transactionCount].type, type);
        acc->transactions[acc->transactionCount].amount = amount;
        acc->transactionCount++;
    }
}

int verifyPin(struct BankAccount *acc) {
    int pin;
    printf("Enter PIN: ");
    scanf("%d", &pin);
    if (pin == acc->pin) return 1;
    printf("Incorrect PIN.\n");
    return 0;
}

int findAccountIndex(struct BankAccount accounts[], int count, int accNo) {
    for (int i = 0; i < count; i++)
        if (accounts[i].accountNumber == accNo)
            return i;
    return -1;
}

void createAccount(struct BankAccount accounts[], int *count) {
    if (*count >= MAX_ACCOUNTS) {
        printf("Account limit reached.\n");
        return;
    }
    printf("Enter name: ");
    scanf(" %[^\n]", accounts[*count].name);
    printf("Set a 4-digit PIN: ");
    scanf("%d", &accounts[*count].pin);
    accounts[*count].accountNumber = 1000 + *count;
    accounts[*count].balance = 0.0;
    accounts[*count].transactionCount = 0;
    accounts[*count].hasLoan = 0;
    accounts[*count].loanRemaining = 0;
    printf("Account created. Your Account Number is %d\n", accounts[*count].accountNumber);
    (*count)++;
}

void deposit(struct BankAccount accounts[], int count) {
    int accNo, index;
    float amount;
    printf("Enter account number: ");
    scanf("%d", &accNo);
    index = findAccountIndex(accounts, count, accNo);
    if (index == -1 || !verifyPin(&accounts[index])) return;
    printf("Enter deposit amount: ");
    scanf("%f", &amount);
    accounts[index].balance += amount;
    addTransaction(&accounts[index], "Deposit", amount);
    printf("Deposit successful.\n");
}

void withdraw(struct BankAccount accounts[], int count) {
    int accNo, index;
    float amount;
    printf("Enter account number: ");
    scanf("%d", &accNo);
    index = findAccountIndex(accounts, count, accNo);
    if (index == -1 || !verifyPin(&accounts[index])) return;
    printf("Enter withdrawal amount: ");
    scanf("%f", &amount);
    if (accounts[index].balance >= amount) {
        accounts[index].balance -= amount;
        addTransaction(&accounts[index], "Withdraw", amount);
        printf("Withdrawal successful.\n");
    } else {
        printf("Insufficient balance.\n");
    }
}
void checkBalance(struct BankAccount accounts[], int count) {
    int accNo, index;
    printf("Enter account number: ");
    scanf("%d", &accNo);
    index = findAccountIndex(accounts, count, accNo);
    if (index == -1 || !verifyPin(&accounts[index])) return;
    printf("Account Holder: %s\n", accounts[index].name);
    printf("Current Balance: %.2f\n", accounts[index].balance);
}

void viewTransactions(struct BankAccount accounts[], int count) {
    int accNo, index;
    printf("Enter account number: ");
    scanf("%d", &accNo);
    index = findAccountIndex(accounts, count, accNo);
    if (index == -1 || !verifyPin(&accounts[index])) return;
    printf("Transaction History:\n");
    for (int i = 0; i < accounts[index].transactionCount; i++) {
        printf("%d. %s - %.2f\n", i + 1, accounts[index].transactions[i].type, accounts[index].transactions[i].amount);
    }
}

void changePin(struct BankAccount accounts[], int count) {
    int accNo, index, newPin;
    printf("Enter account number: ");
    scanf("%d", &accNo);
    index = findAccountIndex(accounts, count, accNo);
    if (index == -1 || !verifyPin(&accounts[index])) return;
    printf("Enter new PIN: ");
    scanf("%d", &newPin);
    accounts[index].pin = newPin;
    printf("PIN changed successfully.\n");
}

void calculateInterest(struct BankAccount accounts[], int count) {
    int accNo, index;
    float rate;
    int years;
    printf("Enter account number: ");
    scanf("%d", &accNo);
    index = findAccountIndex(accounts, count, accNo);
    if (index == -1 || !verifyPin(&accounts[index])) return;
    printf("Enter interest rate (%%): ");
    scanf("%f", &rate);
    printf("Enter number of years: ");
    scanf("%d", &years);
    float compound = accounts[index].balance * pow(1 + rate / 100, years);
    printf("Balance after %d years at %.2f%% interest: %.2f\n", years, rate, compound);
}

void applyLoan(struct BankAccount accounts[], int count) {
    int accNo, index;
    float amount, rate = 8.5 ;
    int years;
    printf("Enter account number: ");
    scanf("%d", &accNo);
    index = findAccountIndex(accounts, count, accNo);
    if (index == -1 || !verifyPin(&accounts[index])) return;
    if (accounts[index].hasLoan) {
        printf("You already have a loan pending.\n");
        return;
    }
    printf("Enter loan amount: ");
    scanf("%f", &amount);
    //printf("Enter interest rate (%%): ");
    //scanf("%f", &rate);
    printf("Enter loan term in years: ");
    scanf("%d", &years);
    float totalRepayment = amount * pow(1 + rate / 100, years);
    accounts[index].loanAmount = amount;
    accounts[index].loanInterestRate = rate;
    accounts[index].loanTermYears = years;
    accounts[index].loanRemaining = totalRepayment;
    accounts[index].hasLoan = 1;
    printf("Loan approved. Total repayment amount: %.2f\n", totalRepayment);
}

void repayLoan(struct BankAccount accounts[], int count) {
    int accNo, index;
    float payment;
    printf("Enter account number: ");
    scanf("%d", &accNo);
    index = findAccountIndex(accounts, count, accNo);
    if (index == -1 || !verifyPin(&accounts[index])) return;
    if (!accounts[index].hasLoan) {
        printf("No active loan.\n");
        return;
    }
    printf("Remaining loan amount: %.2f\n", accounts[index].loanRemaining);
    printf("Enter amount to pay: ");
    scanf("%f", &payment);
    if (payment > accounts[index].balance) {
        printf("Insufficient balance to repay loan.\n");
        return;
    }
    if (payment > accounts[index].loanRemaining) payment = accounts[index].loanRemaining;
    accounts[index].loanRemaining -= payment;
    accounts[index].balance -= payment;
    addTransaction(&accounts[index], "Loan Repayment", payment);
    if (accounts[index].loanRemaining <= 0) {
        accounts[index].hasLoan = 0;
        printf("Loan fully repaid!\n");
    } else {
        printf("Remaining loan: %.2f\n", accounts[index].loanRemaining);
    }
}

int main() {
    struct BankAccount accounts[MAX_ACCOUNTS];
    int count = 0, choice;

    do {
        printf("\n----- Bank Management System -----\n");
        printf("1. Create Account\n2. Deposit\n3. Withdraw\n4. Check Balance\n5. View Transactions\n");
        printf("6. Change PIN\n7. Calculate Interest\n8. Apply Loan\n9. Repay Loan\n0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: createAccount(accounts, &count); break;
            case 2: deposit(accounts, count); break;
            case 3: withdraw(accounts, count); break;
            case 4: checkBalance(accounts, count); break;
            case 5: viewTransactions(accounts, count); break;
            case 6: changePin(accounts, count); break;
            case 7: calculateInterest(accounts, count); break;
            case 8: applyLoan(accounts, count); break;
            case 9: repayLoan(accounts, count); break;
            case 0: printf("Thank you!\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);

    return 0;
}
