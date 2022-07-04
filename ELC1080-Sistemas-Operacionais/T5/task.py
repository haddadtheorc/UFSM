class Task:
    def __init__(self):
        self.id = None
        self.progr = None
        self.memory = None
        self.new_memory = None
        self.cpu_state = None
        self.task_state = "READY"
        self.io = None
        self.turnaround_time = 0
        self.execution_time = []
        self.stopped_time = []
        self.readied_time = []
        self.aux_time = 0
        self.memory_page = 0

    def initialize(self, id, progr, memory, cpu_state, io, memory_page):
        self.id = id
        self.progr = progr
        self.memory = memory
        self.new_memory = memory
        self.cpu_state = cpu_state
        self.io = io
        self.memory_page = memory_page
