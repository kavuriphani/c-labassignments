# Employee Management System

## Overview
A comprehensive C program to manage employee records, calculate salaries based on employee grades, and generate salary slips with detailed breakdowns.

## Features

### 1. **Salary Calculation**
- Calculates Gross Salary: Basic Salary + DA + HRA
- Calculates Net Salary: Gross Salary - PF - IT
- All allowances and deductions calculated as percentages of basic salary

### 2. **Grade-Based Calculation**
Uses the following percentage table:

| Grade | DA % | HRA % | PF % | IT % |
|-------|------|-------|------|------|
| A     | 87   | 14.5  | 0    | 20   |
| B     | 72   | 12    | 5.5  | 15.5 |
| C     | 68   | 10    | 7.5  | 0    |

### 3. **Data Management**
- **Manual Input**: Enter employee data for any number of employees (up to 100)
- **Random Generation**: Auto-generate sample employee data for testing

### 4. **Reports Generated**
- **Summary Report**: Quick overview of all employees
- **Detailed Breakdown**: All salary components for each employee
- **Grade-wise Analysis**: Summary statistics by employee grade
- **Individual Salary Slip**: Detailed slip for specific employee

### 5. **Employee Search**
- Search and display salary slip for any employee by their number

## Program Structure

### Main Data Structure
```c
typedef struct {
    int employeeNumber;
    char employeeName[50];
    char grade;           // A, B, or C
    double basicSalary;
    double da;           // Dearness Allowance
    double hra;          // House Rent Allowance
    double pf;           // Provident Fund
    double it;           // Income Tax
    double grossSalary;
    double netSalary;
} Employee;
```

### Grade Percentage Structure
```c
typedef struct {
    char grade;
    double daPercent;
    double hraPercent;
    double pfPercent;
    double itPercent;
} GradePercentage;
```

## Key Functions

1. **initializeGradePercentages()** - Sets up grade percentage table
2. **getGradePercentage()** - Retrieves percentages for a specific grade
3. **calculateSalary()** - Computes all salary components
4. **readEmployeeData()** - Reads employee data manually
5. **generateRandomEmployeeData()** - Creates sample data automatically
6. **displaySalarySlip()** - Shows formatted salary slip for one employee
7. **displayEmployeeSummaryTable()** - Summary report for all employees
8. **displayDetailedBreakdownTable()** - Detailed breakdown for all employees
9. **displayGradeWiseSummary()** - Statistics grouped by grade
10. **searchAndDisplayEmployee()** - Search and display individual employee

## Compilation & Execution

### On Linux/Mac
```bash
gcc EmployeeManagementSystem.c -o EmployeeManagementSystem
./EmployeeManagementSystem
```

### On Windows (MinGW)
```bash
gcc EmployeeManagementSystem.c -o EmployeeManagementSystem.exe
EmployeeManagementSystem.exe
```

## Usage Guide

1. **Start the program** - Choose between manual input or random data
2. **View Reports** - System automatically displays:
   - Summary table for all employees
   - Detailed breakdown of all salary components
   - Grade-wise statistical summary
3. **Search Employee** - Enter employee number to view their salary slip
4. **Repeat** - Can search multiple employees or exit

## Sample Output Sections

### Grade Percentage Table (displayed at startup)
```
Grade    DA %      HRA %     PF %      IT %
─────────────────────────────────────────────
  A      87.0      14.5      0.0       20.0
  B      72.0      12.0      5.5       15.5
  C      68.0      10.0      7.5       0.0
```

### Summary Report
```
Emp No.  Name                Grade  Basic Sal.   Gross Sal.   Deductions   Net Sal.
─────────────────────────────────────────────────────────────────────────────────
1001     Rajesh Kumar        A      50000.00     57250.00     10000.00     47250.00
1002     Priya Singh         B      45000.00     51570.00     7975.00      43595.00
```

### Individual Salary Slip
```
╔════════════════════════════════════════════════════════╗
║              EMPLOYEE SALARY SLIP                     ║
╚════════════════════════════════════════════════════════╝
Employee Number:  1001
Employee Name:    Rajesh Kumar
Grade:            A
───────────────────────────────────────────────────────
EARNINGS:
  Basic Salary:           Rs. 50000.00
  Dearness Allowance:     Rs. 43500.00
  House Rent Allowance:   Rs. 7250.00
  ────────────────────────────────────
  Gross Salary:           Rs. 100750.00
───────────────────────────────────────────────────────
DEDUCTIONS:
  Provident Fund (PF):    Rs. 0.00
  Income Tax (IT):        Rs. 10000.00
  ────────────────────────────────────
  Total Deductions:       Rs. 10000.00
───────────────────────────────────────────────────────
  NET SALARY:             Rs. 90750.00
═════════════════════════════════════════════════════════
```

### Grade-wise Summary
```
Grade A (3 employees):
  Total Basic Salary:  Rs. 150000.00
  Total Gross Salary:  Rs. 287750.00
  Total Net Salary:    Rs. 257250.00
  Average Net Salary:  Rs. 85750.00

Grade B (4 employees):
  Total Basic Salary:  Rs. 185000.00
  Total Gross Salary:  Rs. 213270.00
  Total Net Salary:    Rs. 184318.75
  Average Net Salary:  Rs. 46079.69
```

## Calculations Example

### For Grade A Employee with Basic Salary of 50,000:
- **DA** = 50,000 × 87% = 43,500
- **HRA** = 50,000 × 14.5% = 7,250
- **Gross Salary** = 50,000 + 43,500 + 7,250 = 100,750
- **PF** = 50,000 × 0% = 0
- **IT** = 50,000 × 20% = 10,000
- **Net Salary** = 100,750 - 0 - 10,000 = 90,750

### For Grade C Employee with Basic Salary of 40,000:
- **DA** = 40,000 × 68% = 27,200
- **HRA** = 40,000 × 10% = 4,000
- **Gross Salary** = 40,000 + 27,200 + 4,000 = 71,200
- **PF** = 40,000 × 7.5% = 3,000
- **IT** = 40,000 × 0% = 0
- **Net Salary** = 71,200 - 3,000 - 0 = 68,200

## Constraints
- Maximum 100 employees
- Supports grades A, B, and C only
- Employee name limited to 50 characters

## Time Complexity
- Adding employee: O(1)
- Searching employee: O(n)
- All reports: O(n)

## Space Complexity
- O(n) where n = number of employees

## Future Enhancements
- Save/load employee data from files
- Update/modify employee information
- Delete employee records
- Generate payroll for specific month
- Department-wise reports
- Performance bonuses
- Tax bracket calculations
