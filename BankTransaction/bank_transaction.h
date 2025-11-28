#ifndef BANK_TRANSACTION_H
#define BANK_TRANSACTION_H

#include <stdbool.h>

#define ACC_FILE "accounts.txt"
#define TX_FILE  "transactions.txt"

typedef struct {
    long account_no;
    char name[100];
    double balance;
} Account;

/* utilities */
void bt_flush_input(void);
void bt_sanitize(char *s);

/* account persistence */
bool bt_load_account(long account_no, Account *out);
bool bt_save_account(const Account *acc);
bool bt_create_account(long account_no, const char *name, double initial_balance);

/* transactions */
bool bt_append_transaction(long account_no, const char *date, char type, double amount, double balance_after);

/* operations */
bool bt_credit_amount(long account_no, double amount, const char *date);
bool bt_debit_amount(long account_no, double amount, const char *date);
double bt_balance_enquiry(long account_no, bool *found);

#endif /* BANK_TRANSACTION_H */
