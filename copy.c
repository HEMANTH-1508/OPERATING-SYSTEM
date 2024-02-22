#include <stdio.h>
#include <stdlib.h>

int main() 
{
    FILE *sourceFile, *targetFile;
    char sourceFilename[100], targetFilename[100];
    char c;

    // Input source filename
    printf("Enter the source filename: ");
    scanf("%s", sourceFilename);

    // Open source file for reading
    sourceFile = fopen(sourceFilename, "r");
    if (sourceFile == NULL) 
    {
        printf("Cannot open source file %s\n", sourceFilename);
        exit(1);
    }

    // Input target filename
    printf("Enter the target filename: ");
    scanf("%s", targetFilename);

    // Open target file for writing
    targetFile = fopen(targetFilename, "w");
    if (targetFile == NULL) 
    {
        printf("Cannot open target file %s\n", targetFilename);
        fclose(sourceFile); // Close the source file before exiting
        exit(1);
    }

    // Copy contents from source file to target file
    while ((c = fgetc(sourceFile)) != EOF) 
    {
        fputc(c, targetFile);
    }

    // Close both files
    fclose(sourceFile);
    fclose(targetFile);

    printf("Contents copied from %s to %s\n", sourceFilename, targetFilename);

    return 0;
}
