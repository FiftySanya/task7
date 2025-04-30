#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
    uid_t uid = getuid();
    struct passwd* pwd = getpwuid(uid);
    if (!pwd) {
        perror("getpwuid");
        return 1;
    }

    gid_t primary_gid = pwd->pw_gid;
    struct group* primary_grp = getgrgid(primary_gid);
    if (!primary_grp) {
        perror("getgrgid");
        return 1;
    }
    printf("Первинна група: %s\n", primary_grp->gr_name);

    int ngroups = 0;
    getgrouplist(pwd->pw_name, primary_gid, NULL, &ngroups);
    gid_t* groups = malloc(ngroups * sizeof(gid_t));
    if (!groups) {
        perror("malloc");
        return 1;
    }
    getgrouplist(pwd->pw_name, primary_gid, groups, &ngroups);

    gid_t unique_groups[ngroups + 1];
    int unique_count = 0;
    unique_groups[unique_count++] = primary_gid;

    for (int i = 0; i < ngroups; ++i) {
        int is_unique = 1;
        for (int j = 0; j < unique_count; ++j) {
            if (groups[i] == unique_groups[j]) {
                is_unique = 0;
                break;
            }
        }
        if (is_unique) {
            unique_groups[unique_count++] = groups[i];
        }
    }

    printf("Групи користувача:\n");
    for (int i = 0; i < unique_count; ++i) {
        struct group* grp = getgrgid(unique_groups[i]);
        if (grp) {
            printf("  Група: %s\n", grp->gr_name);
            printf("    Члени: ");
            char** members = grp->gr_mem;
            while (*members) {
                printf("%s ", *members);
                members++;
            }
            printf("\n");
        }
    }
    free(groups);

    return 0;
}
