#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

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

int main() {
    DIR* dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    long long total = 0;
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        struct stat sb;
        if (stat(entry->d_name, &sb) == 0) {
            total += sb.st_blocks;
        }
    }
    printf("total %lld\n", total / 2);

    rewinddir(dir); // повертає позицію потоку каталогу до початку

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        struct stat sb;
        if (stat(entry->d_name, &sb) == -1) {
            perror("stat");
            continue;
        }

        print_permissions(sb.st_mode);
        printf(" %2ld", sb.st_nlink);
        struct passwd* pwd = getpwuid(sb.st_uid);
        struct group* grp = getgrgid(sb.st_gid);
        printf(" %s %s", pwd ? pwd->pw_name : "unknown", grp ? grp->gr_name : "unknown");
        printf(" %5lld", (long long)sb.st_size);
        char timebuf[20];
        strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&sb.st_mtime));
        printf(" %s %s\n", timebuf, entry->d_name);
    }
    
    closedir(dir);

    return 0;
}
