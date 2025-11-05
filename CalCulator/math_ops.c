#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "math_ops.h"
#include <math.h>

float power(float base, float exp) { return powf(base, exp); }
float sqroot(float x) { return sqrtf(x); }
float log10_val(float x) { return log10f(x); }

/* 🔹 Convert a string like "4.7k", "10M", "2.2u", etc. to a float */
float parse_with_prefix(const char *input)
{
    float value = 0.0;
    char suffix = '\0';
    char cleaned[20];
    int i = 0;

    // Step 1: Clean input — stop at first non-digit/non-dot/non-letter
    while (input[i] && (isdigit(input[i]) || input[i] == '.' || isalpha(input[i])))
    {
        cleaned[i] = input[i];
        i++;
    }
    cleaned[i] = '\0';

    // Step 2: Extract number and optional suffix
    int n = sscanf(cleaned, "%f%c", &value, &suffix);

    if (n == 1)
        return value; // no suffix
    if (n != 2)
        return value; // fallback

    // Step 3: Normalize suffix to lowercase for simplicity
    if (suffix == 'U')
        suffix = 'u';
    if (suffix == 'K')
        suffix = 'k';
    if (suffix == 'M')
        suffix = 'M'; // keep M as Mega, lowercase m is milli

    // Step 4: Apply multiplier
    switch (suffix)
    {
    case 'T':
        return value * 1e12; // tera
    case 'G':
        return value * 1e9; // giga
    case 'M':
        return value * 1e6; // mega
    case 'k':
        return value * 1e3; // kilo
    case 'm':
        return value * 1e-3; // milli
    case 'u':
        return value * 1e-6; // micro
    case 'n':
        return value * 1e-9; // nano
    case 'p':
        return value * 1e-12; // pico
    case 'f':
        return value * 1e-15; // femto
    default:
        return value; // unknown or none
    }
}

void print_with_prefix(float value, const char *unit)
{
    const char *prefix;
    double display_value;

    if (value == 0.0f)
    {
        printf("0 %s\n", unit);
        return;
    }

    if (value >= 1e12)
    {
        prefix = "T";
        display_value = value / 1e12;
    }
    else if (value >= 1e9)
    {
        prefix = "G";
        display_value = value / 1e9;
    }
    else if (value >= 1e6)
    {
        prefix = "M";
        display_value = value / 1e6;
    }
    else if (value >= 1e3)
    {
        prefix = "k";
        display_value = value / 1e3;
    }
    else if (value >= 1)
    {
        prefix = "";
        display_value = value;
    }
    else if (value >= 1e-3)
    {
        prefix = "m";
        display_value = value * 1e3;
    }
    else if (value >= 1e-6)
    {
        prefix = "µ";
        display_value = value * 1e6;
    }
    else if (value >= 1e-9)
    {
        prefix = "n";
        display_value = value * 1e9;
    }
    else if (value >= 1e-12)
    {
        prefix = "p";
        display_value = value * 1e12;
    }
    else
    {
        prefix = "f";
        display_value = value * 1e15;
    }

    printf("%.4f %s%s\n", display_value, prefix, unit);
}

/* 🔹 Basic math functions */
float add(float a, float b) { return a + b; }
float sub(float a, float b) { return a - b; }
float mul(float a, float b) { return a * b; }

float div_safe(float a, float b, int *ok)
{
    if (b == 0)
    {
        *ok = 0;
        return 0.0;
    }
    *ok = 1;
    return a / b;
}

/* 🔹 Interactive Math Menu */
void math_menu(void)
{
    int choice;
    char input1[20], input2[20];
    float a, b, result;
    int ok;

    do
    {
        printf("\n==== MATHEMATICAL OPERATIONS ====\n");
        printf("1. Addition\n");
        printf("2. Subtraction\n");
        printf("3. Multiplication\n");
        printf("4. Division\n");
        printf("0. Return to Main Menu\n");
        printf("5. Power (x^y)\n");
        printf("6. Square Root\n");
        printf("7. Logarithm (base 10)\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        if (choice == 0)
            break;
        if (choice >= 1 && choice <= 5)
        {
            printf("Enter first value (supports T,G,M,k,m,u,n,p,f): ");
            scanf("%s", input1);
            printf("Enter second value (supports T,G,M,k,m,u,n,p,f): ");
            scanf("%s", input2);
            a = parse_with_prefix(input1);
            b = parse_with_prefix(input2);
        }

        switch (choice)
        {
        case 1: // Addition
            result = add(a, b);
            printf("Result = ");
            print_with_prefix(result, "");
            break;

        case 2: // Subtraction
            result = sub(a, b);
            printf("Result = ");
            print_with_prefix(result, "");
            break;

        case 3: // Multiplication
            result = mul(a, b);
            printf("Result = ");
            print_with_prefix(result, "");
            break;

        case 4: // Division
            result = div_safe(a, b, &ok);
            if (ok)
            {
                printf("Result = ");
                print_with_prefix(result, "");
            }
            else
            {
                printf("Error: Division by zero!\n");
            }
            break;

        case 5: // Power (x^y)
            result = power(a, b);
            printf("Result = ");
            print_with_prefix(result, "");
            break;

        case 6: // Square Root
            printf("Enter value (supports prefixes): ");
            scanf("%s", input1);
            a = parse_with_prefix(input1);
            if (a < 0)
                printf("Error: Cannot take square root of a negative number!\n");
            else
            {
                result = sqroot(a);
                printf("√(%.4f) = ", a);
                print_with_prefix(result, "");
            }
            break;

        case 7: // Logarithm (base 10)
            printf("Enter value (supports prefixes): ");
            scanf("%s", input1);
            a = parse_with_prefix(input1);
            if (a <= 0)
                printf("Error: Logarithm undefined for zero or negative numbers!\n");
            else
            {
                result = log10_val(a);
                printf("log10(%.4f) = %.6f\n", a, result);
            }
            break;

        default:
            printf("Invalid choice!\n");
        }

    } while (choice != 0);
}
