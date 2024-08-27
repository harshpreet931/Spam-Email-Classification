#define MAX_EMAIL_SIZE 10000
#define MAX_WORDS 100000
#define MAX_TOKENS 10000

typedef struct
{
    char word[50];
    int spam_count;
    int not_spam_count;    
} WordProbability;

void train(char emails[][MAX_EMAIL_SIZE], int labels[], int email_count);
int predict(char *email);
void test(char test_emails[][MAX_EMAIL_SIZE], int test_labels[], int test_count);