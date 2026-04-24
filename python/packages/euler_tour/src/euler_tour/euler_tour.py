from utils import get_nodes
from collections.abc import Mapping, MutableMapping


class EulerTour:
    def __init__(self, adj_list: Mapping[int, list[int]]):
        self.adj_list: Mapping[int, list[int]] = adj_list
        self.nodes: list[int] = get_nodes(self.adj_list)
        self.start_timer: MutableMapping[int, int] = dict()
        self.end_timer: MutableMapping[int, int] = dict()
        self.timer: int = 0
        if len(self.nodes) > 0:
            self.tour(self.nodes[0])

    def tour(self, x: int):
        if x in self.start_timer:
            raise Exception(
                f"This is atree and {x} shouldn't have been visited according to {self.start_timer}"
            )
        self.start_timer[x] = self.timer
        self.timer += 1

        for child in self.adj_list.get(x, []):
            # assume this is a tree, so each child has only one parent
            # hence we don't have to check if it's been visited
            self.tour(child)
        if x in self.end_timer:
            raise Exception(
                f"This is atree and {x} shouldn't have been visited according to {self.end_timer}"
            )

        self.end_timer[x] = self.timer
        return
