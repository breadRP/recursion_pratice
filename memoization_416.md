# LeetCode 416 - Partition Equal Subset Sum

이 문제는 **분기형 재귀 + 메모이제이션**의 대표 예시로 볼 수 있다.

---

# 1. 문제를 재귀로 보는 핵심

배열의 원소들을 두 그룹으로 나누어 합이 같아질 수 있는지 확인하는 문제다.

전체 합이 `total`이라면, 한쪽 부분집합의 합이

```text
target = total // 2
```

이 될 수 있는지만 확인하면 된다.

따라서 전체 합이 홀수라면 바로 `False`다.

```python
if sum(nums) % 2 != 0:
    return False
```

---

# 2. 상태를 어떻게 잡는가?

재귀 함수의 상태를 다음처럼 잡을 수 있다.

```python
recur(index, current_sum)
```

의미:

```text
index번째 원소부터 보면서
현재까지 만든 합이 current_sum일 때,
target을 만들 수 있는가?
```

여기서

- `index` = 현재 몇 번째 원소를 보고 있는지
- `current_sum` = 지금까지 선택한 원소들의 합

이다.

즉 상태란 **현재 문제를 이어서 풀기 위해 필요한 최소 정보**다.

---

# 3. 왜 분기형 재귀인가?

각 원소마다 선택지는 두 개다.

```text
현재 원소를 선택한다
현재 원소를 선택하지 않는다
```

그래서 재귀도 두 갈래로 분기된다.

```python
return (
    recur(index + 1, current_sum + nums[index])
    or
    recur(index + 1, current_sum)
)
```

이 문제는 둘 중 하나라도 `target`을 만들 수 있으면 성공이므로 `or`로 결과를 합친다.

---

# 4. 종료조건

대표적으로 다음 조건을 사용할 수 있다.

```python
if current_sum == target:
    return True
```

목표 합을 만들었으면 성공이다.

양수 배열이므로 목표보다 커졌다면 더 볼 필요가 없다.

```python
if current_sum > target:
    return False
```

끝까지 봤는데 목표를 못 만들었다면 실패다.

```python
if index == len(nums):
    return False
```

---

# 5. 단순 재귀의 문제점

각 원소마다

```text
선택 / 비선택
```

두 경우가 생기므로 최악의 경우 호출 수는 대략

```text
2^n
```

까지 증가한다.

즉 단순 재귀의 시간복잡도는 대략:

```text
O(2^n)
```

이다.

---

# 6. 왜 메모이제이션이 필요한가?

중요한 점은 서로 다른 선택 경로를 거쳐도 **같은 상태**에 도달할 수 있다는 것이다.

예를 들어 어떤 경로로 왔든

```text
index = 5
current_sum = 11
```

이라면 그 이후의 결과는 항상 같다.

즉

```python
recur(5, 11)
```

을 여러 번 다시 계산할 필요가 없다.

그래서 한 번 계산한 상태의 결과를 저장해둔다.

---

# 7. 메모이제이션 템플릿

```python
memo = {}

def recur(index, current_sum):
    if current_sum == target:
        return True

    if current_sum > target or index == len(nums):
        return False

    state = (index, current_sum)

    if state in memo:
        return memo[state]

    memo[state] = (
        recur(index + 1, current_sum + nums[index])
        or
        recur(index + 1, current_sum)
    )
    return memo[state]
```

여기서 두 재귀 호출을 따로 변수에 먼저 저장하지 않고 `or` 안에 직접 넣은 이유도 중요하다.

```python
select = recur(...)
skip = recur(...)
return select or skip
```

처럼 쓰면 Python은 `select`를 계산한 뒤 `skip`도 **무조건 먼저 계산**한다.  
즉 `select == True`여도 두 번째 재귀 호출까지 이미 실행된 상태다.

반면:

```python
return recur(...) or recur(...)
```

처럼 쓰면 Python의 **short-circuit evaluation(단락 평가)** 이 적용된다.

```text
첫 번째 recur(...)가 True
-> 전체 결과는 이미 True
-> 두 번째 recur(...)는 호출하지 않음

첫 번째 recur(...)가 False
-> 두 번째 recur(...)를 호출해서 확인
```

따라서 재귀에서 `or` / `and`를 사용할 때는 단순히 코드 한 줄을 줄이는 문제가 아니라,
**불필요한 재귀 분기를 실제로 탐색하지 않게 만들 수 있다.**

핵심 구조는:

```text
전에 계산한 상태인가?
YES -> 저장된 결과 반환
NO  -> 계산하고 저장
```

이다.

---

# 8. Boolean 재귀에서 `or` short-circuit

416처럼 "둘 중 하나만 성공하면 되는" 문제에서는 `or`의 평가 방식도 성능에 영향을 줄 수 있다.

예를 들어:

```python
select = recur(select_state)
skip = recur(skip_state)

result = select or skip
```

이 코드는 `select`와 `skip`을 모두 먼저 계산한다.

하지만:

```python
result = recur(select_state) or recur(skip_state)
```

는 첫 번째 호출이 `True`를 반환하면 두 번째 호출을 생략한다.

즉:

```text
A or B
-> A가 True면 B는 평가하지 않음

A and B
-> A가 False면 B는 평가하지 않음
```

이를 **short-circuit evaluation**이라고 한다.

주의할 점:

> "변수를 만들면 느리다"가 핵심이 아니다.  
> **함수 호출을 변수에 저장하려고 먼저 실행해버리면, `or`가 두 번째 호출을 생략할 기회를 잃는 것**이 핵심이다.

---

# 9. 시간복잡도가 왜 줄어드는가?

메모이제이션을 하지 않으면 같은 상태를 여러 번 계산해서 `O(2^n)`까지 커질 수 있다.

하지만 상태는 사실상

```text
(index, current_sum)
```

조합으로 결정된다.

가능한 `index`는 최대 `n`개,
가능한 `current_sum`은 최대 `target` 정도이므로,
서로 다른 상태의 개수는 대략

```text
n * target
```

개다.

따라서 메모이제이션을 사용하면 시간복잡도를 대략

```text
O(n * target)
```

수준으로 줄일 수 있다.

공간복잡도 역시 메모 테이블 때문에 대략

```text
O(n * target)
```

까지 사용할 수 있다.

---

# 10. 시험장에서 떠올릴 포인트

분기 재귀를 만들었는데 시간복잡도가 `O(2^n)`처럼 커진다면 다음을 확인한다.

```text
같은 상태를 여러 번 계산하고 있지 않은가?
```

같은 상태가 반복된다면:

```text
메모이제이션 고려
```

이 문제에서 기억할 핵심은:

```text
416 Partition Equal Subset Sum

상태 = index + current_sum
선택 = 현재 원소 선택 / 비선택
단순 재귀 = O(2^n)
중복 상태 존재 = 메모이제이션
메모이제이션 후 = O(n * target)
Boolean 분기 = or / and short-circuit도 확인
```

이다.
