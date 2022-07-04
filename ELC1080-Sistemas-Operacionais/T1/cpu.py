class CPU:
    def __init__(self):
        self.memory = None
        self.error = None
        self.internal_state = None
        self.io = None

    # funcao para alterar a memoria da cpu
    def change_memory(self, memory):
        self.memory = memory

    # funcao para alterar os erros base da cpu
    def change_error(self, error):
        self.error = error

    # funcao para alterar o estado interno da cpu
    def change_internal_state(self, internal_state):
        self.internal_state = internal_state

    def change_IO(self, io):
        self.io = io

    # funcao para printar o estado interno da cpu
    def print_internal_state(self):
        s = "CPU INTERNAL STATE - PC: " + str(self.internal_state.PC) + " - Register A: " + str(
            self.internal_state.A) + " - Register X: " + str(self.internal_state.X) + " - CPU Mode: " + str(self.internal_state.mode)
        print(s)
        return s

    def execute_instruction(self, code):
        # print("Executando instrucao codigo", code, "e", arguments, "argumentos")

        # 1 - PARA - 0Arg - modo=cpu_parada
        if(code == 1):
            self.internal_state.change_cpu_mode("PARADA")

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
                self.internal_state.PC=self.memory.read(
                    self.internal_state.PC + 1, self.error)
                self.internal_state.PC=self.internal_state.PC - 2

        # 17 - DESVZ - 1Arg - se A for 0, PC = A1
        if(code == 17):
            if(self.internal_state.A == 0):
                self.internal_state.PC=self.memory.read(
                    self.internal_state.PC + 1, self.error)
                self.internal_state.PC=self.internal_state.PC - 2

        # 18 - DESVNZ - 1Arg - se A não for 0, PC = A1
        if(code == 18):
            if(self.internal_state.A != 0):
                self.internal_state.PC=self.memory.read(
                    self.internal_state.PC + 1, self.error)
                self.internal_state.PC=self.internal_state.PC - 2

        # 19 - LE - 1Arg - A = es[A1]
        if(code == 19):
            if(self.memory.info[self.internal_state.PC + 1] == 0):
                input=self.io.read_io()
                try:
                    self.internal_state.A=int(input)
                except:
                    self.error.update(3)
                    self.internal_state.mode="PARADA"
                    self.internal_state.mode_info="RECEIVED INPUT " + \
                        str(input)
            else:
                self.error.update(2)
                self.internal_state.mode="PARADA"
                self.internal_state.mode_info="RECEIVED DEVICE: " + \
                    str(self.memory.info[self.internal_state.PC + 1])

        # 20 - ESCR - 1Arg - es[A1] = A
        if(code == 20):
            if(self.memory.info[self.internal_state.PC + 1] == 1):
                self.io.print_io(self.internal_state.A)
            else:
                self.error.update(1)
                self.internal_state.mode="PARADA"
                self.internal_state.mode_info="RECEIVED DEVICE: " + \
                    str(self.memory.info[self.internal_state.PC + 1])

    # funcao para, dado o estado atual do PC, ler no endereço de memoria correspondente a instruçãoo atual, reconhecer e chamar sua execução
    def read_instruction(self, base_instructions):
        current_instruction_code=self.memory.read(
            self.internal_state.PC, self.error)

        for instruction in base_instructions:
            if(instruction.code == current_instruction_code):
                self.execute_instruction(instruction.code)
                self.internal_state.PC=self.internal_state.PC + 1 + instruction.arguments
                return

        self.error.update(4)
        self.internal_state.mode="PARADA"
        self.internal_state.mode_info="RECEIVED INSTRUCTION: " + \
            str(current_instruction_code)
