#include "mainwindow.h"
#include <QApplication>
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <cstdio>

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

  MainWindow w;
  w.show();

  return a.exec();
}
