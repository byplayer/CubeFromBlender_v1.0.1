#include <QMatrix4x4>
#include <QDir>
#include <QDebug>
#include "Scene.h"
#include "ObjLoader.h"

Scene::Scene( QWidget *parent ) :
    QOpenGLWidget( parent ),
    m_isLoaded( false ),
    m_scale( 1.0f ),
    m_xRot( 0.0f ),
    m_zRot( 0.0f )
{
}

Scene::~Scene()
{
    delete m_cube;
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

    m_cube = new Cube( &m_program, m_vertexAttr, m_colorAttr );
    QString pathToCube = QDir::currentPath() + QString( "/Cube.observerFormat" );
    m_cube->vertices = ObjLoader::load( pathToCube.toStdString().c_str() );
    if ( m_cube->vertices.size() != 0 )
    {
        m_isLoaded = true;
        m_cube->initColors( m_cube->vertices.size() / 3 );
    }

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
    modelView.scale( m_scale );
    modelView.rotate( m_xRot, 1.0f, 0.0f, 0.0f );
    modelView.rotate( m_zRot, 0.0f, 0.0f, 1.0f );
    m_program.setUniformValue( m_matrixUniform, modelView );

    if ( m_isLoaded )
        m_cube->draw();

    m_program.release();
}

void Scene::resizeGL( int w, int h )
{
    glViewport( 0, 0, w, h );
}

void Scene::wheelEvent( QWheelEvent *event )
{
    if ( event->delta() > 0 )
        scalePlus();
    else if ( event->delta() < 0 )
        scaleMinus();

    update();
}

void Scene::scalePlus()
{
    m_scale *= 1.1;
}

void Scene::scaleMinus()
{
    m_scale /= 1.1;
}

void Scene::mousePressEvent( QMouseEvent *event )
{
    m_lastPos = event->pos();
}

void Scene::mouseMoveEvent( QMouseEvent *event )
{
    m_xRot += 180 / m_scale * ( float ) ( event->y() / m_lastPos.y() ) / height();
    m_zRot += 180 / m_scale * ( float ) ( event->x() / m_lastPos.x() ) / width();

    m_lastPos = event->pos();

    if ( m_xRot >= 360 )
        m_xRot = 0;

    if ( m_zRot >= 360 )
        m_zRot = 0;

    update();
}
