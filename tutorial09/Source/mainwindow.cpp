#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  this->setVisible(false);
  ui->pushButton->setVisible(false);
  ui->pushButton_2->setVisible(false);

  startTimer(200);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_pushButton_clicked()
{
  ui->_glWidget->stopGlutLoop();
  QApplication::exit(0);
}

void MainWindow::on_pushButton_2_clicked()
{

}

void MainWindow::timerEvent(QTimerEvent* event)
{
  killTimer(event->timerId());

  ui->_glWidget->initGlut();
  ui->_glWidget->initGlew();

  ui->_glWidget->startGlutLoop();

  QApplication::exit(0);
}
