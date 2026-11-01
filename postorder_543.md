# LeetCode 543 - Diameter of Binary Tree

이 문제는 **Tree Postorder DFS(후위순회) + 반환값과 전체 정답의 분리**를 이해하기 위한 대표 예시다.

## 1. 무엇을 구하는가?

트리에서 두 노드 사이의 최장 경로를 이루는 **간선의 수**를 구한다. 그 경로는 반드시 루트를 통과하지 않는다.

## 2. 먼저 함수의 의미를 정하기

```text
recur(node)
= 현재 node부터 아래로 내려갈 수 있는 가장 긴 높이 (노드 수)

left / right
= 자식에게서 받은 각 서브트리의 높이

self.max_length
= 지금까지 확인한 모든 노드의 지름 후보 중 최댓값 (간선 수)
```

여기서 중요한 질문은 **부모가 자식에게 무엇을 받아야 자신의 지름 후보를 계산할 수 있는가?** 이다. 부모가 필요한 것은 자식 서브트리 전체의 지름이 아니라 자식에서 아래로 이어지는 **한 갈래의 최대 높이**다.

## 3. 후위순회로 값이 올라오는 순서

```text
      A
     / \\
    B   C
   / \\
  D   E

D, E, C -> 높이 1 반환
B -> left=1, right=1
     지름 후보 = 2, 부모 A에게 높이 2 반환
A -> left=2, right=1
     지름 후보 = 3, 부모에게 높이 3 반환
정답 = 3 (간선 수)
```

부모 호출은 자식 호출의 `return`이 끝나야 계속 실행할 수 있다. 따라서 `left = recur(node.left)`, `right = recur(node.right)` 다음 코드가 실행되는 시점에는 이미 자식의 결과가 준비되어 있다.

## 4. 답 갱신과 return은 다른 작업

```python
left = recur(node.left)
right = recur(node.right)

self.max_length = max(self.max_length, left + right)
return max(left, right) + 1
```

- **답 갱신:** 현재 노드를 통과해 왼쪽 끝에서 오른쪽 끝까지 가는 경로는 양쪽 높이의 합이다.
- **return:** 부모에서 아래로 이어 붙일 때는 왼쪽과 오른쪽 중 하나만 선택할 수 있다. 그래서 높은 쪽 + 현재 노드 1개를 반환한다.
- **주의:** `return self.max_length`로 작성하면 부모가 지름을 높이로 착각하게 된다.
- **또 다른 주의:** `left + right`는 현재 노드를 통과하는 후보이지, 항상 현재 서브트리의 최대 지름이라는 뜻은 아니다. 모든 노드에서 `self.max_length`를 갱신하는 이유다.

## 5. 실제 Python 구현

```python
class Solution:
    def diameterOfBinaryTree(self, root):
        self.max_length = 0

        def recur(node):
            if node is None:
                return 0

            left = recur(node.left)
            right = recur(node.right)

            self.max_length = max(self.max_length, left + right)
            return max(left, right) + 1

        recur(root)
        return self.max_length
```

### 왜 +1을 지름 갱신에 넣지 않을까?

빈 노드 높이 0, 실제 노드 높이 1로 **노드 수 기준** 높이를 정의했기 때문이다.

```text
leaf: left=0, right=0
지름 후보 = 0 간선
반환 높이 = 1 노드

left 높이 2, right 높이 1:
지름 후보 = 2+1 = 3 간선
반환 높이 = max(2,1)+1 = 3 노드
```

## 6. 스코프 관련 주의

`self.max_length`는 인스턴스 속성이므로 중첩 함수에서 갱신할 수 있다. 반면 바깥 함수의 지역변수 `max_length`를 내부 함수에서 대입하려면 `nonlocal max_length`를 선언해야 `UnboundLocalError`가 나지 않는다.

## 7. 113과 비교

| 문제 | DFS 과정 | 별도 관리 | 재귀 return |
|---|---|---|---|
| [113 Path Sum II](backtracking_113.md) | 내려가며 path 추가, 돌아오며 pop | 현재 경로와 결과 목록 | 높이 계산 불필요 |
| 543 Diameter | 자식이 계산한 높이를 받은 뒤 현재 노드 처리 | 최대 지름 | 부모용 높이 |

113에서는 **공유 상태의 복구**, 543에서는 **후위순회에서 부모에게 전달할 반환값의 의미**가 핵심이다.

## 8. 복잡도와 회독용 한 줄

- 시간: O(n) — 각 노드 한 번 방문
- 추가 공간: O(h) — 재귀 호출 스택, 편향 트리에서는 O(n)

> **543 = 자식 높이 수집 → 현재 노드를 통과하는 지름 후보로 전체 답 갱신 → 부모에게는 한 갈래 높이 반환.**
