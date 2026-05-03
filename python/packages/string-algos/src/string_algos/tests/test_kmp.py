from string_algos.kmp import get_prefix_map, kmp_search


def test_get_prefix_map():
    a = get_prefix_map("aaa")
    assert a == [0, 1, 2]
    abcc = get_prefix_map("abccabc")
    assert abcc == [0, 0, 0, 0, 1, 2, 3]
    aab = get_prefix_map("aabaaab")
    assert aab == [0, 1, 0, 1, 2, 2, 3]


def test_kmp():
    abcc_empty_res = kmp_search("", "abccabc")
    assert list(abcc_empty_res) == []
    abcc_res = kmp_search("babccabc", "abccabc")
    assert list(abcc_res) == [1]
    abcc_res_dual = kmp_search("babccabccabc", "abccabc")
    assert list(abcc_res_dual) == [1, 5]
