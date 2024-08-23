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

void train(char emails[][MAX_EMAIL_SIZE], int labels[], int email_count)
{
    for(int i = 0; i < email_count, i++)
    {
        char tokens[MAX_TOKENS][50];
        int token_count = 0;
        tokenize(emails[i], tokens, &token_count);

        for(int j = 0; j < token_count; j++)
        {
            int found = 0;
            for(int k = 0; k < word_prob_count; k++)
            {
                if(strcmp(word_probs[k].word, tokens[j]) == 0)
                {
                    found = 1;
                    if(labels[i] == 1)
                    {
                        word_probs[k].spam_count++;
                    }
                    else
                    {
                        word_probs[k].not_spam_count++;
                    }
                    break;
                }
            }

            if(!found)
            {
                strcpy(word_probs[word_prob_count].word, tokens[j]);
                if(labels[i] == 1)
                {
                    word_probs[word_prob_count].spam_count = 1;
                    word_probs[word_prob_count].not_spam_count = 0;
                }
                else
                {
                    word_probs[word_prob_count].spam_count = 0;
                    word_probs[word_prob_count].not_spam_count = 1;
                }
                word_prob_count++;
            }
        }
    }
}

