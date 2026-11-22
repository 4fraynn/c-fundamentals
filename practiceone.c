#include <stdio.h>
#include <string.h>

// 명제 변수(P, Q, R)의 값을 반환하는 함수
int getValue(char token[], int P, int Q, int R) {
    if (strcmp(token, "P") == 0) return P;
    if (strcmp(token, "Q") == 0) return Q;
    if (strcmp(token, "R") == 0) return R;
    return 0;
}

int parseOperand(char expr[][10], int *idx, int P, int Q, int R) {
    int notCount = 0;

    // NOT 연산자 개수 세기
    while (strcmp(expr[*idx], "n") == 0) {
        notCount++;
        (*idx)++;
    }

    // 변수 값 가져오기
    int value = getValue(expr[*idx], P, Q, R);
    (*idx)++;

    // NOT 적용, 홀수면 반전
    if (notCount % 2 == 1) value = !value;
    return value;
}

int applyOp(int left, char op[], int right) {
    if (strcmp(op, "a") == 0) return left && right;          
    if (strcmp(op, "o") == 0) return left || right;    
    if (strcmp(op, "i") == 0) return (!left) || right;      
    return 0;
}

int evaluate(char expr[][10], int tokenCount, int P, int Q, int R) {
    int idx = 0;

    // 첫 번째 피연산자
    int result = parseOperand(expr, &idx, P, Q, R);

    // 이후 연산들 순차적으로 처리
    while (idx < tokenCount) {
        char op[10];
        strcpy(op, expr[idx]);
        idx++;

        int nextValue = parseOperand(expr, &idx, P, Q, R);

        result = applyOp(result, op, nextValue);
    }

    return result;
}

int main() {
    int varCount, opCount, tokenCount;
    scanf("%d %d %d", &varCount, &opCount, &tokenCount);

    char expr[20][10]; // 입력 식 받기
    for (int i = 0; i < tokenCount; i++) {
        scanf("%s", expr[i]);
    }

    
    if (varCount == 1) {
        printf("P RESULT\n");
        for (int P = 1; P >= 0; P--) {
            int result = evaluate(expr, tokenCount, P, 0, 0);
            printf("%c %c\n", P ? 'T' : 'F', result ? 'T' : 'F');
        }
    }
    else if (varCount == 2) {
        printf("P Q RESULT\n");
        for (int P = 1; P >= 0; P--) {
            for (int Q = 1; Q >= 0; Q--) {
                int result = evaluate(expr, tokenCount, P, Q, 0);
                printf("%c %c %c\n", P ? 'T' : 'F', Q ? 'T' : 'F', result ? 'T' : 'F');
            }
        }
    }
    else if (varCount == 3) {
        printf("P Q R RESULT\n");
        for (int P = 1; P >= 0; P--) {
            for (int Q = 1; Q >= 0; Q--) {
                for (int R = 1; R >= 0; R--) {
                    int result = evaluate(expr, tokenCount, P, Q, R);
                    printf("%c %c %c %c\n", P ? 'T' : 'F', Q ? 'T' : 'F', R ? 'T' : 'F', result ? 'T' : 'F');
                }
            }
        }
    }

    return 0;
}