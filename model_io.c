#include "model_io.h"
#include <stdio.h>

void save_model (char* filename, WordProbability* word_probs, int word_prob_count) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error opening file to write %s\n", filename);
        return 0;
    }

    fwrite(&word_prob_count, sizeof(int), 1, file);
    fwrite(word_probs, sizeof(WordProbability), word_prob_count, file);

    fclose(file);
    printf("Model saved to %s\n", filename);
}

int load_model (char* filename, WordProbability* word_probs, int max_words) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file to read %s\n", filename);
        return -1;
    }

    int word_prob_count;
    fread(&word_prob_count, sizeof(int), 1, file);

    if (word_prob_count > max_words) {
        printf("Model file contains too many words\n");
        fclose(file);
        return -1;
    }

    fread(word_probs, sizeof(WordProbability), word_prob_count, file);
    fclose(file);
    printf("Model loaded from %s\n", filename);
    return word_prob_count;
}