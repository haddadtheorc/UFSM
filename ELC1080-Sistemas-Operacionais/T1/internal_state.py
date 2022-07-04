class Internal_State:
    def __init__(self):
        self.PC = 0
        self.A = 0
        self.X = 0
        self.mode = "NORMAL"
        self.mode_info = "NONE"
        #print("Estado interno da CPU iniciado")

    def change_cpu_mode(self, mode):
        self.mode = mode
