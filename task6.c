#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

int main() {
    DIR* dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    struct dirent* entry;
    char* dirs[1024];
    int dir_count = 0;

    while ((entry = readdir(dir)) != NULL) {
        struct stat sb;
        if (stat(entry->d_name, &sb) == 0 && S_ISDIR(sb.st_mode)) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                dirs[dir_count++] = strdup(entry->d_name);
            }
        }
    }
    closedir(dir);

    qsort(dirs, dir_count, sizeof(char*), compare);
    for (int i = 0; i < dir_count; ++i) {
        printf("%s\n", dirs[i]);
        free(dirs[i]);
    }
    
    return 0;
}
