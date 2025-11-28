#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "bank_transaction.h"

int main(void) {
    int choice = 0;
    while (1) {
        printf("\nBank Transaction Management\n");
        printf("1. Credit Amount\n");
        printf("2. Debit Amount\n");
        printf("3. Balance Enquiry\n");
        printf("4. Exit\n");
        printf("Choose option: ");
        if (scanf("%d", &choice) != 1) break;
        bt_flush_input();

        if (choice == 1) {
            long acc_no;
            char date[20];
            double amount;
            printf("Enter Account number: ");
            if (scanf("%ld", &acc_no) != 1) { bt_flush_input(); continue; }
            bt_flush_input();
            bool found = false;
            double bal = bt_balance_enquiry(acc_no, &found);
            if (!found) {
                char name[100];
                printf("Account not found. Enter holder name to create new account: ");
                if (!fgets(name, sizeof name, stdin)) continue;
                name[strcspn(name, "\r\n")] = '\0';
                printf("Enter initial deposit: ");
                if (scanf("%lf", &bal) != 1) { bt_flush_input(); continue; }
                bt_flush_input();
                bt_sanitize(name);
                if (!bt_create_account(acc_no, name, bal)) { printf("Failed to create account.\n"); continue; }
                printf("Created account %ld for %s with balance %.2f\n", acc_no, name, bal);
            }

            printf("Enter Date of transaction (DD-MM-YYYY): ");
            if (!fgets(date, sizeof date, stdin)) continue;
            date[strcspn(date, "\r\n")] = '\0';
            printf("Enter amount to credit: ");
            if (scanf("%lf", &amount) != 1) { bt_flush_input(); continue; }
            bt_flush_input();

            if (bt_credit_amount(acc_no, amount, date)) {
                printf("Credited %.2f to account %ld.\n", amount, acc_no);
            } else {
                printf("Failed to credit amount.\n");
            }

        } else if (choice == 2) {
            long acc_no;
            char date[20];
            double amount;
            printf("Enter Account number: ");
            if (scanf("%ld", &acc_no) != 1) { bt_flush_input(); continue; }
            bt_flush_input();
            bool found = false;
            double bal = bt_balance_enquiry(acc_no, &found);
            if (!found) { printf("Account %ld not found.\n", acc_no); continue; }

            printf("Enter Date of transaction (DD-MM-YYYY): ");
            if (!fgets(date, sizeof date, stdin)) continue;
            date[strcspn(date, "\r\n")] = '\0';
            printf("Enter amount to debit: ");
            if (scanf("%lf", &amount) != 1) { bt_flush_input(); continue; }
            bt_flush_input();

            if (bt_debit_amount(acc_no, amount, date)) {
                printf("Debited %.2f from account %ld.\n", amount, acc_no);
            } else {
                printf("Failed to debit amount (insufficient funds or error).\n");
            }

        } else if (choice == 3) {
            long acc_no;
            printf("Enter Account number: ");
            if (scanf("%ld", &acc_no) != 1) { bt_flush_input(); continue; }
            bt_flush_input();
            bool found = false;
            double bal = bt_balance_enquiry(acc_no, &found);
            if (!found) {
                printf("Account %ld not found.\n", acc_no);
            } else {
                printf("Account %ld balance: %.2f\n", acc_no, bal);
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
