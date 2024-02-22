#include <stdio.h>
#include <stdlib.h>

// Structure to represent a memory block
struct MemoryBlock 
{
    int size;
    int allocated;
    struct MemoryBlock *next;
};

// Function to initialize memory blocks
struct MemoryBlock *initializeMemory(int size) 
{
    struct MemoryBlock *memory = (struct MemoryBlock *)malloc(sizeof(struct MemoryBlock));
    memory->size = size;
    memory->allocated = 0;
    memory->next = NULL;
    return memory;
}

// Function to display memory blocks
void displayMemory(struct MemoryBlock *memory) 
{
    printf("Memory Blocks:\n");
    while (memory != NULL) 
    {
        printf("Size: %d, Allocated: %s\n", memory->size, memory->allocated ? "Yes" : "No");
        memory = memory->next;
    }
}

// Function to allocate memory using first fit strategy
void allocateFirstFit(struct MemoryBlock *memory, int size) 
{
    struct MemoryBlock *temp = memory;
    while (temp != NULL) 
    {
        if (!temp->allocated && temp->size >= size) 
        {
            temp->allocated = 1;
            printf("Memory allocated using First Fit\n");
            return;
        }
        temp = temp->next;
    }
    printf("Memory allocation failed using First Fit\n");
}

// Function to allocate memory using best fit strategy
void allocateBestFit(struct MemoryBlock *memory, int size) 
{
    struct MemoryBlock *temp = memory;
    struct MemoryBlock *bestFit = NULL;
    while (temp != NULL) 
    {
        if (!temp->allocated && temp->size >= size) 
        {
            if (bestFit == NULL || temp->size < bestFit->size) 
            {
                bestFit = temp;
            }
        }
        temp = temp->next;
    }
    if (bestFit != NULL) 
    {
        bestFit->allocated = 1;
        printf("Memory allocated using Best Fit\n");
    } 
    else 
    {
        printf("Memory allocation failed using Best Fit\n");
    }
}

// Function to allocate memory using worst fit strategy
void allocateWorstFit(struct MemoryBlock *memory, int size) 
{
    struct MemoryBlock *temp = memory;
    struct MemoryBlock *worstFit = NULL;
    while (temp != NULL) 
    {
        if (!temp->allocated && temp->size >= size) 
        {
            if (worstFit == NULL || temp->size > worstFit->size) 
            {
                worstFit = temp;
            }
        }
        temp = temp->next;
    }
    if (worstFit != NULL) 
    {
        worstFit->allocated = 1;
        printf("Memory allocated using Worst Fit\n");
    } 
    else 
    {
        printf("Memory allocation failed using Worst Fit\n");
    }
}

int main() 
{
    // Initialize memory blocks
    struct MemoryBlock *memory = initializeMemory(100);
    memory->next = initializeMemory(50);
    memory->next->next = initializeMemory(200);

    // Display initial memory state
    displayMemory(memory);

    // Allocate memory using different strategies
    allocateFirstFit(memory, 70);
    allocateBestFit(memory, 70);
    allocateWorstFit(memory, 70);

    // Display final memory state
    displayMemory(memory);

    return 0;
}
