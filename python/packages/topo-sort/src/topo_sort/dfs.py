from .utils import get_nodes


def dfs_topo_sort(adj: list[list[int]]) -> list[int]:
    nodes = get_nodes(adj)
    finish: list[int] = []
    visited: set[int] = set()

    def dfs(node: int):
        visited.add(node)
        for child in adj[node]:
            if child not in visited:
                # assume it's dag for now
                dfs(child)
        finish.append(node)
        return

    for node in nodes:
        if node not in visited:
            dfs(node)

    return list(reversed(finish))
