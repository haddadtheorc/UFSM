from internal_state import Internal_State
from memory import Memory
from error import Error
from inou import InOu as IO


class CPU:
    def __init__(self):
        self.memory = None
        self.error = None
        self.internal_state = None
        self.io = None
        self.clock = None
        self.base_instructions = None
        self.current_page = -1
        self.new_memory = None

    # inicia a cpu com tudo que ela precisa
    def initialize(self, base_instructions):
        self.memory = Memory(20)
        self.error = Error()
        self.internal_state = Internal_State()
        self.io = IO()
        self.base_instructions = base_instructions
        self.max_mem_pages = 2
        self.remaining_mem_pages = 2
        self.new_memory = [0]*self.max_mem_pages
        print(self.new_memory)


    # altera a memoria atual de uma cpu
    def change_memory(self, memory):
        self.memory = memory

    # altera os erros base de uma cpu
    def change_error(self, error):
        self.error = error

    # altera o estado interno da cpu
    def change_internal_state(self, internal_state):
        self.internal_state = internal_state

    def change_IO(self, io):
        self.io = io

    # nova task na cpu (nova memoria, estado interno, io)
    def change_task(self, task):
        self.memory = task.memory
        self.new_memory[task.memory_page] = task.new_memory
        self.internal_state = task.cpu_state
        self.io = task.io

    def print_internal_state(self, clock):
        s = "PC: " + str(self.internal_state.PC) + " - Register A: " + str(
            self.internal_state.A) + " - Register X: " + str(self.internal_state.X) + " - CPU Mode: " + str(self.internal_state.mode) + " - Clock: " + str(clock.count)
        print(s)
        return s
 

    def read_instruction(self, base_instructions):
        current_instruction_code = self.memory.read(
            self.internal_state.PC, self.error)

        print(f"\n--- RUNNING INSTRUCTION {current_instruction_code} ---")

        for instruction in base_instructions:

            if(instruction.code == current_instruction_code):
                # se for uma instrucao de ES, altera o modo de CPU e dá ao mode_info a instrucao que causou a alteracao
                if(instruction.code == 19 or instruction.code == 20 or instruction.code == 21):
                    self.internal_state.mode = "PRIVILEGIADA"
                    self.internal_state.mode_info = instruction.code
                    return

                # se instrucao de parada
                if(instruction.code == 1):
                    self.internal_state.mode = "PARADA"
                    return

                self.execute_instruction(instruction.code)
                self.internal_state.PC = self.internal_state.PC + 1 + instruction.arguments
                return

        self.error.update(4)
        self.internal_state.mode = "PARADA"
        self.internal_state.mode_info = "RECEIVED INSTRUCTION: " + \
            str(current_instruction_code)

    def execute_instruction(self, code):

        # 2 - CARGI - 1Arg - A = A1
        if(code == 2):
            self.internal_state.A = self.memory.info[self.internal_state.PC + 1]

        # 3 - CARGM - 1Arg - A = mem[A1]
        if(code == 3):
            self.internal_state.A = self.memory.read(
                self.memory.info[self.internal_state.PC + 1], self.error)

        # 4 - CARGX - 1 - A = mem[A1+X]
        if(code == 4):
            self.internal_state.A = self.memory.read(
                self.memory.info[self.internal_state.PC + 1 + self.internal_state.X], self.error)

        # 5 - ARMM - 1Arg - mem[A1] = A
        if(code == 5):
            self.memory.write(
                self.memory.info[self.internal_state.PC + 1], self.internal_state.A, self.error)

        # 6 - ARMX - 1Arg - mem[A1+X] = A
        if(code == 6):
            self.memory.write(
                self.memory.info[self.internal_state.PC + 1 + self.internal_state.X], self.internal_state.A, self.error)

        # 7 - MVAX - 0Arg - X = A
        if(code == 7):
            self.internal_state.X = self.internal_state.A

        # 8 - MVXA - 0Arg - A = X
        if(code == 8):
            self.internal_state.A = self.internal_state.X

        # 9 - INCX - 0 - 0Arg - X++
        if(code == 9):
            self.internal_state.X = self.internal_state.X + 1

        # 10 - SOMA - 1Arg - A+=mem[A1]
        if(code == 10):
            self.internal_state.A = self.internal_state.A + \
                self.memory.read(
                    self.memory.info[self.internal_state.PC + 1], self.error)

        # 11 - SUB - 1Arg - A-=mem[A1]
        if(code == 11):
            self.internal_state.A = self.internal_state.A - \
                self.memory.read(
                    self.memory.info[self.internal_state.PC + 1], self.error)

        # 12 - MULT - 1Arg - A*=mem[A1]
        if(code == 12):
            self.internal_state.A = self.internal_state.A * \
                self.memory.read(
                    self.memory.info[self.internal_state.PC + 1], self.error)

        # 13 - DIV - 1Arg - A/=mem[A1]
        if(code == 13):
            self.internal_state.A = self.internal_state.A / \
                self.memory.read(
                    self.memory.info[self.internal_state.PC + 1], self.error)

        # 14 - RESTO - 1Arg - A%=mem[A1]
        if(code == 14):
            self.internal_state.A = self.internal_state.A % self.memory.read(
                self.memory.info[self.internal_state.PC + 1], self.error)

        # 15 - NEG - 0Arg - A = -A
        if(code == 15):
            self.internal_state.A = -1*(self.internal_state.A)

        # 16 - DESV - 0Arg - PC = A1
        if(code == 16):
            self.internal_state.PC = self.memory.read(
                self.internal_state.PC + 1, self.error)
            self.internal_state.PC = self.internal_state.PC - 2

        # 17 - DESVZ - 1Arg - se A for 0, PC = A1
        if(code == 17):
            if(self.internal_state.A == 0):
                self.internal_state.PC = self.memory.read(
                    self.internal_state.PC + 1, self.error)
                self.internal_state.PC = self.internal_state.PC - 2

        # 18 - DESVNZ - 1Arg - se A não for 0, PC = A1
        if(code == 18):
            if(self.internal_state.A != 0):
                self.internal_state.PC = self.memory.read(
                    self.internal_state.PC + 1, self.error)
                self.internal_state.PC = self.internal_state.PC - 2

    def cpu_execute(self, clock):
        self.print_internal_state(clock)
        self.read_instruction(self.base_instructions)