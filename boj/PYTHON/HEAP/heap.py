class BinaryHeap(object):
    def __init__(self):
        self.items = [None]
    
    def __len(self):
        return len(self.items) - 1
    
    # 삽입
    def _percolate_up():
        i = len(self)
        parent = i // 2
        while parent > 0:
            if self.items[i] < self.items[parent]:
                self.items[i], self.items[parent] = self.items[parent], self.items[i]
                i = parent
                parent = i // 2
    
    def insert(self, k):
        self.items.append(k)
        self._percolate_up()
        
    # 추출
    def _percolate_down(self, idx):
        left = idx<<1
        right = idx<<1|1
        smallest = idx
        
        if left <= len(self) and self.items[left] < self.items[smallest]:
            smallest = left
        if right <= len(self) and self.items[right] < self.items[smallest]:
            smallest = right

        if smallest != idx:
            self.items[idx], self.items[smallest] = \
                self.items[smallest], self.items[idx]
            self._percolate_down(smallest)
        
    
    def extract(self):
        extracted = self.items[1]
        self.items[1] = self.items[-1]
        self.items.pop()
        self._percolate_down(1)
        return extracted
    