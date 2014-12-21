#ifndef CUBE_H
#define CUBE_H

#include <QOpenGLShaderProgram>
#include <vector>

class Cube
{
public:
    Cube( QOpenGLShaderProgram *program, int vertexAttr, int colorAttr );
    void initVertices();
    void initColors( int numOfVertices );

    void draw();

    std::vector<float> vertices;
    std::vector<float> colors;

private:
    QOpenGLShaderProgram *m_program;
    int m_vertexAttr;
    int m_colorAttr;
};

#endif // CUBE_H
