#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int main(void) {
    int choice = 0;
    copy_menu();
    while (scanf("%d", &choice) != -1) {
        if (choice == 1 || choice == 2 || choice == 3) {
            if (choice == 3) {
                return 0;
            }
            cases(choice);
            copy_menu();
        } else {
              printf("Error value, try again, please");
          }
    }
    return 0;
}
