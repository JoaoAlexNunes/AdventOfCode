#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#define TEST_FILE "testinput.txt"
#define INPUT_FILE "input.txt"

// Function prototypes
int part1(char *contents);
int part2(char *contents);
char *readFile(char *filename);

// Part 1
typedef struct
{
    char num;
    int isInitialized;
} Num;

int main()
{
    char *contents = readFile(TEST_FILE);
    // char *contents = readFile(INPUT_FILE);
    //  printf("%s\n", contents);

    // Calculate results for Part One and Part Two
    int resultPart1 = part1(contents);
    int resultPart2 = part2(contents);

    // Output the results
    printf("(%d,%d)\n", resultPart1, resultPart2);

    // Free contents
    free(contents);

    return 0;
}

// Implementation for part1 function
int part1(char *contents)
{
    Num first = {
        .isInitialized = 0,
    };
    Num last = {
        .isInitialized = 0,
    };

    int total = 0;

    for (size_t i = 0; contents[i] != '\0'; i++)
    {
        if (isdigit(contents[i]))
        {
            if (first.isInitialized == 0)
            {
                first.isInitialized = 1;
                first.num = contents[i] - '0';
            }
            last.num = contents[i] - '0';
        }

        if (contents[i] == '\n')
        {
            printf("%d\n", first.num);
            total += (first.num * 10) + last.num;
            first.isInitialized = 0;
            last.isInitialized = 0;
        }
    }
    return total;
}

// Implementation for part2 function
int part2(char *contents)
{
    // Your implementation here...
    return 0;
}

// Implementation for prepare function
char *readFile(char *filename)
{
    FILE *file = fopen(filename, "r");
    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *contents = malloc(sizeof(char) * length + 1);
    fread(contents, 1, length, file);
    contents[length] = '\0';
    return contents;
}
