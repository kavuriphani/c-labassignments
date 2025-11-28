# Library Management System (C)

Menu-driven library management with persistent account storage.

Features:
- Account management (account ID, user name, book count).
- Lend book: increment book count, log transaction.
- Return book: decrement book count, log transaction (fails if count <= 0).
- Book count: display current books with user.

Files:
- `library_accounts.txt`: account_id|user_name|book_count
- `library_transactions.txt`: account_id|book_title|date|type (L=Lend, R=Return)

Build & run (PowerShell):
```powershell
cd c:\Projects\cardealership\LibraryManagement
gcc -g LibraryManagement.c library_management_impl.c -o LibraryManagement.exe
.\LibraryManagement.exe
```
