/*
 * Electricity Bill - Generic Calculator
 * ------------------------------------
 * Single compute function that accepts slab upper-limits and rates
 * as inputs (no hard-coded slab logic inside the function).
 *
 * Build:
 *   gcc ElectricityBill_Generic.c -o ElectricityBill_Generic.exe
 *
 * Run:
 *   .\ElectricityBill_Generic.exe
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

/*
 * computeBill
 * -----------
 * Compute bill amount for `units` using slab upper-limits and rates.
 *
 * Parameters:
 *   units   - consumed units (non-negative)
 *   limits  - array of slab upper-limits (increasing). For the last
 *             slab use INT_MAX to indicate no upper bound.
 *   rates   - array of per-unit rates for each slab
 *   n       - number of slabs (length of limits and rates arrays)
 *
 * Behavior:
 *   For each slab i, the available capacity is (limits[i] - prev_limit).
 *   The function consumes units from lower slabs first and multiplies
 *   consumed units by the corresponding rate. The function does NOT
 *   hard-code any slab values.
 */
double computeBill(int units, const int limits[], const double rates[], int n) {
    if (units <= 0 || n <= 0) return 0.0;

    double bill = 0.0;
    int remaining = units;
    int prev_limit = 0;

    for (int i = 0; i < n && remaining > 0; ++i) {
        int up = limits[i];

        /* capacity of this slab */
        long capacity;
        if (up == INT_MAX) {
            capacity = remaining; /* all remaining units fall here */
        } else {
            capacity = (long)up - prev_limit;
            if (capacity < 0) capacity = 0;
        }

        int use = (int)(remaining < capacity ? remaining : capacity);
        if (use > 0) {
            bill += use * rates[i];
            remaining -= use;
        }

        if (up != INT_MAX) prev_limit = up;
    }

    return bill;
}

/* helper to clear stdin up to newline */
static void flush_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int main(void) {
    int consumerNumber = 0;
    char consumerType = 'R';
    int prevReading = 0, presReading = 0;

    /* Define tariffs in main (data-driven). */
    /* Example: Business slabs: 200,450,INF with rates 2.00,3.25,5.00 */
    const int business_limits[] = {200, 450, INT_MAX};
    const double business_rates[] = {2.00, 3.25, 5.00};
    const int business_slabs = sizeof(business_limits) / sizeof(business_limits[0]);

    /* Residential slabs: 100,250,INF with rates 1.50,2.25,3.00 */
    const int residential_limits[] = {100, 250, INT_MAX};
    const double residential_rates[] = {1.50, 2.25, 3.00};
    const int residential_slabs = sizeof(residential_limits) / sizeof(residential_limits[0]);

    printf("Electricity Bill - Generic Calculator\n");
    printf("------------------------------------\n");

    /* Read consumer number */
    printf("Consumer number: ");
    if (scanf("%d", &consumerNumber) != 1) {
        printf("Invalid consumer number. Exiting.\n");
        return 1;
    }
    flush_stdin();

    /* Read consumer type */
    printf("Consumer type (R=Residential, B=Business): ");
    if (scanf("%c", &consumerType) != 1) {
        printf("Invalid input. Exiting.\n");
        return 1;
    }
    flush_stdin();
    consumerType = (char)toupper((unsigned char)consumerType);
    if (consumerType != 'R' && consumerType != 'B') {
        printf("Invalid consumer type '%c'. Use R or B.\n", consumerType);
        return 1;
    }

    /* Read previous and present readings with basic validation */
    printf("Previous month reading: ");
    if (scanf("%d", &prevReading) != 1) {
        printf("Invalid reading. Exiting.\n");
        return 1;
    }
    flush_stdin();

    printf("Present month reading: ");
    if (scanf("%d", &presReading) != 1) {
        printf("Invalid reading. Exiting.\n");
        return 1;
    }
    flush_stdin();

    if (presReading <= prevReading) {
        printf("Present reading must be greater than previous reading.\n");
        return 1;
    }

    int units = presReading - prevReading;

    double bill = 0.0;
    if (consumerType == 'B') {
        bill = computeBill(units, business_limits, business_rates, business_slabs);
    } else {
        bill = computeBill(units, residential_limits, residential_rates, residential_slabs);
    }

    printf("\n===============================================\n");
    printf("           ELECTRICITY BILL RECEIPT             \n");
    printf("===============================================\n");
    printf("Consumer Number    : %d\n", consumerNumber);
    printf("Consumer Type      : %s\n", consumerType == 'B' ? "Business" : "Residential");
    printf("Number of Units    : %d\n", units);
    printf("Bill Amount (Rs.)  : %.2f\n", bill);
    printf("===============================================\n");

    return 0;
}
