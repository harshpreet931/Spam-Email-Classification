#include "spam_classifier.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

WordProbability word_probs[MAX_WORDS];
int word_prob_count = 0;

void tokenize(char* email, char tokens[][MAX_TOKEN_LENGTH], int* token_count)
{
    char* token = strtok(email, " ");
    while(token != NULL && *token_count < MAX_TOKENS)
    {
        for(int i = 0; token[i]; i++)
        {
            token[i] = tolower(token[i]);
        }

        int j = 0;
        for(int i = 0; token[i] && j < MAX_TOKEN_LENGTH - 1; i++)
        {
            if(isalnum(token[i]))
            {
                token[j++] = token[i];
            }
        }
        token[j] = '\0';

        if(strlen(token) > 0)
        {
            strncpy(tokens[*token_count], token, MAX_TOKEN_LENGTH - 1);
            tokens[*token_count][MAX_TOKEN_LENGTH - 1] = '\0';
            (*token_count)++;
        }
        token = strtok(NULL, " ");
    }
}

void train(char emails[][MAX_EMAIL_SIZE], int labels[], int email_count)
{
    printf("Started Training on %d emails\n", email_count);
    for(int i = 0; i < email_count; i++)
    {
        char tokens[MAX_TOKENS][MAX_TOKEN_LENGTH];
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

            if(!found && word_prob_count < MAX_WORDS)
            {
                strncpy(word_probs[word_prob_count].word, tokens[j], sizeof(word_probs[word_prob_count].word) - 1);
                word_probs[word_prob_count].word[sizeof(word_probs[word_prob_count].word) - 1] = '\0';
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
    printf("Training Completed! Total unique words: %d\n", word_prob_count);
}

double calculate_probability(char *email, int is_spam)
{
    char tokens[MAX_TOKENS][500];
    int token_count = 0;
    tokenize(email, tokens, &token_count);

    double log_prob = 0.0;
    for(int i = 0; i < token_count; i++)
    {
        for(int j = 0; j < word_prob_count; j++)
        {
            if(strcmp(word_probs[j].word, tokens[i]) == 0)
            {
                double p;
                if(is_spam)
                {
                    p = (double)(word_probs[j].spam_count + 1) / (word_probs[j].spam_count + word_probs[j].not_spam_count + 2);
                }
                else
                {
                    p = (double)(word_probs[j].not_spam_count + 1) / (word_probs[j].spam_count + word_probs[j].not_spam_count + 2);
                }
                log_prob += log(p);
                break;
            }
        }
    }
    return log_prob;
}

int predict(char *email)
{
    double spam_prob = calculate_probability(email, 1);
    double not_spam_prob = calculate_probability(email, 0);

    return spam_prob > not_spam_prob ? 1 : 0;
}

void test(char test_emails[][MAX_EMAIL_SIZE], int test_labels[], int test_count)
{
    printf("Started Testing on %d emails\n", test_count);
    int correct = 0;
    for(int i = 0; i < test_count; i++)
    {
        int prediction = predict(test_emails[i]);
        if(prediction == test_labels[i])
        {
            correct++;
        }
        if(i % 100 == 0)
        {
            printf("Testing %d/%d\n", i, test_count);
        }
    }
    printf("Testing Completed!\n");

    printf("Accuracy: %f\n", (double)correct / test_count);
}
