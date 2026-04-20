from topo_sort import dfs_topo_sort, bfs_topo_sort
from typing import Protocol, runtime_checkable


@runtime_checkable
class TopoSort(Protocol):
    def sort(self, input: list[list[int]]) -> list[int]: ...

#TODO: test for cycles

def test_singleroot(graph_single_root: list[list[int]]):
    res = bfs_topo_sort(graph_single_root)
    for i in range(len(graph_single_root)):
        assert i in res

    assert res.index(0) < res.index(1)
    assert res.index(2) < res.index(4)
    assert res.index(2) < res.index(3)


def test_tworoots(graph_two_roots: list[list[int]]):
    res = bfs_topo_sort(graph_two_roots)
    for i in range(len(graph_two_roots)):
        assert i in res

    assert res.index(0) < res.index(1)
    assert res.index(2) < res.index(4)
    assert res.index(2) < res.index(3)
    # both 5 and 0 are roots with deps on 1
    assert res.index(5) < res.index(1)
    assert res.index(0) < res.index(1)
