from collections.abc import Mapping, MutableMapping
from enum import Enum
from .utils import get_nodes
from dataclasses import dataclass


class State(Enum):
    VISITED = 1
    VISITING = 2
    NOT_VISITED = 3


type Result = Cycle | None  # int is end node


@dataclass
class Cycle:
    start_node: int
    end_node: int


def create_cycle(start: int, end: int, parent: Mapping[int, int]) -> list[int]:
    cycle: list[int] = []
    curr: int | None = end
    while curr is not None:
        cycle.append(curr)
        if curr == start:
            break
        curr = parent.get(curr, None)
    cycle.reverse()
    cycle.append(cycle[0])
    return cycle


def dfs_detection(adj_list: Mapping[int, list[int]]) -> list[int] | None:
    nodes: list[int] = get_nodes(adj_list)
    parent: MutableMapping[int, int] = dict()
    states: MutableMapping[int, State] = {node: State.NOT_VISITED for node in nodes}

    def dfs(node: int) -> Result:
        states[node] = State.VISITING
        for child in adj_list.get(node, []):
            match states[child]:
                case State.NOT_VISITED:
                    parent[child] = node
                case State.VISITING:
                    return Cycle(child, node)
                case State.VISITED:
                    continue
            match dfs(child):
                case Cycle() as c:
                    return c
                case None:
                    ...
        states[node] = State.VISITED
        return None

    for node in nodes:
        if states[node] == State.NOT_VISITED:
            print(f"visiting {node}")
            match dfs(node):
                case Cycle() as c:
                    return create_cycle(c.start_node, c.end_node, parent)
                case None:
                    continue

    return None
