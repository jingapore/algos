import pytest


@pytest.fixture
def graph_single_root() -> list[list[int]]:
    return [[1, 2], [], [3, 4], [], []]

@pytest.fixture
def graph_two_roots() -> list[list[int]]:
    return [[1, 2], [], [3, 4], [], [], [1]]
