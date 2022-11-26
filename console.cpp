#include "console.h"

#include <QDebug>
#include <QProcess>
#include <QTextBlock>

Console::Console(QWidget *parent) : QPlainTextEdit(parent) {
  QPalette p = palette();
  p.setColor(QPalette::Base, Qt::black);
  p.setColor(QPalette::Text, Qt::green);
  setPalette(p);
}

void Console::keyPressEvent(QKeyEvent *e) {
  switch (e->key()) {
    case Qt::Key_Backspace: {
      qDebug() << "back";
      break;
    }
    case Qt::Key_Enter: {
      qDebug() << "enter";
      break;
    }
    case Qt::Key_Return: {
      QString command =
          this->document()
              ->findBlockByLineNumber(this->document()->lineCount() - 1)
              .text();
      QProcess p(0);
      p.start("cmd", QStringList() << "/c" << command);
      p.waitForStarted();
      p.waitForFinished();
      QString strTemp = QString::fromLocal8Bit(p.readAllStandardOutput());
      this->appendPlainText(strTemp);
      break;
    }
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
