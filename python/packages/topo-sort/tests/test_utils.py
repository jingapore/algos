from topo_sort import get_deps


def test_get_deps():
    deps = get_deps([[1], [2], []])
    assert len(deps[2]) == 1
    assert len(deps[0]) == 0
