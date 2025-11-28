#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STUDENTS 10
#define MAX_NAME_LEN 50
#define MAX_BRANCH_LEN 30

// Structure to store student information
typedef struct {
    int studentNumber;
    char studentName[MAX_NAME_LEN];
    char branchName[MAX_BRANCH_LEN];
    int marks[3];  // Marks in 3 subjects
    int totalMarks;
    int rank;
} Student;

// Function to read student data
void readStudentData(Student students[], int numStudents) {
    printf("\n========== READING STUDENT DATA ==========\n");
    for (int i = 0; i < numStudents; i++) {
        printf("\nEnter details for Student %d:\n", i + 1);
        
        printf("Student Number: ");
        scanf("%d", &students[i].studentNumber);
        
        printf("Student Name: ");
        scanf("%s", students[i].studentName);
        
        printf("Branch Name: ");
        scanf("%s", students[i].branchName);
        
        printf("Marks in Subject 1: ");
        scanf("%d", &students[i].marks[0]);
        
        printf("Marks in Subject 2: ");
        scanf("%d", &students[i].marks[1]);
        
        printf("Marks in Subject 3: ");
        scanf("%d", &students[i].marks[2]);
        
        // Calculate total marks
        students[i].totalMarks = students[i].marks[0] + students[i].marks[1] + students[i].marks[2];
    }
}

// Function to generate random student data for testing
void generateRandomStudentData(Student students[], int numStudents) {
    // Sample names
    const char *names[] = {"Rajesh", "Priya", "Amit", "Neha", "Vikram", "Anjali", "Arjun", "Deepika", "Rohan", "Shruti"};
    
    // Sample branches
    const char *branches[] = {"CSE", "ECE", "ME", "EE", "CE"};
    
    printf("\n========== GENERATING RANDOM STUDENT DATA ==========\n");
    
    // Seed the random number generator with current time
    srand((unsigned int)time(NULL));
    
    for (int i = 0; i < numStudents; i++) {
        // Generate student number (100-109)
        students[i].studentNumber = 100 + i;
        
        // Assign random name
        strcpy(students[i].studentName, names[i % 10]);
        
        // Assign random branch
        strcpy(students[i].branchName, branches[rand() % 5]);
        
        // Generate random marks for 3 subjects (between 40 and 100)
        students[i].marks[0] = 40 + (rand() % 61);  // 40-100
        students[i].marks[1] = 40 + (rand() % 61);  // 40-100
        students[i].marks[2] = 40 + (rand() % 61);  // 40-100
        
        // Calculate total marks
        students[i].totalMarks = students[i].marks[0] + students[i].marks[1] + students[i].marks[2];
        
        printf("Student %d: %s (%s) - Marks: %d, %d, %d | Total: %d\n", 
               students[i].studentNumber, 
               students[i].studentName, 
               students[i].branchName, 
               students[i].marks[0], 
               students[i].marks[1], 
               students[i].marks[2], 
               students[i].totalMarks);
    }
    printf("Random data generation completed!\n");
}

// Comparator function for sorting in descending order (for ranking)
int compareStudents(const void *a, const void *b) {
    Student *student1 = (Student *)a;
    Student *student2 = (Student *)b;
    
    // Sort in descending order of total marks
    if (student2->totalMarks != student1->totalMarks) {
        return student2->totalMarks - student1->totalMarks;
    }
    // If marks are equal, sort by student number
    return student1->studentNumber - student2->studentNumber;
}

// Function to assign ranks to students
void assignRanks(Student students[], int numStudents) {
    // Sort students by total marks in descending order
    qsort(students, numStudents, sizeof(Student), compareStudents);
    
    // Assign ranks
    int currentRank = 1;
    for (int i = 0; i < numStudents; i++) {
        if (i > 0 && students[i].totalMarks < students[i - 1].totalMarks) {
            currentRank = i + 1;
        }
        students[i].rank = currentRank;
    }
}

// Function to display student data
void displayStudentData(Student students[], int numStudents) {
    printf("\n\n========== STUDENT MANAGEMENT SYSTEM REPORT ==========\n");
    printf("%-15s%-20s%-20s%-15s%-10s\n", "Student No.", "Name", "Branch", "Total Marks", "Rank");
    printf("----------------------------------------------------------------------\n");
    
    for (int i = 0; i < numStudents; i++) {
        printf("%-15d%-20s%-20s%-15d%-10d\n", 
               students[i].studentNumber, 
               students[i].studentName, 
               students[i].branchName, 
               students[i].totalMarks, 
               students[i].rank);
    }
    printf("----------------------------------------------------------------------\n");
}

// Function to display detailed report
void displayDetailedReport(Student students[], int numStudents) {
    printf("\n\n========== DETAILED STUDENT REPORT ==========\n");
    for (int i = 0; i < numStudents; i++) {
        printf("\n--- Student %d (Rank: %d) ---\n", i + 1, students[i].rank);
        printf("Student Number: %d\n", students[i].studentNumber);
        printf("Student Name: %s\n", students[i].studentName);
        printf("Branch: %s\n", students[i].branchName);
        printf("Subject 1 Marks: %d\n", students[i].marks[0]);
        printf("Subject 2 Marks: %d\n", students[i].marks[1]);
        printf("Subject 3 Marks: %d\n", students[i].marks[2]);
        printf("Total Marks: %d\n", students[i].totalMarks);
    }
}

// Comparator function for sorting by rank in ascending order
int compareByRank(const void *a, const void *b) {
    Student *student1 = (Student *)a;
    Student *student2 = (Student *)b;
    
    // Sort in ascending order of rank
    return student1->rank - student2->rank;
}

// Function to display student table ordered by rank (ascending)
void displayStudentsByRank(Student students[], int numStudents) {
    printf("\n\n========== STUDENT DATA - ORDERED BY RANK (1st to Last) ==========\n");
    printf("%-6s%-15s%-20s%-20s%-15s%-10s\n", "Rank", "Student No.", "Name", "Branch", "Total Marks", "Subjects");
    printf("------------------------------------------------------------------------------------\n");
    
    // Create a copy of students array to sort without affecting original
    Student *sortedStudents = (Student *)malloc(numStudents * sizeof(Student));
    for (int i = 0; i < numStudents; i++) {
        sortedStudents[i] = students[i];
    }
    
    // Sort by rank in ascending order
    qsort(sortedStudents, numStudents, sizeof(Student), compareByRank);
    
    // Display sorted data
    for (int i = 0; i < numStudents; i++) {
        printf("%-6d%-15d%-20s%-20s%-15d%d,%d,%d\n", 
               sortedStudents[i].rank,
               sortedStudents[i].studentNumber,
               sortedStudents[i].studentName,
               sortedStudents[i].branchName,
               sortedStudents[i].totalMarks,
               sortedStudents[i].marks[0],
               sortedStudents[i].marks[1],
               sortedStudents[i].marks[2]);
    }
    printf("------------------------------------------------------------------------------------\n");
    
    // Free allocated memory
    free(sortedStudents);
}

// Main function
int main() {
    Student students[MAX_STUDENTS];
    int numStudents = MAX_STUDENTS;
    
    printf("====================================\n");
    printf("  STUDENT MANAGEMENT SYSTEM v1.0\n");
    printf("====================================\n");
    
    int choice;
    printf("\nSelect input method:\n");
    printf("1. Manual Input (Enter data for each student)\n");
    printf("2. Random Data (Auto-generate student data)\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        // Read student data manually
        readStudentData(students, numStudents);
    } else if (choice == 2) {
        // Generate random student data
        generateRandomStudentData(students, numStudents);
    } else {
        printf("Invalid choice! Using random data by default.\n");
        generateRandomStudentData(students, numStudents);
    }
    
    // Assign ranks based on total marks
    assignRanks(students, numStudents);
    
    // Display summary report
    displayStudentData(students, numStudents);
    
    // Display students ordered by rank
    displayStudentsByRank(students, numStudents);
    
    // Display detailed report
    displayDetailedReport(students, numStudents);
    
    printf("\n====================================\n");
    printf("Program completed successfully!\n");
    printf("====================================\n");
    
    return 0;
}
