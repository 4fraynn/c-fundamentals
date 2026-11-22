#include <stdio.h>

#define MAXN 1000 //최대 학생 수
int A[MAXN][MAXN];
char line[MAXN + 1];

int main() {
    int n;
    scanf("%d", &n); // 입력 받기

    for (int i = 0; i < n; i++) {
        scanf("%s", line);
        for (int j = 0; j < n; j++) {
            A[i][j] = line[j] - '0';
        }
    }

    int count = 0;

    //모든 (i, j) 쌍 검사
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) {
            if (i == j) continue; //같은 학생 제외
            if (A[i][j] == 1) continue; //직접 전달 가능하면 제외

    //2단계 전달 가능 여부 확인
            for (int k = 0; k < n; k++) {
                if (A[i][k] == 1 && A[k][j] == 1) {
                    count++;
                    break;
                }
            }
        }
    }

    printf("%d\n", count);
    return 0;
}