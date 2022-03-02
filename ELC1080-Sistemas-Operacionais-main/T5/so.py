from internal_state import Internal_State
from memory import Memory
from inou import InOu as IO
from task import Task


class SO:
    def __init__(self):
        self.cpu = None
        self.progr = None
        self.tasks = []*10
        self.base_tasks = []*2
        self.current_task_id = 0
        self.last_task_id = -1
        self.scheduler = "priority"
        #self.scheduler = "round-robin"
        self.quantum = -1
        self.max_mem_pages = 2
        self.remaining_mem_pages =  self.max_mem_pages


    def initialize_tasks(self, progr):

        if(self.remaining_mem_pages == 0):
            self.remaining_mem_pages = self.max_mem_pages

        self.remaining_mem_pages -=1

        current_task = Task()
        current_task.initialize(
                0, progr, Memory(50), Internal_State(), IO(), self.remaining_mem_pages)
        self.tasks.append(current_task)
        print(f"criando task para page {current_task.memory_page}")
        self.tasks[self.current_task_id].task_state = "RUNNING"


    def initialize_base_tasks(self):
        self.base_tasks.append([2, 0, 7, 2, 7, 5, 17, 8, 20, 1, 9, 8, 11, 17, 18, 7, 1, 0])
        self.base_tasks.append([2, 0, 7, 2, 12, 5, 17, 8, 20, 1, 9, 8, 11, 17, 18, 7, 1, 0])

    def initialize(self, progr):
        self.initialize_base_tasks()
        self.initialize_tasks(progr)
        self.progr = progr
        
        if(self.scheduler == "round-robin"):
            print("\n Selecione o quantum do RR")
            self.quantum = int(input())

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

    def time_sum(self, time):
        sum = 0
        for i in time:
            sum = sum + i
        return sum

    def change_cpu_state(self, task, cpu):
        cpu.change_internal_state(task.cpu_state)
        cpu.change_memory(task.memory)
        return cpu


    def check_alarms(self, cpu, clock):
        if (clock.count == 0):
            return

        for alarm in clock.alarms:
            if clock.count % alarm == 0:
                print(f"\n*** ALARM {alarm} IS RINGING ***")
                cpu.internal_state.mode = "ALARME"
                return True
                
                
        
                
    def check_tasks(self):
        for task in self.tasks:
            if (task.task_state != "FINISHED"):
                return False
        return True

    def finish_program(self, cpu, clock):
        print("\n\n\nALL TASKS HAVE ENDED!!!")
        print("BEGINNING TASK REPORTS:")

        if(cpu.error.code != -1):
            print(
                f"\n {cpu.error.list[cpu.error.code]} \n Error info {cpu.internal_state.mode_info} \n")

        for task in self.tasks:
            print(f"\nTASK {task.id}")
            print(f"Task {task.id} - Input: {task.io.input}")
            print(f"Task {task.id} - Output: {task.io.output}")
            print(f"Task {task.id} - Turnaround time: {task.turnaround_time}")
            print(f"Task {task.id} - Execution time: {self.time_sum(task.execution_time)}")
            print(f"Task {task.id} - Readied time: {self.time_sum(task.readied_time)}")
            print(f"Task {task.id} - Stopped time: {self.time_sum(task.stopped_time)}")
        print(f"\nClock at the end of execution: {clock.count}\n")
        exit

    def handle_mode(self, cpu, clock):
        if(cpu.internal_state.mode == "PRIVILEGIADA" or cpu.internal_state.mode == "ALARME"):
            print(f"\n--- STOPPING Task {self.current_task_id} ---")
            if(cpu.internal_state.mode == "PRIVILEGIADA"):
                if(cpu.internal_state).mode_info == 21:
                    self.handle_create(cpu, clock)
                else:
                    self.handle_io(cpu, clock)
            cpu.internal_state.mode = "NORMAL"
            cpu.internal_state.mode_info = "NONE"
            if(cpu.error.code != -1):
                self.handle_current_task(cpu, clock, "FINISH")
            else:
                self.handle_current_task(cpu, clock, "STOP")
            return cpu

        if(cpu.internal_state.mode == "PARADA"):
            print(f"\n--- FINISHING Task {self.current_task_id} ---")
            self.handle_current_task(cpu, clock, "FINISH")
            if(self.check_tasks() == False):
                return cpu

        # se tudo pronto, ou erro, encerra
        if(self.check_tasks() or cpu.error.code != -1):
            self.finish_program(cpu, clock)
            return cpu

    def handle_current_task(self, cpu, clock, action):

        cpu.error.code = -1

        if(action=="STOP"):
            self.stop_current_task(cpu, clock)
        elif(action=="FINISH"):
            self.finish_current_task(clock)


        if(self.last_task_id != -1):
            self.unlock_last_task(clock)
        self.last_task_id = self.current_task_id   

        print("\n--- CURRENT TASKS STATE")
        for task in self.tasks:
                print(f"\t\t-Task {task.id} - State {task.task_state}")

        if(self.check_tasks() == False):
            self.begin_next_task(cpu, clock)
            
        print("\n--- CURRENT TASKS STATE")
        for task in self.tasks:
                print(f"\t\t-Task {task.id} - State {task.task_state}")

        return cpu

    def unlock_last_task(self, clock):
        if(self.tasks[self.last_task_id].task_state != "FINISHED" and self.last_task_id != self.current_task_id):
            self.tasks[self.last_task_id].task_state = "READY"

            self.tasks[self.last_task_id].stopped_time.append((clock.count - self.tasks[self.last_task_id].aux_time))
            self.tasks[self.last_task_id].aux_time = clock.count

    def stop_current_task(self, cpu, clock):
        self.tasks[self.current_task_id].cpu_state = cpu.internal_state
        self.tasks[self.current_task_id].memory = cpu.memory
        self.tasks[self.current_task_id].new_memory = cpu.new_memory[self.tasks[self.current_task_id].memory_page]
        
        self.tasks[self.current_task_id].task_state = "STOPPED"
        self.tasks[self.current_task_id].execution_time.append((clock.count - self.tasks[self.current_task_id].aux_time))

        self.tasks[self.current_task_id].aux_time = clock.count

    def finish_current_task(self, clock):

        self.tasks[self.current_task_id].task_state = "FINISHED"
        self.tasks[self.current_task_id].turnaround_time = clock.count
        self.tasks[self.current_task_id].execution_time.append((clock.count - self.tasks[self.current_task_id].aux_time))
        self.tasks[self.current_task_id].aux_time = clock.count

        count = 0
        for task in self.tasks:
            if task.task_state == "FINISHED":
                count+=1
        print(f"\n- FINISHED TASKS: {count}/{len(self.tasks)} - ")

    def begin_next_task(self, cpu, clock):

        id = self.get_next_task_id()
        self.current_task_id = id
        cpu.current_page = self.tasks[self.current_task_id].memory_page      
        cpu.internal_state = self.tasks[id].cpu_state
        cpu.memory = self.tasks[id].memory
        cpu.new_memory[self.tasks[self.current_task_id].memory_page] = self.tasks[self.current_task_id].new_memory

        if(self.tasks[id].task_state == "STOPPED"):
            self.tasks[id].stopped_time.append((clock.count - self.tasks[id].aux_time))
        else:
            self.tasks[id].readied_time.append((clock.count - self.tasks[id].aux_time))

        self.tasks[id].aux_time = clock.count
        self.tasks[id].task_state = "RUNNING"
        
        print(f"\n--- BEGINNING Task {self.current_task_id} ---")
        return cpu

    def get_next_task_id(self):
        for task in self.tasks:
            if task.task_state != "FINISHED":
                aux = task
                break
    
        if(self.scheduler == "priority"):
            return self.priority_scheduler(aux)

        if(self.scheduler == "round-robin"):
            return self.round_robin_scheduler(aux)

    def round_robin_scheduler(self, aux):

        for i in range (self.current_task_id +1, len(self.tasks)):
            if self.tasks[i].task_state != "FINISHED":
                aux = self.tasks[i]
                return aux.id
        
        for i in range (0, self.current_task_id):
            if self.tasks[i].task_state != "FINISHED":
                aux = self.tasks[i]
                return aux.id

        return aux.id
        
    def priority_scheduler(self, aux):
        for task in self.tasks:
            if (self.time_sum(task.execution_time) < self.time_sum(aux.execution_time) and task.task_state != "FINISHED"):
                aux = task
        return aux.id

    def handle_create(self, cpu, clock):
        base_task_id = cpu.memory.info[cpu.internal_state.PC + 1]
        print(f"\n--- CREATING TASK FOR BASE PROGR {base_task_id} ---")

        try:
            if(self.remaining_mem_pages == 0):
                self.remaining_mem_pages = self.max_mem_pages
            self.remaining_mem_pages -=1
            new_task = Task()
            new_task.initialize(len(self.tasks), self.base_tasks[base_task_id] ,Memory(50), Internal_State(), IO(), self.remaining_mem_pages)
            new_task.task_state = "READY"
            print(f"criando task para page {new_task.memory_page}")
            
            for i in range(len(new_task.progr)):
                    new_task.memory.write(i, new_task.progr[i], cpu.error)
            
            self.tasks.append(new_task)
            cpu.internal_state.PC = cpu.internal_state.PC + 1 + 1
        except:
            cpu.error.update(5)
            cpu.internal_state.mode = "PARADA"
            cpu.internal_state.mode_info = "RECEIVED PROGRAM " + \
                    str(base_task_id)

    def handle_io(self, cpu, clock):

        if(cpu.internal_state.mode_info == 19):
            self.handle_io_LE(cpu)

        if(cpu.internal_state.mode_info == 20):
            self.handle_io_ESCR(cpu)

        cpu.internal_state.PC = cpu.internal_state.PC + 1 + 1

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
