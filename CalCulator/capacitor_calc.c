#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h> 
#include <stdlib.h>
#include "math_ops.h"
#include "capacitor_calc.h"

/* ────────────────────────────────────────────────
   BASIC CAPACITOR FORMULAS
   ──────────────────────────────────────────────── */

/* Series: 1/Ceq = 1/C1 + 1/C2 + ...  */
/* Parallel: Ceq = C1 + C2 + ...      */

static void series_cap_calc(void) {
    int n;
    printf("Enter number of capacitors in series: ");
    scanf("%d", &n);
    if (n <= 0) { printf("Invalid number.\n"); return; }

    float inv_total = 0.0;
    for (int i = 0; i < n; i++) {
        printf("C%d: ", i + 1);
        char buf[32];
        scanf("%31s", buf);
        float C = parse_with_prefix(buf);
        if (C == 0.0f) { printf("Error: Capacitance cannot be zero.\n"); return; }
        inv_total += 1.0f / C;
    }
    float total = 1.0f / inv_total;
    printf("Equivalent Series Capacitance = ");
    print_with_prefix(total, "F");
}

static void parallel_cap_calc(void) {
    int n;
    printf("Enter number of capacitors in parallel: ");
    scanf("%d", &n);
    if (n <= 0) { printf("Invalid number.\n"); return; }

    float total = 0.0;
    for (int i = 0; i < n; i++) {
        printf("C%d: ", i + 1);
        char buf[32];
        scanf("%31s", buf);
        total += parse_with_prefix(buf);
    }
    printf("Equivalent Parallel Capacitance = ");
    print_with_prefix(total, "F");
}

/* ────────────────────────────────────────────────
   Q, ENERGY, TIME CONSTANT, REACTANCE
   ──────────────────────────────────────────────── */

static void charge_calc(void) {
    char buf1[32], buf2[32];
    printf("Enter capacitance (F, supports prefixes): ");
    scanf("%31s", buf1);
    printf("Enter voltage (V): ");
    scanf("%31s", buf2);

    float C = parse_with_prefix(buf1);
    float V = parse_with_prefix(buf2);
    float Q = C * V;

    printf("Charge (Q = C × V) = ");
    print_with_prefix(Q, "C");
}

static void energy_calc(void) {
    char buf1[32], buf2[32];
    printf("Enter capacitance (F): ");
    scanf("%31s", buf1);
    printf("Enter voltage (V): ");
    scanf("%31s", buf2);

    float C = parse_with_prefix(buf1);
    float V = parse_with_prefix(buf2);
    float E = 0.5f * C * V * V;

    printf("Energy Stored (E = ½CV²) = ");
    print_with_prefix(E, "J");
}

static void time_constant_calc(void) {
    char buf1[32], buf2[32];
    printf("Enter resistance (Ω): ");
    scanf("%31s", buf1);
    printf("Enter capacitance (F): ");
    scanf("%31s", buf2);

    float R = parse_with_prefix(buf1);
    float C = parse_with_prefix(buf2);
    float tau = R * C;

    printf("Time Constant (τ = R × C) = ");
    print_with_prefix(tau, "s");
}

static void reactance_calc(void) {
    char buf1[32], buf2[32];
    printf("Enter frequency (Hz): ");
    scanf("%31s", buf1);
    printf("Enter capacitance (F): ");
    scanf("%31s", buf2);

    float f = parse_with_prefix(buf1);
    float C = parse_with_prefix(buf2);

    if (f == 0.0f || C == 0.0f) { printf("Invalid input.\n"); return; }

    float Xc = 1.0f / (2.0f * 3.14 * f * C);
    printf("Capacitive Reactance (Xc = 1/2πfC) = ");
    print_with_prefix(Xc, "Ω");
}

/* ────────────────────────────────────────────────
   SMD CAPACITOR CODE SECTION
   ──────────────────────────────────────────────── */

static void smd_cap_decode(void) {
    char code[8];
    printf("Enter capacitor code (e.g. 104, 472, 225): ");
    scanf("%7s", code);

    int len = strlen(code);
    if (len != 3 || !(isdigit(code[0]))) {
        printf("Invalid code format.\n");
        return;
    }

    int digits = atoi(code);
    int multiplier = digits % 10;
    int base = digits / 10;

    float value_pf = base * pow(10, multiplier); // value in pF
    printf("Capacitance ≈ ");
    if (value_pf >= 1e6)
        printf("%.3f µF\n", value_pf / 1e6);
    else if (value_pf >= 1e3)
        printf("%.3f nF\n", value_pf / 1e3);
    else
        printf("%.3f pF\n", value_pf);
}

/* ────────────────────────────────────────────────
   MAIN MENU
   ──────────────────────────────────────────────── */

void capacitor_menu(void) {
    int choice;
    do {
        printf("\n==== CAPACITOR CALCULATOR ====\n");
        printf("1. Series Combination\n");
        printf("2. Parallel Combination\n");
        printf("3. Charge (Q = C × V)\n");
        printf("4. Energy (E = ½CV²)\n");
        printf("5. Time Constant (τ = R × C)\n");
        printf("6. Reactance (Xc = 1/2πfC)\n");
        printf("7. Decode SMD Capacitor Code\n");
        printf("0. Return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: series_cap_calc(); break;
            case 2: parallel_cap_calc(); break;
            case 3: charge_calc(); break;
            case 4: energy_calc(); break;
            case 5: time_constant_calc(); break;
            case 6: reactance_calc(); break;
            case 7: smd_cap_decode(); break;
            case 0: break;
            default: printf("Invalid option.\n");
        }
    } while (choice != 0);
}
