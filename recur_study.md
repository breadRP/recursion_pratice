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

## 템플릿

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

시험장에서 떠올릴 질문:

> 현재 노드의 답을 자식 서브트리의 답으로 만들 수 있는가?

---

# 6. 백트래킹형 재귀

핵심은 다음 순서다.

```text
선택
-> 재귀
-> 선택 취소
```

대표 예시

- 순열
- 조합
- 부분집합
- N-Queen
- 경로 탐색

공유 리스트를 사용한다면 한 분기 탐색 후 반드시 원래 상태로 되돌려야 한다.

## 템플릿

```python
def backtrack(...):
    if 완성조건:
        answer.append(path.copy())
        return

    for choice in 가능한_선택:
        path.append(choice)

        backtrack(...)

        path.pop()
```

기억할 문장:

```text
choose -> explore -> unchoose
```

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
