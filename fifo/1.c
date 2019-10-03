#include <stdio.h>
#include <math.h>

int main() {
    int i;
    float f = 1.5f;
    unsigned char (*a)[sizeof(f)];
    a = &f;
    printf("1.5 in bytes: ");
    for (i = 0; i < sizeof(f); ++i)
        printf("%.2x ",(*a)[i]);

    printf("\n\nDiv by zero: %f\n\n",1.0 / 0.0);

     // thanks to Belokon':
    printf("Zero to zeroth power: %f -- surprise! (thanks to IEEE 754)\n\n",pow(0.0, 0.0));

    printf("Zero div by zero: %f\n", 0.0 / 0.0);
}
