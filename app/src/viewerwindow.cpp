#include "viewerwindow.h"

#include <QApplication>

ViewerWindow::ViewerWindow(QObject *parent, int width, int height, const QString &windowTitle) :
    QObject(parent),
    m_gameMode(width, height, windowTitle.toStdString(), "./shaders"),
    m_gameModeStopping(false)
{
    m_gameModeThread = std::thread([this]()
    {
        VT::EventCallbacks eventCallbacks = {};
        eventCallbacks.onStart = std::bind(&ViewerWindow::onStart, this);
        eventCallbacks.onStop = std::bind(&ViewerWindow::onStop, this);

        m_gameMode.Launch(eventCallbacks);
    });
}

ViewerWindow::~ViewerWindow()
{
    m_gameMode.Stop();
    m_gameModeThread.join();
}

void ViewerWindow::onStart()
{
    m_gameModeStopping = false;
}

void ViewerWindow::onStop()
{
    if (!m_gameModeStopping)
    {
        m_gameModeStopping = true;
        QApplication::quit();
    }
}
