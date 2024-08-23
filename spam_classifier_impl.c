#include "spam_classifier.h"
#include <stdio.h>
#include <string.h>

WordProbability word_probs[MAX_WORDS];
int word_prob_count = 0;

void tokenize(char *email, char tokens[][50], int *token_count)
{
    char *token = strtok(email, " ");
    while (token != NULL)
    {
        strcpy(tokens[*token_count], token);
        (*token_count)++;
        token = strtok(NULL, " ");
    }
}

