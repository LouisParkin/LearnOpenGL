#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QFuture>
#include <GL/glew.h>
#include <QOpenGLWidget>

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

  void stopGlutLoop();
  void initGlew();
  void initGlut();
private:
  QFuture<void> _future;
  static int _myGlutWindow;
  bool _cancelled;

  static GLuint _VBO;
  static void createVertexBuffer();
  static void compileShaders();
  static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
};

#endif // GLWIDGET_H
