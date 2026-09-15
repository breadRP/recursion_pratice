# Recursion Practice

재귀 문제를 공부하면서 작성한 연습 코드와 개념 정리 저장소입니다.

## 재귀 핵심 정리

- [Recursion Thinking Guide](recur_study.md)
  - 재귀 문제를 볼 때 먼저 정할 4가지: 함수 의미 / 상태 / 종료조건 / 재귀식
  - 단순 감소형
  - 분기형
  - 구간형
  - 트리 / DFS형
  - 백트래킹형
  - 분할정복형
  - 메모이제이션형
  - 시험장에서 유형을 구분하는 방법
  - 각 유형별 Python 템플릿

## 문제별 핵심 패턴

- [LeetCode 416 - Partition Equal Subset Sum](memoization_416.md)
  - 상태: `index + current_sum`
  - 선택 / 비선택 분기
  - 단순 재귀의 `O(2^n)` 구조
  - 중복 상태와 메모이제이션
  - 메모이제이션 후 `O(n * target)`

## 기존 연습 코드

- `baek10870_fibo.c` — Fibonacci
- `baek24060_merger.c` — Merge Sort 관련 재귀
- `baek25501_recurucer.c` — 재귀 호출 연습
- `baek27433_fac.c` — Factorial

> 재귀 문제를 풀기 전에 `recur_study.md`의 **함수 의미 / 상태 / 종료조건 / 재귀식** 네 항목부터 먼저 적어보는 것을 목표로 한다.
