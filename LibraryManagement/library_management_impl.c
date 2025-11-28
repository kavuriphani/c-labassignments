#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library_management.h"

void lib_sanitize(char *s) {
    for (; *s; ++s) {
        if (*s == '|' || *s == '\r' || *s == '\n') *s = '-';
    }
}

void lib_flush_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) ;
}

bool lib_load_account(long account_id, LibraryAccount *out) {
    FILE *f = fopen(LIB_ACC_FILE, "r");
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
        int count = atoi(tok);
        if (acc == account_id) {
            out->account_id = acc;
            strncpy(out->user_name, name, sizeof out->user_name-1);
            out->user_name[sizeof out->user_name-1] = '\0';
            out->book_count = count;
            found = true;
            break;
        }
    }
    fclose(f);
    return found;
}

bool lib_save_account(const LibraryAccount *acc) {
    FILE *f = fopen(LIB_ACC_FILE, "r");
    char **lines = NULL;
    size_t n = 0;
    if (f) {
        char buf[512];
        while (fgets(buf, sizeof buf, f)) {
            lines = realloc(lines, (n+1) * sizeof(char*));
            lines[n++] = _strdup(buf);
        }
        fclose(f);
    }

    bool updated = false;
    for (size_t i = 0; i < n; ++i) {
        char *line = lines[i];
        char copy[512]; strncpy(copy, line, sizeof copy-1); copy[sizeof copy-1] = '\0';
        char *tok = strtok(copy, "|");
        if (!tok) continue;
        long accid = atol(tok);
        if (accid == acc->account_id) {
            free(lines[i]);
            char newline[256];
            snprintf(newline, sizeof newline, "%ld|%s|%d\n", acc->account_id, acc->user_name, acc->book_count);
            lines[i] = _strdup(newline);
            updated = true;
            break;
        }
    }
    if (!updated) {
        lines = realloc(lines, (n+1) * sizeof(char*));
        char newline[256];
        snprintf(newline, sizeof newline, "%ld|%s|%d\n", acc->account_id, acc->user_name, acc->book_count);
        lines[n++] = _strdup(newline);
    }

    FILE *wf = fopen(LIB_ACC_FILE, "w");
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

bool lib_create_account(long account_id, const char *user_name) {
    LibraryAccount a;
    a.account_id = account_id;
    strncpy(a.user_name, user_name, sizeof a.user_name-1); a.user_name[sizeof a.user_name-1] = '\0';
    a.book_count = 0;
    return lib_save_account(&a);
}

bool lib_append_transaction(long account_id, const char *book_title, const char *date, char type) {
    FILE *f = fopen(LIB_TX_FILE, "a");
    if (!f) return false;
    fprintf(f, "%ld|%s|%s|%c\n", account_id, book_title, date, type);
    fclose(f);
    return true;
}

bool lib_lend_book(long account_id, const char *book_title, const char *date) {
    LibraryAccount a;
    if (!lib_load_account(account_id, &a)) return false;
    a.book_count++;
    if (!lib_save_account(&a)) return false;
    if (!lib_append_transaction(account_id, book_title, date, 'L')) return false;
    return true;
}

bool lib_return_book(long account_id, const char *book_title, const char *date) {
    LibraryAccount a;
    if (!lib_load_account(account_id, &a)) return false;
    if (a.book_count <= 0) return false;
    a.book_count--;
    if (!lib_save_account(&a)) return false;
    if (!lib_append_transaction(account_id, book_title, date, 'R')) return false;
    return true;
}

int lib_get_book_count(long account_id, bool *found) {
    LibraryAccount a;
    if (lib_load_account(account_id, &a)) {
        if (found) *found = true;
        return a.book_count;
    }
    if (found) *found = false;
    return 0;
}
