class Error:
    def __init__(self):
        self.code = -1
        self.list = ["ERROR 0: INVALID MEMORY ADDRESS",
                     "ERROR 1: WRONG IO DEVICE FOR OUTPUT",
                     "ERROR 2: WRONG IO DEVICE FOR INPUT",
                     "ERROR 3: INVALID INPUT",
                     "ERROR 4: INVALID INSTRUCTION",
                     "ERROR 5: INVALID BASE PROGRAM"]

    def update(self, value):
        self.code = value
        if(self.code > -1):
            print(self.list[self.code])
