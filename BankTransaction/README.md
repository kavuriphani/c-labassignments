# Bank Transaction Management System (C)

This program provides a simple bank management console with persistent accounts and transaction logging.

Features
- Create or load accounts stored in `accounts.txt` (`account_no|name|balance`).
- Log transactions to `transactions.txt` (`account_no|date|type|amount|balance_after`).
- Operations: Credit, Debit, Balance Enquiry.

Build & run (PowerShell)
```powershell
gcc -g BankTransaction.c bank_transaction_impl.c -o BankTransaction.exe
.\BankTransaction.exe
```

Notes
- When crediting a non-existent account, the program prompts to create the account and set an initial deposit.
- Debits will fail if the account has insufficient balance.
