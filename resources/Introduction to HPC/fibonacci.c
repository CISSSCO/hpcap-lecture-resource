#include <stdio.h>
#include <stdbool.h>

int fibonacci(int n) {
    if (n <= 1)
        return n;
    else
        return fibonacci(n - 1) + fibonacci(n - 2);
}

int factorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}

bool isPrime(int n) {
    int i;
    if (n <= 1)
        return false;
    for (i = 2; i * i <= n; ++i) {
        if (n % i == 0)
            return false;
    }
    return true;
}

int main() {
    // Fibonacci Series
    int i,fiboTerms = 10;
    printf("Fibonacci Series up to %d terms:\n", fiboTerms);
    for (i = 0; i < fiboTerms; ++i) {
        printf("%d ", fibonacci(i));
    }
    printf("\n");

    // Factorial
    int factorialNum = 5;
    printf("Factorial of %d is: %d\n", factorialNum, factorial(factorialNum));

    // Prime Numbers
    int primeLimit = 20;
    printf("Prime numbers up to %d are:\n", primeLimit);
    for (i = 2; i <= primeLimit; ++i) {
        if (isPrime(i))
            printf("%d ", i);
    }
    printf("\n");

    return 0;
}
