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

private:
    vector<QPoint> vertices;

protected:
    void initializeGL();
//    void resizeGL(int w, int h);
    void paintGL();

    void mousePressEvent(QMouseEvent *event);
};

#endif // CANVASOPENGL_H
