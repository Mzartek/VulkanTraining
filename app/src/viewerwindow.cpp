#include "viewerwindow.h"

#include <QApplication>

ViewerWindow::ViewerWindow(QObject *parent, int width, int height, const QString &windowTitle) :
    QObject(parent),
    VT::GameMode(width, height, windowTitle.toStdString().c_str(), "./shaders")
{
    this->Start();
}

ViewerWindow::~ViewerWindow()
{
    this->Stop();
}

void ViewerWindow::OnStart()
{
}

void ViewerWindow::OnStop()
{
    QApplication::quit();
}
