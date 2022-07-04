class Clock:
    def __init__(self):
        self.count = 0
        print("Clock iniciado com sucesso")

    def reset(self):
        self.count = 0

    def increase(self):
        self.count += 1

    def info(self):
        return self.count
