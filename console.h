#ifndef CONSOLE_H
#define CONSOLE_H

#include <QPlainTextEdit>
#include <QProcess>

class Console : public QPlainTextEdit {
  Q_OBJECT
 public:
  explicit Console(QWidget *parent = nullptr);

  void setUserName(QString name);
  QString getUserName() const;

 protected:
  void keyPressEvent(QKeyEvent *e) override;
  void mousePressEvent(QMouseEvent *e) override;
  void mouseDoubleClickEvent(QMouseEvent *e) override;
  void contextMenuEvent(QContextMenuEvent *e) override;

 private:
  QString m_userName;
  QProcess *m_pProcess;
};

#endif  // CONSOLE_H
