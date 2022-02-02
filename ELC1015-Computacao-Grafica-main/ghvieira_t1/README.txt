Gabriel Haddad Vieira - 201612818

Trabalho 1 - Computação Gráfica - Visualizador de Imagens e API de widgets

- A totalidade das aplicações implementadas pode ser manipulada pelo teclado ou interagindo com os widgets da tela.
- A imagem foi programada para ser plotada sempre ao centro da tela, usando seus próprios parâmetros de tamanho bem como os de tamanho da tela.

- Widgets implementados, em classes separadas: Botão, checkbox. (Widgets possuem posicionamento ancorado em pontos genericos pertinentes ao tamanho da tela, para ao ser redimensionada os widgets acompanharem)
- Manipulação de imagem: Girar 90° para qualquer lado, reescalar a imagem pela metade. Mostrar cada canal de cor separado, mostrar a imagem em escala de cinza. Mostrar a imagem com suas cores invertidas.

- A função que mostra a imagem na tela é a show_image(), que chama funções auxiliares show_image_pixel_point() e show_image_pixel_color() para aplicar os efeitos desejados à imagem.
- A manipulação da imagem é feita pelas variáveis globais image_color_mod e int image_point_mod onde a primeira dirá se algum filtro de cor será aplicado enquanto o segundo dita a orientação da imagem.
- A manipulação da escala da imagem é feita pelas variáveis globais image_scale_mod e image_print_mod que manipulam os laços para printar a imagem bem como os pixels que serão mostrados.

- A manipulação da orientação da imagem pode ser feita com as setas do teclado(esquerda e direita) bem como com os botões de orientação.
- A manipulação da escala da imagem pode ser feita com as setas do teclado (cima e baixo) bem como com os botões de escala.
- A manipulação de cor da imagem pode ser feita com as letras r, g, b, x, z, d(vermelho, verde, azul, tons de cinza, cores invertidas e default) bem como com as checkboxes com sua cor.
