from collections.abc import Mapping


def get_nodes(adj_list: Mapping[int, list[int]]) -> list[int]:
    nodes = list(
        set(list(adj_list.keys()) + list(set(x for y in adj_list.values() for x in y)))
    )
    return sorted(nodes)
