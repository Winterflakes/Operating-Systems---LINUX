#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

void create_directory(char *dirname) {
    int result = mkdir(dirname, 0777);
    if (result == -1) {
        printf("Failed to create directory.\n");
    } else {
        printf("Directory '%s' created successfully.\n", dirname);
    }
}

void remove_directory(char *dirname) {
    int result = rmdir(dirname);
    if (result == -1) {
        printf("Failed to remove directory.\n");
    } else {
        printf("Directory '%s' removed successfully.\n", dirname);
    }
}

void change_directory(char *dirname) {
    int result = chdir(dirname);
    if (result == -1) {
        printf("Failed to change directory.\n");
    } else {
        printf("Changed directory to '%s'.\n", dirname);
    }
}

void list_directory() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if (dir == NULL) {
        printf("Failed to open directory.\n");
        return;
    }

    printf("Contents of current directory:\n");
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
}

void scan_directory() {
    struct dirent **namelist;
    int count;

    count = scandir(".", &namelist, NULL, alphasort);
    if (count == -1) {
        printf("Failed to scan directory.\n");
        return;
    }

    printf("Contents of current directory:\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", namelist[i]->d_name);
        free(namelist[i]);
    }
    free(namelist);
}

int main() {
    int choice;
    char dirname[256];

    while (1) {
        printf("Select an option:\n");
        printf("1. Create Directory\n");
        printf("2. Remove Directory\n");
        printf("3. List Directory (readdir)\n");
        printf("4. Change Directory\n");
        printf("5. List Directory (scandir)\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter directory name to create: ");
                scanf("%s", dirname);
                create_directory(dirname);
                break;
            case 2:
                printf("Enter directory name to remove: ");
                scanf("%s", dirname);
                remove_directory(dirname);
                break;
            case 3:
                list_directory();
                break;
            case 4:
                printf("Enter directory name to change: ");
                scanf("%s", dirname);
                change_directory(dirname);
                break;
            case 5:
                scan_directory();
                break;
            case 6:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice.\n");
                break;
        }

        printf("\n");
    }

    return 0;
}
