#include "spam_classifier.h"
#include <string.h>

void tokenize(char *email, char tokens[][50], int *token_count)
{
    char *token = strtok(email, " ");
    *token_count = 0;

    while (token != NULL) 
    {
        strcpy(tokens[(*token_count)++], token);
        token = strtok(NULL, " ");
    }
}