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
} Record;

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS];
Record records[MAX_RECORDS];
int record_count = 0;
int user_count = 0;
int record_it = 0;
int record_end = 0;

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
    while(1)
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
        while (fscanf(file, "%s %s %f", records[record_count].category, records[record_count].description, &records[record_count].amount) != EOF) {
            record_count++;
        }
        fclose(file);
    }
}

void save_records() {
    FILE *file = fopen("records.dat", "w");
    for (int i = 0; i < record_count; i++) {
        fprintf(file, "%s %s %.2f\n", records[i].category, records[i].description, records[i].amount);
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
            record_it = i;
            record_end = i;
            menu();
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
    if(record_end == record_it)
    {
        record_end--;
    }
    printf("Enter category: ");
    scanf("%s", records[record_count].category);
    printf("Enter description: ");
    scanf(" %[^\n]", records[record_count].description);
    printf("Enter amount: ");
    scanf("%f", &records[record_count].amount);

    record_end++;

    record_count++;
    save_records();
    printf("Record added successfully.\n");
}

void update_record() {
    char description[100];
    printf("Enter the description of the record to update: ");
    scanf(" %[^\n]", description);

    for (int i = 0; i < record_count; i++) {
        if (strcmp(records[i].description, description) == 0) {
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
    printf("Record not found.\n");
}

void delete_record() {
    char description[100];
    printf("Enter the description of the record to delete: ");
    scanf(" %[^\n]", description);

    for (int i = 0; i < record_count; i++) {
        if (strcmp(records[i].description, description) == 0) {
            for (int j = i; j < record_count - 1; j++) {
                records[j] = records[j + 1];
            }
            record_count--;
            save_records();
            printf("Record deleted successfully.\n");
            return;
        }
    }
    printf("Record not found.\n");
}

void view_records() {
    printf("Records:\n");
    if(records[record_it].category[0]!='\0')
    {
        for(int i = record_it ; i <= record_end ; i++)
        printf("Category: %s, Description: %s, Amount: %.2f\n",
        records[i].category, records[i].description, records[i].amount);
    }
    else
    {
        printf("No records found for the person..\n");
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
        default:
            printf("Invalid choice.\n");
    }
}
