from .utils import get_nodes
from collections import deque
from collections.abc import MutableMapping
from .utils import get_deps


# reference: https://dev.to/leopfeiffer/topological-sort-with-kahns-algorithm-3dl1
def bfs_topo_sort(adj: list[list[int]]) -> list[int]:
    nodes = get_nodes(adj)
    deps: MutableMapping[int, set[int]] = get_deps(adj)
    q: deque[int] = deque()
    for node in nodes:
        if len(deps[node]) == 0:
            q.appendleft(node)

    finish: list[int] = []

    while len(q) > 0:
        node = q.pop()
        finish.append(node)
        for child in adj[node]:
            deps[child].discard(node)
            if len(deps[child]) == 0:
                q.appendleft(child)

    return finish
