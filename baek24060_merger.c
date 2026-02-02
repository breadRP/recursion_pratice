// 백준 24060 - 알고리즘 수업 - 병합 정렬1
// 병합정렬이란?
// 배열을 같은 크기의 두 배열로 나누는 과정을(반으로 쪼개서) 반복한후 다시 쪼갠 배열을 하나의 배열로 병합하는 것
// 문제 이해 - merge_sort 함수는 배열을 절반으로 쪼갰다가 다시 합치는 함수 (재귀기능은 가장 작은 배열로 쪼개는데 사용)
// 내가 직접 병합정렬 구현해보는게 관건 + 재귀함수는 내가 어떤 순서로 돌아가는지 알필요가 없다.
// 재귀함수 활용
// 1. 함수의 의미 생각 2. 작은 단계로 쪼개기 3. 초기(종료)조건 생각 4. 현재 함수에서 처리해야할 식 구하기 

#include <stdio.h>

int K = 0; // 저장횟수
int count = 0; // 저장 실행 횟수
int K_value = -1;
int found = 0; // Chat gpt가 알려준 방법 전역 flag (불필요한 연산을 안하기 위한 방법이다.)

void merge_sort(int* A, int p, int r) {
    if (found == 1) return;
    if (p < r) {
        int q; // 중간지점
        q = (p+r) / 2; 
        merge_sort(A, p, q); // 왼쪽
        merge_sort(A, q+1, r); // 오른쪽
        merge(A, p, q, r); // 현재 단계에서 왼쪽, 오른쪽 배열이 모두 정렬되어있다고 믿음
    } 
}

void merge(int* A, int p, int q, int r){  // 현재 함수에서 처리해야할 식
    if (found == 1) return;
    int i = p;
    int j = q + 1;
    int t = 0;
    int tmp[r - p + 1];

    while (i <= q && j <= r) {
        if (A[i] <= A[j]){  // 정렬된 왼쪽과 오른쪽 배열에서 큰값을 하나씩 골라내는 조건문
            tmp[t++] = A[i++];
        }
        else {
            tmp[t++] = A[j++];
        }
    }
    while (i <= q) { // 왼쪽 배열이 남은 경우
        tmp[t++] = A[i++];
    }
    while (j <= r) {
        tmp[t++] = A[j++];
    }
    i = p;
    t = 0;
    while (i <= r) {
        count += 1;
        if (count == K) {
            K_value = tmp[t];
            found = 1;
        }
        A[i++] = tmp[t++]; // A에 저장**
    }
}

int main() {
    int N = 0; // 배열의 크기
    int A[500000];

    scanf("%d", &N); // 문제에서 첫줄에 입력될 두 값 받기
    scanf("%d", &K);

    for (int i=0; i<N; i++) { // 초기배열 A 완성
        scanf("%d", &A[i]);
    }

    merge_sort(A, 0, N-1);
    printf("%d", K_value);
}