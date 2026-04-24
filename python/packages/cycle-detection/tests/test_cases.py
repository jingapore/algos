from cycle_detection import dfs_detection


def test_no_cycle():
    adj_list = dict()
    adj_list[0] = [1, 2, 3]
    cycles = dfs_detection(adj_list)
    assert cycles is None


def test_cycle():
    adj_list = dict()
    adj_list[0] = [1, 2, 3]
    adj_list[1] = [0]
    cycles = dfs_detection(adj_list)
    assert cycles == [0, 1, 0] or cycles == [1, 0, 1]

    adj_list = dict()
    adj_list[5] = [6]
    adj_list[0] = [1, 2, 3]
    adj_list[1] = [4]
    adj_list[4] = [0]
    cycles = dfs_detection(adj_list)
    assert cycles == [0, 1, 4, 0] or cycles == [1, 4, 0, 1] or cycles == [4, 0, 1, 4]


def test_cycle_not_root():
    adj_list = dict()
    adj_list[5] = [6]
    adj_list[0] = [1, 2, 3]
    adj_list[1] = [4]
    adj_list[4] = [1]
    cycles = dfs_detection(adj_list)
    assert cycles == [1, 4, 1] or cycles == [4, 1, 4]


def test_no_cycle_nontree():
    adj_list = dict()
    adj_list[0] = [1, 2]
    adj_list[1] = [2]
    cycles = dfs_detection(adj_list)
    assert cycles is None
