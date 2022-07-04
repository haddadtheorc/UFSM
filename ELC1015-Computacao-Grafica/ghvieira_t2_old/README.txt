Gabriel Haddad Vieira - 201612818


Modo de interpolação escolhido: BEZIER

-Informações gerais
	- A cada três pontos de controle a curva é gerada (grau3). Para fechar a pista se liga o ponto final com o ponto inicial.
	- Os pontos de controle são adicionados com o clique do mouse do usuário.
		Caso o usuario clique em um ponto de controle existente esse ponto pode ser reposicionado. Ele ficará verde para indicar ao usuário que poderá ser reposicionado.
	  	Nesse modo de reposicionamento de pontos ele seguirá o mouse até ser clicado novamente, onde passará a ser estático.	
	- Com pelo menos três pontos de controle a curva passa a ser gerada. A cada outros três pontos de controle, outra curva é gerada. Pontos sobressalentes são conectados entre si ou com o final.
	- A curva é gerada em tempo de execução, sendo atualizada em tempo real ao se adicionar novos pontos ou movendo os já existentes. (BÔNUS).	

-Informações do código
	- O bool track_edit controla se está em modo edição de pista ou não. A tecla ENTER controla isso, apertando para sair ou entrar do modo edição.
		- O modo edição nada mais é que mostrar apenas a pista ou mostrar ela em conjunto com seus pontos de controle e seu grafo de controle.
	- O bezier_shift é a variável que será usada no laço principal da interpolação da curva. Foi usado um valor pequeno para deixar a curva suave.

-Interações com o teclado (BÔNUS)
	- A tecla ENTER entra e sai do modo de edição
	- A tecla Z remove o último ponto de controle adicionado

-Interações com o mouse
	- O clique do mouse cria um novo ponto de controle se não há um ponto de controle naquele lugar ou
		passa a mover um ponto de controle existente para uma nova localização, deixando-o estático com outro clique.

-Para manipulação dos pontos de controle foi usado
	- O vetor track_control_points para armazenar os pontos
	- A variável track_mouse_point pra fazer o ponto a ser editado seguir o mouse
	- A função track_fill_vector() para preencher o vetor acima com os pontos do usuario
	- A função control_point_colision() para saber se o usuario adicionou um novo ponto ou quer editar um atual
	- A função draw_control_points() e draw_control_graph() para respectivamente desenhar os pontos de controle e o grafo de controle.

-Para manipulação da curva bezier foi usado
	- O vetor bezier_final para armazenar os pontos interpolados
	- A função bezier() que preenche o vetor acima com os pontos para as curvas (a cada três) ou une pontos sobressalentes que ainda não formaram uma curva ou não formarão uma curva.
	- A função draw_bezier() que desenha a curva com os pontos do vetor acima.



