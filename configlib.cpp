#include "configlib.h"
#include <QSettings>

ConfigLib::ConfigLib(const QString &filename)
    : m_SettingFile(filename)
{
}

void ConfigLib::saveSetting(const QString &key, const QString &value, const QString &group)
{
    QSettings settings(m_SettingFile, QSettings::IniFormat);
    settings.beginGroup(group);
    settings.setValue(key,value);
    settings.endGroup();
    m_SettingList.insert(key, value);
}

void ConfigLib::getSettingsListInGroup(const QString &group)
{
    QSettings settings(m_SettingFile, QSettings::IniFormat);
    settings.beginGroup(group);
    QStringList content = settings.allKeys();
    foreach (const QString &childKey, content)
    {
        QString value = settings.value(childKey).toString();
        m_SettingList.insert(childKey,value);
    }
    settings.endGroup();
 }

const QString ConfigLib::getSetting(const QString key, const QString value, const QString group)
{
    if(!m_SettingList.contains(key))
    {
        getSettingsListInGroup(group);
        if(m_SettingList.contains(key))
            return m_SettingList.value(key);
        else
        {
            saveSetting(key,value,group);
            return value;
        }
    }
    return m_SettingList.value(key);
}

void ConfigLib::setFileName(const QString &filename)
{
    m_SettingFile = filename;
}
