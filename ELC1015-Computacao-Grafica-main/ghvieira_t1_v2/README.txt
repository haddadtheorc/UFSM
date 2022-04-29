Gabriel Haddad Vieira - 201612818

Trabalho 1 - Computação Gráfica - Manipulação de imagens

- A totalidade das aplicações implementadas pode ser manipulada pelo teclado ou interagindo com os widgets da tela.
- A imagem foi programada para ser plotada sempre ao centro da tela, usando seus próprios parâmetros de tamanho bem como os de tamanho da tela.


- A função que mostra a imagem na tela é a show_image(), que chama funções auxiliares show_image_pixel_point() e show_image_pixel_color() para aplicar os efeitos desejados à imagem.
- A manipulação da imagem é feita pelas variáveis globais image_color_mod e int image_point_mod onde a primeira dirá se algum filtro de cor será aplicado enquanto o segundo dita a orientação da imagem.
- A manipulação da escala da imagem é feita pelas variáveis globais image_scale_mod e image_print_mod que manipulam os laços para printar a imagem bem como os pixels que serão mostrados.



INSTRUÇÕES DE USO:
- A manipulação da orientação da imagem pode ser feita com as setas do teclado(esquerda e direita) bem como com os botões de orientação.
- A manipulação da escala da imagem pode ser feita com as setas do teclado (cima e baixo) bem como com o scroll do mouse.
- A manipulação de cor da imagem pode ser feita com as letras r, g, b, x, z, d(vermelho, verde, azul, tons de cinza, cores invertidas e default) bem como com as checkboxes com sua cor.



MANIPULAÇÃO DE IMAGEM:
Exibição da imagem em canais separados RBG (obrigatório)
Exibição da imagem em tons de cinza (obrigatório)
Exibição do histograma dos canais RGB e luminância (A FAZER) (obrigatório)

Rotacionar a imagem (90º direita ou esquerda) (obrigatório)
Escalar a imagem - 1/2 e 1/4 (obrigatório)

Exibição da imagem em cores invertidas (BÔNUS)



WIDGETS IMPLEMENTADOS:
Botões e checkboxes.
Widgets possuem tamanho e posicionamento, ancorado em pontos genericos, proporcionais ao tamanho da tela. Isso permite, ao aumentar o tamanho da tela, os widgets acompanharem essas modificações.

ESTRUTURAÇÃO DO CÓDIGO:
O código foi estruturando tentando se aproveitar da orientação a objetos provida pelo C++. Com isso o arquivo "main.cpp" ficou o mais enxuto possível, apenas chamando os métodos das classes durante a execução de render().

---Imagens---
A classe Images engloba uma classe para conter um vetor de imagens (classe Image) e facilitar para sua renderização.
Cada imagem no vetor de imagens tem seu atributo filtro (classe Filter) para sua edição. 
O método show() na classe Images trata de renderizar todas as imagens carregadas na aplicação, enquanto o método show() na classe Image renderiza uma por uma com seus filtros aplicados.

---Widgets---
A classe Widget foi criada extremamente modular para facilitar a adição de mais widgets, agindo como um "manager" de botões como foi sugerido no trabalho.
Cada widget tem sua classe separada, mas as funções render() e collide() são comuns a todos.
Tem arrays de widgets(nesse caso botões e checkboxes) como seus atributos e os métodos show() e collide(). 
O método show() trata de renderizar todos os widgets presentes no objeto, enquanto método collide() trata de verificar quaiquer colisões nos widgets.


