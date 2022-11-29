#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_pConsole(new Console), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  m_pConsole->setEnabled(true);
  setCentralWidget(m_pConsole);
  setWindowTitle("SimpleTerminal");
  QIcon icon = QIcon("C:/projects/SimpleTerminate/terminateLogo.png");
  setWindowIcon(icon);
}

MainWindow::~MainWindow() { delete ui; }
