from collections.abc import Mapping, MutableMapping
from collections import defaultdict
from utils import get_nodes
import sys


def floyd_warshall_allpairs_withpath(
    edges: list[tuple[int, int, int]],
) -> tuple[list[list[int]], Mapping[int, Mapping[int, list[int]]]]:
    adj_list: Mapping[int, list[int]] = defaultdict(list)
    for u, v, _ in edges:
        adj_list[u].append(v)
    nodes = get_nodes(adj_list)
    num_nodes = len(nodes)

    shortest_paths: list[list[int]] = [
        [int(sys.maxsize)] * num_nodes for _ in range(num_nodes)
    ]
    # parent map means that from path u to v, v's parent is whatever the val is
    # and to trace it we get the parent, and go u to parent in the map
    parent_map: list[list[int]] = [[-1] * num_nodes for _ in range(num_nodes)]

    for node in nodes:
        shortest_paths[node][node] = 0
        parent_map[node][node] = node

    for u, v, w in edges:
        shortest_paths[u][v] = w
        parent_map[u][v] = u

    for k in nodes:
        for u in nodes:
            for v in nodes:
                candidate_val = shortest_paths[u][k] + shortest_paths[k][v]
                if candidate_val < shortest_paths[u][v]:
                    shortest_paths[u][v] = candidate_val
                    parent_map[u][v] = parent_map[k][v]
    paths: MutableMapping[int, MutableMapping[int, list[int]]] = defaultdict(
        lambda: defaultdict(list)
    )
    for u in nodes:
        for v in nodes:
            if parent_map[u][v] == -1 and u != v:
                continue
            curr: int = v
            while curr != u:
                paths[u][v].append(curr)
                curr = parent_map[u][curr]
            paths[u][v].append(u)
            paths[u][v].reverse()

    return shortest_paths, paths
