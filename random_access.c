#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "employee_records.dat"
#define MAX_EMPLOYEES 100
#define MAX_NAME_LENGTH 50

// Structure to represent an employee
struct Employee 
{
    int id;
    char name[MAX_NAME_LENGTH];
    float salary;
};

// Function to display employee details
void displayEmployee(struct Employee emp) {
    printf("Employee ID: %d\n", emp.id);
    printf("Name: %s\n", emp.name);
    printf("Salary: %.2f\n", emp.salary);
    printf("----------------------------------------\n");
}

// Function to add a new employee to the file
void addEmployee() 
{
    FILE *file = fopen(FILENAME, "ab");
    if (file == NULL) 
    {
        printf("Error opening file!\n");
        return;
    }

    struct Employee emp;
    printf("Enter employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter employee name: ");
    scanf("%s", emp.name);
    printf("Enter employee salary: ");
    scanf("%f", &emp.salary);

    fwrite(&emp, sizeof(struct Employee), 1, file);
    fclose(file);
    printf("Employee added successfully!\n");
}

// Function to display all employee details from the file
void displayAllEmployees() {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Employee emp;
    while (fread(&emp, sizeof(struct Employee), 1, file) == 1) 
    {
        displayEmployee(emp);
    }
    fclose(file);
}

// Function to update employee details based on employee ID
void updateEmployee(int empId) {
    FILE *file = fopen(FILENAME, "rb+");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Employee emp;
    int found = 0;
    while (fread(&emp, sizeof(struct Employee), 1, file) == 1) 
    {
        if (emp.id == empId) 
        {
            found = 1;
            printf("Enter new name: ");
            scanf("%s", emp.name);
            printf("Enter new salary: ");
            scanf("%f", &emp.salary);

            fseek(file, -sizeof(struct Employee), SEEK_CUR);
            fwrite(&emp, sizeof(struct Employee), 1, file);
            printf("Employee details updated successfully!\n");
            break;
        }
    }
    if (!found) 
    {
        printf("Employee with ID %d not found!\n", empId);
    }
    fclose(file);
}

// Function to delete employee record based on employee ID
void deleteEmployee(int empId) 
{
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) 
    {
        printf("Error opening file!\n");
        return;
    }

    FILE *tempFile = fopen("temp.dat", "wb");
    if (tempFile == NULL) 
    {
        printf("Error creating temporary file!\n");
        fclose(file);
        return;
    }

    struct Employee emp;
    int found = 0;
    while (fread(&emp, sizeof(struct Employee), 1, file) == 1) 
    {
        if (emp.id == empId) 
        {
            found = 1;
            printf("Employee with ID %d deleted successfully!\n", empId);
        } 
        else 
        {
            fwrite(&emp, sizeof(struct Employee), 1, tempFile);
        }
    }
    if (!found) 
    {
        printf("Employee with ID %d not found!\n", empId);
    }

    fclose(file);
    fclose(tempFile);

    remove(FILENAME);
    rename("temp.dat", FILENAME);
}

int main() 
{
    int choice, empId;
    printf("Employee Record Management System\n");

    do {
        printf("\n1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Update Employee Details\n");
        printf("4. Delete Employee Record\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                addEmployee();
                break;
            case 2:
                displayAllEmployees();
                break;
            case 3:
                printf("Enter employee ID to update: ");
                scanf("%d", &empId);
                updateEmployee(empId);
                break;
            case 4:
                printf("Enter employee ID to delete: ");
                scanf("%d", &empId);
                deleteEmployee(empId);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
