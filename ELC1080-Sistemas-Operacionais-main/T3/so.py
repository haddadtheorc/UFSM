from os import get_inheritable
from internal_state import Internal_State
from memory import Memory
from inou import InOu as IO
from task import Task


class SO:
    def __init__(self):
        self.cpu = None
        self.progr = None
        self.tasks = []*10
        self.current_task_id = 0

    def initialize_tasks(self, tasks):
        i = 0
        for task in tasks:
            current_task = Task()
            current_task.initialize(
                i, task, Memory(50), Internal_State(), IO())
            self.tasks.append(current_task)
            i += 1

    def initialize(self, progr, tasks):
        self.initialize_tasks(tasks)
        self.progr = progr

    def change_cpu(self, cpu):
        self.cpu = cpu

    def change_clock(self, clock):
        self.clock = clock

    def change_progr(self, progr):
        self.progr = progr

    def change_current_task(self, id):
        self.current_task_id = id

    def get_current_task(self):
        for task in self.tasks:
            if(task.id == self.current_task_id):
                return task

    def handle_mode(self, cpu):
        # se entrou em privilegiada, trata o IO
        if(cpu.internal_state.mode == "PRIVILEGIADA"):
            print(f"\nTask {self.current_task_id} parando\n")
            self.handle_io(cpu)

            # se ainda tem coisa pra rodar, segue
            if(self.check_tasks() == False):
                print(f"\nTask {self.current_task_id} iniciando\n")

            return cpu

        # se uma task parou, mata
        if(cpu.internal_state.mode == "PARADA"):
            print(f"\nTask {self.current_task_id} finalizando\n")
            self.kill_task(cpu)
            # se task remanescente, segue
            if(self.check_tasks() == False):
                print(f"\nTask {self.current_task_id} iniciando \n")
                return cpu
            # se tudo pronto, ou erro, encerra
            if(self.check_tasks() or cpu.error.code != -1):
                if(cpu.error.code != -1):
                    print(
                        f"\n {cpu.error.list[cpu.error.code]} \n Error info {cpu.internal_state.mode_info} \n")

                for task in self.tasks:
                    print(f"Task {task.id} Input: {task.io.input}")
                    print(f"Task {task.id} Output: {task.io.output}")
                return cpu

    # coloca na cpu argumento o estado interno e memória da task argumento
    def change_cpu_state(self, task, cpu):
        cpu.change_internal_state(task.cpu_state)
        cpu.change_memory(task.memory)
        return cpu

    # para temporariamente a task atual, atualiza e returna a cpu argumento com a task seguinte
    def stop_current_task(self, cpu):
        for task in self.tasks:
            if task.id == self.current_task_id:
                task.cpu_state = cpu.internal_state
                task.memory = cpu.memory
                task.task_state = "PARADA"

        for task in self.tasks:
            if(task.task_state != "MORTO" and task.id != self.current_task_id):
                self.current_task_id = task.id
                cpu.internal_state = task.cpu_state
                cpu.memory = task.memory
                return cpu

        for task in self.tasks:
            if(task.task_state != "MORTO" and task.task_state != "PARADA"):
                self.current_task_id = task.id
                cpu.internal_state = task.cpu_state
                cpu.memory = task.memory
                return cpu

    # finaliza a task atual e adiciona a seguinte na cpu argumento, retornando-a 
    def kill_task(self, cpu):
        # procura a task na lista de tasks e altera o estado para morto
        self.tasks[self.current_task_id].task_state = "MORTO"

        # procura pela primeira task não morta para executar
        for task in self.tasks:
            if(task.task_state != "MORTO"):
                cpu = self.change_cpu_state(task, cpu)
                self.change_current_task(task.id)
        return cpu

    def check_tasks(self):
        for task in self.tasks:
            if (task.task_state != "MORTO"):
                return False
        return True

    # tratamento do IO usando o mode_info da estado interno da cpu como base
    def handle_io(self, cpu):
        if(cpu.internal_state.mode_info == 19):
            self.handle_io_LE(cpu)

        if(cpu.internal_state.mode_info == 20):
            self.handle_io_ESCR(cpu)

        cpu.internal_state.mode = "NORMAL"
        cpu.internal_state.mode_info = "NONE"
        cpu.internal_state.PC = cpu.internal_state.PC + 1 + 1
        self.stop_current_task(cpu)

    def handle_io_LE(self, cpu):
        if(cpu.memory.info[cpu.internal_state.PC + 1] == 0):
            input = cpu.io.read_io()
            try:
                cpu.internal_state.A = int(input)
            except:
                cpu.error.update(3)
                cpu.internal_state.mode = "PARADA"
                cpu.internal_state.mode_info = "RECEIVED INPUT " + \
                    str(input)
        else:
            cpu.error.update(2)
            cpu.internal_state.mode = "PARADA"
            cpu.internal_state.mode_info = "RECEIVED DEVICE: " + \
                str(cpu.memory.info[cpu.internal_state.PC + 1])

    def handle_io_ESCR(self, cpu):
        if(cpu.memory.info[cpu.internal_state.PC + 1] == 1):
            self.tasks[self.current_task_id].io.print_io(
                cpu.internal_state.A)
            # self.cpu.io.print_io(self.cpu.internal_state.A)
        else:
            cpu.error.update(1)
            cpu.internal_state.mode = "PARADA"
            cpu.internal_state.mode_info = "RECEIVED DEVICE: " + \
                str(cpu.memory.info[cpu.internal_state.PC + 1])
