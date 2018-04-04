#include "viewerwindow.h"

ViewerWindow::ViewerWindow(QWidget *parent, const QString &windowTitle) :
    QWidget(parent),
    m_gameMode(this->size().width(), this->size().height(), windowTitle.toStdString(), "")
{
}
