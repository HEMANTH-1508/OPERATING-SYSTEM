#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_FILENAME 50

struct Directory {
    char files[MAX_FILES][MAX_FILENAME];
    int file_count;
};

void initializeDirectory(struct Directory *dir) {
    dir->file_count = 0;
}

void addFile(struct Directory *dir, char *filename) {
    if (dir->file_count < MAX_FILES) {
        strcpy(dir->files[dir->file_count], filename);
        dir->file_count++;
        printf("File '%s' added successfully.\n", filename);
    } else {
        printf("Directory is full. Cannot add file '%s'.\n", filename);
    }
}

void deleteFile(struct Directory *dir, char *filename) {
    int found = 0;
    for (int i = 0; i < dir->file_count; i++) {
        if (strcmp(dir->files[i], filename) == 0) {
            found = 1;
            printf("File '%s' deleted successfully.\n", filename);
            // Remove the file by shifting subsequent files
            for (int j = i; j < dir->file_count - 1; j++) {
                strcpy(dir->files[j], dir->files[j + 1]);
            }
            dir->file_count--;
            break;
        }
    }
    if (!found) {
        printf("File '%s' not found.\n", filename);
    }
}

void listFiles(struct Directory *dir) {
    printf("Files in the directory:\n");
    for (int i = 0; i < dir->file_count; i++) {
        printf("%s\n", dir->files[i]);
    }
}

int main() {
    struct Directory dir;
    initializeDirectory(&dir);

    int choice;
    char filename[MAX_FILENAME];

    do {
        printf("\nSingle-Level Directory Operations\n");
        printf("1. Add File\n");
        printf("2. Delete File\n");
        printf("3. List Files\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter filename to add: ");
                scanf("%s", filename);
                addFile(&dir, filename);
                break;
            case 2:
                printf("Enter filename to delete: ");
                scanf("%s", filename);
                deleteFile(&dir, filename);
                break;
            case 3:
                listFiles(&dir);
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
