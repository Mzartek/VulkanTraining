#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_viewerWindow(nullptr)
{
    ui->setupUi(this);

    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect rect = desktopWidget->availableGeometry(desktopWidget->screenNumber());

    const int viewerWidth = static_cast<float>(rect.width()) * 0.75f;
    const int viewerHeight = static_cast<float>(rect.height()) * 0.75f;
    m_viewerWindow = new ViewerWindow(this, viewerWidth, viewerHeight, "Viewer");
}

MainWindow::~MainWindow()
{
    delete ui;
}
