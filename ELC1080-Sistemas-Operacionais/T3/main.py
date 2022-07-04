from instruction import Instruction
from so import SO
from uc import UC


def instructions_load(instructions):
    instructions.append(Instruction([0, "NOP", 0]))
    instructions.append(Instruction([1, "PARA", 0]))
    instructions.append(Instruction([2, "CARGI", 1]))
    instructions.append(Instruction([3, "CARGM", 1]))
    instructions.append(Instruction([4, "CARGX", 1]))
    instructions.append(Instruction([5, "ARMM", 1]))
    instructions.append(Instruction([6, "ARMX", 1]))
    instructions.append(Instruction([7, "MVAX", 0]))
    instructions.append(Instruction([8, "MVXA", 0]))
    instructions.append(Instruction([9, "INCX", 0]))
    instructions.append(Instruction([10, "SOMA", 1]))
    instructions.append(Instruction([11, "SUB", 1]))
    instructions.append(Instruction([12, "MULT", 1]))
    instructions.append(Instruction([13, "DIV", 1]))
    instructions.append(Instruction([14, "RESTO", 1]))
    instructions.append(Instruction([15, "NEG", 0]))
    instructions.append(Instruction([16, "DESV", 1]))
    instructions.append(Instruction([17, "DESVZ", 1]))
    instructions.append(Instruction([18, "DESVNZ", 1]))
    instructions.append(Instruction([19, "LE", 1]))
    instructions.append(Instruction([20, "ESCR", 1]))


def main():

    base_instructions = []
    instructions_load(base_instructions)

    progr = [2, 0, 7, 2, 10, 5, 17, 8, 20, 1, 9, 8, 11, 17, 18, 7, 1, 0]
    progr2 = [2, 0, 7, 2, 7, 5, 17, 8, 20, 1, 9, 8, 11, 17, 18, 7, 1, 0]
    progr3 = [2, 0, 7, 2, 12, 5, 17, 8, 20, 1, 9, 8, 11, 17, 18, 7, 1, 0]

    tasks = [progr, progr2, progr3]

    so = SO()
    so.initialize(progr, tasks)

    uc = UC()
    uc.initialize(so, base_instructions)
    uc.execute()


if __name__ == "__main__":
    main()
