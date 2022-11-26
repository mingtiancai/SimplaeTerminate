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

  m_normalTextColor = QColor("green");
  m_errorTextColor = QColor("red");

  m_fmt.setForeground(QBrush(m_normalTextColor));
  this->mergeCurrentCharFormat(m_fmt);

  m_userName = "gaoming";
  m_userID = "$" + m_userName + ":";
  this->appendPlainText(m_userID);

  QFont font;
  font.setFamily("微软雅黑");
  this->setFont(font);
}

void Console::setUserName(QString name) { m_userName = name; }

QString Console::getUserName() const { return m_userName; }

void Console::keyPressEvent(QKeyEvent *e) {
  switch (e->key()) {
    case Qt::Key_Backspace: {
      QString curLineText =
          this->document()
              ->findBlockByLineNumber(this->document()->lineCount() - 1)
              .text();
      if (curLineText == QString(m_userID))
        break;
      else
        QPlainTextEdit::keyPressEvent(e);
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

      QString commandNew = command.replace(m_userID, "");

      m_pProcess->start("cmd", QStringList() << "/c" << commandNew);
      m_pProcess->waitForStarted();
      m_pProcess->waitForFinished();
      QString stdOutStr =
          QString::fromLocal8Bit(m_pProcess->readAllStandardOutput());
      QString stdErrorStr =
          QString::fromLocal8Bit(m_pProcess->readAllStandardError());

      QString outputStr;

      if (stdOutStr == "") {
        outputStr = stdErrorStr;
        m_fmt.setForeground(QBrush(m_errorTextColor));
      } else {
        outputStr = stdOutStr;
        m_fmt.setForeground(QBrush(m_normalTextColor));
      }

      outputStr = outputStr + "\n";

      this->mergeCurrentCharFormat(m_fmt);
      this->appendPlainText(outputStr);

      m_fmt.setForeground(QBrush(m_normalTextColor));
      this->mergeCurrentCharFormat(m_fmt);
      this->appendPlainText(m_userID);

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
