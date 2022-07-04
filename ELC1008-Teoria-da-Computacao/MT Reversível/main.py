class Rtm:
    def __init__(self, estados, simbolos_entrada, simbolos_fita, transicoes):
        self.estados = estados
        self.simbolos_entrada = simbolos_entrada
        self.simbolos_fita = simbolos_fita
        self.transicoes = transicoes

class State:
    def __init__(self, id):
        self.id = id

class Transitions:
    def __init__(self, estado_atual, leitura_atual, proximo_estado, escrita_atual, movimento_cabeca):
        self.estado_atual = estado_atual
        self.leitura_atual = leitura_atual
        self.proximo_estado = proximo_estado
        self.escrita_atual = escrita_atual
        self.movimento_cabeca = movimento_cabeca


entrada = open("entrada-quintupla.txt", "r")
entrada = entrada.readlines()

rtm_num_estados, rtm_input_symbols, rtm_stripe_symbols, rtm_transitions = entrada[0].split()
rtm = Rtm(rtm_num_estados, rtm_input_symbols, rtm_stripe_symbols, rtm_transitions)


#Preenchendo um vetor de estados com todos os estados que a máquina vai precisar
states = []
aux = entrada[1].split()
for x in range(int(rtm.estados)):
    state = State(aux[x])
    states.append(state)


alphabet_input_symbols = entrada[2].split()
alphabet_stripe_symbols = entrada[3].split()


#Preenchendo um vetor com variáveis do tipo Transition contendo as informações para realizar uma transição
transitions = []
for x in range(int(rtm.transicoes)):
    a = entrada[x+4].split()
    transition = Transitions(a[0][1], a[0][3], a[0][7], a[0][9], a[0][11])
    transitions.append(transition)


entrada = entrada[-1]
marcador_cabeça = 0
marcador_estado = 1
fita_in = entrada + "B"
fita_in = list(fita_in)
fita_hist = []

#Aqui a máquina vai rodando até o estado atual ser o último estado(final), percorrendo o vetor de transições até achar a transição correta e faz as modificações
while (marcador_estado != (int(rtm.estados))):
    index = 0
    for transition in transitions:
        if(marcador_estado == int(transition.estado_atual)):
            if(fita_in[marcador_cabeça] == transition.leitura_atual):
                marcador_estado = int(transition.proximo_estado)
                fita_in[marcador_cabeça] = transition.escrita_atual
                if(transition.movimento_cabeca == "R"):
                    marcador_cabeça+=1
                else:
                    marcador_cabeça-=1

                fita_hist.append(index)

        index +=1

fita_out = fita_in.copy()

print("Fita de Output:",fita_out)
print("Fita de Historico:",fita_hist)

#Aqui vai rebobinando o histórico e dando pop na fita, preenchendo a fita de input conforme vai revertendo os passos
while fita_hist:
    id = fita_hist[-1]
    if(transitions[id].movimento_cabeca=="R"):
        marcador_cabeça-=1
    else:
        marcador_cabeça+=1
    fita_hist.pop()
    fita_in[marcador_cabeça] = transitions[id].leitura_atual

print("Fita de Input:", fita_in)