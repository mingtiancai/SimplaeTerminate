#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_pConsole(new Console)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pConsole->setEnabled(true);
    setCentralWidget(m_pConsole);
}

MainWindow::~MainWindow()
{
    delete ui;
}

