#ifndef USER_MANAGEMENT_H
#define USER_MANAGEMENT_H

#define MAX_USERS 100
#define MAX_RECORDS 100
#define MAX_CATEGORIES 20

typedef struct {
    char username[50];
    char password[50];
} User;

typedef struct {
    char category[50];
    char description[100];
    float amount;
    char username[50];
} Record;

// Declare global variables
extern User users[MAX_USERS];
extern Record records[MAX_RECORDS];
extern int user_count;
extern int record_count;
extern char logged_in_user[50];
extern int authenticated;

// Function prototypes
void load_users();
void save_users();
void load_records();
void save_records();
void authenticate_user();
void add_record();
void register_user();
void update_record();
void delete_record();
void view_records();
void find_best_budget();
void menu();

#endif // USER_MANAGEMENT_H
