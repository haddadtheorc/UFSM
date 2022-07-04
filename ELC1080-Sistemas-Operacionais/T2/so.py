from cpu import CPU
from internal_state import Internal_State
from memory import Memory
from error import Error
from inou import InOu as IO
from clock import Clock

class SO:
    def __init__(self):
        self.cpu = None
        self.clock = None
        self.progr = None

    def initialize(self, progr):
        self.cpu = CPU()
        self.clock = Clock()
        self.progr = progr
        self.cpu.initialize(Memory(20), Error(), Internal_State(), IO())

    # funcao para preencher o programa na memoria
    def prog_to_mem(self):
        for i in range(len(self.progr)):
            self.cpu.memory.write(i, self.progr[i], self.cpu.error) 


    def change_cpu(self, cpu):
        self.cpu = cpu

    def change_cpu(self, clock):
        self.clock = clock

    def change_cpu(self, progr):
        self.progr = progr