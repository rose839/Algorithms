def get_next(pattern):
    """
    generate next function
    :param pattern:
    :return:
    """
    m = len(pattern)
    next = [-1] * m

    for i in range(1, m):
        j = next[i-1]
        while j != -1 and pattern[j+1] != pattern[i]:
            j = next[j]
        if pattern[j+1] == pattern[i]:
            j += 1
        next[i] = j
    return next

def kmp(main, pattern):
    """

    :param main:
    :param pattern:
    :return:
    """
    assert type(main) is str and type(pattern) is str

    n, m = len(main), len(pattern)

    if m == 0:
        return 0
    if n <= m:
        return 0 if main == pattern else -1

    next = get_next(pattern)

    j = 0
    for i in range(n):
        while j > 0 and main[i] != pattern[j]:
            j = next[j-1]+1
        if main[i] == pattern[j]:
            if j == m - 1:
                return i-m+1
            else:
                j += 1
    return -1

if __name__ == "__main__":
    m_str = "hello world"
    p_str = "world"

    print("[kmp] result: ", kmp(m_str, p_str))