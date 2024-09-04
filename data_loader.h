#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include "spam_classifier.h"

// Maximum number of emails that can be loaded
#define MAX_EMAILS 10000

// Loads email data from a file into the provided arrays.
// - emails: Array of email strings.
// - labels: Array of integer labels (1 for spam, 0 for not spam).
// - filename: name of the file to load data from.
// Returns: The number of emails loaded from the file.
int load_data(char (*emails)[MAX_EMAIL_SIZE], int *labels, char *filename);

#endif