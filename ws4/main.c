#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGITS 1000
#define MAX_FACTORIALS 10000
//define number of factorials
#define NUM_FACTS 100

//custom struct to handle larger numbers where factorial > twenty, given that unsigned long long can only handle up to factorial 20
typedef struct {
    int digits[MAX_DIGITS];
    int size;
} BigInt;

//set array to zero in order to remove possibility of garbage values
void initBigInt(BigInt* num) {
    //memset initializes digit array to zero
    memset(num->digits, 0, sizeof(num->digits));
    num->size = 1;
}

//function that converts a smaller int value into user struct representation
void fromInt(BigInt* num, int value) {
    //call initBigInt to initialize custom struct
    initBigInt(num);
    num->digits[0] = value;
    num->size = 1;
}

//print to command line
void printBigInt(const BigInt* num) {
    for (int i = num->size - 1; i >= 0; i--) {
        printf("%d", num->digits[i]);
    }
    printf("\n");
}

//multiply bigInt by some integer and store the result in another instance of bigInt
void multiplyBigInt(BigInt* result, const BigInt* a, int b) {
    //for carry-over values during multiplication
    int carry = 0;
    //loop iterates over each digit, continues until either a carry-over valu exists or digits still left within a
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

struct FactorialResults {
    BigInt results[MAX_FACTORIALS];
    int numResults;
};

void computeFactorials(struct FactorialResults* results, int numFactorials) {
    for (int i = 0; i < numFactorials; i++) {
        factorialBigInt(&results->results[i], i);
    }
    results->numResults = numFactorials;
}

int main(void) {
    struct FactorialResults* results = (struct FactorialResults*)malloc(sizeof(struct FactorialResults));
    results->numResults = 0;

    computeFactorials(results, NUM_FACTS);

    for (int i = 0; i < NUM_FACTS; i++) {
        printf("%5d ", i);
        printBigInt(&results->results[i]);
    }

    free(results);
    return 0;
}
