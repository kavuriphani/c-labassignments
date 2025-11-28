#ifndef LIBRARY_MANAGEMENT_H
#define LIBRARY_MANAGEMENT_H

#include <stdbool.h>

#define LIB_ACC_FILE "library_accounts.txt"
#define LIB_TX_FILE  "library_transactions.txt"

typedef struct {
    long account_id;
    char user_name[100];
    int book_count;
} LibraryAccount;

/* utilities */
void lib_flush_input(void);
void lib_sanitize(char *s);

/* account persistence */
bool lib_load_account(long account_id, LibraryAccount *out);
bool lib_save_account(const LibraryAccount *acc);
bool lib_create_account(long account_id, const char *user_name);

/* transactions */
bool lib_append_transaction(long account_id, const char *book_title, const char *date, char type);

/* operations */
bool lib_lend_book(long account_id, const char *book_title, const char *date);
bool lib_return_book(long account_id, const char *book_title, const char *date);
int lib_get_book_count(long account_id, bool *found);

#endif /* LIBRARY_MANAGEMENT_H */
