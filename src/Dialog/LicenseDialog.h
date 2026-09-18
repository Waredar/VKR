#pragma once

#include <QDialog>

class QLineEdit;
class QPushButton;

class LicenseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LicenseDialog(QWidget* parent = nullptr);

    QString key() const;
    QString signature() const;

private:
    QLineEdit* m_keyEdit;
    QLineEdit* m_signatureEdit;
    QPushButton* m_okButton;
};