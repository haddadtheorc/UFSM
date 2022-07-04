class Memory:
    def __init__(self, value):
        self.info = ["EMPTY"]*value

    def destroy(self):
        self.info.clear()
        print("Memoria destruída com tamanho:", len(self.info))

    def size(self):
        return len(self.info)

    def read(self, address, error):
        try:
            return self.info[address]
        except:
            error.update(0)

    def write(self, address, value, error):
        try:
            self.info[address] = value
        except:
            error.update(0)
