#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double DOUBLE_EPS = 0.0000001;

double input(char* enter_phrase);

void solve_equation(double a, double b, double c);

void my_test();

int main() {
    double a = input("Input integer A: ");
    double b = input("Input integer B: ");
    double c = input("Input integer C: ");

    printf("Quadratic equation: %.4f*x^2 + %.4f*x + %.4f = 0\n", a, b, c);

    solve_equation(a, b, c);

    return 0;
}

double input(char* enter_phrase) {
    double number;
    printf("%s", enter_phrase);
    if (scanf("%lf", &number) != 1) {
        printf("It's not a number!\n");
        exit(0);
    } else {
        return number;
    }
}

void solve_equation(double a, double b, double c) {

    if (a == 0) {
        if (b == 0) {
            if (c == 0) {
                printf("Infinity amount of roots");
            } else {
                printf("No roots!");
            }
        } else {
            printf("1 root: %.3f", -c * 1.0 / b);
        }
    } else {
        double discriminant = b * b - 4 * a * c;

        if (fabs(discriminant) < DOUBLE_EPS) {
            printf("1 root: %.3f", -b * 1.0 / 2 / a);
        } else if (discriminant < 0) {
            printf("No roots!\n");
        } else {
            const double x_1 = (-b * 1.0 + sqrt(discriminant)) / 2 / a;
            const double x_2 = (-b * 1.0 - sqrt(discriminant)) / 2 / a;

            printf("1 root: %.3f\n2 root: %.3f", x_1, x_2);
        }
    }
}
