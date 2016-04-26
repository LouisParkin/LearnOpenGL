#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QFuture>
#include <GL/glew.h>
#include <QOpenGLWidget>
#include "ogldev_util.h"
#include "ogldev_pipeline.h"
#include "ogldev_math_3d.h"
#include <QThread>

#include "AppFilter.h"

class GLWidget : public QOpenGLWidget
{
  Q_OBJECT
public:
  GLWidget(QWidget* parent = 0);
  ~GLWidget();

  void initializeGL();
  void paintGL();
  void resizeGL();

  static void paintTriangle(float yMin, float yMax, float xMin, float xMax);
  static void paintATeapot(double size);
  static void glutRender();
  static void startGlutLoop(GLWidget* me);

  void stopGlutLoop();
  void initGlew();
  void initGlut();

private slots:
  void adjustValueUp();
  void adjustValueDown();
  void adjustValueLeft();
  void adjustValueRight();

private:
  QFuture<void> _future;
  static int _myGlutWindow;
  bool _cancelled;

  static AppFilter* _filter;

  static GLuint _VBO, _IBO;
  static GLuint _gWorldLocation;
  static GLuint _gScaleLocation;
  static PersProjInfo _gPersProjInfo;
  static float _gAdjustX;
  static float _gAdjustY;
  static QThread* _thread;

  static void createVertexBuffer();
  static void compileShaders();
  static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
  static void createIndexBuffer();
  void timerEvent(QTimerEvent* event);
};

#endif // GLWIDGET_H
