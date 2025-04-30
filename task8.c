#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    const char *dir_path = (argc > 1) ? argv[1] : ".";

    DIR* dir = opendir(dir_path);
    if (!dir) {
        perror("opendir");
        return 1;
    }

    printf("Видалити всі файли в директорії %s? (y/n): ", dir_path);
    char response[10];
    fgets(response, sizeof(response), stdin);

    struct dirent* entry;
    if (response[0] == 'y' || response[0] == 'Y') {
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            char filepath[1024];
            snprintf(filepath, sizeof(filepath), "%s/%s", dir_path, entry->d_name);
            struct stat sb;
            if (stat(filepath, &sb) == -1) {
                if (errno != ENOENT) {
                    fprintf(stderr, "Не вдалося отримати інформацію про %s: %s\n", 
                            filepath, strerror(errno));
                }
                continue;
            }
            
            if (S_ISREG(sb.st_mode)) {
                if (unlink(filepath) == -1) {
                    perror("unlink");
                } 
                else {
                    printf("Файл %s видалено.\n", entry->d_name);
                }
            }
        }
    } 
    else {
        printf("Поелементне видалення файлів:\n");
        int found_files = 0;
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            char filepath[1024];
            snprintf(filepath, sizeof(filepath), "%s/%s", dir_path, entry->d_name);
            struct stat sb;

            if (stat(filepath, &sb) == -1) {
                if (errno != ENOENT) {
                    fprintf(stderr, "Не вдалося отримати інформацію про %s: %s\n", 
                            filepath, strerror(errno));
                }
                continue;
            }

            if (S_ISREG(sb.st_mode)) {
                found_files++;
                printf("Видалити файл %s? (y/n): ", entry->d_name);
                fgets(response, sizeof(response), stdin);
                if (response[0] == 'y' || response[0] == 'Y') {
                    if (unlink(filepath) == -1) {
                        perror("unlink");
                    } 
                    else {
                        printf("Файл %s видалено.\n", entry->d_name);
                    }
                }
            }
        }

        if (found_files == 0) {
            printf("Звичайних файлів для видалення не знайдено.\n");
        }
    }
    closedir(dir);

    return 0;
}
