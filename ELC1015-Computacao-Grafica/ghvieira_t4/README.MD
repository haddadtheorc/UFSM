# Trabalho 4 - Geração Objeto 3D com Sweep e Curvas
## Gabriel Haddad Vieira - 201612818


### Instruções de uso:

- Área de edição:
  - Para adição de um ponto de controle para a curva, clique com o mouse.
  - Para mover um ponto de controle, clique e arraste com o mouse.
  - Para remoção do ponto de controle selecionado, ou o último, utilize a tecla 'DEL'.

- Área de visualização:
  - Para alternar entre o modo de visualização ortográfica e perspectiva, utilize a tecla 'M'.
  - Para transformar o objeto em uma mola, utilize a tecla 'S'.
  - Para aumentar ou reduzir o número de pontos da curva bezier, utilize, respectivamente, as teclas '→' e '←'.
  - Para aumentar ou reduzir o número de colunas da matriz de sweep, utilize, respectivamente, as teclas '↑' e '↓'.
  - Para aumentar ou reduzir o número de voltas da mola do objeto gerado, utilize, respectivamente, as teclas 'I' e 'J'.
  - Para aumentar ou reduzir a distância do objeto gerado, utilize o scroll do mouse.
  - Para visualizar o objeto em diferentes ângulos, mova o cursor na direção desejada. 
  
---------------------------------------------------------------------------------------------------

### Requisitos implementados:
- Modelagem do objeto com opção de rotação e translação, para geração de objetos como garrafas, donuts e molas. (Obrigatório)
- Visualização ortográfica e perspectiva (sob vários ângulos) em wireframe, com uso de triângulos. (Obrigatório)
- Parametrização do número de pontos e faces do objeto gerado. (Obrigatório)

*BÔNUS*:
- Curva de Bezier com mútiplos pontos de controle (pelo menos 2 para gerar a curva e o objeto).

---------------------------------------------------------------------------------------------------

### Estruturação do código:
- O código foi estruturando tentando se aproveitar da orientação a objetos provida pelo C++. Com isso o arquivo "main.cpp" ficou o mais enxuto possível, apenas chamando os métodos das classes durante a execução da render().

- Bezier
  - A classe 'Bezier' contém todas as informações pertintentes a construção e desenho da curva Bezier.
  - Os métodos 'drawControlPoints()' e 'drawCurve()' desenham, respectivamente, os pontos de controle da curva e a curva gerada por esses pontos.
  - Os métodos 'addControlPoint()' e 'removeControlPoint()' respectivamente adicionam e removem um ponto de controle.

- Objeto
  - A classe 'Objeto' contém todas as informações pertintentes a construção e desenho do objeto 3D.
  - Os métodos 'calculateCurve()' e 'calculateMatrix()' calculam, respectivamente, cada curva com sua rotação e a matriz de sweep.
  - Os métodos 'drawMatrix()' e 'drawWireframe()' desenham, respectivamente, os pontos da matriz de sweep e o wireframe dos pontos.
  - Os métodos 'changeBezierIncrement()' e 'changeMatrixSize()' alteram, respectivamente, a quantidade de pontos da curva bezier e a quantidade de colunas da matriz de sweep.
  - Os métodos 'changeD()' e 'changeRounds()' alteram, respectivamente, a distância do objeto da tela e o número de voltas da mola gerada.
