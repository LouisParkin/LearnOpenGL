///
/// \file   AppFilter.cpp
/// \author Louis Parkin (louis.parkin@stonethree.com)
/// \date   April 2016
/// This file contains the QObject override for function eventFilter()
///

#include "AppFilter.h"

#include <QEvent>
#include <QKeyEvent>

AppFilter::AppFilter(QObject *parent)
  : QObject(parent)
{

}

AppFilter::~AppFilter()
{

}

bool AppFilter::eventFilter(QObject* watched, QEvent* event)
{
  // Consider events that need to be blocked when the AI is making a move
  if(event->type() == QEvent::KeyPress)
  {
    whichKey(event);

    //...
    return true; // Return true to indicate an event must be filtered out
  }

  // Do what the QObject eventFilter function would have done anyway.
  return QObject::eventFilter(watched, event);
}

void AppFilter::whichKey(QEvent* event)
{
  QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
  if(keyEvent->key() == Qt::Key_Left)
  {
    emit leftPressed();
  }
  else if(keyEvent->key() == Qt::Key_Up)
  {
    emit upPressed();
  }
  else if(keyEvent->key() == Qt::Key_Down)
  {
    emit downPressed();
  }
  else if(keyEvent->key() == Qt::Key_Right)
  {
    emit rightPressed();
  }
}

