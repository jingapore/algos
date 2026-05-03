# map returns length of prefix, not index, that matches suffix ending with map[i] (ending is inclusive)
def get_prefix_map(s: str) -> list[int]:
    n = len(s)
    # pi stores the length, not index, of the prefix that matches the suffix and s[i]
    pi: list[int] = [0] * n
    # k is the length of the matching prefix for the suffix that ends with (i-1) within the for loop
    k = 0
    # start at 1 instead of 0 because when i == 0 p[i] = 0
    for i in range(1, n):
        while k > 0 and s[k] != s[i]:
            # (k-1) instead of k because at this point we claim that prefix of length k matches up to suffix ending with (i-1)
            # so now we are at suffix[i] and we realise there's no match, and we want to wind back
            # meaning the prefioux suffix, i.e. suffix[i-1] had a match and we want to "relax" that down, which means we look at
            # pi[k-1] for that suffix
            # one invariant is that s[i] == s[pi[i]-1] (-1 is to handle 0 indexing) for pi[i] > 0
            k = pi[k - 1]
        # as tempting as it is, note that we can't substitute (s[k] == s[i]) with (k != 0) because that fails when we start this iteration of for i in range(1, n) with k == 0
        if s[k] == s[i]:
            # at this point, we know that s[i-1] is matched by a prefix of length pi[i-1] (this might not be the longest) and also if we reach this condition we can just safely increment k += 1
            # if there's a match at s[i], we extend that prefix
            k += 1
        # we do not need to have this within the (if s[k] == s[i]) loop
        # if we don't find a prefix, k == 0 and we assign accordingly. if we find one i.e. its length is >= 1 then we just set it accordingly
        pi[i] = k

    return pi
