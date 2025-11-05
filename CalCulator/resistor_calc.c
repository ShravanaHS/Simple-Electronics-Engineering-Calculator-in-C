#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include "math_ops.h"
#include "resistor_calc.h"

/* ────────────────────────────────────────────────
   MATERIAL RESISTIVITY TABLE (Ω·m)
   ──────────────────────────────────────────────── */

typedef struct {
    const char *name;
    float rho;
} material_t;

static const material_t materials[] = {
    {"Copper",   1.68e-8},
    {"Aluminum", 2.82e-8},
    {"Gold",     2.44e-8},
    {"Silver",   1.59e-8},
    {"Nichrome", 1.10e-6},
    {"Iron",     1.00e-7},
    {"Tungsten", 5.60e-8},
    {NULL, 0.0f}
};

/* Utility */
static float input_value(const char *prompt) {
    char buf[32];
    printf("%s", prompt);
    scanf("%31s", buf);
    return parse_with_prefix(buf);
}

/* ────────────────────────────────────────────────
   BASIC CALCULATIONS (Series / Parallel / Resistivity)
   ──────────────────────────────────────────────── */

static void series_calc(void) {
    int n;
    printf("Enter number of resistors in series: ");
    scanf("%d", &n);

    if (n <= 0) { printf("Invalid number.\n"); return; }

    float total = 0.0f;
    for (int i = 0; i < n; i++) {
        printf("R%d: ", i + 1);
        char buf[32];
        scanf("%31s", buf);
        total += parse_with_prefix(buf);
    }

    printf("Equivalent Series Resistance = ");
    print_with_prefix(total, "Ω");
}

static void parallel_calc(void) {
    int n;
    printf("Enter number of resistors in parallel: ");
    scanf("%d", &n);

    if (n <= 0) { printf("Invalid number.\n"); return; }

    float inv_total = 0.0f;
    for (int i = 0; i < n; i++) {
        printf("R%d: ", i + 1);
        char buf[32];
        scanf("%31s", buf);
        float R = parse_with_prefix(buf);
        if (R == 0.0f) { printf("Error: R cannot be 0.\n"); return; }
        inv_total += 1.0f / R;
    }

    float total = 1.0f / inv_total;
    printf("Equivalent Parallel Resistance = ");
    print_with_prefix(total, "Ω");
}

static void resistivity_calc(void) {
    int choice;
    printf("\nChoose material:\n");
    for (int i = 0; materials[i].name; i++) {
        printf("%d. %s\n", i + 1, materials[i].name);
    }
    printf("Select option: ");
    scanf("%d", &choice);

    if (choice <= 0 || materials[choice - 1].name == NULL) {
        printf("Invalid choice.\n");
        return;
    }

    float rho = materials[choice - 1].rho;
    float L = input_value("Enter length L (m, supports prefixes): ");
    float A = input_value("Enter cross-sectional area A (m^2): ");
    if (A == 0.0f) { printf("Error: Area cannot be 0.\n"); return; }

    float R = rho * (L / A);
    printf("Resistance (R = ρL/A) for %s = ", materials[choice - 1].name);
    print_with_prefix(R, "Ω");
}

/* ────────────────────────────────────────────────
   COLOUR CODE SECTION
   ──────────────────────────────────────────────── */

typedef struct {
    const char *name;
    int digit;
    float multiplier;
    float tolerance;
} color_t;

static const color_t colors[] = {
    {"black",  0, 1.0f,   -1},
    {"brown",  1, 10.0f,  1},
    {"red",    2, 100.0f, 2},
    {"orange", 3, 1e3f,   -1},
    {"yellow", 4, 1e4f,   -1},
    {"green",  5, 1e5f,   0.5f},
    {"blue",   6, 1e6f,   0.25f},
    {"violet", 7, 1e7f,   0.1f},
    {"grey",   8, 1e8f,   0.05f},
    {"white",  9, 1e9f,   -1},
    {"gold",  -1, 0.1f,   5},
    {"silver",-1, 0.01f, 10},
    {NULL, -1, -1, -1}
};

static int find_color(const char *name) {
    for (int i = 0; colors[i].name; i++) {
        if (strcasecmp(name, colors[i].name) == 0)
            return i;
    }
    return -1;
}

static void decode_color(void) {
    char c1[16], c2[16], c3[16], c4[16], c5[16];
    int type;
    printf("Enter type (4 for 4-band, 5 for 5-band): ");
    scanf("%d", &type);

    if (type == 4) {
        printf("Enter colours (Band1 Band2 Multiplier Tolerance): ");
        scanf("%s %s %s %s", c1, c2, c3, c4);
        int i1 = find_color(c1);
        int i2 = find_color(c2);
        int i3 = find_color(c3);
        int i4 = find_color(c4);

        if (i1 < 0 || i2 < 0 || i3 < 0 || i4 < 0) { printf("Invalid colour.\n"); return; }

        float value = (colors[i1].digit * 10 + colors[i2].digit) * colors[i3].multiplier;
        printf("Resistance = ");
        print_with_prefix(value, "Ω");
        if (colors[i4].tolerance > 0)
            printf("Tolerance = ±%.2f%%\n", colors[i4].tolerance);
    } 
    else if (type == 5) {
        printf("Enter colours (Band1 Band2 Band3 Multiplier Tolerance): ");
        scanf("%s %s %s %s %s", c1, c2, c3, c4, c5);
        int i1 = find_color(c1);
        int i2 = find_color(c2);
        int i3 = find_color(c3);
        int i4 = find_color(c4);
        int i5 = find_color(c5);

        if (i1 < 0 || i2 < 0 || i3 < 0 || i4 < 0 || i5 < 0) { printf("Invalid colour.\n"); return; }

        float value = (colors[i1].digit * 100 + colors[i2].digit * 10 + colors[i3].digit)
                       * colors[i4].multiplier;
        printf("Resistance = ");
        print_with_prefix(value, "Ω");
        if (colors[i5].tolerance > 0)
            printf("Tolerance = ±%.2f%%\n", colors[i5].tolerance);
    } 
    else printf("Invalid type.\n");
}

static void encode_color(void) {
    char buf[32];
    printf("Enter resistance (e.g. 4.7k, 10M): ");
    scanf("%31s", buf);

    float R = parse_with_prefix(buf);
    if (R <= 0.0f) { printf("Invalid resistance.\n"); return; }

    int exp = 0;
    while (R >= 100 && exp < 9) { R /= 10; exp++; }
    while (R < 10 && exp > -2)  { R *= 10; exp--; }

    int d1 = (int)R / 10;
    int d2 = ((int)R) % 10;

    const char *mult_color = NULL;
    for (int i = 0; colors[i].name; i++)
        if (fabs(colors[i].multiplier - pow(10, exp)) < 0.001f)
            mult_color = colors[i].name;

    const char *tol_color = "gold";
    const char *digit_colors[] = {
        "black","brown","red","orange","yellow","green","blue","violet","grey","white"
    };

    if (!mult_color) { printf("Value out of range.\n"); return; }

    printf("Colour Bands: %s - %s - %s - %s\n",
           digit_colors[d1], digit_colors[d2], mult_color, tol_color);
}

/* ────────────────────────────────────────────────
   SMD CODE SECTION
   ──────────────────────────────────────────────── */

static void smd_decode(void) {
    char code[8];
    printf("Enter SMD resistor code (e.g. 472, 1001, 49C): ");
    scanf("%7s", code);
    for (int i = 0; code[i]; i++) code[i] = toupper(code[i]);
    int len = strlen(code);

    // EIA-96 (2 digits + letter)
    if (isalpha(code[len - 1]) && len == 3) {
        int num; char letter;
        sscanf(code, "%2d%c", &num, &letter);
        static const int eia96_values[97] = {
            0,100,102,105,107,110,113,115,118,121,124,127,130,133,137,140,143,147,
            150,154,158,162,165,169,174,178,182,187,191,196,200,205,210,215,221,
            226,232,237,243,249,255,261,267,274,280,287,294,301,309,316,324,332,
            340,348,357,365,374,383,392,402,412,422,432,442,453,464,475,487,499,
            511,523,536,549,562,576,590,604,619,634,649,665,681,698,715,732,750,
            768,787,806,825,845,866,887,909,931,953,976
        };
        static const float eia96_mult[12] = {
            1e-3,1e-2,1e-1,1,10,100,1e3,1e4,1e5,1e6,1e7,1e8
        };
        const char mult_char[] = "YZRABCDEFHJK";
        float base = (num >= 1 && num <= 96) ? eia96_values[num] : 0;
        float mult = 0;
        for (int i = 0; i < 12; i++) if (letter == mult_char[i]) mult = eia96_mult[i];
        if (base == 0 || mult == 0) { printf("Invalid EIA-96 code.\n"); return; }
        float value = base * mult;
        printf("EIA-96 Resistor = "); print_with_prefix(value, "Ω"); return;
    }

    // 3 or 4 digit code
    if (len == 3 || len == 4) {
        int digits = atoi(code);
        int multiplier = digits % 10;
        int base = digits / 10;
        float value = base * pow(10, multiplier);
        printf("SMD %d-digit Resistor = ", len);
        print_with_prefix(value, "Ω");
        return;
    }

    printf("Unknown or unsupported SMD code format.\n");
}

static void smd_encode(void) {
    char buf[32];
    printf("Enter resistance (e.g. 4.7k, 1M): ");
    scanf("%31s", buf);
    float value = parse_with_prefix(buf);
    if (value <= 0) { printf("Invalid value.\n"); return; }

    float temp = value;
    int multiplier = 0;
    while (temp >= 100) { temp /= 10; multiplier++; }
    while (temp < 10 && multiplier > 0) { temp *= 10; multiplier--; }

    int base = (int)(temp + 0.5f);
    int code = base * 10 + multiplier;
    printf("Approx. 3-digit SMD Code: %03d\n", code);
}

/* ────────────────────────────────────────────────
   MAIN RESISTOR MENU
   ──────────────────────────────────────────────── */

void resistor_menu(void) {
    int choice;
    do {
        printf("\n==== RESISTOR CALCULATOR ====\n");
        printf("1. Series Combination\n");
        printf("2. Parallel Combination\n");
        printf("3. Resistance from Resistivity (ρL/A)\n");
        printf("4. Colour Code → Resistance\n");
        printf("5. Resistance → Colour Code\n");
        printf("6. SMD Code → Resistance\n");
        printf("7. Resistance → SMD Code\n");
        printf("0. Return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: series_calc(); break;
            case 2: parallel_calc(); break;
            case 3: resistivity_calc(); break;
            case 4: decode_color(); break;
            case 5: encode_color(); break;
            case 6: smd_decode(); break;
            case 7: smd_encode(); break;
            case 0: break;
            default: printf("Invalid option.\n");
        }
    } while (choice != 0);
}
