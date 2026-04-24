from euler_tour import EulerTour


def test_euler():
    adj_list = {0: [1, 2, 3], 1: [4, 5]}
    et: EulerTour = EulerTour(adj_list)

    assert et.start_timer == {0: 1, 1: 2, 4: 3, 5: 4, 2: 5, 3: 6}
