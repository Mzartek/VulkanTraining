#ifndef VIEWERWINDOW_H
#define VIEWERWINDOW_H

#include <thread>

#include <QObject>

#include <VulkanTraining/GameMode.h>

class ViewerWindow : public QObject
{
    Q_OBJECT

public:
    explicit ViewerWindow(QObject *parent, int width, int height, const QString &windowTitle);
    ~ViewerWindow();

private:
    void onStart();
    void onStop();

    VT::GameMode m_gameMode;
    std::thread m_gameModeThread;
    bool m_gameModeStopping;
};

#endif
