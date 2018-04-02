#ifndef VIEWERWINDOW_H
#define VIEWERWINDOW_H

#include <QWidget>

#include <VulkanTraining/GameMode.h>

class ViewerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ViewerWindow(QWidget *parent, const QString &windowTitle);

private:
    VT::GameMode m_gameMode;
};

#endif
