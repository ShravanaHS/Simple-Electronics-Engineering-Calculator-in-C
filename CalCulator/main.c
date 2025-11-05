#include <stdio.h>
#include "math_ops.h"
#include "ohms_law.h"
#include "inductor_calc.h"
#include "resistor_calc.h"
#include "capacitor_calc.h"




int main(void) {
    int choice;

    do {
        printf("\n==== ELECTRONICS CALCULATOR ====\n");
        printf("5. Inductor Calculations\n");
        printf("4. Capacitor Calculations\n");
        printf("3. Resistor Calculations\n");
        printf("2. Ohm's Law & Power\n");
        printf("1. Mathematical Operations\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 5:
                 inductor_menu();
                  break;

            case 4:
                capacitor_menu();
                break;

            case 3:
                resistor_menu();
                break;
            case 2: 
                ohms_menu(); 
                break;
            case 1:
                math_menu();
                break;
            case 0:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid option.\n");
        }

    } while(choice != 0);

    return 0;
}
