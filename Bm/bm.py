SIZE = 256

def generate_bc(pattern, m, bc):
    """
    generate bad character set
    :param pattern:
    :param m:
    :param bc:
    :return:
    """
    for i in range(m):
        bc[ord(pattern[i])] = i

def generate_gs(pattern, m, suffix, prefix):
    """
    generate good suffix set
    :param pattern:
    :param m:
    :param suffix:
    :param prefix:
    :return:
    """
    for i in range(m-1): # suffix must be greater than length 2
        k = 0
        for j in range(i, -1, -1):
            if pattern[j] == pattern[m-1-k]:
                k += 1
                suffix[k] = j
                if j == 0:
                    prefix[k] = True
            else:
                break

def move_by_gs(j, m, suffix, prefix):
    """
    caculate distance by good set
    :param j: length of good set
    :param m: length of pattern
    :param suffix:
    :param prefix:
    :return:
    """
    k = m - 1 - j
    if suffix[k] != -1:
        return j - suffix[k] + 1
    else:
        for r in range(j+2, m):
            if prefix[m-r]:
                return r
        return m

def bm(main, pattern):
    """
    BM algorithm
    :param main:
    :param pattern:
    :return:
    """
    assert type(main) is str and type(pattern) is str
    n, m = len(main), len(pattern)

    if n <= m:
        return 0 if main == pattern else -1

    bc = [-1] * SIZE
    generate_bc(pattern, m, bc)

    suffix = [-1] * m
    prefix = [False] * m
    generate_gs(pattern, m, suffix, prefix)

    i = 0
    while i < n-m+1:
        j = m - 1
        while j >= 0:
            if main[i+j] != pattern[j]:
                break
            else:
                j -= 1

        # match
        if j == -1:
            return i

        #1.bad character
        x = j - bc[ord(main[i+j])]

        #2.good suffix
        y = 0
        if j != m - 1:
            y = move_by_gs(j, m, suffix, prefix)

        i += max(x, y)

    return -1

if __name__ == "__main__":
    m_str = "hello world"
    p_str = "world"

    print('[bm] result: ', bm(m_str, p_str))