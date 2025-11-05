#ifndef MATH_OPS_H
#define MATH_OPS_H

void math_menu(void);

// Parse user input with SI prefixes (T, G, M, k, m, u, n, p, f)
float parse_with_prefix(const char *input);

// Print values automatically with best-fitting prefix
void print_with_prefix(float value, const char *unit);

// Math operations
float add(float a, float b);
float sub(float a, float b);
float mul(float a, float b);
float div_safe(float a, float b, int *ok);

#endif
