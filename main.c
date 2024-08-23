#include <stdio.h>
#include <string.h>
#include "spam_classifier.h"

int main()
{
    char train_emails[4][MAX_EMAIL_SIZE] = 
    {
        "Win a lottery now!", 
        "Buy a car now",
        "Meeting at 10 AM",
        "Report to me in office"
    }

    int train_labels[4] = {1, 1, 0, 0};

    train(train_emails, train_labels, 4);

    char test_emails[3][MAX_EMAIL_SIZE] = 
    {
        "Win a lottery now",
        "Let's meet at 5",
        "Congratulations you have won!"
    };

    int test_labels[3] = {1, 0, 1};

    test(test_emails, test_labels, 3);

    return 0;
}