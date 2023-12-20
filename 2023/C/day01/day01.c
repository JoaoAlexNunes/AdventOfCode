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
char *read_from_file(char *filename);

// Part 1
typedef struct
{
    char num;
    int is_initted;
} Num;

int main()
{
    char *contents = read_from_file(TEST_FILE);
    // char *contents = read_from_file(INPUT_FILE);
    //  printf("%s\n", contents);

    // Calculate results for Part One and Part Two
    int resultPart1 = part1(contents);
    int resultPart2 = part2(contents);

    // Output the results
    printf("(%d,%d)\n", resultPart1, resultPart2);

    return 0;
}

// Implementation for part1 function
int part1(char *contents)
{
    Num first = {
        .is_initted = 0,
    };
    Num last = {
        .is_initted = 0,
    };

    int total = 0;

    for (size_t i = 0; contents[i] != '\0'; i++)
    {
        if (isdigit(contents[i]))
        {
            if (first.is_initted == 0)
            {
                first.is_initted = 1;
                first.num = contents[i] - '0';
            }
            last.num = contents[i] - '0';
        }

        if (contents[i] == '\n')
        {
            printf("%d\n", first.num);
            total += (first.num * 10) + last.num;
            first.is_initted = 0;
            last.is_initted = 0;
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
char *read_from_file(char *filename)
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
