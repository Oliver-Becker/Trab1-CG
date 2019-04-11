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

    if (isPolygonClosed)
        painter.drawLine(*vertices.begin(), *prev(vertices.end(), 1));

    /* EXAMPLE OF A WHITE SQUARE WITH SIZE 100 X 100
     * for (int i = 100; i <= 200; i++) {
        for(int j = 100; j <= 200; j++) {
            painter.drawPoint(i, j);
        }
    }*/
}

//void CanvasOpenGL::resizeGL(int w, int h) {}

void CanvasOpenGL::polygonFill() {
    map<int, pair<int, float>> ET[WINDOW_HEIGHT];
    priority_queue<tuple<int, float, float> > AET;
    priority_queue<tuple<int, float, float> > nextET;

    for (vector<QPoint>::iterator i = this->vertices.begin(), next_point; i != this->vertices.end(); i++) {
        next_point = next(i, 1);
        QPoint ymin;// = min(i->y(), next_point->y());
        QPoint ymax;// = max(i->y(), next_point->y());

        if (ymin != ymax) {

        }
    }
}

//void vaiPreenchendo(priority_queue<tuple<int, float, float> > &AET, priority_queue<tuple<int, float, float> > &AETaux) {


//    vaiPreenchendo(AETaux, AET);
//}

void CanvasOpenGL::closePolygon() {
    if (this->vertices.size() >= 3)
        isPolygonClosed = true;
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
