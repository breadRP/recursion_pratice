# Recursion Thinking Guide (재귀 함수 사고 과정 정리)

재귀를 설계할 때는 모든 호출을 머릿속에서 끝까지 펼치는 것이 아니라,
**함수의 의미를 정의하고 더 작은 문제의 답을 믿은 뒤 현재 한 단계만 설계하는 것**이 핵심이다.

---

# 1. 재귀 문제를 보면 가장 먼저 생각할 4가지

코드를 쓰기 전에 아래 4줄부터 정리한다.

```text
함수 의미 =
상태 =
종료조건 =
재귀식 =
```

## ① 함수의 의미

`f(...)`가 정확히 무엇을 반환하는지 정한다.

예시

```text
f(n) = n이 2의 거듭제곱인지 반환
f(left, right) = left~right 구간에 대한 답
f(node) = node를 루트로 하는 서브트리의 답
```

재귀에서 가장 중요한 부분이다. 반환값의 의미가 애매하면 재귀식도 꼬이기 쉽다.

## ② 상태(State)

현재 재귀 호출이 **어떤 상황을 나타내는지 결정하는 정보**다.

예시

```text
Power of Two -> n
구간 문제 -> left, right
트리 DFS -> 현재 node
백트래킹 -> 현재 위치 + 지금까지의 선택
```

즉, 다음 재귀 호출로 넘어갈 때 현재 문제 상황을 표현하기 위해 필요한 값들을 상태라고 보면 된다.

## ③ 종료조건(Base Case)

더 이상 문제를 줄이지 않아도 답을 바로 알 수 있는 가장 작은 경우다.

예시

```python
if n == 1:
    return True

if left == right:
    return nums[left]

if node is None:
    return 0
```

## ④ 재귀식 / 현재 단계 처리

더 작은 문제의 답을 이용해서 현재 문제의 답을 만든다.

예시

```python
return n + recur(n - 1)
```

또는 여러 분기가 있다면:

```python
left_result = recur(...)
right_result = recur(...)
return max(left_result, right_result)
```

핵심 생각:

> 작은 문제의 답은 재귀 함수가 이미 제대로 구해준다고 가정하고, 현재 단계만 설계한다.

---

# 2. 단순 감소형 재귀

입력을 조금씩 줄이면서 같은 문제를 반복하는 형태다.

```text
n
-> 더 작은 n
-> 더 작은 n
-> ...
```

대표 예시

- Factorial
- Fibonacci의 기본 형태
- Power of Two
- 자릿수 계산

## 생각 방법

문제를 입력만 더 작게 해서 **똑같은 문제**로 만들 수 있는지 본다.

예를 들어 Power of Two라면:

```text
16이 2의 거듭제곱인가?
-> 8이 2의 거듭제곱인가?
-> 4
-> 2
-> 1
```

## 템플릿

```python
def recur(n):
    if 종료조건:
        return 정답

    return recur(더_작은_n)
```

현재 값을 결과에 포함한다면:

```python
def recur(n):
    if 종료조건:
        return 기본값

    return 현재값 + recur(더_작은_n)
```

예시:

```python
def sum_n(n):
    if n == 0:
        return 0

    return n + sum_n(n - 1)
```

시험장에서 떠올릴 질문:

> 입력을 조금 줄여도 같은 문제인가?

---

# 3. 분기형 재귀

한 상태에서 선택지가 여러 개 있어서 재귀 호출이 트리처럼 갈라지는 형태다.

```text
현재 상태
├─ 선택 A
└─ 선택 B
```

대표 예시

- 왼쪽 / 오른쪽 선택
- 포함 / 미포함
- 여러 경로 중 선택
- 게임에서 최선의 선택

## 생각 방법

현재 가능한 선택을 각각 재귀로 계산하고, 문제에 맞게 결과를 합친다.

```python
result1 = recur(선택1_후_상태)
result2 = recur(선택2_후_상태)
```

결합 방식은 문제에 따라 달라진다.

```python
max(result1, result2)
min(result1, result2)
result1 + result2
result1 or result2
```

### Boolean 분기에서는 short-circuit도 확인

`or` / `and`로 재귀 결과를 합칠 때는 Python의 **short-circuit evaluation(단락 평가)** 을 활용할 수 있다.

```python
# 두 호출을 모두 먼저 실행함
a = recur(choice_a)
b = recur(choice_b)
return a or b
```

위 코드는 `a`가 이미 `True`여도 `b = recur(...)`까지 실행한다.

반면:

```python
return recur(choice_a) or recur(choice_b)
```

는 첫 번째 호출이 `True`면 두 번째 호출을 아예 하지 않는다.

```text
A or B  -> A가 True면 B를 평가하지 않음
A and B -> A가 False면 B를 평가하지 않음
```

특히 분기형 재귀에서는 이 차이로 불필요한 분기를 줄일 수 있다.

> 중요한 점: "변수를 안 만들면 빠르다"가 아니라, **함수 호출을 먼저 끝내버리지 않고 `or` / `and`가 다음 호출 여부를 결정하게 하는 것**이 핵심이다.

## 템플릿

```python
def recur(state):
    if 종료조건:
        return 기본값

    result1 = recur(선택1_후_상태)
    result2 = recur(선택2_후_상태)

    return max(result1, result2)
```

시험장에서 떠올릴 질문:

> 현재 내가 할 수 있는 선택이 몇 개인가?

---

# 4. 구간형 재귀

배열이나 문자열의 일부 구간이 계속 줄어드는 문제에서 자주 사용한다.

실제로 `pop()`으로 데이터를 삭제하지 않고 `left`, `right` 인덱스로 현재 남아 있는 범위를 표현한다.

예시:

```python
nums = [1, 5, 2, 4]
```

```text
recur(1, 3)
```

은 `[5, 2, 4]` 구간만 남아 있다고 보는 것이다.

## 왜 인덱스를 쓰는가?

실제로 `pop()`하면 다른 분기를 탐색하기 전에 배열을 복구해야 한다.

하지만 인덱스만 움직이면:

```python
recur(left + 1, right)
recur(left, right - 1)
```

로 끝난다.

## 템플릿

```python
def recur(left, right):
    if left == right:
        return 기본값

    left_result = recur(left + 1, right)
    right_result = recur(left, right - 1)

    return 결과_결합(left_result, right_result)
```

## LeetCode 486 Predict the Winner 패턴

이 문제에서는 함수의 의미를 다음처럼 잡을 수 있다.

```text
play(left, right)
= 현재 플레이어가 left~right 구간에서
  상대보다 최대 몇 점 앞설 수 있는가
```

```python
def play(left, right):
    if left == right:
        return nums[left]

    left_pick = nums[left] - play(left + 1, right)
    right_pick = nums[right] - play(left, right - 1)

    return max(left_pick, right_pick)
```

왜 빼는가?

`play(...)`의 반환값은 **다음 차례 플레이어가 상대보다 얼마나 유리한지**를 의미한다.
따라서 현재 플레이어 입장에서는 그 값을 빼준다.

```text
현재 플레이어 점수 차이
= 지금 먹은 점수 - 다음 플레이어의 우위
```

최종적으로 Player 1의 점수 차이가 0 이상이면 승리 또는 무승부다.

```python
return play(0, len(nums) - 1) >= 0
```

---

# 5. 트리 / DFS형 재귀

트리는 구조 자체가 재귀적이다.

```text
현재 노드
├─ 왼쪽 서브트리
└─ 오른쪽 서브트리
```

왼쪽 서브트리도 트리고 오른쪽 서브트리도 트리이므로 재귀가 자연스럽다.

## 생각 방법

```text
현재 문제
-> 왼쪽 자식에게 맡김
-> 오른쪽 자식에게 맡김
-> 결과를 합침
```

## 기본 반환형 템플릿

```python
def dfs(node):
    if node is None:
        return 기본값

    left = dfs(node.left)
    right = dfs(node.right)

    return 현재노드와_left_right를_결합
```

예: 최대 깊이

```python
def depth(node):
    if node is None:
        return 0

    left = depth(node.left)
    right = depth(node.right)

    return max(left, right) + 1
```

## 경로 상태를 들고 내려가는 DFS

113 Path Sum II처럼 반환값을 합치는 대신 **현재 root→node 경로를 공유 상태로 들고 내려가는 문제**도 있다.

```text
현재 node 진입
-> 현재 node를 total/path에 반영
-> 왼쪽 DFS
-> 오른쪽 DFS
-> 현재 node를 path에서 제거
```

이 경우 DFS는 "어디를 탐색할지"를 정하고, backtracking은 "탐색 중 수정한 path를 어떻게 복구할지"를 담당한다.

### 종료조건 위치가 항상 함수 맨 위인 것은 아니다

113에서는 두 종류의 종료 판단이 있다.

```text
구조적 종료
-> node is None
-> 현재 node를 처리할 필요가 없으므로 바로 return

의미적 종료
-> 현재 node가 leaf
-> 현재 node의 값까지 total/path에 반영한 뒤에야 정답 여부를 판단 가능
```

따라서 leaf 판정은 현재 node를 state에 반영한 뒤에 두는 것이 자연스럽다.

```python
def dfs(node, total):
    if node is None:
        return

    total += node.val
    path.append(node.val)

    if node.left is None and node.right is None:
        if total == target:
            answer.append(path.copy())
        path.pop()
        return

    dfs(node.left, total)
    dfs(node.right, total)

    path.pop()
```

leaf에서 직접 `return`하면 함수 맨 아래의 `path.pop()`까지 도달하지 않으므로, leaf branch 안에서 자기 `append()`에 대응하는 `pop()`을 수행해야 한다.

시험장에서 떠올릴 질문:

> 현재 노드의 답을 자식 서브트리의 반환값으로 만들 것인가, 아니면 현재 경로 state를 들고 내려갈 것인가?

---

# 6. 백트래킹형 재귀

백트래킹은 완전히 별개의 재귀 모양이라기보다, **분기 탐색 중 공유 상태를 바꾸고 다시 되돌리는 방식**으로 보는 것이 좋다.

핵심은:

```text
choose
-> explore
-> unchoose
```

대표 예시

- 순열
- 조합
- 부분집합
- N-Queen
- 트리의 root→leaf 경로 탐색
- 113 Path Sum II

## 핵심 규칙: append와 pop은 한 쌍

공유 리스트 `path`를 사용한다면:

```python
path.append(choice)   # choose
backtrack(...)        # explore
path.pop()            # unchoose
```

처럼 **내가 만든 상태 변경은 그 선택의 탐색이 끝난 직후 원상복구**한다.

중요한 것은 "항상 모든 재귀 호출 뒤에 pop"이 아니라:

> **이 append가 대표하는 선택의 범위가 끝나는 지점에서 pop한다.**

예를 들어 현재 tree node가 왼쪽과 오른쪽 두 경로의 공통 prefix라면:

```python
path.append(node.val)

dfs(node.left)
dfs(node.right)

path.pop()
```

처럼 왼쪽과 오른쪽을 모두 탐색한 뒤 현재 node를 pop한다.

## 113 Path Sum II에서의 구조

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

### 왜 `path.copy()`인가?

`path`는 모든 재귀 호출이 공유하는 mutable list다.

```python
result.append(path)
```

는 현재 내용을 복사하는 것이 아니라 **같은 list 객체의 reference**를 저장한다.
이후 `path.pop()`이 실행되면 이미 저장한 결과도 같이 바뀔 수 있다.

따라서 정답 경로는:

```python
result.append(path.copy())
```

처럼 snapshot을 저장한다.

## DFS와 Backtracking의 관계

```text
DFS
-> 어느 방향으로 탐색할 것인가
-> 한 경로를 깊게 내려감

Backtracking
-> 탐색하면서 바꾼 공유 state를
   부모 상태로 돌아올 때 복구
```

따라서 113은:

```text
Tree DFS
+ 분기 재귀
+ path 상태 유지
+ Backtracking
```

으로 볼 수 있다.

기억할 문장:

> **선택한다 → 그 선택으로 가능한 탐색을 끝낸다 → 선택을 취소한다.**

---

# 7. 분할정복형 재귀

큰 문제를 여러 개의 작은 독립 문제로 나누고 결과를 합친다.

대표 예시

- Merge Sort
- Quick Sort
- Binary Search

단순 감소형과의 차이:

```text
단순 감소형
n -> n-1

분할정복
큰 문제
├─ 왼쪽 부분
└─ 오른쪽 부분
```

## 템플릿

```python
def divide(left, right):
    if left == right:
        return 기본값

    mid = (left + right) // 2

    left_result = divide(left, mid)
    right_result = divide(mid + 1, right)

    return combine(left_result, right_result)
```

기억할 문장:

```text
Divide -> Conquer -> Combine
```

---

# 8. 메모이제이션형 재귀

새로운 재귀 유형이라기보다는 **재귀 + 결과 저장**이다.

메모이제이션의 핵심 조건은 "재귀인가?"가 아니라:

> **같은 state를 여러 경로에서 반복 계산하는가?**

이다.

분기 재귀에서는 같은 상태가 여러 번 등장할 수 있다.

```text
전에 계산한 상태인가?
YES -> 저장된 값 반환
NO  -> 계산 후 저장
```

## 템플릿

```python
memo = {}

def recur(state):
    if 종료조건:
        return 기본값

    if state in memo:
        return memo[state]

    result = ...

    memo[state] = result
    return result
```

구간형이라면:

```python
memo = {}

def recur(left, right):
    if left == right:
        return nums[left]

    if (left, right) in memo:
        return memo[(left, right)]

    result = ...
    memo[(left, right)] = result

    return result
```

## 일반 이진트리 DFS에서 memo가 보통 필요 없는 이유

보통의 tree는 각 node의 부모가 하나이므로 root에서 특정 node로 가는 경로도 하나다.

```text
root
├─ left subtree
└─ right subtree
```

일반 DFS는 각 node를 한 번 방문하므로 동일한 `node` state를 다른 경로에서 다시 계산하는 일이 거의 없다.

따라서:

```text
일반 Binary Tree DFS
-> overlapping subproblem이 없음
-> memo를 붙여도 다시 조회할 상태가 거의 없음
-> 보통 O(n) 순회만으로 충분
```

113 Path Sum II도 각 node에 한 번씩 도달하므로 일반적으로 memoization이 필요하지 않다.

단, "백트래킹이면 memo를 못 쓴다"는 뜻은 아니다. 서로 다른 선택 경로가 **동일한 state**로 합쳐지는 문제라면 backtracking/분기 재귀에도 memo를 사용할 수 있다.

시험용 판단:

```text
같은 state가 실제로 반복되는가?
YES -> memo 고려
NO  -> memo 불필요
```

---

# 9. 시험장에서 유형 구분하기

```text
입력 하나를 계속 작게 만들 수 있음
-> 단순 감소형

현재 선택지가 여러 개 있음
-> 분기형

배열/문자열의 범위가 계속 줄어듦
-> 구간형

node의 자식을 계속 탐색
-> 트리 / DFS형

선택했다가 다른 선택을 위해 되돌려야 함
-> 백트래킹형

문제를 여러 덩어리로 나누고 결과를 합침
-> 분할정복형

같은 상태가 반복해서 등장
-> 메모이제이션 고려
```

한 문제에 여러 유형이 섞일 수도 있다.

예를 들어 486 Predict the Winner는:

```text
구간형
+ 분기형
+ 최적 선택
+ 메모이제이션 가능
```

이다.

---

# 10. 재귀 실행을 이해하는 법

재귀 설계 시 모든 호출을 머릿속에서 끝까지 추적할 필요는 없다.

```python
left = recur(...)
right = recur(...)
```

를 봤을 때 중요한 것은 각 호출 내부를 전부 펼치는 것이 아니라:

> `recur(...)`가 내가 정의한 의미에 맞는 답을 반환한다고 가정한다.

그리고 현재 단계에서 그 결과를 어떻게 사용할지만 설계한다.

처음 공부할 때는 작은 입력 하나 정도만 직접 호출 트리를 펼쳐서 검증하면 충분하다.

---

# 11. 재귀 설계 체크리스트

문제를 풀기 전에 아래를 채운다.

```text
1. 함수 의미:
   f(...)가 정확히 무엇을 반환하는가?

2. 상태:
   현재 문제 상황을 표현하려면 어떤 값이 필요한가?

3. 종료조건:
   가장 작은 문제의 답은 무엇인가?

4. 재귀식:
   작은 문제의 답으로 현재 문제를 어떻게 만들 것인가?
```

그 다음 추가로 확인한다.

```text
- 매 호출마다 문제 크기가 실제로 줄어드는가?
- 선택지가 여러 개라면 모든 필요한 분기를 탐색하는가?
- 같은 상태가 반복되면 memo가 필요한가?
- mutable 객체를 공유한다면 복구가 필요한가?
- append한 선택은 모든 return 경로에서 대응하는 pop으로 복구되는가?
- 정답에 mutable path를 저장한다면 snapshot(`path.copy()`)이 필요한가?
- 의미적 종료조건을 검사하기 전에 현재 state를 먼저 반영해야 하는가?
```

---

# 12. 한 줄 요약

재귀는 모든 호출을 미리 계산하는 방식이 아니다.

> **함수의 의미를 정의하고, 작은 문제의 답을 이미 알고 있다고 가정한 뒤, 현재 한 단계의 답을 만드는 방식이다.**

시험에서는 먼저 다음 네 줄부터 적는다.

```text
함수 의미 =
상태 =
종료조건 =
재귀식 =
```
