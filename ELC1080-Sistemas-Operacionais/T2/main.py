from instruction import Instruction
from so import SO
from uc import UC

def instructions_load(instructions):
    with open('T2/base_instructions.txt') as f:
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

    so = SO()
    so.initialize(progr)
    so.prog_to_mem()
 
    uc = UC()
    uc.initialize(so)
    uc.execute(base_instructions)




if __name__ == "__main__":
    main()
