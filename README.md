# Bank Management System

A simple terminal-based **Bank Management System** written in C. This project allows users to create accounts, manage transactions (deposits, withdrawals), view account details, apply for and repay loans, and more—all secured with a basic PIN verification system.

---

## 📌 Features

- ✅ Create and manage multiple bank accounts  
- 💰 Deposit and withdraw money  
- 📄 View transaction history  
- 🔐 Secure operations using PIN-based authentication  
- 💹 Interest calculator (Compound interest)  
- 🏦 Apply for and repay loans  
- 🔄 Change PIN functionality  
- 💼 Simple, easy-to-understand command-line interface  

---

## 🛠️ Technologies Used

- **Language:** C
- **Compiler:** GCC or any standard C compiler
- **Platform:** Terminal / Command Line

---

## 📂 Project Structure

```
c code.c         // Main source code file
README.md             // Project documentation (this file)
```

---

## 📸 Sample Menu Output

```text
----- Bank Management System -----
1. Create Account
2. Deposit
3. Withdraw
4. Check Balance
5. View Transactions
6. Change PIN
7. Calculate Interest
8. Apply Loan
9. Repay Loan
0. Exit
Enter choice:
```

---

## 🧮 Interest & Loan Logic

- **Interest** is calculated using the compound interest formula:  
  `A = P * (1 + r/100)^t`
  
- **Loan repayment** tracks remaining loan balance and only allows repayments if the user has sufficient account balance.

---

## 🔐 Security Note

- All sensitive operations (withdrawals, balance checks, etc.) are protected using a **4-digit PIN** entered at account creation.
- The PIN is required every time you perform a critical transaction.

---

## ✨ Future Improvements

- Persistent storage (save data to file or database)
- GUI interface
- Enhanced security with encryption
- More detailed transaction types and timestamps

---

## 🙌 Contributing

Pull requests are welcome! For major changes, please open an issue first to discuss what you would like to change.

---
