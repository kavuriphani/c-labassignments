#include <stdio.h>

#define FEET_TO_METERS 0.3048
#define METERS_TO_FEET 3.28084
#define MILES_TO_KM 1.60934
#define KM_TO_MILES 0.621371

static void flush_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) ;
}

int main(void) {
    int choice = 0;
    double amount = 0.0;
    double converted = 0.0;

    while (1) {
        printf("\n--- Distance Conversion ---\n");
        printf("1. Feet to Meters\n");
        printf("2. Meters to Feet\n");
        printf("3. Miles to Kilometers\n");
        printf("4. Kilometers to Miles\n");
        printf("5. Exit\n");
        printf("Choose option: ");

        if (scanf("%d", &choice) != 1) break;
        flush_input();

        switch (choice) {
            case 1:
                printf("Enter distance in Feet: ");
                if (scanf("%lf", &amount) != 1) { flush_input(); break; }
                flush_input();
                converted = amount * FEET_TO_METERS;
                printf("%.2f Feet = %.2f Meters\n", amount, converted);
                break;

            case 2:
                printf("Enter distance in Meters: ");
                if (scanf("%lf", &amount) != 1) { flush_input(); break; }
                flush_input();
                converted = amount * METERS_TO_FEET;
                printf("%.2f Meters = %.2f Feet\n", amount, converted);
                break;

            case 3:
                printf("Enter distance in Miles: ");
                if (scanf("%lf", &amount) != 1) { flush_input(); break; }
                flush_input();
                converted = amount * MILES_TO_KM;
                printf("%.2f Miles = %.2f Kilometers\n", amount, converted);
                break;

            case 4:
                printf("Enter distance in Kilometers: ");
                if (scanf("%lf", &amount) != 1) { flush_input(); break; }
                flush_input();
                converted = amount * KM_TO_MILES;
                printf("%.2f Kilometers = %.2f Miles\n", amount, converted);
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
