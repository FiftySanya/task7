# Дослідження, моделювання та нестандартні підходи до аналізу процесів, файлових систем, безпеки та ресурсів в Linux

1) root ttyv0 Apr 30 19:07
root pts/0 Apr 30 19:08 (desktop-i0nq9nj)
--More--(END)
2) total 32
-rw-r--r--  1 root wheel   506 Apr 30 20:03 task1.c
-rwxr-xr-x  1 root wheel  8888 Apr 30 19:56 task1
-rw-r--r--  1 root wheel  2064 Apr 30 20:35 task2.c
-rwxr-xr-x  1 root wheel 11264 Apr 30 20:35 task2
-rw-r--r--  1 root wheel     0 Apr 30 20:35 task3.c
3) ./task3 freebsd text.txt
freebsd grep command
4) ./task4 task4.c task3.c
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
-- Натисніть Enter для продовження --

            if (line_count % 20 == 0) {
                printf("-- Натисніть Enter для продовження --\n");
                getchar();
            }
        }
        fclose(fp);
    }

    return 0;
}#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <word> <file>\n", argv[0]);
        return 1;
    }

    const char* word = argv[1];
-- Натисніть Enter для продовження --
5) ./task1.c
./task1
./task2.c
./task2
./task3.c
./text.txt
./task3
./task4.c
./task4
./task5.c
./task5_helper
./task5_helper/1.txt
./task5_helper/2.txt
./task5
6) task5_helper
task6_helper
7) 
