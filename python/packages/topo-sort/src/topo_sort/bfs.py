from .utils import get_nodes
from collections import deque


# reference: https://dev.to/leopfeiffer/topological-sort-with-kahns-algorithm-3dl1
def bfs_topo_sort(adj: list[list[int]]) -> list[int]:
    nodes = get_nodes(adj)
    deps: Mapping[int, set[int]] = get_deps(adj)
    for node in nodes:
        q.append(node)

    finish: list[int] = []

    while len(q) > 0:
        node = q.pop()
        finish.append(node)
        for child in adj[node]:
            q.appendleft(child)

    return finish
