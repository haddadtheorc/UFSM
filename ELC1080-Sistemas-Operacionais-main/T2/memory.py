class Memory:
    def __init__(self, value):
        self.info = ["EMPTY"]*value
        #print("Memoria iniciada com tamanho", len(self.info))

    # funcao auxiliar para destruir a memoria
    def destroy(self):
        self.info.clear()
        print("Memoria destruída com tamanho:", len(self.info))

    # funcao para obter o tamanho da memoria
    def size(self):
        return len(self.info)

    # funcao para obter o valor contido num endereco de memoria (erro em caso de nao encontrar o endereco)
    def read(self, address, error):
        try:
            #print("Na posicao", address, "valor", self.info[address])
            return self.info[address]
        except:
            error.update(0)

    # funcao para alterar o valor contido num endereco de memoria (erro em caso de nao encontrar o endereco)
    def write(self, address, value, error):
        try:
            self.info[address] = value
        except:
            error.update(0)
