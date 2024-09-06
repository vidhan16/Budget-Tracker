#include "user_management.h"
#include <stdio.h>

int main() {
    load_users();
    load_records();
    int choice;
    printf("1. Register\n2. Authenticate\n3. Add Record\n4. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            register_user();
            break;
        case 2:
            authenticate_user();
            break;
        case 3:
            add_record();
            break;
        case 4:
            return 0;
    }
    return 0;
}
