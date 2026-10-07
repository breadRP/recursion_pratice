# LeetCode 113 - Path Sum II

이 문제는 **Tree DFS + Backtracking**의 대표 예시다.

## 1. 먼저 구분할 것

```text
DFS
-> 한 경로를 깊게 탐색하는 방식

Backtracking
-> 탐색하면서 바꾼 공유 path를
   부모 호출로 돌아갈 때 원상복구하는 방식
```

따라서 둘은 대체 관계가 아니라 같이 사용된다.

## 2. State / Invariant

```text
node  = 현재 방문 중인 노드
total = root부터 현재 node까지의 합
path  = root부터 현재 node까지의 값 목록
```

Invariant:

> 현재 호출에서 path에는 root부터 현재 node까지 선택된 경로만 들어 있다.

## 3. 종료조건 위치

113은 종료조건을 전부 함수 맨 위에 몰아넣기 어렵다.

```text
node is None
-> 구조적 종료
-> 바로 return

leaf 판정
-> 현재 node의 값을 total/path에 반영한 뒤 검사
```

현재 leaf의 값도 target sum과 path에 포함되어야 하기 때문이다.

## 4. 기본 템플릿

```python
def dfs(node, total):
    if node is None:
        return

    total += node.val
    path.append(node.val)

    if node.left is None and node.right is None:
        if total == targetSum:
            result.append(path.copy())

        path.pop()
        return

    dfs(node.left, total)
    dfs(node.right, total)

    path.pop()
```

## 5. append / pop 위치

현재 node는 left/right 두 경로 모두의 공통 prefix다.

따라서:

```text
현재 node append
-> left 전체 탐색
-> right 전체 탐색
-> 현재 node pop
```

이 순서가 된다.

leaf branch에서는 `return` 때문에 아래의 공통 `path.pop()`까지 내려가지 않으므로 leaf 안에서 직접 pop해야 한다.

기억할 문장:

> 내가 append한 호출은 빠져나가기 전에 자기 몫의 pop을 한다.

## 6. 왜 path.copy()인가?

`path`는 mutable list이고 모든 호출에서 같은 객체를 공유한다.

```python
result.append(path)
```

는 snapshot이 아니라 같은 object reference를 저장한다.
이후 backtracking의 `path.pop()`이 저장된 결과까지 바꿀 수 있다.

따라서:

```python
result.append(path.copy())
```

로 현재 경로의 복사본을 저장한다.

## 7. Memoization이 필요한가?

보통 필요 없다.

일반 binary tree에서 각 node는 부모가 하나이므로 root에서 그 node로 도달하는 경로가 하나다.
따라서 DFS 중 같은 `node` state를 여러 경로에서 반복 계산하지 않는다.

```text
416
-> 서로 다른 선택 경로가 같은 (index, sum) state로 합쳐짐
-> memo 효과 있음

113
-> 각 tree node에 한 경로로 도달
-> overlapping subproblem이 없음
-> memo 이점 거의 없음
```

중요한 기준은:

> **재귀/백트래킹인지가 아니라 같은 state가 반복되는가?**

## 8. 시험용 한 줄

```text
113 Path Sum II
= Tree DFS
+ path에 현재 node 선택
+ leaf에서 정답 snapshot 저장
+ left/right 탐색
+ pop으로 상태 복구
```
