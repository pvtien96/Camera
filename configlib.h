#ifndef SETTINGLIB_H
#define SETTINGLIB_H

#include <QString>
#include <QHash>

typedef QHash <QString,QString> SettingList;

class ConfigLib
{
public:
    explicit ConfigLib(const QString& filename);

    void saveSetting(const QString &key, const QString &value, const QString &group ="DEFAULT_GROUP");
    void getSettingsListInGroup(const QString &group);
    const QString getSetting(const QString key, const QString value="", const QString group="DEFAULT_GROUP");
    void setFileName(const QString& filename);

protected:
    QString m_SettingFile;
    SettingList m_SettingList;
};

#endif // SETTINGLIB_H
