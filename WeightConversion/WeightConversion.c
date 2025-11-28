#include <stdio.h>

#define POUNDS_TO_KG 0.453592
#define KG_TO_POUNDS 2.20462
#define OUNCES_TO_KG 0.0283495
#define KG_TO_OUNCES 35.274

static void flush_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) ;
}

int main(void) {
    int choice = 0;
    double amount = 0.0;
    double converted = 0.0;

    while (1) {
        printf("\n--- Weight Conversion ---\n");
        printf("1. Pounds to Kilograms\n");
        printf("2. Kilograms to Pounds\n");
        printf("3. Ounces to Kilograms\n");
        printf("4. Kilograms to Ounces\n");
        printf("5. Exit\n");
        printf("Choose option: ");

        if (scanf("%d", &choice) != 1) break;
        flush_input();

        switch (choice) {
            case 1:
                printf("Enter weight in Pounds: ");
                if (scanf("%lf", &amount) != 1) { flush_input(); break; }
                flush_input();
                converted = amount * POUNDS_TO_KG;
                printf("%.2f Pounds = %.2f Kilograms\n", amount, converted);
                break;

            case 2:
                printf("Enter weight in Kilograms: ");
                if (scanf("%lf", &amount) != 1) { flush_input(); break; }
                flush_input();
                converted = amount * KG_TO_POUNDS;
                printf("%.2f Kilograms = %.2f Pounds\n", amount, converted);
                break;

            case 3:
                printf("Enter weight in Ounces: ");
                if (scanf("%lf", &amount) != 1) { flush_input(); break; }
                flush_input();
                converted = amount * OUNCES_TO_KG;
                printf("%.2f Ounces = %.2f Kilograms\n", amount, converted);
                break;

            case 4:
                printf("Enter weight in Kilograms: ");
                if (scanf("%lf", &amount) != 1) { flush_input(); break; }
                flush_input();
                converted = amount * KG_TO_OUNCES;
                printf("%.2f Kilograms = %.2f Ounces\n", amount, converted);
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
