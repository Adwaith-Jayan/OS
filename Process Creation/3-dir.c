#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

void display_file_status(const char *directory) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;

    // Open the directory
    dir = opendir(directory);
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    // Read directory entries
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".." entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construct full path
        char file_path[PATH_MAX];
        snprintf(file_path, sizeof(file_path), "%s/%s", directory, entry->d_name);

        // Get file status
        if (stat(file_path, &file_stat) == -1) {
            perror("stat");
            exit(EXIT_FAILURE);
        }

        // Calculate file size in bits
        long long file_size_bits = (long long)file_stat.st_size * 8;

        // Display file status
        printf("File: %s\n", entry->d_name);
        printf("Size: %lld bits\n", file_size_bits);
        printf("Last modified: %ld\n", file_stat.st_mtime);
        printf("Owner User ID: %d\n", file_stat.st_uid);
        printf("Group ID: %d\n", file_stat.st_gid);
        printf("Mode: %o\n", file_stat.st_mode);
        printf("========================================\n");
    }

    // Close the directory
    closedir(dir);
}

int main() {
    // Get the current working directory
    char current_directory[PATH_MAX];
    if (getcwd(current_directory, sizeof(current_directory)) == NULL) {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }

    // Display status of files in the current directory
    display_file_status(current_directory);

    return 0;
}

