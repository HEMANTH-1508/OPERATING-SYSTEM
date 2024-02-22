#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIRECTORIES 100
#define MAX_FILES_PER_DIRECTORY 100
#define MAX_FILENAME 50

// Structure to represent a file
struct File 
{
    char name[MAX_FILENAME];
};

// Structure to represent a directory
struct Directory 
{
    char name[MAX_FILENAME];
    struct File files[MAX_FILES_PER_DIRECTORY];
    int file_count;
};

// Structure to represent the file system
struct FileSystem 
{
    struct Directory directories[MAX_DIRECTORIES];
    int directory_count;
};

// Function to initialize the file system
void initializeFileSystem(struct FileSystem *fs) 
{
    fs->directory_count = 0;
}

// Function to create a new directory
void createDirectory(struct FileSystem *fs, char *dirname) 
{
    if (fs->directory_count < MAX_DIRECTORIES) 
    {
        struct Directory *new_directory = &fs->directories[fs->directory_count];
        strcpy(new_directory->name, dirname);
        new_directory->file_count = 0;
        fs->directory_count++;
        printf("Directory '%s' created successfully.\n", dirname);
    } 
    else 
    {
        printf("Cannot create directory. Maximum directory limit reached.\n");
    }
}

// Function to add a file to a directory
void addFile(struct FileSystem *fs, char *dirname, char *filename) 
{
    int found = 0;
    for (int i = 0; i < fs->directory_count; i++) {
        if (strcmp(fs->directories[i].name, dirname) == 0) {
            if (fs->directories[i].file_count < MAX_FILES_PER_DIRECTORY) 
            {
                struct Directory *dir = &fs->directories[i];
                strcpy(dir->files[dir->file_count].name, filename);
                dir->file_count++;
                found = 1;
                printf("File '%s' added to directory '%s'.\n", filename, dirname);
            } 
            else 
            {
                printf("Cannot add file. Maximum file limit reached for directory '%s'.\n", dirname);
            }
            break;
        }
    }
    if (!found) 
    {
        printf("Directory '%s' not found.\n", dirname);
    }
}

// Function to list files in a directory
void listFiles(struct FileSystem *fs, char *dirname) 
{
    int found = 0;
    for (int i = 0; i < fs->directory_count; i++) 
    {
        if (strcmp(fs->directories[i].name, dirname) == 0) 
        {
            found = 1;
            printf("Files in directory '%s':\n", dirname);
            for (int j = 0; j < fs->directories[i].file_count; j++) 
            {
                printf("%s\n", fs->directories[i].files[j].name);
            }
            break;
        }
    }
    if (!found) 
    {
        printf("Directory '%s' not found.\n", dirname);
    }
}

int main() {
    struct FileSystem fs;
    initializeFileSystem(&fs);

    int choice;
    char dirname[MAX_FILENAME];
    char filename[MAX_FILENAME];

    do {
        printf("\nTwo-Level Directory Operations\n");
        printf("1. Create Directory\n");
        printf("2. Add File\n");
        printf("3. List Files\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                printf("Enter directory name to create: ");
                scanf("%s", dirname);
                createDirectory(&fs, dirname);
                break;
            case 2:
                printf("Enter directory name to add file: ");
                scanf("%s", dirname);
                printf("Enter filename to add: ");
                scanf("%s", filename);
                addFile(&fs, dirname, filename);
                break;
            case 3:
                printf("Enter directory name to list files: ");
                scanf("%s", dirname);
                listFiles(&fs, dirname);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
