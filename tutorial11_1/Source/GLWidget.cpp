#include "GLWidget.h"
#include <GL/glut.h>
#include <QThread>

#include "ogldev_util.h"
#include "ogldev_pipeline.h"
#include "ogldev_math_3d.h"

int GLWidget::_myGlutWindow = 0;
GLuint GLWidget::_VBO = 0;
GLuint GLWidget::_IBO = 0;
GLuint GLWidget::_gWorldLocation = 0;

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

/// The function, in this tutorial, used when Idle and when Rendering.
void GLWidget::glutRender()
{
  glClear(GL_COLOR_BUFFER_BIT);

  /// allocate a static variable scale
  static float scale = 0.0f;

  /// increment scale by 0.001.
  scale += 0.001f;

  Pipeline pipeLine;
  pipeLine.Scale(sinf(scale * 0.1f), sinf(scale * 0.1f), sinf(scale * 0.1f));
  pipeLine.WorldPos(sinf(scale), 0.0f, 0.0f);
  pipeLine.Rotate(sinf(scale) * 90.0f, sinf(scale) * 90.0f, sinf(scale) * 90.0f);

  /// Load the matrix into the shader.
  glUniformMatrix4fv(_gWorldLocation, 1, GL_TRUE, (const GLfloat*)pipeLine.GetWorldTrans());

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, _VBO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);

  glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);

  glutSwapBuffers();
  QThread::msleep(5);
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

  /**
   * Create vertex buffer: glGenBuffers, glBindBuffer, glBufferData.
   */
  createVertexBuffer();

  /**
   * Create the index buffer: glGenBuffers, glBindBuffer, glBufferData.
   */
  createIndexBuffer();

  /**
   * Read shaders from file, compile, verify and add to shader program.
   */
  compileShaders();

  /**
   * Start the rendering loop.
   */
  glutMainLoop();
}

void GLWidget::stopGlutLoop()
{
  glutDestroyWindow(_myGlutWindow);
}

void GLWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT);
//  paintATeapot(0.6);
//  paintTriangle( -0.5, 0.5, -0.5, 0.5);

}

void GLWidget::createVertexBuffer()
{
  /**
   * Vector3f is a composite data type that consists of an x, y, and z coordinate.
   * Vertices is an array of three coordinates.
   */
  Vector3f Vertices[4];
  Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
  Vertices[1] = Vector3f(0.0f, -1.0f, 1.0f);
  Vertices[2] = Vector3f(1.0f, -1.0f, 0.0f);
  Vertices[3] = Vector3f(0.0f, 1.0f, 0.0f);

  /**
   * _VBO is a member GLuint that points to the vertex shader buffer (VBO = vertex buffer object)
   * glGenBuffers makes the space available fort allocating to _VBO
   */
  glGenBuffers(1, &_VBO);

  /**
   * glBindBuffer attaches the buffer (_VBO) as a space to be used for Arrayed buffer storage.
   */
  glBindBuffer(GL_ARRAY_BUFFER, _VBO);

  /**
   * glBufferData presents Vertices as the data location from where vertex data will be obtained.
   */
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

void GLWidget::createIndexBuffer()
{
  unsigned int Indices[] = { 0, 3, 1,
                             1, 3, 2,
                             2, 3, 0,
                             0, 1, 2
                           };

  glGenBuffers(1, &_IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}

void GLWidget::compileShaders()
{
  /**
   * Create a new shader program.
   */
  GLuint ShaderProgram = glCreateProgram();


  /// Make sure the shader program creation succeeded.
  if (ShaderProgram == 0) {
    fprintf(stderr, "Error creating shader program\n");
    exit(1);
  }

  /// Make strings for reading the GLSL source from file.
  std::string vs, fs;

  /// Read the vertex shader source from file.
  if (!ReadFile(pVSFileName, vs)) {
    exit(1);
  };

  /// Read the fragment shader source from file.
  if (!ReadFile(pFSFileName, fs)) {
    exit(1);
  };

  /// Add the shaders to the shader program.
  AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
  AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

  GLint Success = 0;
  GLchar ErrorLog[1024] = { 0 };

  glLinkProgram(ShaderProgram); ///< Link the shader program, assuming to the GL Context.
  glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success); ///< Get shader link status.

  /// Handle error if linking failed.
  if (Success == 0) {
    glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
    fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
    exit(1);
  }

  /// A shader program that links is not by definition valid, so validate it.
  glValidateProgram(ShaderProgram);

  /// Retrieve the validation status.
  glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);

  /// Handle the error if validation failed.
  if (!Success) {
    glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
    fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
    exit(1);
  }

  /// Assign a program for OpenGL to use.
  glUseProgram(ShaderProgram);

  /// This tutorial is about the use of Uniform shader attributes (matrices) to transform vertices, retrieve and store it.
  _gWorldLocation = glGetUniformLocation(ShaderProgram, "gWorld");

  /// Ensure it succeeded, handle the possible failure.
  assert(_gWorldLocation != 0xFFFFFFFF);
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

/// This will be called once for the vertex shader and once for the fragment shader.
void GLWidget::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
  /// Create a new shader object
  GLuint ShaderObj = glCreateShader(ShaderType);

  /// Make sure it was created.
  if (ShaderObj == 0) {
    fprintf(stderr, "Error creating shader type %d\n", ShaderType);
    exit(1);
  }

  const GLchar* p[1];
  p[0] = pShaderText; ///< Implicit transfer of shader text from char* to GLchar*
  GLint Lengths[1];
  Lengths[0] = strlen(pShaderText); ///< Store the length of the null terminated string.

  glShaderSource(ShaderObj, 1, p, Lengths);  ///< Link the shader source to the shader object
  glCompileShader(ShaderObj); ///< compile the shader.

  GLint success;
  glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success); ///< Check the compile status to ensure it succeeded.

  /// Handle the error if the shader did not compile successfully.
  if (!success) {
    GLchar InfoLog[1024];
    glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
    fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
    exit(1);
  }

  /// Attach the shader to the shader program.
  glAttachShader(ShaderProgram, ShaderObj);
}

