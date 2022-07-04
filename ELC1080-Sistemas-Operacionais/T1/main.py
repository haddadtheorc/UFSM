from internal_state import Internal_State
from memory import Memory
from error import Error
from inou import InOu as IO
from cpu import CPU
from instruction import Instruction


def instructions_load(instructions):
    with open('T1/base_instructions.txt') as f:
        base_instructions = f.read().split("\n")
    for i in range(len(base_instructions)):
        base_instructions[i] = base_instructions[i].split(" ")
    for base_instruction in base_instructions:
        instructions.append(Instruction(base_instruction))


def main():

    base_instructions = []
    instructions_load(base_instructions)

    # programa para executar na cpu
    progr = [2, 0, 7, 2, 10, 5, 17, 8, 20, 1, 9, 8, 11, 17, 18, 7, 1, 0]

    # variáveis que representam o computador
    memory = Memory(20)
    io = IO()
    cpu = CPU()
    internal_state = Internal_State()
    error = Error()

    # inicializa a CPU com as variáveis criadas
    cpu.change_memory(memory)
    cpu.change_error(error)
    cpu.change_internal_state(internal_state)
    cpu.change_IO(io)

    # copia o programa para a memória
    for i in range(len(progr)):
        cpu.memory.write(i, progr[i], cpu.error)

    # leitura do programa na memória
    # for i in range(cpu.memory.size()):
    #     cpu.memory.read(i, cpu.error)

    # for instruction in base_instructions:
    #     print(type(instruction.code))

    # executa ums instrução por vez até parar
    f = open("T1/results.txt", "a")
    f.truncate(0)
    while(cpu.error.code == -1 and cpu.internal_state.mode == "NORMAL"):
        state = cpu.print_internal_state()
        f.write(state + " \n")
        cpu.read_instruction(base_instructions)

    if(cpu.error.code != -1):
        print(cpu.internal_state.mode_info)
        f.write("\n" + str(cpu.error.list[cpu.error.code]) +
                "\n" "Error info: " + str(cpu.internal_state.mode_info) + "\n")

    f.write("\n" + "Input: " + str(cpu.io.input) +
            "\n" + "Output: " + str(cpu.io.output) + "\n")
    f.close()


if __name__ == "__main__":
    main()
