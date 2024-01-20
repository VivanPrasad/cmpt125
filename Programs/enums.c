// Enumeration in C

#include <stdio.h>

int main(void) {
    enum Color {
        RED = 0,
        GREEN,
        BLUE
    };
    enum Color background = RED;
    switch (background) {
        case 0: 
            printf("Color is RED\n");
            break;
        case 1:
            printf("Color is GREEN\n");
            break;
        case 2:
            printf("Color is not BLUE\n");
            break;
    }
    return 0;
}