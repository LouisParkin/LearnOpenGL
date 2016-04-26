///
/// \file   AppFilter.h
/// \author Louis Parkin (louis.parkin@stonethree.com)
/// \date   April 2016
/// This file contains the inner class and member definitions of the AppFilter class
///

#ifndef APPFILTER_H
#define APPFILTER_H

#include <QObject>

///
/// The AppFilter class is a small class for filtering events in an application.
///
class AppFilter : public QObject
{
    Q_OBJECT
public:

  ///
  /// AppFilter is the default constructor for AppFilter objects.
  ///
  /// \param parent is the QObject that will eventually destroy the pointer to AppFilter (if not null).
  ///
  AppFilter(QObject* parent = 0);

  ///
  /// ~AppFilter is the default destructor for AppFilter objects.
  ///
  virtual ~AppFilter();

  signals:

  void upPressed();
  void downPressed();
  void leftPressed();
  void rightPressed();

protected:

  ///
  /// eventFilter filters events if this object has been installed as an event filter for the watched object.
  ///
  /// \param watched the Object that the event filter has been installed on.
  /// \param event is any event that took place on the given object, like keystrokes, mouse activity etc.
  /// \return true if an event should not be handled further, False if the event should be processed.
  ///
  virtual bool eventFilter(QObject* watched, QEvent* event);
  private:
  void whichKey(QEvent* event);
};

#endif // APPFILTER_H
