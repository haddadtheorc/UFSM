## Trabalho 3 - Multiprogramação - Sistemas Operacionais

Agora o SO tem acesso a mais de um processo, cada um com dados de memória, estado atual, estado da CPU e programa únicos.
A CPU altera a execução dos processos em dois cenários: Ou quando um processo finalizou (seu estado é morto), ou quando um processo buscou acessar ES (a tarefa do processo é executada, o processo é parado e outro toma seu lugar). Ao parar, um processo salva o estado atual interno da CPU e memória para si, para devolver esses valores para a CPU quando for voltar a executar.
