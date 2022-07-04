class InOu:
    def __init__(self):
        self.input = []
        self.output = []

    def read_io(self):
        self.input.append(input())
        return self.input[-1]

    def print_io(self, value):
        self.output.append(value)
        print("OUTPUT:", self.output[-1])
