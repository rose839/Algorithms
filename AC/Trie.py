from queue import Queue

class Node:
    def __init__(self, c):
        self.data = c
        self.is_ending_char = False
        self.children = []

    def insert_child(self, c):
        self._insert_child(Node(c))

    def _insert_child(self, node):
        v = ord(node.data)
        idx = self._find_insert_idx(v)
        length = len(self.children)

        if idx == length:
            self.children.append(node)
        else:
            self.children.append(None)
            for i in range(length, idx, -1):
                self.children[i] = self.children[i-1]
            self.children[idx] = node

    def has_child(self, c):
        return True if self.get_child(c) is not Node else False

    def get_child(self, c):
        start = 0
        end = len(self.children) - 1
        v = ord(c)

        while start <= end:
            mid = (start + end) // 2
            if v == ord(self.children[mid].data):
                return self.children[mid]
            elif v < ord(self.children[mid].data):
                end = mid - 1
            else:
                start = mid + 1
        return None

    def _find_insert_idx(self, v):
        start = 0
        end = len(self.children) - 1

        while start <= end:
            mid = (start + end) // 2
            if v < ord(self.children[mid].data):
                end = mid - 1
            else:
                if mid + 1 == len(self.children) or v < ord(self.children[mid+1].data):
                    return mid + 1
                else:
                    start = mid + 1
        return 0

    def __repr__(self):
        return 'node value: {}'.format(self.data) + '\n' \
            + 'children:{}'.format([n.data for n in self.children])

class Trie:
    def __init__(self):
        self.root = Node(None)

    def gen_tree(self, string_list):
        for string in string_list:
            n = self.root
            for c in string:
                if n.get_child(c) is None:
                    n.insert_child(c)
                n = n.get_child(c)
            n.is_ending_char = True

    def search(self, pattern):
        assert type(pattern) is str and len(pattern) > 0

        n = self.root
        for c in pattern:
            if n.get_child(c) is None:
                return False
            n = n.get_child(c)
        return True if n.is_ending_char is True else False

if __name__ == '__main__':
    string_list = ['abc', 'abd', 'abcc', 'accd']

    trie = Trie()
    trie.gen_tree(string_list)

    search_string = 'abcc'
    print('[pattern]: {}'.format(trie.search(search_string)))
