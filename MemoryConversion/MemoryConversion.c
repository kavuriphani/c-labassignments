#include <stdio.h>

#define KB_TO_MB 0.001
#define MB_TO_KB 1024.0
#define MB_TO_GB 0.0009765625
#define GB_TO_MB 1024.0
#define MB_TO_TB 0.000000953674316
#define TB_TO_MB 1048576.0
#define GB_TO_TB 0.0009765625
#define TB_TO_GB 1024.0

static void flush_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) ;
}

int main(void) {
    int choice = 0;
    double amount = 0.0;
    double converted = 0.0;

    while (1) {
        printf("\n--- Memory Size Conversion ---\n");
        printf("1. Kilobytes to Megabytes\n");
        printf("2. Megabytes to Gigabytes\n");
        printf("3. Megabytes to Terabytes\n");
        printf("4. Gigabytes to Terabytes\n");
        printf("5. Exit\n");
        printf("Choose option: ");

        if (scanf("%d", &choice) != 1) break;
        flush_input();

        switch (choice) {
            case 1:
                printf("Enter size in Kilobytes: ");
                if (scanf("%lf", &amount) != 1) { flush_input(); break; }
                flush_input();
                converted = amount * KB_TO_MB;
                printf("%.2f KB = %.2f MB\n", amount, converted);
                break;

            case 2:
                printf("Enter size in Megabytes: ");
                if (scanf("%lf", &amount) != 1) { flush_input(); break; }
                flush_input();
                converted = amount * MB_TO_GB;
                printf("%.2f MB = %.2f GB\n", amount, converted);
                break;

            case 3:
                printf("Enter size in Megabytes: ");
                if (scanf("%lf", &amount) != 1) { flush_input(); break; }
                flush_input();
                converted = amount * MB_TO_TB;
                printf("%.2f MB = %.2f TB\n", amount, converted);
                break;

            case 4:
                printf("Enter size in Gigabytes: ");
                if (scanf("%lf", &amount) != 1) { flush_input(); break; }
                flush_input();
                converted = amount * GB_TO_TB;
                printf("%.2f GB = %.2f TB\n", amount, converted);
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
