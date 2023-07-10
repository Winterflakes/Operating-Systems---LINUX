#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

// Function to create a file
void createFile(const char* filename) {
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    
    if (fd == -1) {
        perror("Error creating file");
        return;
    }
    
    printf("File created successfully.\n");
    close(fd);
}

// Function to read contents of a file
void readFile(const char* filename) {
    int fd = open(filename, O_RDONLY);
    
    if (fd == -1) {
        perror("Error opening file");
        return;
    }
    
    char buffer[1024];
    ssize_t bytesRead;
    
    printf("File contents:\n");
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytesRead);
    }
    
    if (bytesRead == -1) {
        perror("Error reading file");
    }
    
    close(fd);
}

// Function to write to a file
void writeFile(const char* filename, const char* content) {
    int fd = open(filename, O_WRONLY | O_APPEND);
    
    if (fd == -1) {
        perror("Error opening file");
        return;
    }
    
    ssize_t bytesWritten = write(fd, content, strlen(content));
    
    if (bytesWritten == -1) {
        perror("Error writing to file");
    } else {
        printf("Successfully wrote %zd bytes to file.\n", bytesWritten);
    }
    
    close(fd);
}

// Function to read contents of a file in reverse order
void readReverse(const char* filename) {
    int fd = open(filename, O_RDONLY);
    
    if (fd == -1) {
        perror("Error opening file");
        return;
    }
    
    off_t fileSize = lseek(fd, 0, SEEK_END);
    
    char buffer;
    ssize_t bytesRead;
    
    printf("File contents in reverse order:\n");
    for (off_t i = fileSize - 1; i >= 0; i--) {
        lseek(fd, i, SEEK_SET);
        bytesRead = read(fd, &buffer, sizeof(buffer));
        if (bytesRead == -1) {
            perror("Error reading file");
            break;
        }
        write(STDOUT_FILENO, &buffer, bytesRead);
    }
    
    close(fd);
}

// Function to search for a pattern in a file
void searchPattern(const char* filename, const char* pattern) {
    int fd = open(filename, O_RDONLY);
    
    if (fd == -1) {
        perror("Error opening file");
        return;
    }
    
    char buffer[1024];
    ssize_t bytesRead;
    
    printf("Matching lines:\n");
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        char* occurrence = strstr(buffer, pattern);
        if (occurrence != NULL) {
            write(STDOUT_FILENO, buffer, bytesRead);
        }
    }
    
    if (bytesRead == -1) {
        perror("Error reading file");
    }
    
    close(fd);
}

// Function to delete a file
void deleteFile(const char* filename) {
    if (unlink(filename) == -1) {
        perror("Error deleting file");
    } else {
        printf("File deleted successfully.\n");
    }
}

// Function to print file status using stat
void printFileStatus(const char* filename) {
    struct stat fileStat;
    
    if (stat(filename, &fileStat) == -1) {
        perror("Error getting file status");
        return;
    }
    
    printf("File status:\n");
    printf("File Size: %ld bytes\n", fileStat.st_size);
    printf("Number of Links: %ld\n", fileStat.st_nlink);
    printf("File Permissions: %o\n", fileStat.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
}

// Function to print file status using fstat
void printFileStatusF(int fd) {
    struct stat fileStat;
    
    if (fstat(fd, &fileStat) == -1) {
        perror("Error getting file status");
        return;
    }
    
    printf("File status:\n");
    printf("File Size: %ld bytes\n", fileStat.st_size);
    printf("Number of Links: %ld\n", fileStat.st_nlink);
    printf("File Permissions: %o\n", fileStat.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
}

// Function to create a file with 4K bytes free space (file with holes)
void createFileWithHoles(const char* filename) {
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    
    if (fd == -1) {
        perror("Error creating file");
        return;
    }
    
    // Seek to the 4K byte position
    lseek(fd, 4 * 1024 - 1, SEEK_SET);
    
    // Write a single byte at the 4K byte position
    ssize_t bytesWritten = write(fd, "", 1);
    
    if (bytesWritten == -1) {
        perror("Error writing to file");
    } else {
        printf("File with holes created successfully.\n");
    }
    
    close(fd);
}

// Function to copy contents from one file to another
void copyFile(const char* sourceFile, const char* destFile) {
    int sourceFD = open(sourceFile, O_RDONLY);
    
    if (sourceFD == -1) {
        perror("Error opening source file");
        return;
    }
    
    int destFD = open(destFile, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    
    if (destFD == -1) {
        perror("Error creating destination file");
        close(sourceFD);
        return;
    }
    
    char buffer[1024];
    ssize_t bytesRead, bytesWritten;
    
    printf("Copying contents...\n");
    while ((bytesRead = read(sourceFD, buffer, sizeof(buffer))) > 0) {
        bytesWritten = write(destFD, buffer, bytesRead);
        if (bytesWritten == -1) {
            perror("Error writing to destination file");
            break;
        }
    }
    
    if (bytesRead == -1) {
        perror("Error reading source file");
    } else {
        printf("Contents copied successfully.\n");
    }
    
    close(sourceFD);
    close(destFD);
}

int main() {
    char filename1[100];
    char filename2[100];
    char pattern[100];
    char content[1000];
    
    // Create a file
    printf("Enter filename to create: ");
    scanf("%s", filename1);
    createFile(filename1);
    
    // Write to a file
    printf("Enter filename to write: ");
    scanf("%s", filename1);
    printf("Enter content to write:```");
    scanf(" %[^\n]s", content);
    writeFile(filename1, content);
    
    // Read contents of a file
    printf("Enter filename to read: ");
    scanf("%s", filename1);
    readFile(filename1);
    
    // Read contents of a file in reverse order
    printf("Enter filename to read in reverse: ");
    scanf("%s", filename1);
    readReverse(filename1);
    
    // Search for a pattern in a file
    printf("Enter filename to search: ");
    scanf("%s", filename1);
    printf("Enter pattern to search: ");
    scanf("%s", pattern);
    searchPattern(filename1, pattern);
    
    // Delete a file
    printf("Enter filename to delete: ");
    scanf("%s", filename1);
    deleteFile(filename1);
    
    // Print file status using stat
    printf("Enter filename to get status: ");
    scanf("%s", filename1);
    printFileStatus(filename1);
    
    // Print file status using fstat
    printf("Enter filename to get status with fstat: ");
    scanf("%s", filename1);
    int fd = open(filename1, O_RDONLY);
    printFileStatusF(fd);
    close(fd);
    
    // Create a file with holes
    printf("Enter filename to create file with holes: ");
    scanf("%s", filename1);
    createFileWithHoles(filename1);
    
    // Copy contents from one file to another
    printf("Enter source filename to copy: ");
    scanf("%s", filename1);
    printf("Enter destination filename: ");
    scanf("%s", filename2);
    copyFile(filename1, filename2);
    
    return 0;
}
