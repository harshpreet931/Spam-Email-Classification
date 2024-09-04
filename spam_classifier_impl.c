#include "spam_classifier.h"
#include "model_io.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

// Array to store word probabilities to classify!
WordProbability word_probs[MAX_WORDS];

// Number of unique words or word probabilities in the array
int word_prob_count = 0;

// Tokenizes a email into token / individual words.
// - email: Email text to tokenize.
// - tokens: Array to store the resulting tokens.
// - token_count: Pointer to store the number of tokens.
void tokenize(char* email, char tokens[][MAX_TOKEN_LENGTH], int* token_count)
{
    // Tokenize the email using space, tab, newline, carriage return, form feed, vertical tab, 
    // comma, period, exclamation mark, question mark, semicolon, colon, double quotes, single quotes, 
    // parentheses, square brackets, curly braces as delimiters.
    // We never know what kind of delimiters can be used in the email.
    char* token = strtok(email, " \t\n\r\f\v,.!?;:\"'()[]{}");
    while(token != NULL && *token_count < MAX_TOKENS)
    {
        // Convert the token to lowercase
        for(int i = 0; token[i]; i++)
        {
            token[i] = tolower(token[i]);
        }

        // Copy the token to the tokens array
        if(strlen(token) > 0)
        {
            strncpy(tokens[*token_count], token, MAX_TOKEN_LENGTH - 1);
            tokens[*token_count][MAX_TOKEN_LENGTH - 1] = '\0';
            (*token_count)++;
        }

        // Get the next token
        token = strtok(NULL, " \t\n\r\f\v,.!?;:\"'()[]{}");
    }
}
// Explained in the header file spam_classifier.h
void train(char emails[][MAX_EMAIL_SIZE], int labels[], int email_count)
{
    printf("Started Training on %d emails\n", email_count);
    
    // Loop through each email to process it.
    for(int i = 0; i < email_count; i++)
    {   
        char tokens[MAX_TOKENS][MAX_TOKEN_LENGTH];
        int token_count = 0;
        // Tokenize the email to get individual words
        tokenize(emails[i], tokens, &token_count);

        // Loop through each token and update the word probabilities,
        // i.e. spam_count and not_spam_count for each word.
        for(int j = 0; j < token_count; j++)
        {
            int found = 0;
            // To check if the word is already in the word_probs array
            for(int k = 0; k < word_prob_count; k++)
            {
                if(strcmp(word_probs[k].word, tokens[j]) == 0)
                {
                    found = 1;
                    // Update the spam_count or not_spam_count based on the label
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

            // If the word is not found in the word_probs array, add it.
            // I.e the token that we have right now is a new word.
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
    printf("Training Completed!");
}

// Calculate the log-probability of an email being spam or not spam.
// - email: Email text to calculate the probability for.
// - is_spam: Flag to tell spam(1) or not spam(0).
// Returns: The log-probability of the email being spam or not spam.
double calculate_probability(char *email, int is_spam)
{
    char tokens[MAX_TOKENS][500];
    int token_count = 0;
    // Tokenize the email to get individual words
    tokenize(email, tokens, &token_count);

    double log_prob = 0.0;
    // Loop through each token and calculate the log-probability
    for(int i = 0; i < token_count; i++)
    {
        for(int j = 0; j < word_prob_count; j++)
        {
            if(strcmp(word_probs[j].word, tokens[i]) == 0)
            {
                double p;
                // Calculate the probability based on the spam or not spam flag (Laplacian Smoothing)
                if(is_spam)
                {
                    p = (double)(word_probs[j].spam_count + 1) / (word_probs[j].spam_count + word_probs[j].not_spam_count + 2);
                }
                else
                {
                    p = (double)(word_probs[j].not_spam_count + 1) / (word_probs[j].spam_count + word_probs[j].not_spam_count + 2);
                }
                log_prob += log(p); // Add the log-probability
                break;
            }
        }
    }
    return log_prob;
}

// Simple function to predict whether an email is spam or not spam.
// - email: Email text to predict.
// Returns: 1 if the email is spam, 0 if not spam.
int predict(char *email)
{
    double spam_prob = calculate_probability(email, 1);
    double not_spam_prob = calculate_probability(email, 0);

    // If the spam probability is greater than not spam probability, predict spam.
    return spam_prob > not_spam_prob ? 1 : 0;
}

// Explained in the header file spam_classifier.h
void test(char test_emails[][MAX_EMAIL_SIZE], int test_labels[], int test_count)
{
    printf("Started Testing on %d emails\n", test_count);
    int correct = 0;

    // Loop through each test email and predict the label.
    for(int i = 0; i < test_count; i++)
    {
        int prediction = predict(test_emails[i]);
        if(prediction == test_labels[i])
        {
            correct++;
        }

        // Verbose output.
        if(i % 100 == 0)
        {
            printf("Testing %d/%d\n", i, test_count);
        }
    }
    printf("Testing Completed!\n");
    
    // Simple way to calculate accuracy.
    printf("Accuracy: %f\n", (double)correct / test_count);
}