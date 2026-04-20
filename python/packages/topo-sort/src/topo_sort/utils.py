from collections.abc import Iterable


def get_nodes(adj: list[list[int]]) -> Iterable[int]:
    return range(len(adj))
