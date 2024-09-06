#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "spam_classifier.h"
#include "data_loader.h"
#include "model_io.h"

#define MAX_EMAILS 10000
#define TRAIN_RATIO 0.80
#define MODEL_FILENAME "spam_model.bin"

// External variables defined in spam_classifier_impl.c
extern WordProbability word_probs[MAX_WORDS];
extern int word_prob_count;

int main(int argc, char *argv[]) 
{   
    // Case if the program is run with the "--predict" argument
    // Check if the program is run with the "--predict" argument
    if(argc > 1 && (strcmp(argv[1], "--predict") == 0)) 
    {
        // Load the pre-trained model from the file
        word_prob_count = load_model(MODEL_FILENAME, word_probs, MAX_WORDS);
        if (word_prob_count < 0) 
        {
            printf("Error loading model\n");
            return 1;
        }

        printf("Enter email to predict:  (To stop press -> '|')\n");
        char *email = malloc(MAX_EMAIL_SIZE * sizeof(char));
        if(email == NULL) 
        {
            printf("Error allocating memory for email\n");
            return 1;
        }
        // Continuously read emails from the user and predict if they are spam or not
        while(1) 
        {
            fgets(email, MAX_EMAIL_SIZE, stdin);
            // Stop if the user enters '|'
            if (email[0] == '|') 
            {
                break;
            }

            // Predict if the email is spam or not
            int result = predict(email);
            if (result == 1) 
            {
                printf("SPAM\n");
            } 
            else 
            {
                printf("NOT SPAM\n");
            }
        }

        free(email);
    }
    else 
    {
        // Default case: Train the model and test it on a dataset
        // Timing variables for measuring performance
        struct timeval start, end;

        // Allocate memory for emails and labels
        // The emails are stored as a 2D array of characters, 2D because each email is a string of characters
        // and that email is an element of the emails array.
        // The labels are stored as a normal array.
        char (*emails)[MAX_EMAIL_SIZE] = malloc(MAX_EMAILS * sizeof(*emails));
        int *labels = malloc(MAX_EMAILS * sizeof(*labels));

        if (emails == NULL || labels == NULL) 
        {
            printf("Error allocating memory for emails and labels\n");
            free(emails);
            free(labels);
            return 1;
        }

        // Load email data and the labels from the dataset
        int email_count = load_data(emails, labels, "./spm_database.txt");

        // Calculate the number of emails for training and testing
        int train_count = (int)(email_count * TRAIN_RATIO);
        int test_count = email_count - train_count;
        
        // Start the timer before training and testing
        gettimeofday(&start, NULL);
        long long before = start.tv_sec * 1000LL + start.tv_usec / 1000;

        // Trainining and Testing
        train(emails, labels, train_count);
        test(emails + train_count, labels + train_count, test_count);

        // Stop the timer after training and testing and print the performance
        gettimeofday(&end, NULL);
        long long after = end.tv_sec * 1000LL + end.tv_usec / 1000;
        printf("Time taken: %lld ms\n", after - before);

        // Save the trained model to a file for future use
        save_model(MODEL_FILENAME, word_probs, word_prob_count);

        // Free the allocated memory!
        free(emails);
        free(labels);
    }
    return 0;
}