Trabalho 4 - Geração de Engrenagens 3D

Gabriel Haddad Vieira - 201612818


Requisitos básicos implementados (4/4):

1/4 - Modelagem de engrenagem tipo spur gear - Implementado. Na classe gear há a criação da engrenagem. Usa seu tamanho e número de dentes para parâmetro de criação.
							 Ela é printada em 2d na função draw_gear_2d() e em 3d na função draw_gear_3d().
2/4 - Animação (rotação) - Implementado. Na classe gear na função rotate_gear_3d() faz-se a rotação da engrenagem implementada.
3/4 - Visualização ortográfica e perspectiva (sob vários ângulos) em wireframe - Implementado. Na classe camera há todo o código que trabalha com a visualização sob vários ângulos.
4/4 - Parametrização do número de dentes e raios. - Implementado. Na classe gear toda a criação da engrenagem usa o número de dentes como parâmetro para sua criação balanceada.


Informações gerais do código:
A gear.h contém tudo necessário para a criação, visualização e rotação da engrenagem spur gear básica. 
A camera.h contém tudo necessário para a visualização ortográfica e perspectiva da engrenagem implementada.
A vetor.h contém as informações dos pontos a serem usados tanto para a engrenagem quanto para a câmera. Uma classe para armazenar pontos do tipo xyz.
É usado o mouse (botão 0) para mover a câmera para observar de diversos ângulos a engrenagem.

Extras:
- A interação com a setas do teclado (direita e esquerda) alterna o sentido de rotação da engrenagem. (BÔNUS)
- A interação com as setas do teclado (cima e baixo) aumenta e diminui o número de dentes na engrenagem. (BÔNUS)
- A interação com a barra de espaço liga e desliga o sentido de rotação da engrenagem. (BÔNUS)