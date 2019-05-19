from Vector import vector


class State:
    nextStates = []

    def __init__(self, value):
        self.value = value

    def getState(self):
        return self.value
