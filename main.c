#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

double DOUBLE_EPS = 0.0000001;

enum number_of_roots {
    ZERO, ONE, TWO, INF
};

struct equation_answer {

    enum number_of_roots number_roots;
    double x_1;
    double x_2;
};

/**
 * Reads float point numbers from console
 * @param enter_phrase - what input
 * @return floating point number
 */
double input(char* enter_phrase);

/**
 * Print the quadratic equation on console
 * @param a - first coefficient
 * @param b - second coefficient
 * @param c - third coefficient
 */
void print_equation(double a, double b, double c);

/**
 * Solves the quadratic equation
 * @param a - first coefficient
 * @param b - second coefficient
 * @param c - third coefficient
 * @param answer - the roots of quadratic equation
 */
void solve_equation(double a, double b, double c, struct equation_answer* answer);

/**
 * Tests
 */
void my_test();

/**
 * Prints the assert output
 * @param a - first coefficient
 * @param b - second coefficient
 * @param c - third coefficient
 * @param answer - the roots of quadratic equation
 */
void print_assert(double a, double b, double c, struct equation_answer answer);

/**
 * Prints the roots of quadratic equation
 * @param answer - the roots of quadratic equation
 */
void print_answer(struct equation_answer answer);

int main() {

    my_test();

    double a = input("Input integer A: ");
    double b = input("Input integer B: ");
    double c = input("Input integer C: ");

    struct equation_answer answer;

    print_equation(a, b, c);

    solve_equation(a, b, c, &answer);

    print_answer(answer);

    return 0;
}

void print_equation(double a, double b, double c) {
    printf("Quadratic equation: %lf*x^2 + %lf*x + %lf = 0\n", a, b, c);
}

void print_answer(struct equation_answer answer) {
    if (answer.number_roots == ZERO) {
        printf("No roots!\n\n");
    } else if (answer.number_roots == INF) {
        printf("Infinite number of roots!\n\n");
    } else if (answer.number_roots == ONE) {
        printf("One root: x = %lf\n\n", answer.x_1 + 0.0);
    } else {
        printf("Two roots: x1 = %lf, x2 = %lf\n\n", answer.x_1 + 0.0, answer.x_2 + 0.0);
    }
}

double input(char* enter_phrase) {
    double number;
    printf("%s", enter_phrase);
    if (scanf("%lf", &number) != 1) {
        printf("It's not a number! Try again!\n");
        exit(0);
    } else {
        return number;
    }
}

void solve_equation(double a, double b, double c, struct equation_answer* answer) {

    if (a == 0) {
        if (b == 0) {
            if (c == 0) {
                answer->number_roots = INF;
            } else {
                answer->number_roots = ZERO;
            }
        } else {
            answer->number_roots = ONE;
            answer->x_1 = -c * 1.0 / b;
        }
    } else {
        double discriminant = b * b - 4 * a * c;

        if (fabs(discriminant) < DOUBLE_EPS) {
            answer->number_roots = ONE;
            answer->x_1 = -b * 1.0 / 2 / a;
        } else if (discriminant < 0) {
            answer->number_roots = ZERO;
        } else {
            answer->number_roots = TWO;
            answer->x_1 = (-b * 1.0 + sqrt(discriminant)) / 2 / a;
            answer->x_2 = (-b * 1.0 - sqrt(discriminant)) / 2 / a;
        }
    }
}

void my_test() {

    printf("*** TESTS ***\n");

    struct equation_answer test_answer;

    solve_equation(0, 0, 0, &test_answer);
    assert(test_answer.number_roots == INF);
    print_assert(0, 0, 0, test_answer);

    solve_equation(0, 0, 1, &test_answer);
    assert(test_answer.number_roots == ZERO);
    print_assert(0, 0, 1, test_answer);

    solve_equation(0, 1, 0, &test_answer);
    assert(test_answer.number_roots == ONE && fabs(test_answer.x_1) < DOUBLE_EPS);
    print_assert(0, 1, 0, test_answer);

    solve_equation(0, 1, 1, &test_answer);
    assert(test_answer.number_roots == ONE && fabs(test_answer.x_1 - (-1)) < DOUBLE_EPS);
    print_assert(0, 1, 1, test_answer);

    solve_equation(1, 0, 0, &test_answer);
    assert(test_answer.number_roots == ONE && fabs(test_answer.x_1) < DOUBLE_EPS);
    print_assert(1, 0, 0, test_answer);

    solve_equation(1, 0, 1, &test_answer);
    assert(test_answer.number_roots == ZERO);
    print_assert(1, 0, 1, test_answer);

    solve_equation(1, 1, 0, &test_answer);
    assert(test_answer.number_roots == TWO &&
           (fabs(test_answer.x_1 - (-1)) < DOUBLE_EPS && fabs(test_answer.x_2) < DOUBLE_EPS ||
            fabs(test_answer.x_2 - (-1)) < DOUBLE_EPS && fabs(test_answer.x_1) < DOUBLE_EPS));
    print_assert(1, 1, 0, test_answer);

    solve_equation(1, 1, 1, &test_answer);
    assert(test_answer.number_roots == ZERO);
    print_assert(1, 1, 1, test_answer);

    solve_equation(3.4, 7.8, -9.2, &test_answer);
    assert(test_answer.number_roots == TWO &&
           (fabs(test_answer.x_1 - 0.8583 < DOUBLE_EPS && fabs(test_answer.x_2 - (-3.1525))) < DOUBLE_EPS ||
            fabs(test_answer.x_2 - (-3.1525)) < DOUBLE_EPS && fabs(test_answer.x_1 - 0.8583) < DOUBLE_EPS));
    print_assert(3.4, 7.8, -9.2, test_answer);

    printf("*** TEST OK ***\n");
}

void print_assert(double a, double b, double c, struct equation_answer answer) {
    print_equation(a, b, c);
    print_answer(answer);
}
