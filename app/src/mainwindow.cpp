#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_viewerWindow(new ViewerWindow(this, "Viewer"))
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
