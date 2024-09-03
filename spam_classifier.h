#ifndef SPAM_CLASSIFIER_H
#define SPAM_CLASSIFIER_H

#define MAX_WORDS 10000
#define MAX_TOKEN_LENGTH 100
#define MAX_TOKENS 1000
#define MAX_EMAIL_SIZE 10000

typedef struct
{
    char word[MAX_TOKEN_LENGTH];
    int spam_count;
    int not_spam_count;    
} WordProbability;

void train(char emails[][MAX_EMAIL_SIZE], int labels[], int email_count);
int predict(char *email);
void test(char test_emails[][MAX_EMAIL_SIZE], int test_labels[], int test_count);

#endif