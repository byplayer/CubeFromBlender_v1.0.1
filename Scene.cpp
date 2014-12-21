#include <QMatrix4x4>
#include <QDir>
#include <QDebug>
#include "Scene.h"
#include "ObjLoader.h"

Scene::Scene( QWidget *parent ) :
    QOpenGLWidget( parent ),
    m_isLoaded( false )
{
    QString pathToCube = QDir::currentPath() + QString( "/Cube.observerFormat" );

    m_cube.vertices = ObjLoader::load( pathToCube.toStdString().c_str() );

    if ( m_cube.vertices.size() != 0 )
    {
        m_isLoaded = false;
        m_cube.initColors( m_cube.vertices.size() / 3 );
        qDebug() << m_cube.vertices.size();
        qDebug() << m_cube.colors.size();
    }
}

void Scene::initializeGL()
{
    glClearColor( 0.1f, 0.1f, 0.2f, 1.0f );

    QOpenGLShader vShader( QOpenGLShader::Vertex );
    vShader.compileSourceFile( ":/Shaders/vShader.glsl" );

    QOpenGLShader fShader( QOpenGLShader::Fragment );
    fShader.compileSourceFile( ":/Shaders/fShader.glsl" );

    m_program.addShader( &vShader );
    m_program.addShader( &fShader );
    if ( !m_program.link() )
    {
        qWarning( "Error: unable to link a shader program" );
        return;
    }

    m_vertexAttr = m_program.attributeLocation( "vertexAttr" );
    m_colorAttr = m_program.attributeLocation( "colorAttr" );
    m_matrixUniform = m_program.uniformLocation( "matrix" );

    glEnable( GL_DEPTH_TEST );
}

void Scene::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    if ( !m_program.bind() )
        return;

    QMatrix4x4 modelView;
    modelView.perspective( 60.0f, 4.0f / 3.0f, 0.1f, 400.0f );
    modelView.translate( 0.0f, 0.0f, -3.0f );
    m_program.setUniformValue( m_matrixUniform, modelView );

    if ( m_isLoaded )
        drawCube( m_cube );

    m_program.release();
}

void Scene::resizeGL( int w, int h )
{
    glViewport( 0, 0, w, h );
}

void Scene::drawCube( const Cube &cube )
{
    m_program.setAttributeArray( m_vertexAttr, cube.vertices.data(), 3 );
    m_program.setAttributeArray( m_colorAttr, cube.colors.data(), 3 );

    m_program.enableAttributeArray( m_vertexAttr );
    m_program.enableAttributeArray( m_colorAttr );

    glDrawArrays( GL_TRIANGLES, 0, cube.vertices.size() / 3 );

    m_program.disableAttributeArray( m_vertexAttr );
    m_program.disableAttributeArray( m_colorAttr );
}
