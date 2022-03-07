#include "config.h"

Config* Config::m_pInstance = Q_NULLPTR;
bool Config::m_newAllocate = false;

const QString Config::NETWORK_GROUP = "NETWORK_GROUP";
const QString Config::MANAGER_ADDRESS = "MANAGER_ADDRESS";
const QString Config::UDP_SEND_PORT = "UDP_SEND_PORT";
const QString Config::UDP_RECEIVE_PORT = "UDP_RECEIVE_PORT";
const QString Config::PYTHON_SEND_PORT = "PYTHON_SEND_PORT";

const QString Config::TIMER_GROUP = "TIMER_GROUP";
const QString Config::VIDEO_TIMER = "VIDEO_TIMER";
const QString Config::IMAGE_TIMER = "IMAGE_TIMER";

Config::Config(const QString& fileName) : ConfigLib(fileName)
{
    if(m_pInstance != Q_NULLPTR)
        return;
    m_pInstance = this;
    loadConfigure();
}

Config *Config::Instance(const QString& fileName)
{
    if (m_pInstance == Q_NULLPTR)
    {
        m_newAllocate = true;
        new Config(fileName);
    }
    return m_pInstance;
}

void Config::Release()
{
    if(m_newAllocate && m_pInstance != Q_NULLPTR)
    {
        m_newAllocate = false;
        delete m_pInstance;
    }
    m_pInstance = Q_NULLPTR;
}

Config::~Config()
{
    Config::Release();
}

void Config::loadConfigure()
{
    ManagerAddress = getSetting(MANAGER_ADDRESS, "127.0.0.1", NETWORK_GROUP);
    UdpSendPort = getSetting(UDP_SEND_PORT, "4001", NETWORK_GROUP).toInt();
    UdpReceivePort = getSetting(UDP_RECEIVE_PORT, "1234", NETWORK_GROUP).toInt();
    PythonSendPort = getSetting(PYTHON_SEND_PORT, "2902", NETWORK_GROUP).toInt();

    VideoTimer = getSetting(VIDEO_TIMER, "40", TIMER_GROUP).toInt();
    ImageTimer = getSetting(IMAGE_TIMER, "1000", TIMER_GROUP).toInt();
}

void Config::LoadConfigure()
{
    Instance()->loadConfigure();
}

void Config::saveConfigure()
{
    saveSetting(MANAGER_ADDRESS, ManagerAddress, NETWORK_GROUP);
    saveSetting(UDP_SEND_PORT, QString::number(UdpSendPort), NETWORK_GROUP);
    saveSetting(UDP_RECEIVE_PORT, QString::number(UdpReceivePort), NETWORK_GROUP);
    saveSetting(PYTHON_SEND_PORT, QString::number(PythonSendPort), NETWORK_GROUP);

    saveSetting(VIDEO_TIMER, QString::number(VideoTimer), TIMER_GROUP);
    saveSetting(IMAGE_TIMER, QString::number(ImageTimer), IMAGE_TIMER);
}
