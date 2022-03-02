class Clock:
    def __init__(self):
        self.count = 0
        print("Clock iniciado com sucesso")

    def destroy(self):
        self.count = 0

    # funcao para aumentar o contador do clock
    def increase(self):
        self.count +=1 

    # funcao para obter o valor do clock
    def info(self):
        return self.count
    
