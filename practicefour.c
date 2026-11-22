#include <stdio.h>
#include <stdlib.h>

int DHash(int x) {
    //자릿수 합 계산
    int sum = 0;
    while (x > 0) {
        sum += x % 10;
        x /= 10;
    }
    return (sum * 8) % 14; //DHash 계산
}

int main() {
    int N;
    scanf("%d", &N);

    int *arr = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    int freq[14] = {0}; //해시값 빈도 저장
    for (int i = 0; i < N; i++) {
        int h = DHash(arr[i]);
        freq[h]++;  //해당 해시값 개수 증가
    }

    long long result = 0; //같은 해시값끼리 쌍 개수 계산
    for (int i = 0; i < 14; i++) {
        if (freq[i] > 1) {
            result += (long long)freq[i] * (freq[i] - 1) / 2;
        }
    }

    printf("%lld\n", result);

    free(arr);
    return 0;
}

