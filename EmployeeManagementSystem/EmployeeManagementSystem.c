#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MAX_EMPLOYEES 100
#define MAX_NAME_LEN 50

// Structure to store employee information
typedef struct {
    int employeeNumber;
    char employeeName[MAX_NAME_LEN];
    char grade;  // A, B, or C
    double basicSalary;
    double da;   // Dearness Allowance
    double hra;  // House Rent Allowance
    double pf;   // Provident Fund
    double it;   // Income Tax
    double grossSalary;
    double netSalary;
} Employee;

// Structure to store grade percentages
typedef struct {
    char grade;
    double daPercent;
    double hraPercent;
    double pfPercent;
    double itPercent;
} GradePercentage;

// Initialize grade percentages as per given table
void initializeGradePercentages(GradePercentage gradeTable[]) {
    gradeTable[0].grade = 'A';
    gradeTable[0].daPercent = 87.0;
    gradeTable[0].hraPercent = 14.5;
    gradeTable[0].pfPercent = 0.0;
    gradeTable[0].itPercent = 20.0;
    
    gradeTable[1].grade = 'B';
    gradeTable[1].daPercent = 72.0;
    gradeTable[1].hraPercent = 12.0;
    gradeTable[1].pfPercent = 5.5;
    gradeTable[1].itPercent = 15.5;
    
    gradeTable[2].grade = 'C';
    gradeTable[2].daPercent = 68.0;
    gradeTable[2].hraPercent = 10.0;
    gradeTable[2].pfPercent = 7.5;
    gradeTable[2].itPercent = 0.0;
}

// Get grade percentages based on employee grade
GradePercentage getGradePercentage(char grade, GradePercentage gradeTable[]) {
    for (int i = 0; i < 3; i++) {
        if (gradeTable[i].grade == grade) {
            return gradeTable[i];
        }
    }
    // Default to grade C if not found
    return gradeTable[2];
}

// Calculate salary components
void calculateSalary(Employee *emp, GradePercentage gradeTable[]) {
    GradePercentage gradePercentage = getGradePercentage(emp->grade, gradeTable);
    
    // Calculate allowances as percentage of basic salary
    emp->da = (emp->basicSalary * gradePercentage.daPercent) / 100.0;
    emp->hra = (emp->basicSalary * gradePercentage.hraPercent) / 100.0;
    
    // Calculate gross salary
    emp->grossSalary = emp->basicSalary + emp->da + emp->hra;
    
    // Calculate deductions as percentage of basic salary
    emp->pf = (emp->basicSalary * gradePercentage.pfPercent) / 100.0;
    emp->it = (emp->basicSalary * gradePercentage.itPercent) / 100.0;
    
    // Calculate net salary
    emp->netSalary = emp->grossSalary - emp->pf - emp->it;
}

// Function to read employee data manually
void readEmployeeData(Employee employees[], int *numEmployees, GradePercentage gradeTable[]) {
    printf("\n========== READING EMPLOYEE DATA ==========\n");
    printf("Enter number of employees (max %d): ", MAX_EMPLOYEES);
    scanf("%d", numEmployees);
    
    if (*numEmployees > MAX_EMPLOYEES) {
        printf("Number of employees exceeds maximum limit. Setting to %d\n", MAX_EMPLOYEES);
        *numEmployees = MAX_EMPLOYEES;
    }
    
    for (int i = 0; i < *numEmployees; i++) {
        printf("\n--- Employee %d ---\n", i + 1);
        
        printf("Employee Number: ");
        scanf("%d", &employees[i].employeeNumber);
        
        printf("Employee Name: ");
        scanf("%s", employees[i].employeeName);
        
        printf("Grade (A/B/C): ");
        scanf(" %c", &employees[i].grade);
        employees[i].grade = toupper(employees[i].grade);
        
        printf("Basic Salary: ");
        scanf("%lf", &employees[i].basicSalary);
        
        // Calculate all salary components
        calculateSalary(&employees[i], gradeTable);
    }
    printf("\nData entry completed!\n");
}

// Function to generate random employee data
void generateRandomEmployeeData(Employee employees[], int *numEmployees, GradePercentage gradeTable[]) {
    const char *names[] = {"Rajesh Kumar", "Priya Singh", "Amit Patel", "Neha Verma", "Vikram Reddy",
                           "Anjali Gupta", "Arjun Nair", "Deepika Sharma", "Rohan Kapoor", "Shruti Iyer"};
    char grades[] = {'A', 'B', 'C'};
    
    *numEmployees = 10;
    printf("\n========== GENERATING RANDOM EMPLOYEE DATA ==========\n");
    
    srand((unsigned int)time(NULL));
    
    for (int i = 0; i < *numEmployees; i++) {
        employees[i].employeeNumber = 1001 + i;
        strcpy(employees[i].employeeName, names[i % 10]);
        employees[i].grade = grades[rand() % 3];
        
        // Generate random basic salary between 20000 and 80000
        employees[i].basicSalary = 20000 + (rand() % 60001);
        
        // Calculate all salary components
        calculateSalary(&employees[i], gradeTable);
        
        printf("Employee %d: %s (Grade %c) - Basic: %.2f | Gross: %.2f | Net: %.2f\n",
               employees[i].employeeNumber,
               employees[i].employeeName,
               employees[i].grade,
               employees[i].basicSalary,
               employees[i].grossSalary,
               employees[i].netSalary);
    }
    printf("Random data generation completed!\n");
}

// Function to display employee salary slip
void displaySalarySlip(Employee emp) {
    printf("\n====================================================\n");
    printf("              EMPLOYEE SALARY SLIP                     ║\n");
    printf("====================================================\n");
    printf("Employee Number:  %d\n", emp.employeeNumber);
    printf("Employee Name:    %s\n", emp.employeeName);
    printf("Grade:            %c\n", emp.grade);
    printf("=========================================================\n");
    printf("EARNINGS:\n");
    printf("  Basic Salary:           Rs. %.2f\n", emp.basicSalary);
    printf("  Dearness Allowance:     Rs. %.2f\n", emp.da);
    printf("  House Rent Allowance:   Rs. %.2f\n", emp.hra);
    printf("  ====================================\n");
    printf("  Gross Salary:           Rs. %.2f\n", emp.grossSalary);
    printf("=========================================================\n");
    printf("DEDUCTIONS:\n");
    printf("  Provident Fund (PF):    Rs. %.2f\n", emp.pf);
    printf("  Income Tax (IT):        Rs. %.2f\n", emp.it);
    printf("  ====================================\n");
    printf("  Total Deductions:       Rs. %.2f\n", emp.pf + emp.it);
    printf("=========================================================\n");
    printf("  NET SALARY:             Rs. %.2f\n", emp.netSalary);
    printf("====================================================\n");
}

// Function to display summary table
void displayEmployeeSummaryTable(Employee employees[], int numEmployees) {
    printf("\n\n========== EMPLOYEE MANAGEMENT SYSTEM - SUMMARY REPORT ==========\n");
    printf("%-8s%-20s%-7s%-15s%-15s%-15s%-15s\n", 
           "Emp No.", "Name", "Grade", "Basic Sal.", "Gross Sal.", "Deductions", "Net Sal.");
    printf("=====================================================================================\n");
    
    for (int i = 0; i < numEmployees; i++) {
        printf("%-8d%-20s%-7c%-15.2f%-15.2f%-15.2f%-15.2f\n",
               employees[i].employeeNumber,
               employees[i].employeeName,
               employees[i].grade,
               employees[i].basicSalary,
               employees[i].grossSalary,
               employees[i].pf + employees[i].it,
               employees[i].netSalary);
    }
    printf("=====================================================================================\n");
}

// Function to display detailed breakdown table
void displayDetailedBreakdownTable(Employee employees[], int numEmployees) {
    printf("\n\n========== DETAILED SALARY BREAKDOWN ==========\n");
    printf("%-8s%-20s%-7s%-12s%-12s%-12s%-12s%-12s%-12s%-12s\n",
           "Emp No.", "Name", "Grade", "Basic", "DA", "HRA", "Gross", "PF", "IT", "Net");
    printf("==========================================================================================================\n");
    
    for (int i = 0; i < numEmployees; i++) {
        printf("%-8d%-20s%-7c%-12.2f%-12.2f%-12.2f%-12.2f%-12.2f%-12.2f%-12.2f\n",
               employees[i].employeeNumber,
               employees[i].employeeName,
               employees[i].grade,
               employees[i].basicSalary,
               employees[i].da,
               employees[i].hra,
               employees[i].grossSalary,
               employees[i].pf,
               employees[i].it,
               employees[i].netSalary);
    }
    printf("==========================================================================================================\n");
}

// Function to display grade-wise summary
void displayGradeWiseSummary(Employee employees[], int numEmployees) {
    printf("\n\n========== GRADE-WISE SUMMARY ==========\n");
    
    for (char grade = 'A'; grade <= 'C'; grade++) {
        double totalBasic = 0, totalGross = 0, totalNet = 0;
        int count = 0;
        
        for (int i = 0; i < numEmployees; i++) {
            if (employees[i].grade == grade) {
                totalBasic += employees[i].basicSalary;
                totalGross += employees[i].grossSalary;
                totalNet += employees[i].netSalary;
                count++;
            }
        }
        
        if (count > 0) {
            printf("\nGrade %c (%d employees):\n", grade, count);
            printf("  Total Basic Salary:  Rs. %.2f\n", totalBasic);
            printf("  Total Gross Salary:  Rs. %.2f\n", totalGross);
            printf("  Total Net Salary:    Rs. %.2f\n", totalNet);
            printf("  Average Net Salary:  Rs. %.2f\n", totalNet / count);
        }
    }
    printf("\n");
}

// Function to search and display employee details
void searchAndDisplayEmployee(Employee employees[], int numEmployees) {
    int empNo;
    printf("\nEnter Employee Number to search: ");
    scanf("%d", &empNo);
    
    for (int i = 0; i < numEmployees; i++) {
        if (employees[i].employeeNumber == empNo) {
            displaySalarySlip(employees[i]);
            return;
        }
    }
    printf("Employee with number %d not found!\n", empNo);
}

// Main function
int main() {
    Employee employees[MAX_EMPLOYEES];
    int numEmployees = 0;
    GradePercentage gradeTable[3];
    
    // Initialize grade percentages
    initializeGradePercentages(gradeTable);
    
    printf("====================================================\n");
    printf("    EMPLOYEE MANAGEMENT SYSTEM v1.0\n");
    printf("====================================================\n");
    
    // Display grade percentage table
    printf("\nGrade Percentage Table:\n");
    printf("=====================================================\n");
    printf("Grade    DA %%      HRA %%     PF %%      IT %%\n");
    printf("=====================================================\n");
    for (int i = 0; i < 3; i++) {
        printf("  %c      %.1f      %.1f      %.1f      %.1f\n",
               gradeTable[i].grade,
               gradeTable[i].daPercent,
               gradeTable[i].hraPercent,
               gradeTable[i].pfPercent,
               gradeTable[i].itPercent);
    }
    printf("=====================================================\n");
    
    int choice;
    printf("\nSelect input method:\n");
    printf("1. Manual Input (Enter employee data)\n");
    printf("2. Random Data (Auto-generate employee data)\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        readEmployeeData(employees, &numEmployees, gradeTable);
    } else if (choice == 2) {
        generateRandomEmployeeData(employees, &numEmployees, gradeTable);
    } else {
        printf("Invalid choice! Using random data by default.\n");
        generateRandomEmployeeData(employees, &numEmployees, gradeTable);
    }
    
    // Display all reports
    displayEmployeeSummaryTable(employees, numEmployees);
    displayDetailedBreakdownTable(employees, numEmployees);
    displayGradeWiseSummary(employees, numEmployees);
    
    // Search and display individual salary slip
    char searchAgain = 'Y';
    while (searchAgain == 'Y' || searchAgain == 'y') {
        searchAndDisplayEmployee(employees, numEmployees);
        printf("\nSearch another employee? (Y/N): ");
        scanf(" %c", &searchAgain);
    }
    
    printf("\n====================================================\n");
    printf("Program completed successfully!\n");
    printf("====================================================\n");
    
    return 0;
}
