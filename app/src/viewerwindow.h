#ifndef VIEWERWINDOW_H
#define VIEWERWINDOW_H

#include <QObject>

#include <VulkanTraining/GameMode.h>

class ViewerWindow : public QObject
{
    Q_OBJECT

public:
    explicit ViewerWindow(QObject *parent, int width, int height, const QString &windowTitle);

private:
    VT::GameMode m_gameMode;
};

#endif
