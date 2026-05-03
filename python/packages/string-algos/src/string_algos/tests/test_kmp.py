from string_algos.kmp import get_prefix_map


def test_get_prefix_map():
    a = get_prefix_map("aaa")
    assert a == [0, 1, 2]
    abcc = get_prefix_map("abccabc")
    assert abcc == [0, 0, 0, 0, 1, 2, 3]
