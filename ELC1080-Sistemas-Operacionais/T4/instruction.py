class Instruction:
    def __init__(self, info):
        self.code = int(info[0])
        self.name = info[1]
        self.arguments = int(info[2])
