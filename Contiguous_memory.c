#include <stdio.h>
#include <stdbool.h>

#define max 25

typedef struct MemoryBlock {
    int start;
    int size;
    bool allocated;
} MemoryBlock;

MemoryBlock memory[max];
int nf;

void initializeMemory() {
    for (int i = 0; i < max; i++) {
        memory[i].start = -1;
        memory[i].size = 0;
        memory[i].allocated = false;
    }
}

int worstFit(int size) {
    int index = -1;
    int maxFreeSize = -1;

    for (int i = 0; i < max; i++) {
        if (!memory[i].allocated && memory[i].size >= size) {
            if (memory[i].size > maxFreeSize) {
                maxFreeSize = memory[i].size;
                index = i;
            }
        }
    }

    return index;
}

int bestFit(int size) {
    int index = -1;
    int minFreeSize = max + 1;

    for (int i = 0; i < max; i++) {
        if (!memory[i].allocated && memory[i].size >= size) {
            if (memory[i].size < minFreeSize) {
                minFreeSize = memory[i].size;
                index = i;
            }
        }
    }

    return index;
}

int firstFit(int size) {
    int index = -1;

    for (int i = 0; i < max; i++) {
        if (!memory[i].allocated && memory[i].size >= size) {
            index = i;
            break;
        }
    }

    return index;
}

void displayMemory() {
    printf("\nMemory Status:\n");
    for (int i = 0; i < max; i++) {
        if (memory[i].size > 0) {
            printf("[%d] - %s, Start: %d, Size: %d\n", i, memory[i].allocated ? "Allocated" : "Free", memory[i].start, memory[i].size);
        }
    }
}

int main() {
    int nb, fitType;

    printf("Enter the number of blocks in memory: ");
    scanf("%d", &nb);

    initializeMemory();

    printf("Enter the sizes of blocks:\n");
    for (int i = 0; i < nb; i++) {
        printf("Block %d: ", i);
        scanf("%d", &memory[i].size);
        memory[i].start = 0;
    }

    printf("Enter the number of files: ");
    scanf("%d", &nf);

    printf("Enter the sizes of files:\n");
    for (int i = 0; i < nf; i++) {
        printf("File %d: ", i);
        scanf("%d", &memory[i + nb].size);
    }

    printf("\nChoose Memory Allocation Technique:\n");
    printf("1. Worst-Fit\n");
    printf("2. Best-Fit\n");
    printf("3. First-Fit\n");
    printf("Enter your choice: ");
    scanf("%d", &fitType);

    int index;
    for (int i = 0; i < nf; i++) {
        switch (fitType) {
            case 1:
                index = worstFit(memory[i + nb].size);
                break;
            case 2:
                index = bestFit(memory[i + nb].size);
                break;
            case 3:
                index = firstFit(memory[i + nb].size);
                break;
            default:
                printf("Invalid choice. Exiting the program.\n");
                return 1;
        }

        if (index != -1) {
            memory[index].allocated = true;
            memory[index].start = index;
            memory[index].size = memory[i + nb].size;
        } else {
            printf("Memory allocation failed for file %d. No suitable block found.\n", i + 1);
        }
    }

    printf("\nMemory Allocation Results:\n");
    printf("File No\t\tFile Size \n");
    for (int i = 0; i < nf; i++) {
        printf("%d\t\t%d\t\n", i + 1, memory[i + nb].size);
    }

    displayMemory();

    return 0;
}
