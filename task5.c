#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void list_files(const char* path) {
    DIR* dir = opendir(path);
    if (!dir) {
        perror("opendir");
        return;
    }

    struct dirent* entry;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        
        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
        printf("%s\n", fullpath);

        struct stat sb;
        if (stat(fullpath, &sb) == 0 && S_ISDIR(sb.st_mode)) {
            list_files(fullpath);
        }
    }
    closedir(dir);
}

int main() {
    list_files(".");
    return 0;
}
