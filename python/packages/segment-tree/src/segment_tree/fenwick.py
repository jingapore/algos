class Fenwick:
    def __init__(self, n: int):
        self.arr: list[int] = [0] * n

    def point_query(self, idx: int) -> int:
        return self.arr[idx]
