#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include "spam_classifier.h"

#define MAX_EMAILS 10000

int load_data(char (*emails)[MAX_EMAIL_SIZE], int *labels, char *filename);

#endif