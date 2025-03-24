#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Characters allowed in the text file
char getRandomChar() {
    char chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 \n";
    return chars[rand() % (sizeof(chars) - 1)];
}

// Generate a text file with the given number of characters
void generateTextFile(const char *filename, int charCount) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    srand(time(NULL));
    for (int i = 0; i < charCount; i++) {
        fputc(getRandomChar(), file);
    }

    fclose(file);
}

// Count the number of lines (iterative)
int countLinesIterative(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return -1;

    int count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') count++;
    }

    fclose(file);
    return count;
}

// Count the number of lines (recursive)
int countLinesRecursive(FILE *file, int count) {
    char ch = fgetc(file);
    if (ch == EOF) return count;
    if (ch == '\n') count++;
    return countLinesRecursive(file, count);
}

// Count empty lines
int countEmptyLines(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return -1;

    int emptyCount = 0;
    char line[1024];

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '\n') emptyCount++;
    }

    fclose(file);
    return emptyCount;
}

// Measure execution time of a function
double measureExecutionTime(int (*func)(const char *), const char *filename) {
    clock_t start, end;
    start = clock();
    func(filename);
    end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC * 1000000; // Convert to microseconds
}

// Main function
int main() {
    const char *filename = "random_text.txt";
    int charCount;

    printf("Enter the number of characters to generate: ");
    scanf("%d", &charCount);

    // Generate text file
    generateTextFile(filename, charCount);
    printf("Text file '%s' generated with %d characters.\n", filename, charCount);

    // Measure execution time
    double timeIterative = measureExecutionTime(countLinesIterative, filename);

    // Recursive count requires opening file separately
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file for recursive count!\n");
        return 1;
    }
    clock_t start = clock();
    int linesRecursive = countLinesRecursive(file, 0);
    clock_t end = clock();
    fclose(file);
    double timeRecursive = ((double)(end - start)) / CLOCKS_PER_SEC * 1000000;

    // Count empty lines
    int emptyLines = countEmptyLines(filename);

    // Print results
    printf("\nLine count (iterative): %d (%.2f us)\n", countLinesIterative(filename), timeIterative);
    printf("Line count (recursive): %d (%.2f us)\n", linesRecursive, timeRecursive);
    printf("Empty line count: %d\n", emptyLines);

    return 0;
}
