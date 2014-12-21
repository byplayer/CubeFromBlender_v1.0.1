#include <GL/gl.h>
#include "Cube.h"

Cube::Cube( QOpenGLShaderProgram *program, int vertexAttr, int colorAttr ) :
    m_program( program ),
    m_vertexAttr( vertexAttr ),
    m_colorAttr( colorAttr )
{

}

void Cube::initVertices()
{
    vertices.clear();
    vertices.resize( 9 );

    // 0
    vertices[0] = -0.5f;
    vertices[1] = -0.5f;
    vertices[2] = 0.0f;

    // 1
    vertices[3] = 0.5f;
    vertices[4] = -0.5f;
    vertices[5] = 0.0f;

    // 2
    vertices[6] = -0.5f;
    vertices[7] = 0.5f;
    vertices[8] = 0.0f;
}

void Cube::initColors( int numOfVertices )
{
    colors.clear();
    colors.resize( numOfVertices * 3 );

    for ( unsigned int i = 0, j = 0; i < numOfVertices / 3; ++i )
    {
        colors[j++] = 1.0f;
        colors[j++] = 0.0f;
        colors[j++] = 0.0f;

        colors[j++] = 0.0f;
        colors[j++] = 1.0f;
        colors[j++] = 0.0f;

        colors[j++] = 0.0f;
        colors[j++] = 0.0f;
        colors[j++] = 1.0f;
    }
}

void Cube::draw()
{
    m_program->setAttributeArray( m_vertexAttr, vertices.data(), 3 );
    m_program->setAttributeArray( m_colorAttr, colors.data(), 3 );

    m_program->enableAttributeArray( m_vertexAttr );
    m_program->enableAttributeArray( m_colorAttr );

    glDrawArrays( GL_TRIANGLES, 0, vertices.size() / 3 );

    m_program->disableAttributeArray( m_vertexAttr );
    m_program->disableAttributeArray( m_colorAttr );
}
