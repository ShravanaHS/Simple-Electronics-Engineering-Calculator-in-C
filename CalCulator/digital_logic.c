#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include "digital_logic.h"
#include "math_ops.h"   // optional: for parse_with_prefix if you want numeric parsing with prefixes

/* --------------------
   Helper utilities
   -------------------- */

static void print_bin_uint32(uint32_t v, int bits) {
    if (bits <= 0) bits = 32;
    for (int i = bits - 1; i >= 0; --i) {
        putchar((v & (1u << i)) ? '1' : '0');
        if (i % 4 == 0 && i != 0) putchar(' '); // nibble spacing
    }
}

/* Parse integer from a string supporting prefixes like 0b/0x, or decimal */
static uint32_t parse_int(const char *s) {
    if (s == NULL) return 0;
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
        return (uint32_t)strtoul(s + 2, NULL, 16);
    } else if (s[0] == '0' && (s[1] == 'b' || s[1] == 'B')) {
        return (uint32_t)strtoul(s + 2, NULL, 2);
    } else if (s[0] == '0' && isdigit((unsigned char)s[1])) {
        return (uint32_t)strtoul(s, NULL, 8); // octal literal like 0755
    } else {
        return (uint32_t)strtoul(s, NULL, 10);
    }
}

/* --------------------
   Number system conversions
   -------------------- */

static void convert_number_systems(void) {
    char buf[64];
    printf("Enter number (prefix 0b for binary, 0x for hex, leading 0 for octal, otherwise decimal): ");
    scanf("%63s", buf);
    uint32_t val = parse_int(buf);

    printf("DEC: %u\n", val);
    printf("HEX: 0x%X\n", val);
    printf("OCT: 0%o\n", val);
    printf("BIN: ");
    print_bin_uint32(val, 32);
    putchar('\n');
}

/* --------------------
   Bitwise operations
   -------------------- */

static void bitwise_ops(void) {
    char a_str[64], b_str[64];
    printf("Enter first operand: ");
    scanf("%63s", a_str);
    printf("Enter second operand: ");
    scanf("%63s", b_str);

    uint32_t a = parse_int(a_str);
    uint32_t b = parse_int(b_str);

    printf("A = %u (0x%X) BIN: ", a, a); print_bin_uint32(a, 32); putchar('\n');
    printf("B = %u (0x%X) BIN: ", b, b); print_bin_uint32(b, 32); putchar('\n');

    printf("A & B = %u (0x%X) BIN: ", a & b, a & b); print_bin_uint32(a & b, 32); putchar('\n');
    printf("A | B = %u (0x%X) BIN: ", a | b, a | b); print_bin_uint32(a | b, 32); putchar('\n');
    printf("A ^ B = %u (0x%X) BIN: ", a ^ b, a ^ b); print_bin_uint32(a ^ b, 32); putchar('\n');
    printf("~A    = %u (0x%X) BIN: ", ~a, ~a); print_bin_uint32(~a, 32); putchar('\n');
    printf("A << 1 = %u (0x%X) BIN: ", a << 1, a << 1); print_bin_uint32(a << 1, 32); putchar('\n');
    printf("A >> 1 = %u (0x%X) BIN: ", a >> 1, a >> 1); print_bin_uint32(a >> 1, 32); putchar('\n');
}

/* --------------------
   Shift and rotate (32-bit)
   -------------------- */

static void shift_rotate(void) {
    char buf[64];
    printf("Enter value: ");
    scanf("%63s", buf);
    uint32_t v = parse_int(buf);

    int n; printf("Enter shift/rotate amount (0-31): "); scanf("%d", &n);
    n &= 31;

    uint32_t lshift = v << n;
    uint32_t rshift = v >> n;
    uint32_t rrotate = (v >> n) | (v << (32 - n));
    uint32_t lrotate = (v << n) | (v >> (32 - n));

    printf("Value: "); print_bin_uint32(v, 32); putchar('\n');
    printf("Left shift  << %d : ", n); print_bin_uint32(lshift, 32); putchar('\n');
    printf("Right shift >> %d : ", n); print_bin_uint32(rshift, 32); putchar('\n');
    printf("Rotate L   rol %d : ", n); print_bin_uint32(lrotate, 32); putchar('\n');
    printf("Rotate R   ror %d : ", n); print_bin_uint32(rrotate, 32); putchar('\n');
}

/* --------------------
   Truth table generator for 1..3 inputs
   -------------------- */

static int gate_eval(int gate_type, int *inputs, int n_inputs) {
    /* gate_type:
       0 = AND
       1 = OR
       2 = NAND
       3 = NOR
       4 = XOR
       5 = XNOR
       6 = NOT (only inputs[0] used)
    */
    if (gate_type == 6) return !inputs[0];

    int res;
    if (gate_type == 0) { res = 1; for (int i=0;i<n_inputs;i++) res &= inputs[i]; }
    else if (gate_type == 1) { res = 0; for (int i=0;i<n_inputs;i++) res |= inputs[i]; }
    else if (gate_type == 2) { res = 1; for (int i=0;i<n_inputs;i++) res &= inputs[i]; res = !res; }
    else if (gate_type == 3) { res = 0; for (int i=0;i<n_inputs;i++) res |= inputs[i]; res = !res; }
    else if (gate_type == 4) { res = 0; for (int i=0;i<n_inputs;i++) res ^= inputs[i]; }
    else if (gate_type == 5) { res = 0; for (int i=0;i<n_inputs;i++) res ^= inputs[i]; res = !res; }
    else res = 0;

    return res;
}

static void truth_table(void) {
    int gate;
    printf("Select gate: 0=AND 1=OR 2=NAND 3=NOR 4=XOR 5=XNOR 6=NOT\n");
    scanf("%d", &gate);
    int n;
    if (gate == 6) n = 1; else {
        printf("Number of inputs (1..3): "); scanf("%d", &n);
        if (n < 1) n = 1;
        if (n > 3) n = 3;
    }

    int rows = 1 << n;
    printf("\nTruth table for %s with %d input(s):\n", (gate==0?"AND":gate==1?"OR":gate==2?"NAND":gate==3?"NOR":gate==4?"XOR":gate==5?"XNOR":"NOT"), n);
    for (int r = 0; r < rows; ++r) {
        int inputs[3] = {0,0,0};
        for (int b = 0; b < n; ++b) inputs[b] = (r >> (n - 1 - b)) & 1;
        for (int b = 0; b < n; ++b) printf("%d ", inputs[b]);
        int out = gate_eval(gate, inputs, n);
        printf("| %d\n", out);
    }
}

/* --------------------
   Flip-flop single-step simulator (SR, D, JK)
   -------------------- */

static void flop_simulator(void) {
    int type;
    printf("Select flip-flop: 1=SR 2=D 3=JK: ");
    scanf("%d", &type);

    int Qprev;
    printf("Enter previous Q (0 or 1): ");
    scanf("%d", &Qprev);

    if (type == 1) {
        int S, R;
        printf("Enter S (0/1) and R (0/1): ");
        scanf("%d %d", &S, &R);
        if (S == 0 && R == 0) {
            printf("No change: Qnext = %d\n", Qprev);
        } else if (S == 0 && R == 1) {
            printf("Reset: Qnext = 0\n");
        } else if (S == 1 && R == 0) {
            printf("Set: Qnext = 1\n");
        } else {
            printf("Invalid/Forbidden (S=1,R=1) — undefined in basic SR flop\n");
        }
    } else if (type == 2) {
        int D;
        printf("Enter D (0/1): ");
        scanf("%d", &D);
        printf("D latch: Qnext = %d\n", D);
    } else if (type == 3) {
        int J, K;
        printf("Enter J (0/1) and K (0/1): ");
        scanf("%d %d", &J, &K);
        int Qnext;
        if (J == 0 && K == 0) Qnext = Qprev;
        else if (J == 0 && K == 1) Qnext = 0;
        else if (J == 1 && K == 0) Qnext = 1;
        else { /* J==1 && K==1 */ Qnext = !Qprev; }
        printf("JK flop: Qnext = %d\n", Qnext);
    } else {
        printf("Invalid flop type.\n");
    }
}

/* --------------------
   Module menu
   -------------------- */

void digital_menu(void) {
    int choice;
    do {
        printf("\n==== DIGITAL LOGIC MODULE ====\n");
        printf("1. Number System Conversions (bin/dec/oct/hex)\n");
        printf("2. Bitwise Operations (AND/OR/XOR/NOT/SHIFT)\n");
        printf("3. Shift & Rotate\n");
        printf("4. Truth Table Generator (1-3 inputs)\n");
        printf("5. Flip-flop Step (SR/D/JK)\n");
        printf("0. Return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: convert_number_systems(); break;
            case 2: bitwise_ops(); break;
            case 3: shift_rotate(); break;
            case 4: truth_table(); break;
            case 5: flop_simulator(); break;
            case 0: break;
            default: printf("Invalid option.\n");
        }
    } while (choice != 0);
}
