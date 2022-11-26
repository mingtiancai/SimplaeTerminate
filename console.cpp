#include "console.h"

#include <QDebug>

Console::Console(QWidget *parent) : QPlainTextEdit(parent) {
  document()->setMaximumBlockCount(100);
  QPalette p = palette();
  p.setColor(QPalette::Base, Qt::black);
  p.setColor(QPalette::Text, Qt::green);
  setPalette(p);
}

void Console::keyPressEvent(QKeyEvent *e) {
  switch (e->key()) {
    case Qt::Key_Backspace:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
      break;
    default:
      QPlainTextEdit::keyPressEvent(e);
  }
}

void Console::mousePressEvent(QMouseEvent *e) {
  Q_UNUSED(e);
  setFocus();
}

void Console::mouseDoubleClickEvent(QMouseEvent *e) { Q_UNUSED(e); }

void Console::contextMenuEvent(QContextMenuEvent *e) { Q_UNUSED(e); }
