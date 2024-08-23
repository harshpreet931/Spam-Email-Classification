#include <stdio.h>
#include <string.h>
#include "spam_classifier.h"

#define NUM_TRAIN_EMAILS 80
#define NUM_TEST_EMAILS 20

int main() {
    char train_emails[NUM_TRAIN_EMAILS][MAX_EMAIL_SIZE] = {
        "Win a lottery now!", "Buy a car now", "Meeting at 10 AM", "Report to me in office",
        "Congratulations! You've won $1000000", "Urgent: Your account needs attention",
        "Team lunch next Friday", "Project status update", "Free iPhone giveaway!",
        "Enhance your performance", "Quarterly report due", "New office policy",
        "You're our lucky winner", "Double your income now", "Client meeting rescheduled",
        "Your package has been shipped", "Hot singles in your area", "Vacation leave approved",
        "Exclusive offer just for you", "Password reset required", "Conference call at 2 PM",
        "Claim your prize now", "Urgent wire transfer needed", "Team building event next month",
        "Get rich quick opportunity", "Your opinion matters - take our survey", "New hire orientation",
        "Miracle weight loss solution", "IT system maintenance tonight", "Congratulations on your promotion",
        "Unbelievable discounts inside", "Reminder: Timesheet due", "Free trial membership",
        "Increase your credit score fast", "Upcoming performance review", "Holiday party invitation",
        "You've been selected for a special offer", "New project kickoff meeting", "Earn money from home",
        "Limited time offer - act now", "Deadline extension approved", "Your resume has been shortlisted",
        "Unlock hidden potential", "Budget approval needed", "Thank you for your purchase",
        "Invest in cryptocurrency now", "Office closed for renovation", "Congratulations! You're pre-approved",
        "Enhance your love life", "New company benefits package", "Your account has been compromised",
        "Last chance for amazing deals", "Volunteer opportunity available", "You've won the jackpot",
        "Boost your energy naturally", "Workplace safety training", "Exclusive membership invitation",
        "Get a loan instantly", "New product launch meeting", "Your credit card has been charged",
        "Become a millionaire overnight", "Employee satisfaction survey", "You've been chosen for a trial",
        "Miracle hair growth formula", "Expense reports due tomorrow", "Confirm your email to claim prize",
        "Lose weight without diet or exercise", "Team performance metrics", "You're our 1,000,000th visitor",
        "Instant approval for high limit card", "New hire welcome lunch", "Congratulations on your inheritance",
        "Reduce debt quickly", "Company picnic next Saturday", "Your account needs verification",
        "Make money while you sleep", "Fire drill scheduled for Friday", "You've qualified for a special rate"
    };

    int train_labels[NUM_TRAIN_EMAILS] = {
        1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0,
        0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1,
        0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1,
        1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1
    };

    train(train_emails, train_labels, NUM_TRAIN_EMAILS);

    char test_emails[NUM_TEST_EMAILS][MAX_EMAIL_SIZE] = {
        "Win big prizes now", "Team meeting at 3 PM", "You're the lucky winner", "Project deadline extended",
        "Get rich quick scheme", "Quarterly sales report", "Free gift waiting for you", "New hire onboarding",
        "Unlock your potential now", "Office supply order", "Amazing weight loss trick", "Performance review scheduled",
        "Exclusive VIP membership", "Reminder: Submit timesheet", "Instant loans available", "Company policy update",
        "Miracle cure discovered", "Client presentation tomorrow", "Double your income today", "Team building workshop"
    };

    int test_labels[NUM_TEST_EMAILS] = {
        1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0
    };

    test(test_emails, test_labels, NUM_TEST_EMAILS);

    return 0;
}