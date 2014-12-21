#ifndef SCENE_H
#define SCENE_H

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include "Cube.h"

class Scene : public QOpenGLWidget
{
public:
    Scene( QWidget *parent = 0);

private:
    void initializeGL();
    void paintGL();
    void resizeGL( int w, int h );

    void drawCube( const Cube &cube );

    QOpenGLShaderProgram m_program;

    int m_vertexAttr;
    int m_colorAttr;
    int m_matrixUniform;

    Cube m_cube;
    bool m_isLoaded;
};

#endif // SCENE_H
