from Trie import Node, Trie
from queue import Queue

class ACNode(Node):
    def __init__(self, c: str):
        super(ACNode, self).__init__(c)
        self.fail = None
        self.length = 0

    def insert_child(self, c: str):
        self._insert_child(ACNode(c))

class ACTrie(Trie):
    def __init__(self):
        self.root = ACNode(None)

def build_failure_pointer(ac_trie: ACTrie) -> None:
    root = ac_trie.root

    node_queue = Queue()
    node_queue.put((root, root.length))
    root.fail = None

    while not node_queue.empty():
        p, length = node_queue.get()
        for pc in p.children:
            pc.length = length+1
            if p == root:
                pc.fail = root
            else:
                q = p.fail
                while q != root and not q.has_child(pc.data):
                    q = q.fail

                if q.has_child(pc.data):
                    pc.fail = q.get_child(pc.data)
                else:
                    pc.fail = root
            node_queue.put((pc, pc.length))

def ac(main: str, ac_trie: ACTrie) -> list:
    root = ac_trie.root
    build_failure_pointer(ac_trie)

    ret = []
    p = root
    for i, c in enumerate(main):
        while p != root and not p.has_child(c):
            p = p.fail
        if p.has_child(c):
            q = p.get_child(c)
            while q != root:
                if q.is_ending_char:
                    ret.append((i-q.length+1, i))
                q = q.fail
            p = p.get_child(c)

    return ret

if __name__ == "__main__":
    ac_trie = ACTrie()
    ac_trie.gen_tree(['fuck', 'shit', 'hello', 'world'])

    m_str = 'what is that shit'

    filter_range_list = ac(m_str, ac_trie)
    print('AC result: {}'.format(filter_range_list))
