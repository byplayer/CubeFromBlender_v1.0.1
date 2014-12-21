#ifndef SCENE_H
#define SCENE_H

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QWheelEvent>
#include <QMouseEvent>
#include "Cube.h"

class Scene : public QOpenGLWidget
{
public:
    Scene( QWidget *parent = 0);
    ~Scene();

private:
    void initializeGL();
    void paintGL();
    void resizeGL( int w, int h );

    void wheelEvent( QWheelEvent *event );
    void scalePlus();
    void scaleMinus();

    void mousePressEvent( QMouseEvent *event );
    void mouseMoveEvent( QMouseEvent *event );

    QOpenGLShaderProgram m_program;

    int m_vertexAttr;
    int m_colorAttr;
    int m_matrixUniform;

    Cube *m_cube;
    bool m_isLoaded;
    float m_scale;
    QPoint m_lastPos;
    float m_xRot;
    float m_zRot;
};

#endif // SCENE_H
