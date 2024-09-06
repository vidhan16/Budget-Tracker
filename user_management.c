#include "user_management.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// Define global variables
User users[MAX_USERS];
Record records[MAX_RECORDS];
int user_count = 0;
int record_count = 0;
char logged_in_user[50];
int authenticated = 0;

// Implement the functions

void load_users() {
    FILE *file = fopen("users.dat", "r");
    if (file != NULL) {
        while (fscanf(file, "%s %s", users[user_count].username, users[user_count].password) != EOF) {
            user_count++;
        }
        fclose(file);
    }
}

void save_users() {
    FILE *file = fopen("users.dat", "w");
    for (int i = 0; i < user_count; i++) {
        fprintf(file, "%s %s\n", users[i].username, users[i].password);
    }
    fclose(file);
}

void load_records() {
    FILE *file = fopen("records.dat", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    record_count = 0; // Ensure record_count starts from 0

    while (fscanf(file, "%[^\t]\t%[^\t]\t%f\t%[^\n]\n",
                  records[record_count].category,
                  records[record_count].description,
                  &records[record_count].amount,
                  records[record_count].username) != EOF) {
        record_count++;
    }

    fclose(file);
    printf("Records loaded successfully.\n");
}


void save_records() {
    FILE *file = fopen("records.dat", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < record_count; i++) {
        fprintf(file, "%s\t%s\t%.2f\t%s\n", records[i].category, records[i].description, records[i].amount, records[i].username);
    }

    fclose(file);
    printf("Records saved successfully.\n");
}


void register_user() {
    if (user_count >= MAX_USERS) {
        printf("User limit reached.\n");
        return;
    }

    char username[50];
    char password[50];
    char confirm_password[50];

    printf("Enter new username: ");
    scanf("%s", username);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Username already exists.\n");
            return;
        }
    }

    printf("Enter new password: ");
    scanf("%s", password);
    printf("Confirm password: ");
    scanf("%s", confirm_password);

    if (strcmp(password, confirm_password) != 0) {
        printf("Passwords do not match.\n");
        return;
    }

    strcpy(users[user_count].username, username);
    strcpy(users[user_count].password, password);
    user_count++;
    save_users();
    printf("User registered successfully.\n");
}

void authenticate_user() {
    char username[50];
    char password[50];

    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            strcpy(logged_in_user, username);
            authenticated = 1;
            while(1) menu();
            return;
        }
    }

    printf("No user found.. Want to register ?\n1 for yes\n0 for no\n");
    int res;
    scanf("%d",&res);
    if(res == 1)
    {
        register_user();
        authenticate_user();
    }
}

void add_record() {
    if (record_count >= MAX_RECORDS) {
        printf("Record limit reached.\n");
        return;
    }
    printf("Enter category: ");
    getchar(); 
    fgets(records[record_count].category, sizeof(records[record_count].category), stdin);
    records[record_count].category[strcspn(records[record_count].category, "\n")] = 0;

    printf("Enter description: ");
    fgets(records[record_count].description, sizeof(records[record_count].description), stdin);
    records[record_count].description[strcspn(records[record_count].description, "\n")] = 0;  

    printf("Enter amount: ");
    scanf("%f", &records[record_count].amount);
    strcpy(records[record_count].username, logged_in_user); 

    record_count++;
    save_records();
    printf("Record added successfully.\n");
}
void update_record() {
    char description[100];
    char category[100];
    int found = 0;

    printf("Enter the description of the record to update: ");
    getchar();
    scanf("%[^\n]", description);


    for (int i = 0; i < record_count; i++) {
        if (strcmp(records[i].description, description) == 0 && strcmp(records[i].username, logged_in_user) == 0) {
            found = 1;
            printf("Record found. Enter new details:\n");
            printf("Enter new category: ");
            getchar();
            fgets(category, sizeof(category), stdin);
            category[strcspn(category, "\n")] = '\0'; 
            strcpy(records[i].category, category);

            printf("Enter new description: ");
            fgets(records[i].description, sizeof(records[i].description), stdin);
            records[i].description[strcspn(records[i].description, "\n")] = '\0';

            printf("Enter new amount: ");
            scanf("%f", &records[i].amount);

            // Update the record in the data file
            save_records();

            printf("Record updated successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Record not found or does not belong to you.\n");
    }
}

void delete_record() {
    char description[100];
    printf("Enter the description of the record to delete: ");
    scanf(" %[^\n]", description);

    for (int i = 0; i < record_count; i++) {
        
        if (strcmp(records[i].description, description) == 0 && strcmp(records[i].username, logged_in_user) == 0) {
            for (int j = i; j < record_count - 1; j++) {
                records[j] = records[j + 1];
            }
            record_count--;
            save_records();
            printf("Record deleted successfully.\n");
            return;
        }
    }
    printf("Record not found or does not belong to you.\n");
}
void view_records() {
    int found = 0;
    printf("Your Records:\n");
    
    for (int i = 0; i < record_count; i++) {
        if (strcmp(records[i].username, logged_in_user) == 0) {
            printf("Category: %s, Description: %s, Amount: %.2f\n",
                   records[i].category, records[i].description, records[i].amount);
            found = 1;
        }
    }
    
    if (!found) {
        printf("No records found.\n");
    }
}

void find_best_budget() {
    float total[MAX_CATEGORIES] = {0};
    char categories[MAX_CATEGORIES][50] = {0};
    int category_count = 0;

    // List of basic necessities
    const char *necessities[] = {
        "Groceries", "House rent", "Car EMI", "Transportation",
        "Mobile Recharge", "Fastag Recharge", "Electricity Bills",
        "Water Bills", "College Fees", "School Fees"
    };
    int necessity_count = sizeof(necessities) / sizeof(necessities[0]);

    // List of slightly important expenses
    const char *important_expenses[] = {
        "TV", "Sofa", "Bed", "Tables", "Refrigerator",
        "Oven", "Microwave", "Laptops", "Mobile", "Household Stuffs"
    };
    int important_count = sizeof(important_expenses) / sizeof(important_expenses[0]);

    for (int i = 0; i < record_count; i++) {
        if (strcmp(records[i].username, logged_in_user) == 0) {
            int found = 0;
            for (int j = 0; j < category_count; j++) {
                if (strcasecmp(categories[j], records[i].category) == 0) {
                    total[j] += records[i].amount;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                strcpy(categories[category_count], records[i].category);
                total[category_count] = records[i].amount;
                category_count++;
            }
        }
    }

    if (category_count == 0) {
        printf("No spending records found for user %s.\n", logged_in_user);
        return;
    }

    printf("Best Budget Plan for %s:\n", logged_in_user);

    // Display basic necessities
    printf("Basic Necessities:\n");
    int found_necessities = 0;
    for (int i = 0; i < category_count; i++) {
        for (int j = 0; j < necessity_count; j++) {
            if (strcasecmp(categories[i], necessities[j]) == 0) {
                printf("- %s: %.2f\n", categories[i], total[i]);
                found_necessities = 1;
            }
        }
    }
    if (!found_necessities) {
        printf("No basic necessities found in your spending records.\n");
    }

    // Display slightly important expenses
    printf("\nSlightly Important Expenses:\n");
    int found_important = 0;
    for (int i = 0; i < category_count; i++) {
        for (int j = 0; j < important_count; j++) {
            if (strcasecmp(categories[i], important_expenses[j]) == 0) {
                printf("- %s: %.2f\n", categories[i], total[i]);
                found_important = 1;
            }
        }
    }
    if (!found_important) {
        printf("No slightly important expenses found in your spending records.\n");
    }

    // Display luxury expenses
    printf("\nLuxury Expenses:\n");
    int found_luxury = 0;
    for (int i = 0; i < category_count; i++) {
        int is_necessity = 0, is_important = 0;
        for (int j = 0; j < necessity_count; j++) {
            if (strcasecmp(categories[i], necessities[j]) == 0) {
                is_necessity = 1;
                break;
            }
        }
        for (int j = 0; j < important_count; j++) {
            if (strcasecmp(categories[i], important_expenses[j]) == 0) {
                is_important = 1;
                break;
            }
        }
        if (!is_necessity && !is_important) {
            printf("- %s: %.2f\n", categories[i], total[i]);
            found_luxury = 1;
        }
    }
    if (!found_luxury) {
        printf("No luxury expenses found in your spending records.\n");
    }

    // Finding the category with the lowest spending
    float min_amount = total[0];
    char best_category[50];
    strcpy(best_category, categories[0]);

    for (int i = 1; i < category_count; i++) {
        if (total[i] < min_amount) {
            min_amount = total[i];
            strcpy(best_category, categories[i]);
        }
    }

    printf("\nCategory with the lowest spending: %s (%.2f)\n", best_category, min_amount);
}

void menu() {
    int choice;

    printf("1. Add Record\n");
    printf("2. Update Record\n");
    printf("3. Delete Record\n");
    printf("4. View Records\n");
    printf("5. Find Best Budget\n");
    printf("6. Exit\n");
    printf("7. Switch User\n");
    printf("Choose an option: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            add_record();
            break;
        case 2:
            update_record();
            break;
        case 3:
            delete_record();
            break;
        case 4:
            view_records();
            break;
        case 5:
            find_best_budget();
            break;
        case 6:
            exit(0);
        case 7:
            authenticate_user();
        default:
            exit(0);
    }
}