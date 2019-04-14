#ifndef CANVASOPENGL_H
#define CANVASOPENGL_H

#include <QOpenGLWidget>
#include <QtGui>
#include <QWidget>
#include <vector>
#include <queue>
#include <QMouseEvent>

using namespace std;


class CanvasOpenGL : public QOpenGLWidget {
public:
    int R, G, B;
    bool isPolygonClosed;

    CanvasOpenGL(QWidget *parent);
    ~CanvasOpenGL();
    void clearScreen();
    void closePolygon();
    void polygonFill();
    void MakeAET(int currentY,
                 priority_queue<tuple<float, int, float>, vector<tuple<float, int, float> >, std::greater<tuple<float, int, float> > > ET[],
                 priority_queue<tuple<float, int, float>, vector<tuple<float, int, float> >, std::greater<tuple<float, int, float> > > &AET,
                 priority_queue<tuple<float, int, float>, vector<tuple<float, int, float> >, std::greater<tuple<float, int, float> > > &AETaux);


private:
    vector<QPoint> vertices;

protected:
    void initializeGL();
//    void resizeGL(int w, int h);
    void paintGL();

    void mousePressEvent(QMouseEvent *event);
};

#endif // CANVASOPENGL_H
