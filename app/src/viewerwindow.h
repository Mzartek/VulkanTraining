#ifndef VIEWERWINDOW_H
#define VIEWERWINDOW_H

#include <QObject>

#include <VulkanTraining/GameMode.h>

class ViewerWindow : public QObject, public VT::GameMode
{
    Q_OBJECT

public:
    explicit ViewerWindow(QObject *parent, int width, int height, const QString &windowTitle);
    ~ViewerWindow();

private:
    void OnStart() override;
    void OnStop() override;
};

#endif
