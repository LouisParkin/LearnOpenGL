#include "GLWidget.h"
#include <GL/glut.h>

#include "ogldev_util.h"
#include "ogldev_math_3d.h"

int GLWidget::_myGlutWindow = 0;
GLuint GLWidget::_VBO = 0;
GLuint GLWidget::_gScaleLocation;

const char* pVSFileName = "/home/lparkin/Projects/S3/LearnOpenGL/shader.vs";
const char* pFSFileName = "/home/lparkin/Projects/S3/LearnOpenGL/shader.fs";

GLWidget::GLWidget(QWidget* parent)
  : QOpenGLWidget(parent)
{

}

GLWidget::~GLWidget()
{

}

void GLWidget::initializeGL()
{
  glClearColor(0.84, 0.84, 0.84, 0);
}

void GLWidget::glutRender()
{
  glClear(GL_COLOR_BUFFER_BIT);

  static float scale = 0.0f;

  scale += 0.001f;

  glUniform1f(_gScaleLocation, sinf(scale));

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, _VBO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glDrawArrays(GL_TRIANGLES, 0, 3);

  glDisableVertexAttribArray(0);

  glutSwapBuffers();
}

void GLWidget::initGlut()
{
  glutInitWindowSize(1024, 768);
  glutInitWindowPosition(100, 100);
  _myGlutWindow = glutCreateWindow("Tutorial");

  glutDisplayFunc(glutRender);
  glutIdleFunc(glutRender);
}

void GLWidget::initGlew()
{
  GLenum res = glewInit();
  Q_ASSERT_X(res == GLEW_OK, "GLWidget::GLWidget()", "GLWidget could not initialize glew");
}

void GLWidget::startGlutLoop()
{
  glClearColor(0.0f/*.84*/, 0.0f/*.84*/, 0.0f/*.84*/, 0.0f);

  char* version = (char*)glGetString(GL_VERSION);
  fprintf(stdout, "Version: '%s'\n", version);

  createVertexBuffer();

  compileShaders();

  glutMainLoop();
}

void GLWidget::stopGlutLoop()
{
  glutDestroyWindow(_myGlutWindow);
}

void GLWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT);
  paintATeapot(0.6);
//  paintTriangle( -0.5, 0.5, -0.5, 0.5);

}

void GLWidget::createVertexBuffer()
{
  Vector3f Vertices[3];
  Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
  Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
  Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);

  glGenBuffers(1, &_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, _VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

void GLWidget::compileShaders()
{
  GLuint ShaderProgram = glCreateProgram();

  if (ShaderProgram == 0) {
    fprintf(stderr, "Error creating shader program\n");
    exit(1);
  }

  std::string vs, fs;

  if (!ReadFile(pVSFileName, vs)) {
    exit(1);
  };

  if (!ReadFile(pFSFileName, fs)) {
    exit(1);
  };

  AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
  AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

  GLint Success = 0;
  GLchar ErrorLog[1024] = { 0 };

  glLinkProgram(ShaderProgram);
  glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
  if (Success == 0) {
    glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
    fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
    exit(1);
  }

  glValidateProgram(ShaderProgram);
  glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
  if (!Success) {
    glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
    fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
    exit(1);
  }

  glUseProgram(ShaderProgram);

  _gScaleLocation = glGetUniformLocation(ShaderProgram, "gScale");
  assert(_gScaleLocation != 0xFFFFFFFF);
}

void GLWidget::resizeGL()
{

}

void GLWidget::paintATeapot(double size)
{
  glColor3f(0.0, 0.0, 0.0);
  glutWireTeapot(size);
}

void GLWidget::paintTriangle(float yMin, float yMax, float xMin, float xMax)
{
  glBegin(GL_TRIANGLES);
  {
    glColor3f(1, 0, 0);
    glVertex3f(xMin, yMin, 0);

    glColor3f(0, 1, 0);
    glVertex3f(xMax, yMin, 0);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    glColor3f(0, 0, 1);
//    glVertex3f((abs(xMax) - abs(xMin)), yMax, 0);
  }
  glEnd();
}

void GLWidget::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
  GLuint ShaderObj = glCreateShader(ShaderType);

  if (ShaderObj == 0) {
    fprintf(stderr, "Error creating shader type %d\n", ShaderType);
    exit(1);
  }

  const GLchar* p[1];
  p[0] = pShaderText;
  GLint Lengths[1];
  Lengths[0] = strlen(pShaderText);
  glShaderSource(ShaderObj, 1, p, Lengths);
  glCompileShader(ShaderObj);
  GLint success;
  glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
  if (!success) {
    GLchar InfoLog[1024];
    glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
    fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
    exit(1);
  }

  glAttachShader(ShaderProgram, ShaderObj);
}

