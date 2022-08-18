#ifndef ___3D_H__
#define ___3D_H__

#define pi 3.14159265

/*
- Objeto
  - A classe 'Objeto' contém todas as informações pertintentes a construção e desenho do objeto 3D.
  - Os métodos 'calculateCurve()' e 'calculateMatrix()' calculam, respectivamente, cada curva com sua rotação e a matriz de sweep.
  - Os métodos 'drawMatrix()' e 'drawWireframe()' desenham, respectivamente, os pontos da matriz de sweep e o wireframe dos pontos.
  - Os métodos 'changeBezierIncrement()' e 'changeMatrixSize()' alteram, respectivamente, a quantidade de pontos da curva bezier e a quantidade de colunas da matriz de sweep.
  - Os métodos 'changeD()' e 'changeRounds()' alteram, respectivamente, a distância do objeto da tela e o número de voltas da mola gerada.
*/

class _3D
{
public:

    float offsetY = 0;
    float d = 1000;
    bool ortho = false;
    bool spring = false;
    int rounds = 1;
    int matrix_size = 10;
    int mouseX, mouseY;
    float bezierIncrement = 20;
    vector<vector<Vector3>> matrix;

    // Atualização da posição atual do mouse
    void setMouse (float x, float y){
        mouseX = x;
        mouseY = y;
    }

    // Altera o d do objeto (com isso a distância dele da tela)
    void changeD (float change){
        if(!ortho){
            if(d+(change*5) < 0)
                return;
            d+=(change*5);
        }
    }

    // Altera o deltaT da curva bezier
    void changeBezierIncrement (float change){
        if(bezierIncrement+change <= 0)
            return;
        bezierIncrement += change;
    }

    // Altera o tamanho da matriz de sweep
    void changeMatrixSize(int change){
        if(matrix_size + change < 1)
            return;
        matrix_size+=change;
    }

    // Altera o número de voltas da mola gerada
    void changeRounds(int change){
        if(rounds + change < 1)
            return;
        rounds += change;
    }

    // Calcula a matriz de sweep (com suas múltiplas curvas)
    vector<vector<Vector3>> calculateMatrix(vector <Vector3> controlPoints){
        float ang = 0;
        float angX, angY;
        float springMod = 0;
        vector<vector<Vector3>> matrix;

        for(int i = 0; i < controlPoints.size(); i++){
           controlPoints[i].y = controlPoints[i].y - offsetY/2;
        }
        for(int i = 0; i < matrix_size; i++){
            ang = i*pi*((!spring)?2:2*rounds)/matrix_size;
            angX = ang + mouseX*pi*2/offsetY;
            angY = mouseY*pi*2/offsetY;
            matrix.push_back(calculateCurve(controlPoints, angX, angY, springMod));
            springMod+=d/50;
        }
        return matrix;
    }

    // Calcula uma bezier com N pontos de controle
    Vector2 calculateNBezier (vector<Vector3> controlPoints, float t) {
        vector<Vector3> tmp = controlPoints;
        int i = tmp.size() - 1;
        while (i > 0) {
            for (int k = 0; k < i; k++) {
                tmp[k].x = tmp[k].x + t * (tmp[k+1].x - tmp[k].x);
                tmp[k].y = tmp[k].y + t * (tmp[k+1].y - tmp[k].y);

            }
            i--;
        }
        return Vector2(tmp[0].x, tmp[0].y);
}

    // Calcula a rotação no eixo X baseado na posição Y do mouse
    Vector3 calculateAngleX(Vector3 point, float angle){
        return Vector3(point.x, point.y*cos(angle) - point.z*sin(angle), point.y*sin(angle) + point.z*cos(angle));
    }

    // Calcula a rotação no eixo Y baseado na posição X do mouse
    Vector3 calculateAngleY(Vector3 point, float angle){
        return Vector3(point.x*cos(angle) - point.z*sin(angle), point.y, point.x*sin(angle) + point.z*cos(angle));
    }

    // Calcula a curva bezier (com sua rotacao) e adiciona na matriz
    vector <Vector3> calculateCurve(vector<Vector3> controlPoints, float angX, float angY, float springMod){
        vector <Vector3> curve;
        for(int i = 0; i <= bezierIncrement; i++){
            float t = float(i)/bezierIncrement;
            Vector2 point = calculateNBezier(controlPoints, t);
            float x = point.x;
            float y = point.y;

            Vector3 rotatedPoint = calculateAngleY(Vector3(x, y, 0), angX);
            rotatedPoint = calculateAngleX(rotatedPoint, angY);

            rotatedPoint.z += controlPoints[0].z;
            rotatedPoint.x = rotatedPoint.x*d/((ortho)?d*2:rotatedPoint.z);
            rotatedPoint.y = ((spring)?springMod*rounds:0)+ rotatedPoint.y*d/((ortho)?d*2:rotatedPoint.z);

            curve.push_back(rotatedPoint);
        }
        return curve;
    }

    // Desenha o objeto (função principal que chama as demais)
    void draw(vector<Vector3> controlPoints, float _offsetY){
        if(controlPoints.size() < 2) return;
        offsetY = _offsetY;
        matrix = calculateMatrix(controlPoints);
        drawMatrix();
        drawWireframe(matrix);
    }

    // Desenha cada ponto da matriz de sweep
    void drawMatrix(){
        CV::color(0, 0, 0);
        for(int i = 0; i < matrix.size(); i++){
            for(int j = 0; j < matrix[i].size(); j++){
                CV::translate(800, ((spring)?125:350));
                CV::point(matrix[i][j].x, matrix[i][j].y);
            }
        }
    }

    // Desenha o wireframe do objeto
    void drawWireframe(vector<vector<Vector3>> matrix){
        CV::color(0, 0, 0);
        int i, j = 0;
        for(i = 0; i < matrix.size() - 1; i++){
            for(j = 0; j < matrix[i].size() - 1; j++){
                CV::line(matrix[i][j].x, matrix[i][j].y, matrix[i+1][j].x, matrix[i+1][j].y);
                CV::line(matrix[i][j].x, matrix[i][j].y, matrix[i+1][j+1].x, matrix[i+1][j+1].y);
                CV::line(matrix[i][j].x, matrix[i][j].y, matrix[i][j+1].x, matrix[i][j+1].y);
            }
            CV::line(matrix[i][j].x, matrix[i][j].y, matrix[i+1][j].x, matrix[i+1][j].y);
        }
        if(!spring){
            for(j = 0; j < matrix[i].size() - 1; j++){
                CV::line(matrix[i][j].x, matrix[i][j].y, matrix[0][j].x, matrix[0][j].y);
                CV::line(matrix[i][j].x, matrix[i][j].y, matrix[0][j+1].x, matrix[0][j+1].y);
                CV::line(matrix[i][j].x, matrix[i][j].y, matrix[0][j+1].x, matrix[0][j+1].y);
            }
            CV::line(matrix[i][j].x, matrix[i][j].y, matrix[0][j].x, matrix[0][j].y);
        }
    }
};

#endif
