#include "console.h"

#include <QDebug>
#include <QProcess>
#include <QTextBlock>

Console::Console(QWidget *parent) : QPlainTextEdit(parent) {
  QPalette p = palette();
  p.setColor(QPalette::Base, Qt::black);
  p.setColor(QPalette::Text, Qt::green);
  setPalette(p);

  m_pProcess = new QProcess();

  m_userName = "gaoming";
  this->appendPlainText(m_userName + ":");
}

void Console::setUserName(QString name) { m_userName = name; }

QString Console::getUserName() const { return m_userName; }

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

      QString commandNew = command.replace(m_userName + ":", "");

      m_pProcess->start("cmd", QStringList() << "/c" << commandNew);
      m_pProcess->waitForStarted();
      m_pProcess->waitForFinished();
      QString strTemp =
          QString::fromLocal8Bit(m_pProcess->readAllStandardOutput());
      QString outputStr = strTemp + "\n" + m_userName + ":";
      this->appendPlainText(outputStr);
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
