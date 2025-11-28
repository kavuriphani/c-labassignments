# Student Management System

## Overview
A C program to manage student records, calculate total marks, and assign ranks based on performance.

## Features
- **Read Student Data**: Input information for 10 students including:
  - Student Number
  - Student Name
  - Branch Name
  - Marks in 3 subjects

- **Calculate Total Marks**: Automatically calculates total marks for each student across 3 subjects

- **Assign Ranks**: Allocates ranks based on total marks in descending order
  - Students with higher total marks get better ranks
  - If marks are equal, students are ranked by student number

- **Display Reports**:
  - Summary report showing all students with their details and ranks
  - Detailed report with subject-wise marks

## Program Structure

### Data Structure
```c
typedef struct {
    int studentNumber;
    char studentName[50];
    char branchName[30];
    int marks[3];        // Marks in 3 subjects
    int totalMarks;      // Total marks (calculated)
    int rank;            // Rank (assigned)
} Student;
```

### Key Functions
1. **readStudentData()** - Reads input data for all students
2. **assignRanks()** - Calculates total marks and assigns ranks
3. **displayStudentData()** - Shows summary report
4. **displayDetailedReport()** - Shows detailed information
5. **compareStudents()** - Comparator for sorting

## Compilation & Execution

### On Linux/Mac
```bash
gcc StudentManagementSystem.c -o StudentManagementSystem
./StudentManagementSystem
```

### On Windows (MinGW)
```bash
gcc StudentManagementSystem.c -o StudentManagementSystem.exe
StudentManagementSystem.exe
```

## Sample Input/Output

### Input Example:
```
Student 1:
Student Number: 101
Student Name: Rajesh
Branch Name: CSE
Marks in Subject 1: 85
Marks in Subject 2: 90
Marks in Subject 3: 88

Student 2:
Student Number: 102
Student Name: Priya
Branch Name: ECE
Marks in Subject 1: 92
Marks in Subject 2: 88
Marks in Subject 3: 91
... (continue for 10 students)
```

### Output Example:
```
STUDENT MANAGEMENT SYSTEM REPORT
Student No.    Name                Branch              Total Marks Rank
----------------------------------------------------------
102            Priya               ECE                 271         1
101            Rajesh              CSE                 263         2
103            Amit                CSE                 258         3
...
```

## Algorithm

1. **Read Data**: Accept student details through user input
2. **Calculate Total**: Sum marks from 3 subjects for each student
3. **Sort**: Use qsort() to arrange students by total marks (descending)
4. **Assign Ranks**: 
   - Rank 1 to student with highest marks
   - If two students have same marks, give same rank
   - Next rank skips appropriately
5. **Display**: Show summary and detailed reports

## Constraints
- Maximum 10 students (can be modified by changing MAX_STUDENTS)
- Maximum 50 characters for student name
- Maximum 30 characters for branch name
- Marks assumed to be out of 100 for each subject

## Time Complexity
- Reading: O(n)
- Sorting: O(n log n)
- Display: O(n)
- Overall: O(n log n)

## Space Complexity
- O(n) where n = number of students

## Future Enhancements
- Add functionality to save/load data from files
- Search for specific student
- Update student records
- Delete student records
- Calculate GPA
- Generate merit list
- Add more subjects
