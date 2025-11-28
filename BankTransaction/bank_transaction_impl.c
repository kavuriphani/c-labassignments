#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "bank_transaction.h"

/* remove trailing newline and '|' if present */
void bt_sanitize(char *s) {
    for (; *s; ++s) {
        if (*s == '|' || *s == '\r' || *s == '\n') *s = '-';
    }
}

void bt_flush_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) ;
}

/* Load account by scanning accounts file; returns true if found */
bool bt_load_account(long account_no, Account *out) {
    FILE *f = fopen(ACC_FILE, "r");
    if (!f) return false;
    char line[512];
    bool found = false;
    while (fgets(line, sizeof line, f)) {
        line[strcspn(line, "\r\n")] = '\0';
        char *tok = strtok(line, "|");
        if (!tok) continue;
        long acc = atol(tok);
        tok = strtok(NULL, "|");
        if (!tok) continue;
        char name[100]; strncpy(name, tok, sizeof name-1); name[sizeof name-1] = '\0';
        tok = strtok(NULL, "|");
        if (!tok) continue;
        double bal = atof(tok);
        if (acc == account_no) {
            out->account_no = acc;
            strncpy(out->name, name, sizeof out->name-1);
            out->name[sizeof out->name-1] = '\0';
            out->balance = bal;
            found = true;
            break;
        }
    }
    fclose(f);
    return found;
}

/* Save or update account: read all, update matching account_no or append, then write back */
bool bt_save_account(const Account *acc) {
    FILE *f = fopen(ACC_FILE, "r");
    char **lines = NULL;
    size_t cap = 0, n = 0;
    if (f) {
        char buf[512];
        while (fgets(buf, sizeof buf, f)) {
            lines = realloc(lines, (n+1) * sizeof(char*));
            lines[n++] = _strdup(buf);
        }
        fclose(f);
    }

    /* update or append */
    bool updated = false;
    for (size_t i = 0; i < n; ++i) {
        char *line = lines[i];
        char copy[512]; strncpy(copy, line, sizeof copy-1); copy[sizeof copy-1] = '\0';
        char *tok = strtok(copy, "|");
        if (!tok) continue;
        long accno = atol(tok);
        if (accno == acc->account_no) {
            /* replace this line */
            free(lines[i]);
            char newline[256];
            snprintf(newline, sizeof newline, "%ld|%s|%.2f\n", acc->account_no, acc->name, acc->balance);
            lines[i] = _strdup(newline);
            updated = true;
            break;
        }
    }
    if (!updated) {
        /* append */
        lines = realloc(lines, (n+1) * sizeof(char*));
        char newline[256];
        snprintf(newline, sizeof newline, "%ld|%s|%.2f\n", acc->account_no, acc->name, acc->balance);
        lines[n++] = _strdup(newline);
    }

    /* write back */
    FILE *wf = fopen(ACC_FILE, "w");
    if (!wf) {
        for (size_t i = 0; i < n; ++i) free(lines[i]);
        free(lines);
        return false;
    }
    for (size_t i = 0; i < n; ++i) {
        fputs(lines[i], wf);
        free(lines[i]);
    }
    free(lines);
    fclose(wf);
    return true;
}

bool bt_create_account(long account_no, const char *name, double initial_balance) {
    Account a;
    a.account_no = account_no;
    strncpy(a.name, name, sizeof a.name-1); a.name[sizeof a.name-1] = '\0';
    a.balance = initial_balance;
    if (!bt_save_account(&a)) return false;
    /* record initial deposit as a transaction so transactions.txt exists and shows account creation */
    if (!bt_append_transaction(account_no, "CREATED", 'C', initial_balance, a.balance)) {
        /* not fatal, but inform via stderr */
        fprintf(stderr, "Warning: failed to append initial transaction for account %ld\n", account_no);
    }
    return true;
}

bool bt_append_transaction(long account_no, const char *date, char type, double amount, double balance_after) {
    FILE *f = fopen(TX_FILE, "a");
    if (!f) return false;
    fprintf(f, "%ld|%s|%c|%.2f|%.2f\n", account_no, date, type, amount, balance_after);
    fclose(f);
    return true;
}

bool bt_credit_amount(long account_no, double amount, const char *date) {
    Account a;
    if (!bt_load_account(account_no, &a)) return false;
    a.balance += amount;
    if (!bt_save_account(&a)) return false;
    if (!bt_append_transaction(account_no, date, 'C', amount, a.balance)) return false;
    return true;
}

bool bt_debit_amount(long account_no, double amount, const char *date) {
    Account a;
    if (!bt_load_account(account_no, &a)) return false;
    if (a.balance < amount) return false;
    a.balance -= amount;
    if (!bt_save_account(&a)) return false;
    if (!bt_append_transaction(account_no, date, 'D', amount, a.balance)) return false;
    return true;
}

double bt_balance_enquiry(long account_no, bool *found) {
    Account a;
    if (bt_load_account(account_no, &a)) {
        if (found) *found = true;
        return a.balance;
    }
    if (found) *found = false;
    return 0.0;
}
