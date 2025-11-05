#include <stdio.h>
#include <math.h>
#include "ohms_law.h"
#include "math_ops.h"  // for parse_with_prefix, print_with_prefix, div_safe

/* Utility: prompt and parse a value (supports prefixes) */
static float input_value(const char *prompt) {
    char buf[64];
    printf("%s", prompt);
    scanf("%63s", buf);
    return parse_with_prefix(buf);
}

/* Menu and calculators */
void ohms_menu(void) {
    int choice;

    do {
        printf("\n==== OHM'S LAW & POWER CALCULATOR ====\n");
        printf("1. Calculate Voltage (V)\n");
        printf("2. Calculate Current (I)\n");
        printf("3. Calculate Resistance (R)\n");
        printf("4. Calculate Power (P)\n");
        printf("0. Return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        if (choice == 0) break;

        switch (choice) {
            case 1: { /* Voltage */
                int sub;
                printf("\nCalculate V using:\n");
                printf("1) I and R (V = I * R)\n");
                printf("2) P and I (V = P / I)\n");
                printf("3) P and R (V = sqrt(P * R))\n");
                printf("Select option: ");
                scanf("%d", &sub);

                if (sub == 1) {
                    float I = input_value("Enter current I (e.g. 10m, 2.2A): ");
                    float R = input_value("Enter resistance R (e.g. 4.7k, 220): ");
                    float V = I * R;
                    printf("Voltage = ");
                    print_with_prefix(V, "V");
                } else if (sub == 2) {
                    float P = input_value("Enter power P (e.g. 250m, 1W): ");
                    float I = input_value("Enter current I (e.g. 10m, 2.2A): ");
                    if (I == 0.0f) {
                        printf("Error: Division by zero (I = 0)\n");
                    } else {
                        float V = P / I;
                        printf("Voltage = ");
                        print_with_prefix(V, "V");
                    }
                } else if (sub == 3) {
                    float P = input_value("Enter power P (e.g. 250m, 1W): ");
                    float R = input_value("Enter resistance R (e.g. 4.7k, 220): ");
                    if (P < 0.0f || R < 0.0f) {
                        printf("Error: Negative value not allowed for sqrt(P*R).\n");
                    } else {
                        float V = sqrtf(P * R);
                        printf("Voltage = ");
                        print_with_prefix(V, "V");
                    }
                } else {
                    printf("Invalid option.\n");
                }
                break;
            }

            case 2: { /* Current */
                int sub;
                printf("\nCalculate I using:\n");
                printf("1) V and R (I = V / R)\n");
                printf("2) P and V (I = P / V)\n");
                printf("3) P and R (I = sqrt(P / R))\n");
                printf("Select option: ");
                scanf("%d", &sub);

                if (sub == 1) {
                    float V = input_value("Enter voltage V (e.g. 5, 12V): ");
                    float R = input_value("Enter resistance R (e.g. 1k, 330): ");
                    int ok;
                    float I = div_safe(V, R, &ok);
                    if (!ok) printf("Error: Division by zero (R = 0)\n");
                    else {
                        printf("Current = ");
                        print_with_prefix(I, "A");
                    }
                } else if (sub == 2) {
                    float P = input_value("Enter power P (e.g. 1W, 250m): ");
                    float V = input_value("Enter voltage V (e.g. 5, 12V): ");
                    if (V == 0.0f) {
                        printf("Error: Division by zero (V = 0)\n");
                    } else {
                        float I = P / V;
                        printf("Current = ");
                        print_with_prefix(I, "A");
                    }
                } else if (sub == 3) {
                    float P = input_value("Enter power P (e.g. 250m, 1W): ");
                    float R = input_value("Enter resistance R (e.g. 4.7k, 220): ");
                    if (R <= 0.0f) {
                        printf("Error: R must be > 0 for sqrt(P/R).\n");
                    } else if (P < 0.0f) {
                        printf("Error: P must be >= 0 for sqrt(P/R).\n");
                    } else {
                        float I = sqrtf(P / R);
                        printf("Current = ");
                        print_with_prefix(I, "A");
                    }
                } else {
                    printf("Invalid option.\n");
                }
                break;
            }

            case 3: { /* Resistance */
                int sub;
                printf("\nCalculate R using:\n");
                printf("1) V and I (R = V / I)\n");
                printf("2) V and P (R = V^2 / P)\n");
                printf("3) P and I (R = P / I^2)\n");
                printf("Select option: ");
                scanf("%d", &sub);

                if (sub == 1) {
                    float V = input_value("Enter voltage V (e.g. 5, 12V): ");
                    float I = input_value("Enter current I (e.g. 10m, 2A): ");
                    if (I == 0.0f) {
                        printf("Error: Division by zero (I = 0)\n");
                    } else {
                        float R = V / I;
                        printf("Resistance = ");
                        print_with_prefix(R, "Ω");
                    }
                } else if (sub == 2) {
                    float V = input_value("Enter voltage V (e.g. 12V): ");
                    float P = input_value("Enter power P (e.g. 1W): ");
                    if (P == 0.0f) {
                        printf("Error: Division by zero (P = 0)\n");
                    } else {
                        float R = (V * V) / P;
                        printf("Resistance = ");
                        print_with_prefix(R, "Ω");
                    }
                } else if (sub == 3) {
                    float P = input_value("Enter power P (e.g. 250m, 1W): ");
                    float I = input_value("Enter current I (e.g. 10m, 2A): ");
                    if (I == 0.0f) {
                        printf("Error: Division by zero (I = 0)\n");
                    } else {
                        float R = P / (I * I);
                        printf("Resistance = ");
                        print_with_prefix(R, "Ω");
                    }
                } else {
                    printf("Invalid option.\n");
                }
                break;
            }

            case 4: { /* Power */
                int sub;
                printf("\nCalculate P using:\n");
                printf("1) V and I (P = V * I)\n");
                printf("2) V and R (P = V^2 / R)\n");
                printf("3) I and R (P = I^2 * R)\n");
                printf("Select option: ");
                scanf("%d", &sub);

                if (sub == 1) {
                    float V = input_value("Enter voltage V (e.g. 5, 12V): ");
                    float I = input_value("Enter current I (e.g. 10m, 2A): ");
                    float P = V * I;
                    printf("Power = ");
                    print_with_prefix(P, "W");
                } else if (sub == 2) {
                    float V = input_value("Enter voltage V (e.g. 12V): ");
                    float R = input_value("Enter resistance R (e.g. 1k, 220): ");
                    if (R == 0.0f) {
                        printf("Error: Division by zero (R = 0)\n");
                    } else {
                        float P = (V * V) / R;
                        printf("Power = ");
                        print_with_prefix(P, "W");
                    }
                } else if (sub == 3) {
                    float I = input_value("Enter current I (e.g. 10m, 2A): ");
                    float R = input_value("Enter resistance R (e.g. 1k, 220): ");
                    float P = (I * I) * R;
                    printf("Power = ");
                    print_with_prefix(P, "W");
                } else {
                    printf("Invalid option.\n");
                }
                break;
            }

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 0);
}
