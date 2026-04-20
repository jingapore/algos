def _get_nodes(adj: list[list[int]]) -> list[int]:
    return []


def dfs_topo_sort(adj: list[list[int]]) -> list[int]:
    nodes = _get_nodes(adj)
    finish: list[int] = []
    visited: set[int] = set()

    def dfs(node: int):
        visited.add(node)
        for child in adj[node]:
            # check whether visited?
            dfs(node)
        finish.append(node)
        return

    for node in nodes:
        if node not in visited:
            dfs(node)

    return list(reversed(finish))
