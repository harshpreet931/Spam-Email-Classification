#ifndef MODEL_IO_H
#define MODEL_IO_H

#include "spam_classifier.h"

// Saves the model data (word probabilities) to a binary file.
// -filename: The name of the file to save the model to.
// -word_probs: The array of word probabilities to save.
// -word_prob_count: The number of word probabilities in the array.
void save_model(char* filename, WordProbability* word_probs, int word_prob_count);

// Loads the model data (word probabilities) from a binary file.
// -filename: The name of the file to load the model from.
// -word_probs: The array to load the word probabilities into.
// -max_words: The maximum number of word probabilities that can be loaded.
int load_model(char* filename, WordProbability* word_probs, int max_words);

#endif