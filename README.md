# Recursion Practice

재귀 문제를 공부하면서 작성한 연습 코드와 개념 정리 저장소입니다.

## 재귀 핵심 정리

- [재귀 문제 설계 사고법 · 훈련 가이드](recursive_design_practice.md)
  - 문제 관찰 → 함수 계약 → 정보 흐름 → 처리 시점 → 반례 검증
  - 15분 설계 연습, 힌트 요청 방식, 3회독 복습법
  - 543 / 236 / 105 / 98 / 113을 통한 구조 비교와 고정 사고 방지


- [Recursion Thinking Guide](recur_study.md)
  - **순회별 확보 정보 → Body의 수행 시점 → Return으로 부모에게 전달할 정보**
  - 112 / 113 / 543을 Input·Body·Return 관점에서 비교
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

- [LeetCode 98 - Validate Binary Search Tree](bst_98.md)
  - 조상 제약을 상한·하한으로 전달하고 현재 노드에서 검사
  - Contract / Parameter / Body / Return과 초기 설계의 수정 과정


- [LeetCode 113 - Path Sum II](backtracking_113.md)
  - Tree DFS + Backtracking
  - append → left/right 탐색 → pop
  - leaf 판정 전 현재 node state 반영
  - `path.copy()`로 정답 snapshot 저장
  - 일반 tree DFS에서 memoization이 보통 불필요한 이유

- [LeetCode 543 - Diameter of Binary Tree](postorder_543.md)
  - 후위순회: 자식의 높이를 먼저 계산하고 부모에게 반환
  - 현재 노드를 통과하는 지름 후보와 반환 높이 구분
  - `left + right`로 최대 지름 갱신, `max(left, right) + 1` 반환
  - 간선 수와 노드 수 차이, `self` / `nonlocal` 주의

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
