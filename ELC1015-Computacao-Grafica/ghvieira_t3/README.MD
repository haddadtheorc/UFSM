# Trabalho 3 - Computação Gráfica - Transformações geométricas
## Gabriel Haddad Vieira - 201612818


### Instruções de uso:
- Para acelerar ou frear, utilize as setas do teclado (<- e ->). (Há um valor máximo de velocidade).
- Para visualizar as coordenadas da animação e sua rotação, utilize a tecla 'C'.

---------------------------------------------------------------------------------------------------

### Requisitos implementados:
- Desenho da bicicleta e personagem (partes do desenho devem ser estruturadas em classes específicas). (Obrigatório)
- Animação de pedalar com posicionamento correto das pernas e pedais, e correta rotação das rodas. (Obrigatório)
- Uso de matrizes de rotação e translação para posicionar os elementos de desenho na tela. (Obrigatório)
- Controle de FPS. (Obrigatório)

*BÔNUS*:
- Ligação matematicamente correta da perna com o pedal. (Função que calcula intersecção de círculos para posição correta do joelho)(Evita deformar a perna).
- Utilização de curva Bezier. (4 pontos de controle)(Capa do personagem).
- Técnica de parallax para background. (Nuvens e montanhas em diferentes velocidades).
- Controle de velocidade. (Setas para esquerda e direita).
- Visualização das coordenadas e suas rotações. (Tecla 'C')(Pontos de controle).
- Animação da curva Bezier. (Movimento de acordo com a velocidade).

---------------------------------------------------------------------------------------------------

### Estruturação do código:
- O código foi estruturando tentando se aproveitar da orientação a objetos provida pelo C++. Com isso o arquivo "main.cpp" ficou o mais enxuto possível, apenas chamando os métodos das classes durante a execução da render().

- Bicicleta
  - A classe 'Bike' contém todas as informações pertintentes ao desenho e transformações da bicicleta.
  - Seu tamanho é proporcional ao tamanho da tela.
  - Sua função principal é a render(), chamada a cada iteração da própria render da Canvas. Essa função chama suas auxiliares para tratarem o necessário em relação a renderização da bicicleta.
  - As funções com rotate (rotatePedals, rotateWheels, ...) fazem toda a transformação dos pontos para sua rotação.
  - As funções com render (renderPedals, renderWheels, ...) fazem toda a renderização dos pontos após suas transformações.

- Personagem
  - A classe 'Pilot' contém todas as informações pertintentes ao desenho e transformações do piloto.
  - Seu tamanho é proporcional ao tamanho da tela.
  - A capa do personagem é construída se utilizando da curva de Bezier. Para sua geração, foram utilizados 4 pontos de controle.
  - As funções com render (renderCloak, renderPilot, ...) fazem toda a renderização dos pontos após suas transformações.
  - A função calculateKnee() é construída para localizar a posição correta do joelho. Para isso são usados tanto o tamanho da coxa (e sua posição no banco) bem como o tamanho da canela e sua posição no pedal. Com isso é possível calcular o ponto de intersecção desses dois círculos e posicionar corretamente o joelho na coordenada. Isso evita deformar a perna, de modo que ambos tamanhos (coxa e canela) ficam fixos.

- Fundo
  - A classe 'Background' contém todas as informações pertintentes ao desenho e transformações do fundo.
  - Seu tamanho é proporcional ao tamanho da tela.
  - Diferentes elementos (nuvens, montanhas) possuem diferentes velocidades para gerar o efeito de perspectiva.

- FPS
  - A classe 'FPS' contém todas as informações pertinentes ao controle de FPS.
  - Seu valor, obtido através do método 'getFrames' é utilizado na 'render()' na 'main.cpp' para afetar diretamente a velocidade.