#include <stdio.h>
#include <string.h>

static void flush_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) ;
}

static void celsius_to_fahrenheit(void) {
    double celsius;
    printf("Enter temperature in Celsius: ");
    if (scanf("%lf", &celsius) != 1) { flush_input(); return; }
    double fahrenheit = (celsius * 9.0 / 5.0) + 32.0;
    printf("%.2f°C = %.2f°F\n", celsius, fahrenheit);
}

static void fahrenheit_to_celsius(void) {
    double fahrenheit;
    printf("Enter temperature in Fahrenheit: ");
    if (scanf("%lf", &fahrenheit) != 1) { flush_input(); return; }
    double celsius = (fahrenheit - 32.0) * 5.0 / 9.0;
    printf("%.2f°F = %.2f°C\n", fahrenheit, celsius);
}

static void time_12_to_24(void) {
    int hour, min, sec;
    char period[10];
    printf("Enter time (HH MM SS AM/PM): ");
    if (scanf("%d %d %d %s", &hour, &min, &sec, period) != 4) { flush_input(); return; }
    
    if (hour < 1 || hour > 12 || min < 0 || min > 59 || sec < 0 || sec > 59) {
        printf("Invalid input.\n");
        return;
    }
    
    int hour24 = hour;
    if (period[0] == 'A' || period[0] == 'a') {
        if (hour == 12) hour24 = 0;
    } else if (period[0] == 'P' || period[0] == 'p') {
        if (hour != 12) hour24 = hour + 12;
    } else {
        printf("Invalid period (use AM or PM).\n");
        return;
    }
    
    printf("%02d:%02d:%02d %s = %02d:%02d:%02d\n", hour, min, sec, period, hour24, min, sec);
}

static void time_24_to_12(void) {
    int hour, min, sec;
    printf("Enter time (HH MM SS in 24-hour format): ");
    if (scanf("%d %d %d", &hour, &min, &sec) != 3) { flush_input(); return; }
    
    if (hour < 0 || hour > 23 || min < 0 || min > 59 || sec < 0 || sec > 59) {
        printf("Invalid input.\n");
        return;
    }
    
    char period[5];
    int hour12 = hour;
    if (hour < 12) {
        strcpy(period, "AM");
        if (hour == 0) hour12 = 12;
    } else {
        strcpy(period, "PM");
        if (hour != 12) hour12 = hour - 12;
    }
    
    printf("%02d:%02d:%02d = %02d:%02d:%02d %s\n", hour, min, sec, hour12, min, sec, period);
}

int main(void) {
    int choice = 0;
    
    while (1) {
        printf("\n--- Unit Conversion ---\n");
        printf("1. Temperature Conversion\n");
        printf("2. Time Conversion\n");
        printf("3. Exit\n");
        printf("Choose option: ");
        if (scanf("%d", &choice) != 1) break;
        flush_input();
        
        if (choice == 1) {
            int sub_choice;
            printf("\n--- Temperature Conversion ---\n");
            printf("1. Celsius to Fahrenheit\n");
            printf("2. Fahrenheit to Celsius\n");
            printf("3. Back to main menu\n");
            printf("Choose option: ");
            if (scanf("%d", &sub_choice) != 1) { flush_input(); continue; }
            flush_input();
            
            if (sub_choice == 1) celsius_to_fahrenheit();
            else if (sub_choice == 2) fahrenheit_to_celsius();
            else if (sub_choice == 3) continue;
            else printf("Invalid option.\n");
            
        } else if (choice == 2) {
            int sub_choice;
            printf("\n--- Time Conversion ---\n");
            printf("1. 12-Hour to 24-Hour\n");
            printf("2. 24-Hour to 12-Hour\n");
            printf("3. Back to main menu\n");
            printf("Choose option: ");
            if (scanf("%d", &sub_choice) != 1) { flush_input(); continue; }
            flush_input();
            
            if (sub_choice == 1) time_12_to_24();
            else if (sub_choice == 2) time_24_to_12();
            else if (sub_choice == 3) continue;
            else printf("Invalid option.\n");
            
        } else if (choice == 3) {
            printf("Exiting.\n");
            break;
        } else {
            printf("Invalid option.\n");
        }
    }
    
    return 0;
}
