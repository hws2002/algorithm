# Time Complexity of Sorting Algorithms
모두 오름차순으로 정렬하는 경우를 가정한다.
## SelectionSort vs InsertionSort
SelectionSort은 최악의 경우이던, 최선의 경우이던, 평균이던, 무조건 O(${n(n-1)\over2}$)의 시간 복잡도를 가진다.  
그러나 InsertionSort은 최선의 경우 O($n$)의 시간 복잡도를 가지며, (이미 오름차순으로 정렬되어 있는 상황).
최악의 경우 O(${n(n-1)\over2}$)의 시간 복잡도를 가진다(내림차순으로 정렬하는 상황).
