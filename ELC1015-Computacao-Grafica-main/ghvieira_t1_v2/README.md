# Trabalho 1 - Computação Gráfica - Manipulação de imagens
## Gabriel Haddad Vieira - 201612818


### Instruções de uso:
- Para selecionar uma imagem na tela, basta clicar sobre ela. Com isso ela se torna ativa e passa a acompanhar o mouse.
- Clicar numa imagem ativa a faz ser liberada e ficar estacionária na tela como as demais.
- A manipulação da orientação da imagem pode ser feita com as letras 'a' e 'd' - para rodar, respectivamente, para esquerda e direita - bem como com os botões de rotação.
- A manipulação da escala da imagem pode ser feita com as letras 'w' e 's' - para, respetivamente, aumentar e diminuir - bem como com o scroll do mouse.
- A manipulação de cor da imagem pode ser feita com as letras 'r', 'g', 'b', 'x', 'z' - vermelho, verde, azul, tons de cinza, cores invertidas - bem como com as checkboxes com sua cor.
- As modificações feitas com essas mecânicas vão ser ativadas pela imagem que estiver ativa - ou seja, a imagem selecionada pelo usuário ao clicar com o mouse.

---------------------------------------------------------------------------------------------------

### Requisitos implementados:
- Carregar imagem colorida (RGB) em formato BMP. (Obrigatório)
- Mover cada imagem individualmente com o uso do mouse. (Obrigatório)
- Exibir a imagem em canais separados RBG. (Obrigatório)
- Exibir a imagem em tons de cinza. (Obrigatório)
- Exibir o histograma dos canais RGB e luminância. (A FAZER) (Obrigatório)
- Rotacionar a imagem (90º direita ou esquerda). (Obrigatório)
- Escalar a imagem (1/2 e 1/4). (Obrigatório)

*BÔNUS*:
- Exibir a imagem em cores invertidas.

---------------------------------------------------------------------------------------------------

### Widgets implementados:
- Botões e checkboxes.
- Todos os widgets implementados possuem um posicionamento - ancorado em pontos genericos - e um tamanho, ambos atributos proporcionais ao tamanho da tela. Isso permite, ao refatorar o tamanho da tela, os widgets acompanharem essas modificações.

### Estruturação do código:
- O código foi estruturando tentando se aproveitar da orientação a objetos provida pelo C++. Com isso o arquivo "main.cpp" ficou o mais enxuto possível, apenas chamando os métodos das classes durante a execução de render().

- Imagens
  - A classe 'Images' contém vetor de imagens (classe 'Image') como atributo, para melhor leitura e facilitar para sua renderização.
  - Cada imagem no vetor de imagens tem seu atributo filtro (classe 'Filter') para sua edição. 
  - O método show() na classe 'Images' trata de renderizar todas as imagens carregadas na aplicação, enquanto o método collide() trata de verificar quaiquer colisões na imagem.
  - Enquanto isso método show() na classe 'Image' renderiza exclusivamente aquela imagem.

- Widgets
  - A classe 'Widget' foi criada extremamente modular para facilitar a adição de mais widgets, agindo como o "manager" de botões como foi sugerido no trabalho.
  - Possui como atributo um array de widgets - nesse caso botões e checkboxes - e os métodos show() e collide(). 
  - O método show() trata de renderizar todos os widgets presentes no objeto, enquanto método collide() trata de verificar quaiquer colisões nos widgets.
  - Os widgets são criados e armazenados no array no método initialize(). Cada widget tem sua classe separada, bem como atributos e métodos únicos, mas os métodos render() e collide() são comuns a todos.

- Filtros
  - A classe 'Filter' contém todas as informações de possíveis filtros a serem aplicados na imagem. Ela armazena não somente os filtros de cores, mas de orientação e de escala.
  - Seu método filter() aplica os filtros de cor na imagem preemptivo a sua impressão. O método reset() remove quaisquer filtros aplicados em uma imagem.
