#define MAX_EMAIL_SIZE 1000
#define MAX_WORDS 1000
#define MAX_TOKENS 100

typedef struct
{
    char word[50];
    int spam_count;
    int not_spam_count;
} WordProbability;

void tokenize(char *email, char token[][50], int *token_count);
void train(char [][MAX_EMAIL_SIZE], int labels[], int email_count);
double calculate_probability(char *email, int is_spam);
int predict(char *email);
void test(char test_emails[][MAX_EMAIL_SIZE], int test_labels[], int test_count);

