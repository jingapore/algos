from topo_sort import dfs_topo_sort


def test_dfs(graph_a: list[list[int]]):
    res = dfs_topo_sort(graph_a)
    for i in range(len(graph_a)):
        assert i in res

    assert res.index(0) < res.index(1)
    assert res.index(2) < res.index(4)
    assert res.index(2) < res.index(3)
