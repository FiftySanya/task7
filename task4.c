#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> [file2 ...]\n", argv[0]);
        return 1;
    }

    int line_count = 0;
    for (int i = 1; i < argc; i++) {
        FILE* fp = fopen(argv[i], "r");
        if (!fp) {
            perror("fopen");
            continue;
        }

        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), fp)) {
            printf("%s", buffer);
            line_count++;
            if (line_count % 20 == 0) {
                printf("-- Натисніть Enter для продовження --\n");
                getchar();
            }
        }
        fclose(fp);
    }

    return 0;
}
