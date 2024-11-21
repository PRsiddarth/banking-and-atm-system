#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ATTEMPTS 3

// Structure to represent a user account
typedef struct {
    char username[50];
    char password[50];
    float balance; // Changed to float for ATM functionality
} UserAccount;

// Function prototypes
void registerUser (UserAccount *users, int *numUsers);
void loginUser (UserAccount *users, int numUsers, char *username, char *password);
void displayMenu();
void withdraw(UserAccount *user);
void deposit(UserAccount *user);
void checkBalance(UserAccount *user);
void atmOperations(UserAccount *user);

int main() {
    UserAccount users[100];
    int numUsers = 0;
    char username[50], password[50];

    while (1) {
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser (users, &numUsers);
                break;
            case 2:
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);
                loginUser (users, numUsers, username, password);
                break;
            case 3:
                return 0;
            default:
                printf("Invalid option.\n");
        }
    }

    return 0;
}

// Function to register a new user
void registerUser (UserAccount *users, int *numUsers) {
    printf("Enter username: ");
    scanf("%s", users[*numUsers].username);
    printf("Enter password: ");
    scanf("%s", users[*numUsers].password);
    users[*numUsers].balance = 0.0f; // Initial balance
    (*numUsers)++;
}

// Function to login to an existing account
void loginUser (UserAccount *users, int numUsers, char *username, char *password) {
    int i;
    for (i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Login successful!\n");
            atmOperations(&users[i]); // Proceed to ATM operations
            return;
        }
    }
    printf("Invalid username or password.\n");
}

// Function to display ATM menu and handle operations
void atmOperations(UserAccount *user) {
    int choice;
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                checkBalance(user);
                break;
            case 2:
                deposit(user);
                break;
            case 3:
                withdraw(user);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
}

void displayMenu() {
    printf("\nATM Menu:\n");
    printf("1. Check Balance\n");
    printf("2. Deposit\n");
    printf("3. Withdraw\n");
    printf("4. Exit\n");
}

void checkBalance(UserAccount *user) {
    printf("Your current balance is: $%.2f\n", user->balance);
}

void deposit(UserAccount *user) {
    float amount;
    printf("Enter the amount to deposit: $");
    scanf("%f", &amount);
    
    if (amount > 0) {
        user->balance += amount;
        printf("Successfully deposited $%.2f. New balance is: $%.2f\n", amount, user->balance);
    } else {
        printf("Invalid amount. Please enter a positive value.\n");
    }
}

void withdraw(UserAccount *user) {
    float amount;
    printf("Enter the amount to withdraw: $");
    scanf("%f", &amount);
    
    if (amount > 0 && amount <= user->balance) {
        user->balance -= amount;
        printf("Successfully withdrew $%.2f. New balance is: $%.2f\n", amount, user->balance);
    } else if (amount > user->balance) {
        printf("Insufficient funds. Your current balance is: $%.2f\n", user->balance);
    } else {
        printf("Invalid amount. Please enter a positive value.\n");
    }
}