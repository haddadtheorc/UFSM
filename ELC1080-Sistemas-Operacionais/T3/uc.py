from cpu import CPU
from clock import Clock


class UC:
    def __init__(self):
        self.clock = None
        self.so = None
        self.cpu = None
        self.base_instructions = None

    def initialize(self, so, base_instructions):
        self.so = so
        self.clock = Clock()
        self.cpu = CPU()
        self.base_instructions = base_instructions
        self.cpu.initialize(base_instructions)
        self.prog_to_mem()
        self.cpu.change_task(self.so.get_current_task())

    def prog_to_mem(self):
        for task in self.so.tasks:
            for i in range(len(task.progr)):
                task.memory.write(i, task.progr[i], self.cpu.error)

    def change_so(self, so):
        self.so = so

    def change_cpu(self, cpu):
        self.cpu = cpu

    def handle_interruption(self):
        self.cpu = self.so.handle_mode(self.cpu)

    def execute(self):
        print(f"Task {self.so.current_task_id} iniciando \n")

        while(self.cpu.error.code == -1 and self.cpu.internal_state.mode == "NORMAL"):

            self.cpu.cpu_execute()
            self.clock.increase()
            
            if(self.cpu.check_interruption()):
                self.handle_interruption()
                    
                
