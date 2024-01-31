// Enumeration in C

#include <stdio.h>

int main(void) {
    enum Color { RED = 0, GREEN, BLUE};
    enum Color background = GREEN;
    switch (background) {
        case RED: 
            printf("Color is RED\n"); break;
        default:
            printf("Color is not RED\n"); break;
    }
    return 0;
}