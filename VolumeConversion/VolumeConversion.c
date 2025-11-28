#include <stdio.h>

#define GALLONS_TO_LITERS 3.78541
#define LITERS_TO_GALLONS 0.264172
#define LITERS_TO_FLOZ 33.814
#define FLOZ_TO_LITERS 0.0295735

static void flush_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) ;
}

int main(void) {
    int choice = 0;
    double amount = 0.0;
    double converted = 0.0;

    while (1) {
        printf("\n--- Volume Conversion ---\n");
        printf("1. Gallons to Liters\n");
        printf("2. Liters to Gallons\n");
        printf("3. Liters to Fluid Ounces\n");
        printf("4. Fluid Ounces to Liters\n");
        printf("5. Exit\n");
        printf("Choose option: ");

        if (scanf("%d", &choice) != 1) break;
        flush_input();

        switch (choice) {
            case 1:
                printf("Enter volume in Gallons: ");
                if (scanf("%lf", &amount) != 1) { flush_input(); break; }
                flush_input();
                converted = amount * GALLONS_TO_LITERS;
                printf("%.2f Gallons = %.2f Liters\n", amount, converted);
                break;

            case 2:
                printf("Enter volume in Liters: ");
                if (scanf("%lf", &amount) != 1) { flush_input(); break; }
                flush_input();
                converted = amount * LITERS_TO_GALLONS;
                printf("%.2f Liters = %.2f Gallons\n", amount, converted);
                break;

            case 3:
                printf("Enter volume in Liters: ");
                if (scanf("%lf", &amount) != 1) { flush_input(); break; }
                flush_input();
                converted = amount * LITERS_TO_FLOZ;
                printf("%.2f Liters = %.2f Fluid Ounces\n", amount, converted);
                break;

            case 4:
                printf("Enter volume in Fluid Ounces: ");
                if (scanf("%lf", &amount) != 1) { flush_input(); break; }
                flush_input();
                converted = amount * FLOZ_TO_LITERS;
                printf("%.2f Fluid Ounces = %.2f Liters\n", amount, converted);
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
