from collections.abc import Iterable, MutableMapping
from collections import defaultdict


def get_nodes(adj: list[list[int]]) -> Iterable[int]:
    return range(len(adj))


def get_deps(adj: list[list[int]]) -> MutableMapping[int, set[int]]:
    deps: MutableMapping[int, set[int]] = defaultdict(set)
    for node, children in enumerate(adj):
        for child in children:
            deps[child].add(node)
    return deps
