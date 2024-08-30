#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "spam_classifier.h"
#include "data_loader.h"

#define MAX_EMAILS 10000
#define TRAIN_RATIO 0.80

int main() {
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

    printf("Enter an email to predict: (To stop enter - '|')\n");
    char email[MAX_EMAIL_SIZE];
    while(1)
    {
        fgets(email, MAX_EMAIL_SIZE, stdin);
        if(email[0] == '|')
        {
            break;
        }
        int prediction = predict(email);
        if(prediction == 1)
        {
            printf("Spam\n");
        }
        else
        {
            printf("Not Spam\n");
        }
    }

    free(emails);
    free(labels);
    return 0;
}