#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGITS 1000

typedef struct {
    int digits[MAX_DIGITS];
    int size;
} BigInt;

void initBigInt(BigInt* num) {
    memset(num->digits, 0, sizeof(num->digits));
    num->size = 1;
}

void fromInt(BigInt* num, int value) {
    initBigInt(num);
    num->digits[0] = value;
    num->size = 1;
}

void printBigInt(const BigInt* num) {
    for (int i = num->size - 1; i >= 0; i--) {
        printf("%d", num->digits[i]);
    }
    printf("\n");
}

void addBigInt(BigInt* result, const BigInt* a, const BigInt* b) {
    int carry = 0;
    int maxSize = (a->size > b->size) ? a->size : b->size;
    for (int i = 0; i < maxSize || carry; i++) {
        if (i == result->size) {
            result->size++;
        }
        result->digits[i] = carry + (i < a->size ? a->digits[i] : 0) + (i < b->size ? b->digits[i] : 0);
        carry = result->digits[i] >= 10;
        if (carry) {
            result->digits[i] -= 10;
        }
    }
}

void multiplyBigInt(BigInt* result, const BigInt* a, int b) {
    int carry = 0;
    for (int i = 0; i < a->size || carry; i++) {
        if (i == result->size) {
            result->size++;
        }
        long long current = result->digits[i] + (i < a->size ? a->digits[i] : 0) * (long long)b + carry;
        result->digits[i] = current % 10;
        carry = current / 10;
    }
    while (result->size > 1 && result->digits[result->size - 1] == 0) {
        result->size--;
    }
}

void factorialBigInt(BigInt* result, int n) {
    fromInt(result, 1);
    BigInt temp;
    for (int i = 2; i <= n; i++) {
        initBigInt(&temp);
        multiplyBigInt(&temp, result, i);
        *result = temp;
    }
}

int main(void) {
    for (int i = 1; i <= 100; i++) {
        BigInt result;
        factorialBigInt(&result, i);
        printf("Factorial of %d: ", i);
        printBigInt(&result);
    }
    return 0;
}
