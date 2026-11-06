# LeetCode 98 — Validate Binary Search Tree

## 핵심 설계

- **Contract:** 현재 노드를 루트로 하는 서브트리가 전달받은 범위 안에서 유효한 BST인지 검사한다.
- **Parameter:** `up_bound`(상한), `low_bound`(하한). 조상 값의 단순 최댓값/최솟값이 아닌 **현재 노드가 만족해야 할 제약**이다.
- **Body:** `low_bound < node.val < up_bound`를 확인한다. 바로 아래 자식만 비교하지 않고 **현재 노드가 자기 제약을 검사**한다.
- **Return:** 왼쪽과 오른쪽 서브트리의 유효성 결과를 `and`로 결합한다.
- **Base Case:** 빈 노드는 `True`. 리프라고 조건 검사 없이 `True`를 반환하면 안 된다.

## 직접 작성한 풀이

```python
class Solution:
    def isValidBST(self, root: TreeNode | None) -> bool:
        def recur(node, up_bound, low_bound):
            if node is None:
                return True

            if not (node.val > low_bound and node.val < up_bound):
                return False

            return (
                recur(node.left, min(up_bound, node.val), low_bound)
                and recur(node.right, up_bound, max(low_bound, node.val))
            )

        return recur(root, float('inf'), float('-inf'))
```

## 배운 점

처음에는 부모에서 자식 값을 검사하고, 조상 값들의 최대·최솟값을 전달하려 했다. 하지만 **서브트리 전체에 적용되는 상·하한**을 전달하면 각 호출이 자기 노드만 검사해도 된다. 현재 노드가 이미 범위 검사를 통과했으므로 `min(up_bound, node.val)`은 `node.val`, `max(low_bound, node.val)`도 `node.val`로 단순화 가능하다.

전위/후위부터 정하는 게 아니라 **함수 계약 → Parameter 의미 → 현재 노드 검사 → 자식에게 제약 전달** 순으로 사고했다는 점이 핵심.

- 시간: **O(n)** / 재귀 스택: **O(h)** (최악 O(n))
