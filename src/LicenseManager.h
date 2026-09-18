#pragma once

class QString;

class LicenseManager
{
public:
    enum class Result
    {
        Success,
        Invalid,
    };

    Result activate(const QString& key, const QString& signature);
    bool activateFromFile();
    bool isActive() const;
    void clear();

private:
    QString filePath() const;
    bool loadFromFile(QString& key, QString& signature);
    bool saveToFile(const QString& key, const QString& signature);
    void removeFile();

private:
    bool m_active = false;
};