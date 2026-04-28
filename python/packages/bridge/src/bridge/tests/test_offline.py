from bridge import offline_detect


def test_offline():
    adj_list: dict[int, list[int]] = {0: [1], 1: [0, 2], 2: [1]}
    bridges = offline_detect(adj_list)
    assert set(bridges) == set([(0, 1), (1, 2)])
