#include "LicenseManager.h"

#include <tool_enabler.h>

#include <QFile>
#include <QTextStream>
#include <QStandardPaths>

QString LicenseManager::filePath() const
{
    QString home = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    return home + "/c3d.lic";
}

bool LicenseManager::loadFromFile(QString& key, QString& signature)
{
    QFile file(filePath());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);

    key = in.readLine().trimmed();
    signature = in.readLine().trimmed();

    return !key.isEmpty() && !signature.isEmpty();
}

bool LicenseManager::saveToFile(const QString& key, const QString& signature)
{
    QFile file(filePath());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);
    out << key << "\n";
    out << signature << "\n";

    return true;
}

void LicenseManager::removeFile()
{
    QFile::remove(filePath());
}

LicenseManager::Result LicenseManager::activate(const QString& key, const QString& signature)
{

    QByteArray keyB = key.toUtf8();
    QByteArray sigB = signature.toUtf8();

    EnableMathModules(
        keyB.constData(),
        keyB.size(),
        sigB.constData(),
        sigB.size()
    );

    m_active = IsMathVisionEnable();
    
    if (m_active)
        saveToFile(key, signature);

    return m_active
        ? Result::Success
        : Result::Invalid;
}

bool LicenseManager::activateFromFile()
{
    QString key;
    QString signature;

    if (!loadFromFile(key, signature))
        return false;

    QByteArray keyB = key.toUtf8();
    QByteArray sigB = signature.toUtf8();

    EnableMathModules(
        keyB.constData(),
        keyB.size(),
        sigB.constData(),
        sigB.size()
    );

    m_active = IsMathVisionEnable();

    return m_active;
}


void LicenseManager::clear()
{
    DisableMathModules();
    removeFile();

    m_active = false;
}

bool LicenseManager::isActive() const
{
    return m_active && IsMathVisionEnable();
}