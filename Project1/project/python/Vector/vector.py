class Item:
    next = None
    prev = None

    def __init__(self, value):
        self.value = value

    def __getitem__(self, item):
        if item is 0:
            return self.value
        elif item > 0:
            return self.next[(item - 1)]
        else:
            return self.prev[item + 1]

    def __iter__(self):
        return self

    def __next__(self):
        if self.next is not None:
            return self.next
        else:
            raise StopIteration

    def __str__(self):
        return self.value

    def add(self, other):
        other.prev = self
        self.next = other

    def addat(self, other, key):
        if key is 0:
            self.prev = other
            other.next = self
        else:
            curr = self
            while key - 1 is not 0:
                curr = curr.next
                key -= 1

            other.next = curr.next
            other.prev = curr
            other.next.prev = other
            curr.next = other
        return other

    def __add__(self, other):
        curr = self
        while curr.next is not None:
            curr = curr.next

        other.prev = curr
        curr.next = other
        other.prev = curr
        curr.next = other

        return other

    def test(self, key):
        curr = self
        if key > 0:
            while key > 0:
                print(f'{key} - {curr}')
                curr = curr.next
                if curr is None:
                    key = 0
                else:
                    key -= 1
        else:
            while key < 0:
                print(f'{-key} - {curr}')
                curr = curr.prev
                if curr is None:
                    key = 0
                else:
                    key += 1

    def remove(self, key):
        curr = self
        if key is 0:
            curr = curr.next
            curr.prev = None
            aux = curr.next
            aux.prev = curr
            curr.next = aux
            return curr
        elif key is -1:
            curr = curr.prev
            curr.next = None
            return curr
        else:
            while key is not 1:
                curr = curr.next
                key -= 1
            curr.next = curr.next.next
            curr.next.prev = curr

            return curr.next

    def __eq__(self, other):
        self.value == other.value


class Vector:
    size = 0
    first = None
    last = None

    def __init__(self):
        self.size = 0
        self.first = None
        self.last = None

    def __len__(self):
        return self.size

    def __iter__(self):
        self.n = 0
        #yield self.size
        return self

    def __next__(self):
        if (self.n + 1) <= self.size:
            self.n += 1
            return self.first[self.n - 1]
        else:
            raise StopIteration

    def add(self, item):
        self.size += 1
        obj = Item(item)
        obj.prev = None
        obj.next = None
        if self.first is None:
            self.first = obj
        if self.last is None:
            self.last = obj
        else:
            obj = self.first + obj
            self.last = obj

    def __add__(self, other):
        if isinstance(other, Vector):
            self.size += other.size
            self.last.next = other.first
            self.last = other.last
        else:
            self.add(other)

    def __getitem__(self, item):
        if item >= self.size or item < 0:
            return None
        if item < self.size/2:
            return self.first[item]
        else:
            return self.last[(item - self.size) + 1]

    def addat(self, item, key):
        if key <= 0:
            aux = Item(item)
            aux.prev = None
            aux.next = None
            self.size += 1
            aux = self.first.addat(aux, 0)
            self.first = aux
        elif key >= self.size:
            self.add(item)
        else:
            aux = Item(item)
            aux.prev = None
            aux.next = None
            self.size += 1
            self.first.addat(aux, key)

    def test(self):
        print(f'Printing from beginning:')
        self.first.test(self.size)
        print(f'\nPrinting from ending:')
        self.last.test(-self.size)

    def remove(self, key):
        if key is 0:
            if self.size is 1:
                self.first = None
                self.last = None
            else:
                aux = self.first.remove(0)
                if self.size is 2:
                    self.first = aux
                    self.last = aux
                else:
                    self.first = aux
        elif key is self.size - 1:
            self.last = self.last.remove(-1)
        elif key is self.size - 2:
            self.last = self.first.remove(key)
        else:
            self.first.remove(key)
        self.size -= 1
