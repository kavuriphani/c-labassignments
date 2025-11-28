#include <stdio.h>
#include <string.h>

typedef struct {
    int product_number;
    char product_name[128];
    char product_type; /* 'E' or 'M' */
    double price_per_unit;
    int quantity;
    double total_bill;
    double gst_percent;
    double gst_amount;
    double net_bill;
} Product;

static void flush_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) ;
}

static double lookup_gst(char type, double total) {
    if (type == 'E' || type == 'e') {
        if (total < 10000.0) return 10.0;
        if (total >= 10000.0 && total < 25000.0) return 12.5;
        if (total >= 25000.0 && total < 50000.0) return 16.25;
        return 18.0;
    } else if (type == 'M' || type == 'm') {
        if (total < 10000.0) return 0.0;
        if (total >= 10000.0 && total < 25000.0) return 2.5;
        if (total >= 25000.0 && total < 50000.0) return 3.25;
        return 5.0;
    }
    return 0.0; /* default if unknown type */
}

int main(void) {
    Product p = {0};

    printf("Enter Product number: ");
    if (scanf("%d", &p.product_number) != 1) return 1;
    flush_input();

    printf("Enter Product name: ");
    if (!fgets(p.product_name, sizeof p.product_name, stdin)) return 1;
    p.product_name[strcspn(p.product_name, "\r\n")] = '\0';

    printf("Enter Product type (E-Electronics / M-Medical): ");
    int ch = getchar();
    if (ch == EOF) return 1;
    p.product_type = (char)ch;
    flush_input();

    printf("Enter Price of each unit: ");
    if (scanf("%lf", &p.price_per_unit) != 1) return 1;
    printf("Enter Quantity purchased: ");
    if (scanf("%d", &p.quantity) != 1) return 1;

    p.total_bill = p.price_per_unit * (double)p.quantity;
    p.gst_percent = lookup_gst(p.product_type, p.total_bill);
    p.gst_amount = p.total_bill * p.gst_percent / 100.0;
    p.net_bill = p.total_bill + p.gst_amount;

    printf("\n--- Product Bill ---\n");
    printf("Product number : %d\n", p.product_number);
    printf("Product name   : %s\n", p.product_name);
    printf("Product type   : %c\n", p.product_type);
    printf("Unit price     : %.2f\n", p.price_per_unit);
    printf("Quantity       : %d\n", p.quantity);
    printf("Total bill     : %.2f\n", p.total_bill);
    printf("GST %% (rate)   : %.2f%%\n", p.gst_percent);
    printf("GST amount     : %.2f\n", p.gst_amount);
    printf("Net bill       : %.2f\n", p.net_bill);

    return 0;
}
