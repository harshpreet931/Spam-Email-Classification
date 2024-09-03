#ifndef MODEL_IO_H
#define MODEL_IO_H

#include "spam_classifier.h"

void save_model(char* filename, WordProbability* word_probs, int word_prob_count);
int load_model(char* filename, WordProbability* word_probs, int max_words);

#endif