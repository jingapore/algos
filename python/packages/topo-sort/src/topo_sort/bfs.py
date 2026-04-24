from .utils import get_nodes
from collections import deque
from collections.abc import MutableMapping
from .utils import get_deps


# reference: https://dev.to/leopfeiffer/topological-sort-with-kahns-algorithm-3dl1
def bfs_topo_sort(adj: list[list[int]]) -> list[int]:
    nodes = get_nodes(adj)
    # this doesn't have to be a map, a counter will do
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
            # we can just decrement counter
            deps[child].discard(node)
            if len(deps[child]) == 0:
                q.appendleft(child)

    if len(finish) < len(list(nodes)):
        # because of cycle we won't be able to push all nodes
        raise Exception("Cycle detected")

    return finish
