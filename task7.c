#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void print_permissions(mode_t mode) {
    printf((S_ISDIR(mode)) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}

void print_file_info(const char* filename, struct stat* sb) {
    printf("Права доступу: ");
    print_permissions(sb->st_mode);
    printf("\nВласник: %s\n", getpwuid(sb->st_uid)->pw_name);
    printf("Група: %s\n", getgrgid(sb->st_gid)->gr_name);
    printf("Розмір: %lld байт\n", (long long)sb->st_size);
}

int main() {
    uid_t uid = getuid();
    DIR* dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".c") == entry->d_name + strlen(entry->d_name) - 2) {
            struct stat sb;

            if (stat(entry->d_name, &sb) == 0 && sb.st_uid == uid) {
                printf("Файл: %s\n", entry->d_name);
                print_file_info(entry->d_name, &sb);

                if (sb.st_mode & S_IROTH) {
                    printf("Дозвіл на читання для інших уже встановлено.\n\n");
                    continue;
                }

                printf("Надати іншим дозвіл на читання? (y/n): ");
                char response[10];
                fgets(response, sizeof(response), stdin);

                if (response[0] == 'y' || response[0] == 'Y') {
                    if (chmod(entry->d_name, sb.st_mode | S_IROTH) == -1) {
                        perror("chmod");
                    }
                    else {
                        printf("Права доступу оновлено.\n");
                        if (stat(entry->d_name, &sb) == 0) {
                            printf("Нові права доступу: ");
                            print_permissions(sb.st_mode);
                            printf("\n");
                        }
                    }
                }
                printf("\n");
            }
        }
    }
    closedir(dir);

    return 0;
}
