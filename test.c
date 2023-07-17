/*Code made by: Joona Manninen
17.7.2023 as part of systeemiohjelmointi course in LUT University*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 1024

void reverseLines(FILE *input, FILE *output)
{
    char **lines = NULL;
    char line[MAX_LINE_LENGTH];
    int numLines = 0;

    // Read lines from input file
    while (fgets(line, sizeof(line), input) != NULL)
    {

        // Remove newline character at the end
        line[strcspn(line, "\n")] = '\0';
        // Keyword for stopping the stdin reading.
        if (strcmp(line, "printNow") == 0)
        {
            printf("**************************\n");
            break;
        }

        // Allocate memory for the line
        char *newLine = malloc(strlen(line) + 1);
        if (newLine == NULL)
        {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }

        // Copy the line to allocated memory
        strcpy(newLine, line);

        // Resize the array to accommodate the new line
        char **temp = realloc(lines, (numLines + 1) * sizeof(char *));
        if (temp == NULL)
        {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        lines = temp;

        // Add the new line to the array
        lines[numLines++] = newLine;
    }

    // Print lines in reverse order
    for (int i = numLines - 1; i >= 0; i--)
    {
        fprintf(output, "%s\n", lines[i]);
    }

    // Free allocated memory
    for (int i = 0; i < numLines; i++)
    {
        free(lines[i]);
    }
    free(lines);
}

int main(int argc, char *argv[])
{
    FILE *input;
    FILE *output;

    // Check the number of command-line arguments
    if (argc == 1)
    {
        // No arguments, use stdin and stdout
        input = stdin;
        output = stdout;
        fprintf(stdout, ("Write lines you want to be reversed and print the lines with writing printNow:\n"));
    }
    else if (argc == 2)
    {
        // One argument, use input file and stdout
        input = fopen(argv[1], "r");
        output = stdout;
    }
    else if (argc == 3)
    {

        // Check if input and output files are the same
        if (strcmp(argv[1], argv[2]) == 0)
        {
            fprintf(stderr, "Input and output file must differ\n");
            exit(1);
        }

        // Two arguments, use input file and output file
        input = fopen(argv[1], "r");
        output = fopen(argv[2], "w");
    }
    else
    {
        // Too many arguments error.
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    // Check if files were opened successfully
    if (input == NULL)
    {
        fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
        exit(1);
    }
    if (output == NULL)
    {
        fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
        exit(1);
    }

    // Reverse the lines and print the result
    reverseLines(input, output);

    // Close files
    if (input != stdin)
    {
        fclose(input);
    }
    if (output != stdout)
    {
        fclose(output);
    }

    return 0;
}
