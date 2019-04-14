#include "canvasopengl.h"

#define WINDOW_HEIGHT 480

CanvasOpenGL::CanvasOpenGL(QWidget *parent) : QOpenGLWidget(parent) {
    R = 255;
    G = 255;
    B = 255;

    isPolygonClosed = false;
}

CanvasOpenGL::~CanvasOpenGL() {}

void CanvasOpenGL::initializeGL() {}

void CanvasOpenGL::paintGL() {
    //create a QPainter and pass a pointer to the device.
    //A paint device can be a QWidget, a QPixmap or a QImage
    QPainter painter(this);

    QPen myPen(1); // 1 px
    QColor color(R, G, B);
    myPen.setColor(color);

    painter.setPen(myPen);

    for (vector<QPoint>::iterator i = this->vertices.begin(); i != this->vertices.end(); i++) {
        painter.drawPoint(*i);
        if (i != this->vertices.begin())
            painter.drawLine(*prev(i, 1), *i);
    }

    if (isPolygonClosed) {
        painter.drawLine(*vertices.begin(), *prev(vertices.end(), 1));
        polygonFill();
    }

}

//void CanvasOpenGL::resizeGL(int w, int h) {}

void CanvasOpenGL::polygonFill() {
    // A tupla representa os seguintes elementos: X atual, Y max, variação (1/m)
    priority_queue<tuple<float, int, float>, vector<tuple<float, int, float> >, std::greater<tuple<float, int, float> > > ET[WINDOW_HEIGHT];
    priority_queue<tuple<float, int, float>, vector<tuple<float, int, float> >, std::greater<tuple<float, int, float> > > AET;
    priority_queue<tuple<float, int, float>, vector<tuple<float, int, float> >, std::greater<tuple<float, int, float> > > nextET;

    // Cria Edge Table
    for (unsigned long long i = 0, next_point = 0; i < this->vertices.size(); i++) {
        next_point = i + 1; // Pega o próximo ponto do vetor de vértices
        if (next_point == this->vertices.size()) // Caso o próximo ponto seja o último
            next_point = 0;    // O próximo é o primeiro

        QPoint pointMin, pointMax;  // Descobre qual ponto possui o menor Y
        if (vertices[i].y() > vertices[next_point].y()){
            pointMin = vertices[next_point];
            pointMax = vertices[i];
        } else {
            pointMin = vertices[i];
            pointMax = vertices[next_point];
        }

        if (pointMin.y() != pointMax.y()) { // Caso os dois pontos possuam o mesmo Y, não precisa incluir na ET
            int dx = pointMax.x() - pointMin.x();   // Calcula a diferença do X e Y para calcular a variação m
            int dy = pointMax.y() - pointMin.y();
            ET[pointMin.y()].push(make_tuple(pointMin.x(), pointMax.y(), float (dx / float (dy)))); // insere o
        }
    }

    MakeAET(0, ET, AET, nextET);   // Percorre o algorítmo da tabela de vértices ativo
}

void CanvasOpenGL::MakeAET(int currentY,
            priority_queue<tuple<float, int, float>, vector<tuple<float, int, float> >, std::greater<tuple<float, int, float> > > ET[WINDOW_HEIGHT],
            priority_queue<tuple<float, int, float>, vector<tuple<float, int, float> >, std::greater<tuple<float, int, float> > > &AET,
            priority_queue<tuple<float, int, float>, vector<tuple<float, int, float> >, std::greater<tuple<float, int, float> > > &AETaux) {

    if (currentY == WINDOW_HEIGHT)
        return;

    // Coloca os elementos da ET na AET
    while (ET[currentY].size() > 0) {
        float x, m;
        int y;
        tie(x, y, m) = ET[currentY].top();

        AET.push(ET[currentY].top());
        ET[currentY].pop();
        tie(x, y, m) = AET.top();
    }

    QPainter painter(this);
    QPen myPen(1); // 1 px
    QColor color(R, G, B);
    myPen.setColor(color);

    painter.setPen(myPen);

    // Percorre a AET pintando o interior do polígono
    while (AET.size() > 0) {
        tuple<float, int, float> initial = AET.top();
        AET.pop();
        tuple<float, int, float> final = AET.top();
        AET.pop();

        int initialY, finalY;
        float initialX, initialM, finalX, finalM;
        tie(initialX, initialY, initialM) = initial;
        tie(finalX, finalY, finalM) = final;

        // Pinta na tela a linha entre os dois pontos das retas. Para o ponto da esquerda, arredonda-se para cima. Já na direita, arredonda para baixo.
        painter.drawLine(int(ceil(initialX)), currentY, int(floor(finalX)), currentY);

        initialX += initialM;   // Muda o X conforme a variação (m)
        finalX += finalM;

        if (currentY+1 < initialY)  // Caso o próximo nível do Y seja menor que o Y máximo da aresta,
            AETaux.push(make_tuple(initialX, initialY, initialM));  // adiciona na fila auxiliar
        if (currentY+1 < finalY)
            AETaux.push(make_tuple(finalX, finalY, finalM));
    }

    MakeAET(currentY+1, ET, AETaux, AET);   // Por fim, inverte a fila auxiliar com a fila normal, que agora está vazia.
}

void CanvasOpenGL::closePolygon() {
    if (this->vertices.size() >= 3) {
        isPolygonClosed = true;
    }
}

void CanvasOpenGL::mousePressEvent(QMouseEvent *event) {
    if (isPolygonClosed)
        return;

    if (event->buttons() == Qt::RightButton) {
        closePolygon();
    } else {
        this->vertices.push_back(event->pos());
    }
    this->update();
}

void CanvasOpenGL::clearScreen() {
    isPolygonClosed = false;

    if(!this->vertices.empty()) {
        this->vertices.clear();
        this->update();
    }
}
