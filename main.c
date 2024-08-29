#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
// #include <sys/resource.h>
#include <time.h>
#include "spam_classifier.h"
#include "data_loader.h"

#define MAX_EMAILS 10000
#define TRAIN_RATIO 0.80

int main() {
    struct timeval start, end;
    // struct rusage usage_start, usage_start;
    // getrusage(RUSAGE_SELF, &usage_start);

    char (*emails)[MAX_EMAIL_SIZE] = malloc(MAX_EMAILS * sizeof(*emails));
    int *labels = malloc(MAX_EMAILS * sizeof(*labels));
    
    if (!emails || !labels) {
        printf("Memory allocation failed\n");
        return 1;
    }

    int email_count = load_data(emails, labels, "./spm_dataset.txt");
    if (email_count <= 0) {
        free(emails);
        free(labels);
        printf("Error loading data\n");
        return 1;
    }

    int train_count = (int)(email_count * TRAIN_RATIO);
    int test_count = email_count - train_count;
    
    printf("Training on %d emails, testing on %d emails\n", train_count, test_count);
    
    gettimeofday(&start, NULL);
    long long before = start.tv_sec * 1000LL + start.tv_usec / 1000;

    train(emails, labels, train_count);
    test(emails + train_count, labels + train_count, test_count);

    gettimeofday(&end, NULL);
    long long after = end.tv_sec * 1000LL + end.tv_usec / 1000;
    // getrusage(RUSAGE_SELF, &usage_end);
    // long long memory_used = usage_end.ru_maxrss - usage_start.ru_maxrss;

    printf("Time taken: %lld ms\n", after - before);
    // printf("Memory used: %lld KB\n", memory_used);

    free(emails);
    free(labels);

    return 0;
}