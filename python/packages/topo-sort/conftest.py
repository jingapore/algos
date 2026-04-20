import pytest


@pytest.fixture
def graph_a() -> list[list[int]]:
    return [[1, 2], [], [3, 4], [], []]
