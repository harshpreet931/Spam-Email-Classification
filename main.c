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

extern WordProbability word_probs[MAX_WORDS];
extern int word_prob_count;

int main(int argc, char *argv[]) {
    if(argc > 1 && (strcmp(argv[1], "--predict") == 0)) {
        word_prob_count = load_model(MODEL_FILENAME, word_probs, MAX_WORDS);
        if (word_prob_count < 0) {
            printf("Error loading model\n");
            return 1;
        }

        printf("Enter email to predict:  (To stop press -> '|')\n");
        char email[MAX_EMAIL_SIZE];
        while(1) {
            fgets(email, MAX_EMAIL_SIZE, stdin);
            if (email[0] == '|') {
                break;
            }
            int prediction = predict(email);
            if (prediction == 1) {
                printf("SPAM\n");
            } else {
                printf("NOT SPAM\n");
            }
        }
    }
    else {
        struct timeval start, end;
        char (*emails)[MAX_EMAIL_SIZE] = malloc(MAX_EMAILS * sizeof(*emails));
        int *labels = malloc(MAX_EMAILS * sizeof(*labels));
        int email_count = load_data(emails, labels, "./spm_database.txt");
        int train_count = (int)(email_count * TRAIN_RATIO);
        int test_count = email_count - train_count;
        
        gettimeofday(&start, NULL);
        long long before = start.tv_sec * 1000LL + start.tv_usec / 1000;

        train(emails, labels, train_count);
        test(emails + train_count, labels + train_count, test_count);

        gettimeofday(&end, NULL);
        long long after = end.tv_sec * 1000LL + end.tv_usec / 1000;
        printf("Time taken: %lld ms\n", after - before);

        save_model(MODEL_FILENAME, word_probs, word_prob_count);

        free(emails);
        free(labels);
    }
    return 0;
}