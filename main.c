#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "spam_classifier.h"
#include "data_loader.h"

#define MAX_EMAILS 10000
#define TRAIN_RATIO 0.80

int main(int argc, char *argv[]) {
    if(argc > 1 && strcmp(argv[1], "-p") == 0) {
        char email[MAX_EMAIL_SIZE];
        printf("Enter the email content: (Press Ctrl+D to finish)\n");
        int input_length = 0;
        char c;
        while ((c = getchar()) != EOF && input_length < MAX_EMAIL_SIZE - 1) {
            if(c == '|') break; 
            
            email[input_length++] = c;
        }
        email[input_length] = '\0';

        predict_cli_input(email);
        return 0;
    }
    
    struct timeval start, end;
    char (*emails)[MAX_EMAIL_SIZE] = malloc(MAX_EMAILS * sizeof(*emails));
    int *labels = malloc(MAX_EMAILS * sizeof(*labels));
    int email_count = load_data(emails, labels, "./spm_dataset.txt");
    int train_count = (int)(email_count * TRAIN_RATIO);
    int test_count = email_count - train_count;
    
    gettimeofday(&start, NULL);
    long long before = start.tv_sec * 1000LL + start.tv_usec / 1000;

    train(emails, labels, train_count);
    test(emails + train_count, labels + train_count, test_count);

    gettimeofday(&end, NULL);
    long long after = end.tv_sec * 1000LL + end.tv_usec / 1000;
    printf("Time taken: %lld ms\n", after - before);

    free(emails);
    free(labels);
    return 0;
}