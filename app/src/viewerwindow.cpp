#include "viewerwindow.h"

ViewerWindow::ViewerWindow(QWidget *parent, const QString &windowTitle)
    : QWidget(parent),
#if defined(Q_OS_WIN)
    m_gameMode(windowTitle.toStdString(), reinterpret_cast<VT::winid_t>(this->winId()), VT::SurfacePlatform::WIN32, "")
#elif defined(Q_OS_LINUX)
    m_gameMode(windowTitle.toStdString(), reinterpret_cast<VT::winid_t>(this->winId()), VT::SurfacePlatform::XLIB, "")
#endif
{
}
