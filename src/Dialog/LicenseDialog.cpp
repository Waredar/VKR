#include "LicenseDialog.h"

#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>

LicenseDialog::LicenseDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("License Activation");
    setModal(true);
    resize(300, 150);

    m_keyEdit = new QLineEdit(this);
    m_keyEdit->setPlaceholderText("License key");

    m_signatureEdit = new QLineEdit(this);
    m_signatureEdit->setPlaceholderText("Signature");

    m_okButton = new QPushButton("OK", this);

    auto* layout = new QVBoxLayout(this);
    layout->addWidget(m_keyEdit);
    layout->addWidget(m_signatureEdit);
    layout->addWidget(m_okButton);

    connect(m_okButton, &QPushButton::clicked, this, [this]()
        {
            if (m_keyEdit->text().isEmpty() || m_signatureEdit->text().isEmpty())
                return;

            accept();
        });
}

QString LicenseDialog::key() const
{
    return m_keyEdit->text();
}

QString LicenseDialog::signature() const
{
    return m_signatureEdit->text();
}