/*
 * Electricity Bill Generator
 * --------------------------
 * Simple console program to calculate monthly electricity bills for
 * two consumer types: Residential and Business. The program prompts
 * for consumer details (number, type, previous and present readings),
 * computes units consumed, applies slab rates, and prints a receipt.
 *
 * Build (MinGW on Windows):
 *   gcc ElectricityBillGenerator.c -o ElectricityBillGenerator.exe
 *
 * Run (PowerShell):
 *   .\ElectricityBillGenerator.exe
 *
 * Rate tables (implemented):
 *  - Business:
 *      0-200 units   : Rs. 2.00 / unit
 *      201-450 units : Rs. 3.25 / unit (for units above 200)
 *      451+ units    : Rs. 5.00 / unit (for units above 450)
 *  - Residential:
 *      0-99 units    : Rs. 1.50 / unit
 *      100-249 units : Rs. 2.25 / unit (for units above 100)
 *      250+ units    : Rs. 3.00 / unit (for units above 250)
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * calculateBusinessBill
 * ---------------------
 * Calculate the electricity bill for a Business consumer using
 * a slab-based tariff.
 *
 * Parameters:
 *   units - number of units consumed (non-negative integer)
 *
 * Returns:
 *   bill amount as a double (in currency units)
 */
double calculateBusinessBill(int units) {
    double bill = 0.0;
    
    if (units <= 200) {
        bill = units * 2.00;
    } else if (units <= 450) {
        bill = (200 * 2.00) + ((units - 200) * 3.25);
    } else {
        bill = (200 * 2.00) + (250 * 3.25) + ((units - 450) * 5.00);
    }
    
    return bill;
}

/**
 * calculateResidentialBill
 * ------------------------
 * Calculate the electricity bill for a Residential consumer using
 * a slab-based tariff.
 *
 * Parameters:
 *   units - number of units consumed (non-negative integer)
 *
 * Returns:
 *   bill amount as a double (in currency units)
 */
double calculateResidentialBill(int units) {
    double bill = 0.0;
    
    if (units < 100) {
        bill = units * 1.50;
    } else if (units < 250) {
        bill = (100 * 1.50) + ((units - 100) * 2.25);
    } else {
        bill = (100 * 1.50) + (150 * 2.25) + ((units - 250) * 3.00);
    }
    
    return bill;
}

/**
 * displayBillDetails
 * ------------------
 * Print a formatted bill receipt to stdout.
 *
 * Parameters:
 *   consumerNumber - integer identifier for the consumer
 *   consumerType   - 'R' for Residential, 'B' for Business
 *   units          - number of units consumed
 *   billAmount     - calculated bill amount
 */
void displayBillDetails(int consumerNumber, char consumerType, int units, double billAmount) {
    printf("\n");
    printf("===============================================\n");
    printf("           ELECTRICITY BILL RECEIPT             \n");
    printf("===============================================\n");
    printf("Consumer Number    : %d\n", consumerNumber);
    printf("Consumer Type      : %s\n", consumerType == 'B' ? "Business" : "Residential");
    printf("Number of Units    : %d\n", units);
    printf("Bill Amount (Rs.)  : %.2f\n", billAmount);
    printf("===============================================\n\n");
}

int main() {
    int consumerNumber;
    char consumerType;
    int previousReading, presentReading;
    int units;
    double billAmount;
    int choice;
    
    /* Simple menu loop: 1 to calculate, 2 to exit. */
    while (1) {
        printf("\n========================================\n");
        printf("   ELECTRICITY BILL CALCULATOR\n");
        printf("========================================\n");
        printf("1. Calculate Bill\n");
        printf("2. Exit\n");
        printf("========================================\n");
        printf("Enter your choice (1 or 2): ");
        scanf("%d", &choice);
        getchar(); // Clear the newline from buffer
        
        if (choice == 2) {
            printf("\nThank you for using Electricity Bill Calculator!\n");
            break;
        }
        
        if (choice != 1) {
            printf("\nInvalid choice! Please enter 1 or 2.\n");
            continue;
        }
        
        /* Input consumer details */
        printf("\n--- Enter Consumer Details ---\n");
        printf("Consumer Number: ");
        scanf("%d", &consumerNumber);
        getchar(); // Clear the newline from buffer
        
        /* Input and validate consumer type */
        printf("Consumer Type (R-Residential / B-Business): ");
        scanf("%c", &consumerType);
        getchar(); // Clear the newline from buffer
        
        /* Convert to uppercase for case-insensitive input */
        consumerType = toupper(consumerType);
        
        /* Validate consumer type */
        if (consumerType != 'R' && consumerType != 'B') {
            printf("\nError: Invalid consumer type! Please enter 'R' for Residential or 'B' for Business.\n");
            continue;
        }
        
        printf("Previous Month Reading (in units): ");
        scanf("%d", &previousReading);
        getchar(); // Clear the newline from buffer
        
        printf("Present Month Reading (in units): ");
        scanf("%d", &presentReading);
        getchar(); // Clear the newline from buffer
        
        /* Validate readings: present must be strictly greater than previous */
        if (presentReading <= previousReading) {
            printf("\nError: Present reading must be greater than previous reading!\n");
            continue;
        }
        
        /* Calculate units consumed */
        units = presentReading - previousReading;
        
        /* Calculate bill based on consumer type */
        if (consumerType == 'B') {
            billAmount = calculateBusinessBill(units);
        } else {
            billAmount = calculateResidentialBill(units);
        }
        
        /* Display bill details */
        displayBillDetails(consumerNumber, consumerType, units, billAmount);
    }
    
    return 0;
}
