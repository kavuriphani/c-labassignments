#include <stdio.h>

/* Exchange rates (approximate) */
#define INR_TO_USD 0.012  /* 1 INR = 0.012 USD */
#define USD_TO_INR 83.33  /* 1 USD = 83.33 INR */
#define INR_TO_JPY 1.62   /* 1 INR = 1.62 JPY */
#define JPY_TO_INR 0.617  /* 1 JPY = 0.617 INR */

static void flush_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) ;
}

int main(void) {
    int choice = 0;
    double amount = 0.0;
    double converted = 0.0;

    while (1) {
        printf("\n--- Currency Conversion ---\n");
        printf("1. INR to US Dollar\n");
        printf("2. INR to Japan Yen\n");
        printf("3. US Dollar to INR\n");
        printf("4. Japan Yen to INR\n");
        printf("5. Exit\n");
        printf("Choose option: ");

        if (scanf("%d", &choice) != 1) break;
        flush_input();

        switch (choice) {
            case 1:
                printf("Enter amount in INR: ");
                if (scanf("%lf", &amount) != 1) { flush_input(); break; }
                flush_input();
                converted = amount * INR_TO_USD;
                printf("%.2f INR = %.2f USD\n", amount, converted);
                break;

            case 2:
                printf("Enter amount in INR: ");
                if (scanf("%lf", &amount) != 1) { flush_input(); break; }
                flush_input();
                converted = amount * INR_TO_JPY;
                printf("%.2f INR = %.2f JPY\n", amount, converted);
                break;

            case 3:
                printf("Enter amount in USD: ");
                if (scanf("%lf", &amount) != 1) { flush_input(); break; }
                flush_input();
                converted = amount * USD_TO_INR;
                printf("%.2f USD = %.2f INR\n", amount, converted);
                break;

            case 4:
                printf("Enter amount in JPY: ");
                if (scanf("%lf", &amount) != 1) { flush_input(); break; }
                flush_input();
                converted = amount * JPY_TO_INR;
                printf("%.2f JPY = %.2f INR\n", amount, converted);
                break;

            case 5:
                printf("Exiting.\n");
                return 0;

            default:
                printf("Invalid option.\n");
        }
    }

    return 0;
}
