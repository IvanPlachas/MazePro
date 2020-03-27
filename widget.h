#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QKeyEvent>
#include <QMouseEvent>

class Object3D;

class Widget : public QOpenGLWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void initShaders();
    void initCube(float x, float y, float z, float width, QString imag);
    void initWall(float x, float y, float z, float width, QString imag);
    void initUpDown(float y, float width, QString imag);
    void initInside(float x, float y, float z, float width, QString imag);

private:
    QMatrix4x4 m_projectionMatrix;
    QOpenGLShaderProgram m_program;
    QVector2D m_mousePosition;
    QQuaternion m_rotation;
    QVector<Object3D *> m_objects;
    GLfloat angle=270;
};
#endif // WIDGET_H
