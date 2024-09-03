#include "model_io.h"
#include <stdio.h>

void save_model(char* filename, WordProbability* word_probs, int word_prob_count) {
    File *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error opening file to write %s\n", filename);
        return 0;
    }

    fwrite(&word_prob_count, sizeof(int), 1, file);
    fwrite(word_probs, sizeof(WordProbability), word_prob_count, file);

    fclose(file);
    printf("Model saved to %s\n", filename);
}