class Task:
    def __init__(self):
        self.id = None
        self.progr = None
        self.memory = None
        self.cpu_state = None
        self.task_state = "PRONTO"
        self.io = None

    def initialize(self, id, progr, memory, cpu_state, io):
        self.id = id
        self.progr = progr
        self.memory = memory
        self.cpu_state = cpu_state
        self.io = io
