#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include "configlib.h"
#include <QHash>


class Config : public ConfigLib
{
public:
    explicit Config(const QString& fileName = "config.ini");
    static Config* Instance(const QString& fileName = "config.ini");
    static void Release();
    void loadConfigure();
    static void LoadConfigure();
    void saveConfigure();
    static void SaveConfigure();

private:
    ~Config();

public slots:

private:
    static bool m_newAllocate;
    static Config *m_pInstance;

public:
    //Network group
    static const QString NETWORK_GROUP;
    static const QString MANAGER_ADDRESS;
    static const QString UDP_SEND_PORT;
    static const QString UDP_RECEIVE_PORT;
    static const QString PYTHON_SEND_PORT;

    //Timer group
    static const QString TIMER_GROUP;
    static const QString VIDEO_TIMER;
    static const QString IMAGE_TIMER;

public:
    QString ManagerAddress = "";
    uint UdpSendPort = 0;
    uint UdpReceivePort = 0;
    uint PythonSendPort = 0;

    uint VideoTimer = 0;
    uint ImageTimer = 0;
};

#endif // CONFIG_H
