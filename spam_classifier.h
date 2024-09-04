#ifndef SPAM_CLASSIFIER_H
#define SPAM_CLASSIFIER_H

// Maximum number of words that can be tracked for spam classification
#define MAX_WORDS 10000

// Maximum length of a single token (word) in characters
#define MAX_TOKEN_LENGTH 500

// Maximum number of tokens (words) in an email
#define MAX_TOKENS 1000

// Maximum size of an email in characters
#define MAX_EMAIL_SIZE 10000

// Custom Structure to store the probability for a specific word
typedef struct
{
    char word[MAX_TOKEN_LENGTH];  // The word itself
    int spam_count;               // Number of times the word appears in the spam emails
    int not_spam_count;           // Number of times the word appears in the non-spam emails
} WordProbability;

// Trains the spam classifier model using the provided emails and labels.
// - emails: An array of email strings.
// - labels: An array of integer labels (1 for spam, 0 for not spam).
// - email_count: The number of emails in the training set.
void train(char emails[][MAX_EMAIL_SIZE], int labels[], int email_count);

// Predicts whether an email is spam or not spam.
// - email: The email string to predict.
// Returns: 1 if the email is predicted to be spam, 0 if not spam.
int predict(char *email);

// Tests the spam classifier model using the provided test emails and labels.
// - test_emails: An array of email strings for testing.
// - test_labels: An array of integer labels (1 for spam, 0 for not spam).
// - test_count: The number of emails in the test set.
void test(char test_emails[][MAX_EMAIL_SIZE], int test_labels[], int test_count);

#endif