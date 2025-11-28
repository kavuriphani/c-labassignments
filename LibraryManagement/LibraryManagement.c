#include <stdio.h>
#include <string.h>
#include "library_management.h"

int main(void) {
    int choice = 0;
    while (1) {
        printf("\nLibrary Management System\n");
        printf("1. Lend book\n");
        printf("2. Return book\n");
        printf("3. Book count\n");
        printf("4. Exit\n");
        printf("Choose option: ");
        if (scanf("%d", &choice) != 1) break;
        lib_flush_input();

        if (choice == 1) {
            long acc_id;
            char book_title[128];
            char date[20];
            printf("Enter Library account ID: ");
            if (scanf("%ld", &acc_id) != 1) { lib_flush_input(); continue; }
            lib_flush_input();

            bool found = false;
            int count = lib_get_book_count(acc_id, &found);
            if (!found) {
                char user_name[100];
                printf("Account not found. Enter user name to create: ");
                if (!fgets(user_name, sizeof user_name, stdin)) continue;
                user_name[strcspn(user_name, "\r\n")] = '\0';
                lib_sanitize(user_name);
                if (!lib_create_account(acc_id, user_name)) {
                    printf("Failed to create account.\n");
                    continue;
                }
                printf("Created account %ld for %s.\n", acc_id, user_name);
            }

            printf("Enter book title: ");
            if (!fgets(book_title, sizeof book_title, stdin)) continue;
            book_title[strcspn(book_title, "\r\n")] = '\0';
            lib_sanitize(book_title);

            printf("Enter date of lent (DD-MM-YYYY): ");
            if (!fgets(date, sizeof date, stdin)) continue;
            date[strcspn(date, "\r\n")] = '\0';

            if (lib_lend_book(acc_id, book_title, date)) {
                printf("Book \"%s\" lent to account %ld.\n", book_title, acc_id);
            } else {
                printf("Failed to lend book.\n");
            }

        } else if (choice == 2) {
            long acc_id;
            char book_title[128];
            char date[20];
            printf("Enter Library account ID: ");
            if (scanf("%ld", &acc_id) != 1) { lib_flush_input(); continue; }
            lib_flush_input();

            bool found = false;
            int count = lib_get_book_count(acc_id, &found);
            if (!found) { printf("Account %ld not found.\n", acc_id); continue; }

            printf("Enter book title: ");
            if (!fgets(book_title, sizeof book_title, stdin)) continue;
            book_title[strcspn(book_title, "\r\n")] = '\0';
            lib_sanitize(book_title);

            printf("Enter date of return (DD-MM-YYYY): ");
            if (!fgets(date, sizeof date, stdin)) continue;
            date[strcspn(date, "\r\n")] = '\0';

            if (lib_return_book(acc_id, book_title, date)) {
                printf("Book \"%s\" returned from account %ld.\n", book_title, acc_id);
            } else {
                printf("Failed to return book (no books in account or error).\n");
            }

        } else if (choice == 3) {
            long acc_id;
            printf("Enter Library account ID: ");
            if (scanf("%ld", &acc_id) != 1) { lib_flush_input(); continue; }
            lib_flush_input();

            bool found = false;
            int count = lib_get_book_count(acc_id, &found);
            if (!found) {
                printf("Account %ld not found.\n", acc_id);
            } else {
                printf("Account %ld has %d book(s).\n", acc_id, count);
            }

        } else if (choice == 4) {
            printf("Exiting.\n");
            break;
        } else {
            printf("Invalid option.\n");
        }
    }
    return 0;
}
