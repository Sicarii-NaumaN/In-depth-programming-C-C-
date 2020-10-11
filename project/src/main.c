#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int main(void) {
    char var[256];
    copy_menu();
    while (scanf("%4s", var) != -1) {
        int choice = atoi(var);
        if (choice == 1 || choice == 2 || choice == 3) {
            if (choice == 3) {
                return 0;
            }
            cases(choice);
            copy_menu();
        } else {
              printf("%s", "Error value, try again, please\n");
          }
    }
    return 0;
}
