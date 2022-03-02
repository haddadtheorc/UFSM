class UC:
    def __init__(self):
        self.so = None

    def initialize(self, so):
        self.so = so
        
    # funcao para alterar o so de uma unidade de controle
    def change_so(self, so):
        self.so = so

    # laço principal
    def execute(self, base_instructions):
        f = open("T2/results.txt", "a")
        f.truncate(0)
        while(self.so.cpu.error.code == -1 and self.so.cpu.internal_state.mode == "NORMAL"):
            state = self.so.cpu.print_internal_state()
            f.write(state + " \n")
            self.so.cpu.read_instruction(base_instructions)
            self.so.clock.increase()

        
        if(self.so.cpu.error.code != -1):
            print(self.so.cpu.internal_state.mode_info)
            f.write("\n" + str(self.so.cpu.error.list[self.so.cpu.error.code]) +
                "\n" "Error info: " + str(self.so.cpu.internal_state.mode_info) + "\n")

        f.write("\n" + "Input: " + str(self.so.cpu.io.input) +
            "\n" + "Output: " + str(self.so.cpu.io.output) + "\n")
        f.close()

        return

