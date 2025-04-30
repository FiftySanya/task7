#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand48(time(NULL));

    printf("Випадкові числа від 0.0 до 1.0:\n");
    for (int i = 0; i < 5; ++i) {
        printf("%f\n", drand48());
    }

    double n = 10.0;
    printf("Випадкові числа від 0.0 до %f:\n", n);
    for (int i = 0; i < 5; ++i) {
        printf("%f\n", drand48() * n);
    }
    
    return 0;
}
