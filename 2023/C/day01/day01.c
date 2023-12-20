#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Defines
#define TEST_FILE "testinput.txt"
#define INPUT_FILE "input.txt"
#define NUMBERS 9
#define MAX_LENGTH 5

// Structures
typedef struct
{
    char num;
    int isInitialized;
} Num;

typedef struct
{
    const char *word;
    int value;
} Mapnumbers;

// Main Functions prototypes
char *readFile(char *filename);
int part1(char *contents);
int part2(char *contents);

// Helper Functions prototypes
void processDigit(char ch, Num *first, Num *last, int *total);
int isInNumbers(char *word, int length, Mapnumbers *map);
int isWordNumeric(char *buffer, size_t buffer_index, Mapnumbers *map);

// Funtions
int main()
{
    char *contents = readFile(INPUT_FILE);

    // Calculate results for Part One and Part Two
    int resultPart1 = part1(contents);
    int resultPart2 = part2(contents);

    // Output the results
    printf("(%d,%d)\n", resultPart1, resultPart2);

    // Free contents
    free(contents);

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
    fclose(file);
    return contents;
}

void processDigit(char ch, Num *first, Num *last, int *total)
{
    if (isdigit(ch))
    {
        if (first->isInitialized == 0)
        {
            first->isInitialized = 1;
            first->num = ch - '0';
        }
        last->num = ch - '0';
    }

    if (ch == '\n')
    {
        *total += (first->num * 10) + last->num;
        first->isInitialized = 0;
        last->isInitialized = 0;
    }
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
        processDigit(contents[i], &first, &last, &total);
    }
    return total;
}

// Implementation for part2 function
int part2(char *contents)
{
    Num first = {
        .isInitialized = 0,
    };
    Num last = {
        .isInitialized = 0,
    };

    Mapnumbers map[NUMBERS] = {
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9},
    };

    int total = 0;

    for (size_t i = 0; contents[i] != '\0'; i++)
    {
        if (isalpha(contents[i]))
        {
            int value = isWordNumeric(contents, i, map);
            if (value != 0)
            {
                if (first.isInitialized == 0)
                {
                    first.isInitialized = 1;
                    first.num = value;
                }
                last.num = value;
            }
        }
        processDigit(contents[i], &first, &last, &total);
    }
    return total;
}

int isInNumbers(char *word, int length, Mapnumbers *map)
{
    word[length] = '\0';
    for (size_t i = 0; i < NUMBERS; i++)
    {
        if (strcmp(map[i].word, word) == 0)
        {
            return map[i].value;
        }
    }
    return 0;
}

int isWordNumeric(char *buffer, size_t buffer_index, Mapnumbers *map)
{
    char *num_word = malloc(sizeof(char) * MAX_LENGTH);
    for (size_t i = 0; i < MAX_LENGTH; i++)
    {
        num_word[i] = buffer[buffer_index];
        buffer_index++;
        int value = isInNumbers(num_word, i + 1, map);
        if (value != 0)
        {
            free(num_word);
            return value;
        }
    }
    free(num_word);
    return 0;
}
