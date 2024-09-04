#include "model_io.h"
#include <stdio.h>

// Saves the model data (word probabilities) to a binary file.
void save_model (char* filename, WordProbability* word_probs, int word_prob_count) 
{
    FILE *file = fopen(filename, "wb");
    
    if (file == NULL) 
    {
        // If the file is not opened, print an error message. Return early.
        printf("Error opening file to write %s\n", filename);
        return;
    }

    // Write the count of word probabilities to the file.
    fwrite(&word_prob_count, sizeof(int), 1, file);

    // Write the actual word probabilities to the file.
    fwrite(word_probs, sizeof(WordProbability), word_prob_count, file);

    fclose(file);
    printf("Model saved to %s\n", filename);
}

// Loads the model data (word probabilities) from a binary file.
int load_model (char* filename, WordProbability* word_probs, int max_words) 
{
    FILE *file = fopen(filename, "rb");
    
    if (file == NULL) 
    {
        // If the file is not opened, print an error message. Return early.
        printf("Error opening file to read %s\n", filename);
        return -1;
    }

    int word_prob_count;
    // Read the count of word probabilities from the file.
    fread(&word_prob_count, sizeof(int), 1, file);

    // If the count of word probabilities is greater than the maximum number of words, print an error message and return early.
    if (word_prob_count > max_words) 
    {
        printf("Model file contains too many words\n");
        fclose(file);
        return -1;
    }

    // Load the word probabilities from the file into the provided array.
    fread(word_probs, sizeof(WordProbability), word_prob_count, file);
    fclose(file);

    // Print a message indicating that the model was successfully loaded.
    printf("Model loaded from %s\n", filename);
    return word_prob_count;
}