#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "spam_classifier.h"

#define MAX_EMAILS 10000
#define TRAIN_RATIO 0.8

int main() {
    struct timeval start, end;
    char emails[MAX_EMAILS][MAX_EMAIL_SIZE];
    int labels[MAX_EMAILS];
    int email_count = 0;

    FILE* file = fopen('')

    
    
    
    
    
    
    
    // ------------------------------------------------------------------- old code.
    gettimeofday(&start, NULL);
    long long start_time = start.tv_sec * 1000LL + start.tv_usec / 1000;

    train(train_emails, train_labels, NUM_TRAIN_EMAILS);
    

    test(test_emails, test_labels, NUM_TEST_EMAILS);

    gettimeofday(&end, NULL);
    long long end_time = end.tv_sec * 1000LL + end.tv_usec / 1000;

    printf("Execution time: %lld ms\n", end_time - start_time);

    return 0;
}