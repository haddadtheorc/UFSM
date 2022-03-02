import random
class Clock:
    def __init__(self):
        self.count = 0
        self.alarms = [0]*3
        self.initialize_alarms()
        print(f"Alarms - {self.alarms}")

    def initialize_alarms(self):
        for i in range(0, 3):
            self.alarms[i] = random.randint(2, 10)


    def reset(self):
        self.count = 0

    def increase(self):
        self.count += 1

    def info(self):
        return self.count
