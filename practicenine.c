#include <stdio.h>
#include <string.h>

#define MAX 1000

void reverseStore(char str[], int arr[], int *len) {
    *len = strlen(str);
    for (int i = 0; i < *len; i++) {
        arr[i] = str[*len - 1 - i] - '0';
    }
}

void printNumber(int arr[], int len) {
    while (len > 1 && arr[len - 1] == 0) {
        len--;
    }

    for (int i = len - 1; i >= 0; i--) {
        printf("%d", arr[i]);
    }
}

void addBig(int A[], int lenA, int B[], int lenB, int result[], int *lenR) {
    int carry = 0;
    int maxLen = lenA > lenB ? lenA : lenB;

    for (int i = 0; i < maxLen; i++) {
        int sum = carry;

        if (i < lenA) sum += A[i];
        if (i < lenB) sum += B[i];

        result[i] = sum % 10;
        carry = sum / 10;
    }

    *lenR = maxLen;

    if (carry > 0) {
        result[(*lenR)++] = carry;
    }
}

void subtractBig(int A[], int lenA, int B[], int lenB, int result[], int *lenR) {
    int borrow = 0;

    for (int i = 0; i < lenA; i++) {
        int diff = A[i] - borrow;

        if (i < lenB) diff -= B[i];

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result[i] = diff;
    }

    *lenR = lenA;

    while (*lenR > 1 && result[*lenR - 1] == 0) {
        (*lenR)--;
    }
}

void multiplyBig(int A[], int lenA, int B[], int lenB, int result[], int *lenR) {
    for (int i = 0; i < MAX * 2; i++) {
        result[i] = 0;
    }

    for (int i = 0; i < lenA; i++) {
        for (int j = 0; j < lenB; j++) {
            result[i + j] += A[i] * B[j];
        }
    }

    *lenR = lenA + lenB;

    for (int i = 0; i < *lenR; i++) {
        if (result[i] >= 10) {
            result[i + 1] += result[i] / 10;
            result[i] %= 10;
        }
    }

    while (*lenR > 1 && result[*lenR - 1] == 0) {
        (*lenR)--;
    }
}

long long modBig(char str[], long long M) {
    long long rem = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        rem = (rem * 10 + (str[i] - '0')) % M;
    }

    return rem;
}

long long powerMod(long long base, long long exp, long long mod) {
    long long result = 1 % mod;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }

        base = (base * base) % mod;
        exp /= 2;
    }

    return result;
}

int main() {
    char inputA[MAX], inputB[MAX];
    long long M, E;

    scanf("A = %s", inputA);
    scanf(" B = %s", inputB);
    scanf(" M = %lld", &M);
    scanf(" E = %lld", &E);

    int A[MAX], B[MAX];
    int lenA, lenB;

    reverseStore(inputA, A, &lenA);
    reverseStore(inputB, B, &lenB);

    int result[MAX * 2];
    int lenR;

    addBig(A, lenA, B, lenB, result, &lenR);
    printf("A + B = ");
    printNumber(result, lenR);
    printf("\n");

    subtractBig(A, lenA, B, lenB, result, &lenR);
    printf("A - B = ");
    printNumber(result, lenR);
    printf("\n");

    multiplyBig(A, lenA, B, lenB, result, &lenR);
    printf("A * B = ");
    printNumber(result, lenR);
    printf("\n");

    long long modA = modBig(inputA, M);
    printf("A mod M = %lld\n", modA);

    printf("A^E mod M = %lld\n", powerMod(modA, E, M));

    return 0;
}