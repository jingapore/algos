from collections.abc import Mapping
from dataclasses import dataclass
from utils import get_nodes


@dataclass
class State:
    time_in: int
    lowest_time_from_traversal: int


def offline_detect(adj_list: Mapping[int, list[int]]) -> list[tuple[int, int]]:
    nodes: list[int] = get_nodes(adj_list)
    node_states: list[State | None] = [None] * len(nodes)
    bridges: list[tuple[int, int]] = []
    timer: int = 0

    def dfs(node: int, parent: int | None) -> int:
        nonlocal timer
        nonlocal bridges
        nonlocal node_states
        state = State(time_in=timer, lowest_time_from_traversal=timer)
        timer += 1
        for child in adj_list[node]:
            if child == parent:
                continue
            child_lowest_time = dfs(child, node)
            if child_lowest_time > state.time_in:
                bridges.append((node, child))
            state.lowest_time_from_traversal = min(
                state.lowest_time_from_traversal, child_lowest_time
            )
        node_states[node] = state
        return state.lowest_time_from_traversal

    for node in nodes:
        if node_states[node] is None:
            timer = 0
            dfs(node, None)
    return bridges
