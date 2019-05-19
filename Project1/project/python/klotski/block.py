class Block:
    bid = -1
    x = -1
    y = -1
    height = 0
    width = 0

    def __init__(self, bid, x, y):
        if bid is 0:
            self.bid = 0
            self.x = 0
            self.y = 1
            self.width = 2
            self.height = 2

        else:
            self.bid = bid
            if 0 <= x < 5:
                self.x = x
            else:
                print(f'Wrong X value in block {bid}')
                return
            if 0 <= y < 4:
                self.y = y
            else:
                print(f'Wrong Y value in block {bid}')
                return
            self.height = 1
            self.width = 1

    def makeHorizontal(self):
        self.width = 2
        self.height = 1

    def makeVertical(self):
        self.height = 2
        self.width = 1

    def makeSquare(self):
        self.width = 1
        self.height = 1

    def moveUp(self):
        if self.y > 0:
            self.y -= 1
            return 1
        else:
            return 0

    def getX(self):
        return self.x

    def getY(self):
        return self.y

    def getWidth(self):
        return self.width

    def getHeight(self):
        return self.height

    def getCoords(self):
        coords = [self.x, self.y]
        return coords

    def moveUp(self):
        self.x -= 1

    def moveDown(self):
        self.x += 1

    def moveLeft(self):
        self.y -= 1

    def moveRight(self):
        self.y += 1

    def getBid(self):
        return self.bid

    def copy(self):
        newone = Block(int(self.bid), int(self.x), int(self.y))
        newone.height = int(self.height)
        newone.width = int(self.width)
        return newone
