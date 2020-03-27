#include "widget.h"
#include <QOpenGLContext>
#include <object3d.h>
#include <iostream>
QTextStream cout(stdout);

int mas[25][25] = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                   {1,0,0,0,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1},
                   {1,0,0,0,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1},
                   {1,0,0,0,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1},
                   {1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
                   {1,0,4,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
                   {1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1},
                   {1,2,2,2,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,1},
                   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1},
                   {1,0,0,0,0,0,0,4,0,1,0,0,3,0,0,1,0,4,0,1,0,0,0,0,1},
                   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,1},
                   {1,0,0,0,1,1,1,1,1,1,1,1,2,2,2,1,0,0,0,1,0,0,0,0,1},
                   {1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                   {1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                   {1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
                   {1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,2,2,2,1},
                   {1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,1},
                   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1},
                   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,4,0,0,1},
                   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1},
                   {1,1,1,1,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1,1,1,1,1,1,1}};

float fx=0, fz=-1, fy=0;
float xb=0, zb=0;
int dirrection = 270, dirrectionBefore=270;
int state=0;
int t1=0, t2=0, t3=0, t4=0;
float lightPow = 0.5;
float specular = 0;

Widget::Widget(QWidget *parent): QOpenGLWidget(parent)
{
}

Widget::~Widget()
{
}

void Widget::initializeGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE); //отсечение задних граней, чтобы они не рисовались
    initShaders();
    int i=0, j=0, k=0;
    for(float x=-1.2; x<=1.3; x+=0.1)
    {
        for(float z=-1.2; z<=1.3; z+=0.1)
        {
            if(mas[j][i]==1 || mas[j][i]==2)
            {
                initWall(x, 0, z, 0.1, ":/wall.jpg");
            }
            else if(mas[j][i]==3)
            {
                initCube(x, -0.1, z, 0.1, ":/wall.png");
            }
            else if(mas[j][i]==4)
            {
                initCube(x, -0.1, z, 0.1, ":/cube2.png");
            }
            j++;
        }
        i++; j=0;
    }
    initUpDown(0, 2.8, ":/stone_texture.jpg");
    initInside(-2.25, 0, -2, 0.5, ":/menu.png");
    initInside(-2.25, 0, -3, 0.5, ":/info.jpg");
    initInside(-2.25, 0, -4, 0.5, ":/victory.png");
    initInside(-2.25, 0, -5, 0.5, ":/map.png");
    initCube(-2.51, 0, -4.84, 0.025, ":/cube2.png");
    initCube(-2.51, 0.062, -4.77, 0.025, ":/cube2.png");
    initCube(-2.51, 0.035, -5.095, 0.025, ":/cube2.png");
    initCube(-2.51, -0.145, -5.2, 0.025, ":/cube2.png");

    //showFullScreen();
}

void Widget::resizeGL(int w, int h)
{
    float aspect = w / (float)h;

    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(45, aspect, 0.1f, 10.0f);
}

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    QMatrix4x4 VievMatrix;
    VievMatrix.setToIdentity();
    switch (state)
    {
        case 0:
            lightPow = 5.5;
            specular = 0;
            //dirrectionBefore = dirrection;
            VievMatrix.rotate(270, QVector3D(0, 1, 0));
            VievMatrix.translate(2, 0, 2);
            break;
        case 1:
            lightPow = 0.5;
            specular = 900;
            VievMatrix.rotate(dirrection, QVector3D(0, 1, 0));
            VievMatrix.translate(fx, fy, fz);
            break;
        case 2:
            lightPow = 3.5;
            specular = 0;
            VievMatrix.rotate(270, QVector3D(0, 1, 0));
            VievMatrix.translate(2, 0, 3);
            break;
        case 3:
            lightPow = 3.5;
            specular = 0;
            dirrectionBefore = dirrection;
            VievMatrix.rotate(270, QVector3D(0, 1, 0));
            VievMatrix.translate(2, 0, 5);
            break;
        case 5:
            //t1=0; t2=0; t3=0; t4=0;
            lightPow = 3.5;
            specular = 0;
            VievMatrix.rotate(270, QVector3D(0, 1, 0));
            VievMatrix.translate(2, 0, 4);
            break;
    }
    //cout << "x:" << fx << " z:" << fz <<endl;

    m_program.bind();
    m_program.setUniformValue("u_projectionMatrix", m_projectionMatrix);
    m_program.setUniformValue("u_vievMatrix", VievMatrix);
    m_program.setUniformValue("u_lightPosition", QVector4D(0, 0, 0, 1.0));
    m_program.setUniformValue("u_lightPower", lightPow);
    m_program.setUniformValue("u_specularFactor", specular);
    int k = m_objects.size() - 4;
    for(int i = 0; i < k; ++i)
    {
        m_objects[i]->draw(&m_program, context()->functions());
    }
    if(t1) m_objects[k]->draw(&m_program, context()->functions());
    if(t2) m_objects[k+1]->draw(&m_program, context()->functions());
    if(t3) m_objects[k+2]->draw(&m_program, context()->functions());
    if(t4) m_objects[k+3]->draw(&m_program, context()->functions());
}

void Widget::initShaders()
{
    if(!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/verShader.vsh"))
        close();
    if(!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragShader.fsh"))
        close();
    if(!m_program.link())
        close();
}


void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        m_mousePosition = QVector2D(event->localPos());
        int x = m_mousePosition.x(), y = m_mousePosition.y();
        cout << "x:" << x << " y:" << y <<endl;
        if(!state)
        {
            if(y>0 && y<317)
            {
                if(x>450 && x<1567)
                {
                    dirrection = 270;
                    state = 1;
                    event->accept(); update();
                }
            }
            if(y>405 && y<710)
            {
                if(x>311 && x<1695)
                {
                    state = 2; event->accept(); update();
                }
            }
            if(y>814 && y<1057)
            {
                if(x>378 && x<1556) close();
            }
        }
    }
    event->accept(); //Подтверждает срабатывание события
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() != Qt::LeftButton) return;
    QVector2D diff = QVector2D(event->localPos()) - m_mousePosition;
    m_mousePosition = QVector2D(event->localPos());
    float angle = diff.length() / 2;
    QVector3D axis = QVector3D(0, diff.x(), 0.0);
    m_rotation = QQuaternion::fromAxisAndAngle(axis, angle) * m_rotation;
    update();
}

void Widget::keyPressEvent(QKeyEvent *e)
{
    QMatrix4x4 modelViewMatrix;
    int i=0, j=0;
    float fx1=fx+0.177, fx2=fx-0.177, fz1=fz+0.177, fz2=fz-0.177;
    if(fy==0)
    {
        for(float x=1.2; x>=-1.3; x-=0.1)
        {
              for(float z=1.2; z>=-1.3; z-=0.1)
              {
                   if(mas[i][j]==1 && fx1>=x && fx2<=x && fz1>=z && fz2<=z)
                   {
                       fz=zb; fx=xb;
                       return;
                   }
                   i++;
              }
              j++; i=0;
         }
    }
    switch ( e->key() )
    {
        case Qt::Key_W:
            switch (dirrection)
            {
                case 0:
                    zb=fz;
                    fz+=0.004;
                    break;
                case 90:
                    xb=fx;
                    fx-=0.004;
                    break;
                case 180:
                    zb=fz;
                    fz-=0.004;
                    break;
                case 270:
                    xb=fx;
                    fx+=0.004;
                    break;
            }
            break;
        case Qt::Key_S:
            switch (dirrection)
            {
                case 0:
                    zb=fz;
                    fz-=0.004;
                    break;
                case 90:
                    xb=fx;
                    fx+=0.004;
                    break;
                case 180:
                    zb=fz;
                    fz+=0.004;
                    break;
                case 270:
                    xb=fx;
                    fx-=0.004;
                    break;
            }
            break;
        case Qt::Key_A:
            switch (dirrection)
            {
                case 0:
                    xb=fx;
                    fx+=0.004;
                    break;
                case 90:
                    zb=fz;
                    fz+=0.004;
                    break;
                case 180:
                    xb=fx;
                    fx-=0.004;
                    break;
                case 270:
                    zb=fz;
                    fz-=0.004;
                    break;
            }
            break;
        case Qt::Key_D:
            switch (dirrection)
            {
                case 0:
                    xb=fx;
                    fx-=0.004;
                    break;
                case 90:
                    zb=fz;
                    fz-=0.004;
                    break;
                case 180:
                    xb=fx;
                    fx+=0.004;
                    break;
                case 270:
                    zb=fz;
                    fz+=0.004;
                    break;
            }
            break;
        case Qt::Key_Q:
            if(!dirrection) dirrection = 270;
            else dirrection -= 90;
            break;
        case Qt::Key_F:
            if(!t1 && fz>-0.15 && fz<0.15 && fx>0.45 && fx<0.65) t1 = 1;
            else if(!t2 && fz>0.25 && fz<0.45 && fx>0.85 && fx<1.15) t2 = 1;
            else if(!t3 && fz>-0.15 && fz<0.15 && fx>-0.65 && fx<-0.35) t3 = 1;
            else if(!t4 && fz>-1.5 && fz<-0.75 && fx>-1.5 && fx<-0.75) t4 = 1;
            else if(t1 && t2 && t3 && t4 && fz>-0.15 && fz<0.15 && fx>-0.15 && fx<0.15) state = 5;
            cout << "t1:" << t1 << " t2:" << t2 << " t3:" << t3 << " t4:" << t4 <<endl;
            break;
        case Qt::Key_Tab:
            if(state == 1) state = 3;
            else if(state == 3) {dirrection = dirrectionBefore; state = 1;}
            break;
        case Qt::Key_E:
            if(dirrection == 270) dirrection = 0;
            else dirrection += 90;
            break;
        case Qt::Key_Escape:
            fx = 0; fz = -1; fy = 0;
            t1=0; t2=0; t3=0; t4=0;
            state = 0;
            break;
        case Qt::Key_0:
            close();
            break;
    }
    update();
}

/*
 * л.в.
 * л.н.
 * п.в.
 * п.н.
*/
void Widget::initCube(float x, float y, float z, float width, QString imag)
{
    float width_div_2 = width / 2.0f;
    QVector<VertexData> vertexes;
    vertexes.append(VertexData(QVector3D(-width_div_2+x, width_div_2+y, width_div_2+z), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2+x, -width_div_2+y, width_div_2+z), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2+x, width_div_2+y, width_div_2+z), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2+x, -width_div_2+y, width_div_2+z), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 1.0)));

    vertexes.append(VertexData(QVector3D(width_div_2+x, width_div_2+y, width_div_2+z), QVector2D(0.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2+x, -width_div_2+y, width_div_2+z), QVector2D(0.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2+x, width_div_2+y, -width_div_2+z), QVector2D(1.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2+x, -width_div_2+y, -width_div_2+z), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));

    vertexes.append(VertexData(QVector3D(width_div_2+x, width_div_2+y, width_div_2+z), QVector2D(0.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2+x, width_div_2+y, -width_div_2+z), QVector2D(0.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2+x, width_div_2+y, width_div_2+z), QVector2D(1.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2+x, width_div_2+y, -width_div_2+z), QVector2D(1.0, 0.0), QVector3D(0.0, 1.0, 0.0)));

    vertexes.append(VertexData(QVector3D(width_div_2+x, width_div_2+y, -width_div_2+z), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2+x, -width_div_2+y, -width_div_2+z), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2+x, width_div_2+y, -width_div_2+z), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2+x, -width_div_2+y, -width_div_2+z), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, -1.0)));

    vertexes.append(VertexData(QVector3D(-width_div_2+x, width_div_2+y, width_div_2+z), QVector2D(0.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2+x, width_div_2+y, -width_div_2+z), QVector2D(0.0, 0.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2+x, -width_div_2+y, width_div_2+z), QVector2D(1.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2+x, -width_div_2+y, -width_div_2+z), QVector2D(1.0, 0.0), QVector3D(-1.0, 0.0, 0.0)));

    QVector<GLuint> indexes;
    for(int i = 0; i < 20; i += 4)
    {
        indexes.append(i + 0); indexes.append(i + 1); indexes.append(i + 2);
        indexes.append(i + 2); indexes.append(i + 1); indexes.append(i + 3);
    }

    m_objects.append(new Object3D(vertexes, indexes, QImage(imag)));

}

void Widget::initWall(float x, float y, float z, float width, QString imag)
{
    float width_div_2 = width / 2.0f;
    QVector<VertexData> vertexes;
    vertexes.append(VertexData(QVector3D(-width_div_2+x, 2*width_div_2+y, width_div_2+z), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2+x, -2*width_div_2+y, width_div_2+z), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2+x, 2*width_div_2+y, width_div_2+z), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2+x, -2*width_div_2+y, width_div_2+z), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 1.0)));

    vertexes.append(VertexData(QVector3D(width_div_2+x, 2*width_div_2+y, width_div_2+z), QVector2D(0.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2+x, -2*width_div_2+y, width_div_2+z), QVector2D(0.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2+x, 2*width_div_2+y, -width_div_2+z), QVector2D(1.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2+x, -2*width_div_2+y, -width_div_2+z), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));

    vertexes.append(VertexData(QVector3D(width_div_2+x, 2*width_div_2+y, -width_div_2+z), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2+x, -2*width_div_2+y, -width_div_2+z), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2+x, 2*width_div_2+y, -width_div_2+z), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2+x, -2*width_div_2+y, -width_div_2+z), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, -1.0)));

    vertexes.append(VertexData(QVector3D(-width_div_2+x, 2*width_div_2+y, width_div_2+z), QVector2D(0.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2+x, 2*width_div_2+y, -width_div_2+z), QVector2D(0.0, 0.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2+x, -2*width_div_2+y, width_div_2+z), QVector2D(1.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2+x, -2*width_div_2+y, -width_div_2+z), QVector2D(1.0, 0.0), QVector3D(-1.0, 0.0, 0.0)));

    QVector<GLuint> indexes;
    for(int i = 0; i < 16; i += 4)
    {
        indexes.append(i + 0); indexes.append(i + 1); indexes.append(i + 2);
        indexes.append(i + 2); indexes.append(i + 1); indexes.append(i + 3);
    }

    m_objects.append(new Object3D(vertexes, indexes, QImage(imag)));
}

void Widget::initUpDown(float y, float width, QString imag)
{
    float width_div_2 = width / 2.0f;
    QVector<VertexData> vertexes;

    vertexes.append(VertexData(QVector3D(width_div_2, -0.1+y, width_div_2), QVector2D(0.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -0.1+y, -width_div_2), QVector2D(0.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -0.1+y, width_div_2), QVector2D(1.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -0.1+y, -width_div_2), QVector2D(1.0, 0.0), QVector3D(0.0, 1.0, 0.0)));

    vertexes.append(VertexData(QVector3D(-width_div_2, 0.1+y, width_div_2), QVector2D(0.0, 1.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, 0.1+y, -width_div_2), QVector2D(0.0, 0.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, 0.1+y, width_div_2), QVector2D(1.0, 1.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, 0.1+y, -width_div_2), QVector2D(1.0, 0.0), QVector3D(0.0, -1.0, 0.0)));

    QVector<GLuint> indexes;
    for(int i = 0; i < 8; i += 4)
    {
        indexes.append(i + 0); indexes.append(i + 1); indexes.append(i + 2);
        indexes.append(i + 2); indexes.append(i + 1); indexes.append(i + 3);
    }

    m_objects.append(new Object3D(vertexes, indexes, QImage(imag)));

}

void Widget::initInside(float x, float y, float z, float width, QString imag)
{
    float width_div_2 = width / 2.0f, q = 0.15;
    QVector<VertexData> vertexes;

    vertexes.append(VertexData(QVector3D(-width_div_2+x, width_div_2+y, width_div_2+z+q), QVector2D(0.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2+x, -width_div_2+y, width_div_2+z+q), QVector2D(0.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2+x, width_div_2+y, -width_div_2+z-q), QVector2D(1.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2+x, -width_div_2+y, -width_div_2+z-q), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));

    QVector<GLuint> indexes;
    indexes.append(0); indexes.append(1); indexes.append(2);
    indexes.append(2); indexes.append(1); indexes.append(3);

    m_objects.append(new Object3D(vertexes, indexes, QImage(imag)));

}
