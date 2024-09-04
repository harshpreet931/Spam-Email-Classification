#include "data_loader.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Loads email data and their labels from a txt file provided.
// Returns the number of emails loaded from the file.
int load_data(char (*emails)[MAX_EMAIL_SIZE], int *labels, char *filename) 
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) 
    {
        // Error opening file, return -1
        printf("Error opening file %s\n", filename);
        return -1;
    }
    printf("File opened successfully\n");

    int email_count = 0;
    char line[MAX_EMAIL_SIZE + 10];

    // Read each line from the file until the end or the maximum number of emails
    while (fgets(line, sizeof(line), file) && email_count < MAX_EMAILS) 
    {
        // Tokenize the line to get the label and the email content
        char *label_str = strtok(line, ",");
        char *content = strtok(NULL, "\n");

        // If both label and content are present, process and store them.
        if (label_str && content) 
        {
            labels[email_count] = atoi(label_str);
            strncpy(emails[email_count], content, MAX_EMAIL_SIZE - 1);
            emails[email_count][MAX_EMAIL_SIZE - 1] = '\0';
            email_count++;
        }
        
        // Verbose output.
        if (email_count % 1000 == 0) 
        {
            printf("Processed %d emails\n", email_count);
        }
    }
    fclose(file);

    // Verbose output.
    printf("Total emails processed: %d\n", email_count);

    // If no emails were read, return -1
    if (email_count == 0) 
    {
        printf("No emails were read from the file. Check the file content.\n");
        return -1;
    }

    return email_count;
}