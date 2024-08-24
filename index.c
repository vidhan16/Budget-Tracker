#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_RECORDS 100
#define MAX_CATEGORIES 5

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void start(){
    // clear_screen();
	printf("\n\n\n\n");
	printf("\t\t\t\t\t\t       _______   __    __  _______    ______   ________  ________     \n");
	printf("\t\t\t\t\t\t      /       \\ /  |  /  |/       \\  /      \\ /        |/        |    \n");
	printf("\t\t\t\t\t\t      $$$$$$$  |$$ |  $$ |$$$$$$$  |/$$$$$$  |$$$$$$$$/ $$$$$$$$/     \n");
	printf("\t\t\t\t\t\t      $$ |__$$ |$$ |  $$ |$$ |  $$ |$$ | _$$/ $$ |__       $$ |       \n");
	printf("\t\t\t\t\t\t      $$    $$< $$ |  $$ |$$ |  $$ |$$ |/    |$$    |      $$ |       \n");
	printf("\t\t\t\t\t\t      $$$$$$$  |$$ |  $$ |$$ |  $$ |$$ |$$$$ |$$$$$/       $$ |       \n");
	printf("\t\t\t\t\t\t      $$ |__$$ |$$ \\__$$ |$$ |__$$ |$$ \\__$$ |$$ |_____    $$ |       \n");
	printf("\t\t\t\t\t\t      $$    $$/ $$    $$/ $$    $$/ $$    $$/ $$       |   $$ |       \n");
	printf("\t\t\t\t\t\t      $$$$$$$/   $$$$$$/  $$$$$$$/   $$$$$$/  $$$$$$$$/    $$/        \n");
	printf("\t\t\t\t\t\t ________  _______    ______    ______   __    __  ________  _______  \n");
	printf("\t\t\t\t\t\t/        |/       \\  /      \\  /      \\ /  |  /  |/        |/       \\ \n");
	printf("\t\t\t\t\t\t$$$$$$$$/ $$$$$$$  |/$$$$$$  |/$$$$$$  |$$ | /$$/ $$$$$$$$/ $$$$$$$  |\n");
	printf("\t\t\t\t\t\t   $$ |   $$ |__$$ |$$ |__$$ |$$ |  $$/ $$ |/$$/  $$ |__    $$ |__$$ |\n");
	printf("\t\t\t\t\t\t   $$ |   $$    $$< $$    $$ |$$ |      $$  $$<   $$    |   $$    $$< \n");
	printf("\t\t\t\t\t\t   $$ |   $$$$$$$  |$$$$$$$$ |$$ |   __ $$$$$  \\  $$$$$/    $$$$$$$  |\n");
	printf("\t\t\t\t\t\t   $$ |   $$ |  $$ |$$ |  $$ |$$ \\__/  |$$ |$$  \\ $$ |_____ $$ |  $$ |\n");
	printf("\t\t\t\t\t\t   $$ |   $$ |  $$ |$$ |  $$ |$$    $$/ $$ | $$  |$$       |$$ |  $$ |\n");
	printf("\t\t\t\t\t\t   $$/    $$/   $$/ $$/   $$/  $$$$$$/  $$/   $$/ $$$$$$$$/ $$/   $$/ \n");
	
}

typedef struct {
    char category[50];
    char description[100];
    float amount;
    char username[50];  // New field to store the username associated with the record
} Record;

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS];
Record records[MAX_RECORDS];
int record_count = 0;
int user_count = 0;
int authenticated = 0;
char logged_in_user[50];  // Store the username of the logged-in user

void load_users();
void save_users();
void load_records();
void save_records();
void authenticate_user();
void add_record();
void update_record();
void delete_record();
void view_records();
void find_best_budget();
void menu();

int main() {
    start();
    int choice;
    load_users();
    load_records();
    authenticate_user();
    while(authenticated)
    {
        menu();
    }

    return 0;
}

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
    if (file != NULL) {
        while (fscanf(file, "%s\t%[^\t]\t%f\t%s", records[record_count].category, records[record_count].description, &records[record_count].amount, records[record_count].username) != EOF) {
            record_count++;
        }
        fclose(file);
    }
}

void save_records() {
    FILE *file = fopen("records.dat", "w");
    for (int i = 0; i < record_count; i++) {
        fprintf(file, "%s\t%s\t%.2f\t%s\n", records[i].category, records[i].description, records[i].amount, records[i].username);
    }
    fclose(file);
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
            strcpy(logged_in_user, username);  // Store the logged-in user's username
            menu();
            authenticated = 1;
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
    getchar(); // Consume newline left over by previous input
    fgets(records[record_count].category, sizeof(records[record_count].category), stdin);
    records[record_count].category[strcspn(records[record_count].category, "\n")] = 0;  // Remove newline

    printf("Enter description: ");
    fgets(records[record_count].description, sizeof(records[record_count].description), stdin);
    records[record_count].description[strcspn(records[record_count].description, "\n")] = 0;  // Remove newline

    printf("Enter amount: ");
    scanf("%f", &records[record_count].amount);
    strcpy(records[record_count].username, logged_in_user);  // Assign the logged-in user to the record

    record_count++;
    save_records();
    printf("Record added successfully.\n");
}
void update_record() {
    char description[100];
    printf("Enter the description of the record to update: ");
    scanf(" %[^\n]", description);

    for (int i = 0; i < record_count; i++) {
        // Check if the record belongs to the logged-in user and matches the description
        if (strcmp(records[i].description, description) == 0 && strcmp(records[i].username, logged_in_user) == 0) {
            printf("Enter new category: ");
            scanf("%s", records[i].category);
            printf("Enter new description: ");
            scanf(" %[^\n]", records[i].description);
            printf("Enter new amount: ");
            scanf("%f", &records[i].amount);

            save_records();
            printf("Record updated successfully.\n");
            return;
        }
    }
    printf("Record not found or does not belong to you.\n");
}
void delete_record() {
    char description[100];
    printf("Enter the description of the record to delete: ");
    scanf(" %[^\n]", description);

    for (int i = 0; i < record_count; i++) {
        // Check if the record belongs to the logged-in user and matches the description
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

    for (int i = 0; i < record_count; i++) {
        int found = 0;
        for (int j = 0; j < category_count; j++) {
            if (strcmp(categories[j], records[i].category) == 0) {
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

    float min_amount = total[0];
    char best_category[50];
    strcpy(best_category, categories[0]);

    for (int i = 1; i < category_count; i++) {
        if (total[i] < min_amount) {
            min_amount = total[i];
            strcpy(best_category, categories[i]);
        }
    }

    printf("Category with the best budget (lowest spending): %s, Amount: %.2f\n", best_category, min_amount);
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
            printf("Invalid choice.\n");
    }
}

