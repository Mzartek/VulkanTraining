#include "viewerwindow.h"

ViewerWindow::ViewerWindow(QObject *parent, int width, int height, const QString &windowTitle) :
    QObject(parent),
    m_gameMode(width, height, windowTitle.toStdString(), "./shaders")
{
}
