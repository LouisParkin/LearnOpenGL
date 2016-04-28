#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QFuture>
#include <GL/glew.h>
#include <QOpenGLWidget>
#include "ogldev_util.h"
#include "ogldev_pipeline.h"
#include "ogldev_math_3d.h"

class GLWidget : public QOpenGLWidget
{
public:
  GLWidget(QWidget* parent = 0);
  ~GLWidget();

  void initializeGL();
  void paintGL();
  void resizeGL();

  static void paintTriangle(float yMin, float yMax, float xMin, float xMax);
  static void paintATeapot(double size);
  static void glutRender();
  static void startGlutLoop();

  static void stopGlutLoop();
  void initGlew();
  void initGlut();
private:
  QFuture<void> _future;
  static int _myGlutWindow;
  bool _cancelled;

  static GLuint _VBO, _IBO;
  static GLuint _gWorldLocation;
  static GLuint _gScaleLocation;
  static GLuint _gWVPLocation;
  static PersProjInfo _gPersProjInfo;
  static Camera* _pGameCamera;

  static void createVertexBuffer();
  static void compileShaders();
  static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
  static void createIndexBuffer();
  static void SpecialKeyboardCB(int Key, int x, int y);
};

#endif // GLWIDGET_H
