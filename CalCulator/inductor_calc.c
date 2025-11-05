#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include "math_ops.h"
#include "inductor_calc.h"

/* ────────────────────────────────────────────────
   BASIC INDUCTOR FORMULAS
   ──────────────────────────────────────────────── */

/* Series: L_total = L1 + L2 + L3 ... */
/* Parallel: 1/L_total = 1/L1 + 1/L2 + ... */

static void series_ind_calc(void) {
    int n;
    printf("Enter number of inductors in series: ");
    scanf("%d", &n);
    if (n <= 0) { printf("Invalid number.\n"); return; }

    float total = 0.0f;
    for (int i = 0; i < n; i++) {
        printf("L%d: ", i + 1);
        char buf[32];
        scanf("%31s", buf);
        total += parse_with_prefix(buf);
    }

    printf("Equivalent Series Inductance = ");
    print_with_prefix(total, "H");
}

static void parallel_ind_calc(void) {
    int n;
    printf("Enter number of inductors in parallel: ");
    scanf("%d", &n);
    if (n <= 0) { printf("Invalid number.\n"); return; }

    float inv_total = 0.0f;
    for (int i = 0; i < n; i++) {
        printf("L%d: ", i + 1);
        char buf[32];
        scanf("%31s", buf);
        float L = parse_with_prefix(buf);
        if (L == 0.0f) { printf("Error: Inductance cannot be zero.\n"); return; }
        inv_total += 1.0f / L;
    }

    float total = 1.0f / inv_total;
    printf("Equivalent Parallel Inductance = ");
    print_with_prefix(total, "H");
}

/* ────────────────────────────────────────────────
   ENERGY, TIME CONSTANT, REACTANCE
   ──────────────────────────────────────────────── */

static void energy_calc(void) {
    char buf1[32], buf2[32];
    printf("Enter inductance (H): ");
    scanf("%31s", buf1);
    printf("Enter current (A): ");
    scanf("%31s", buf2);

    float L = parse_with_prefix(buf1);
    float I = parse_with_prefix(buf2);
    float E = 0.5f * L * I * I;

    printf("Energy Stored (E = ½LI²) = ");
    print_with_prefix(E, "J");
}

static void time_constant_calc(void) {
    char buf1[32], buf2[32];
    printf("Enter inductance (H): ");
    scanf("%31s", buf1);
    printf("Enter resistance (Ω): ");
    scanf("%31s", buf2);

    float L = parse_with_prefix(buf1);
    float R = parse_with_prefix(buf2);
    if (R == 0.0f) { printf("Error: Resistance cannot be zero.\n"); return; }

    float tau = L / R;
    printf("Time Constant (τ = L / R) = ");
    print_with_prefix(tau, "s");
}

static void reactance_calc(void) {
    char buf1[32], buf2[32];
    printf("Enter frequency (Hz): ");
    scanf("%31s", buf1);
    printf("Enter inductance (H): ");
    scanf("%31s", buf2);

    float f = parse_with_prefix(buf1);
    float L = parse_with_prefix(buf2);

    if (f == 0.0f || L == 0.0f) { printf("Invalid input.\n"); return; }

    float Xl = 2.0f * 3.14 * f * L;
    printf("Inductive Reactance (Xl = 2πfL) = ");
    print_with_prefix(Xl, "Ω");
}

/* ────────────────────────────────────────────────
   SMD INDUCTOR CODE DECODER
   ──────────────────────────────────────────────── */

static void smd_ind_decode(void) {
    char code[8];
    printf("Enter inductor SMD code (e.g. 4R7, 101, 220): ");
    scanf("%7s", code);
    for (int i = 0; code[i]; i++) code[i] = toupper(code[i]);

    // If contains R, e.g. 4R7 → 4.7 µH
    if (strchr(code, 'R')) {
        float value = 0.0f;
        sscanf(code, "%f", &value);
        printf("Inductance ≈ %.3f µH\n", value);
        return;
    }

    // If numeric only, e.g. 101 → 10 × 10¹ = 100 µH
    int len = strlen(code);
    if (len == 3 && isdigit(code[0])) {
        int digits = atoi(code);
        int multiplier = digits % 10;
        int base = digits / 10;
        float value = base * pow(10, multiplier);
        printf("Inductance ≈ ");
        print_with_prefix(value * 1e-6, "H"); // Convert µH → H
        return;
    }

    printf("Unknown code format.\n");
}

/* ────────────────────────────────────────────────
   MAIN MENU
   ──────────────────────────────────────────────── */

void inductor_menu(void) {
    int choice;
    do {
        printf("\n==== INDUCTOR CALCULATOR ====\n");
        printf("1. Series Combination\n");
        printf("2. Parallel Combination\n");
        printf("3. Energy Stored (½LI²)\n");
        printf("4. Time Constant (τ = L/R)\n");
        printf("5. Reactance (Xl = 2πfL)\n");
        printf("6. Decode SMD Inductor Code\n");
        printf("0. Return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: series_ind_calc(); break;
            case 2: parallel_ind_calc(); break;
            case 3: energy_calc(); break;
            case 4: time_constant_calc(); break;
            case 5: reactance_calc(); break;
            case 6: smd_ind_decode(); break;
            case 0: break;
            default: printf("Invalid option.\n");
        }
    } while (choice != 0);
}
