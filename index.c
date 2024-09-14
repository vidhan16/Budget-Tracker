#include "user_management.h"
#include <stdio.h>
void start(){
	printf("\n\n\n\n");
	printf("\t\t\t\t\t       _______   __    __  _______    ______   ________  ________     \n");
	printf("\t\t\t\t\t      /       \\ /  |  /  |/       \\  /      \\ /        |/        |    \n");
	printf("\t\t\t\t\t      $$$$$$$  |$$ |  $$ |$$$$$$$  |/$$$$$$  |$$$$$$$$/ $$$$$$$$/     \n");
	printf("\t\t\t\t\t      $$ |__$$ |$$ |  $$ |$$ |  $$ |$$ | _$$/ $$ |__       $$ |       \n");
	printf("\t\t\t\t\t      $$    $$< $$ |  $$ |$$ |  $$ |$$ |/    |$$    |      $$ |       \n");
	printf("\t\t\t\t\t      $$$$$$$  |$$ |  $$ |$$ |  $$ |$$ |$$$$ |$$$$$/       $$ |       \n");
	printf("\t\t\t\t\t      $$ |__$$ |$$ \\__$$ |$$ |__$$ |$$ \\__$$ |$$ |_____    $$ |       \n");
	printf("\t\t\t\t\t      $$    $$/ $$    $$/ $$    $$/ $$    $$/ $$       |   $$ |       \n");
	printf("\t\t\t\t\t      $$$$$$$/   $$$$$$/  $$$$$$$/   $$$$$$/  $$$$$$$$/    $$/        \n");
	printf("\t\t\t\t\t ________  _______    ______    ______   __    __  ________  _______  \n");
	printf("\t\t\t\t\t/        |/       \\  /      \\  /      \\ /  |  /  |/        |/       \\ \n");
	printf("\t\t\t\t\t$$$$$$$$/ $$$$$$$  |/$$$$$$  |/$$$$$$  |$$ | /$$/ $$$$$$$$/ $$$$$$$  |\n");
	printf("\t\t\t\t\t   $$ |   $$ |__$$ |$$ |__$$ |$$ |  $$/ $$ |/$$/  $$ |__    $$ |__$$ |\n");
	printf("\t\t\t\t\t   $$ |   $$    $$< $$    $$ |$$ |      $$  $$<   $$    |   $$    $$< \n");
	printf("\t\t\t\t\t   $$ |   $$$$$$$  |$$$$$$$$ |$$ |   __ $$$$$  \\  $$$$$/    $$$$$$$  |\n");
	printf("\t\t\t\t\t   $$ |   $$ |  $$ |$$ |  $$ |$$ \\__/  |$$ |$$  \\ $$ |_____ $$ |  $$ |\n");
	printf("\t\t\t\t\t   $$ |   $$ |  $$ |$$ |  $$ |$$    $$/ $$ | $$  |$$       |$$ |  $$ |\n");
	printf("\t\t\t\t\t   $$/    $$/   $$/ $$/   $$/  $$$$$$/  $$/   $$/ $$$$$$$$/ $$/   $$/ \n");
}
int main() {
    start();
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
