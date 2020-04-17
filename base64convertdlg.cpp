#include "base64convertdlg.h"
#include "ui_base64convertdlg.h"
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QBuffer>
#include <QFile>

Base64ConvertDlg::Base64ConvertDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Base64ConvertDlg)
{
    ui->setupUi(this);
    connect(ui->btnT2P, SIGNAL(clicked()), this, SLOT(onT2P()));
    connect(ui->btnAddPng, SIGNAL(clicked()), this, SLOT(onAddPng()));
    connect(ui->btnP2T, SIGNAL(clicked()), this, SLOT(onP2T()));
    connect(ui->btnSave, SIGNAL(clicked()), this, SLOT(onSave()));
}

Base64ConvertDlg::~Base64ConvertDlg()
{
    delete ui;
}

void Base64ConvertDlg::onAddPng()
{
    QString strFile = QFileDialog::getOpenFileName(this, "get files", ".", "Images (*.png *.jpg)");
    m_strImage = strFile;
    if (!strFile.isEmpty())
    {
        QFile f(strFile);
        if (f.open(QIODevice::ReadOnly))
        {
            m_ary = f.readAll();
            m_img.load(strFile);
            QPixmap pix(strFile);
            if (!pix.isNull())
            {
                ui->lblPixmap->setPixmap(pix);
            }
        }
    }
}

void Base64ConvertDlg::onP2T()
{
    if (!m_img.isNull())
    {
#if 0
        QByteArray bytes;
        QBuffer buffer(&bytes);
        buffer.open(QIODevice::WriteOnly);
        m_img.save(&buffer, "PNG"); // writes pixmap into bytes in PNG format
        buffer.close();

        bytes = bytes.toBase64();
        ui->textEdit->setText(bytes.constData());
#else
        QFile file(m_strImage);
        if (file.open(QIODevice::ReadOnly))
        {
            QByteArray ary = file.readAll().toBase64();
            ui->textEdit->setText(ary.constData());
        }
#endif
    }
}
void Base64ConvertDlg::onT2P()
{
    QString str = ui->textEdit->toPlainText().trimmed();
    if (!str.isEmpty())
    {
        QByteArray ary = str.toAscii();
        m_ary = QByteArray::fromBase64(ary);
        QPixmap pix;
        pix.loadFromData(m_ary);
        ui->lblPixmap->setPixmap(pix);
    }
}

void Base64ConvertDlg::onSave()
{
    if (!m_ary.isEmpty())
    {
        QString strFile = QFileDialog::getSaveFileName(this, "Save");
        if (!strFile.isEmpty())
        {
            QFile f(strFile);
            if (f.open(QIODevice::WriteOnly))
            {
                f.write(m_ary);
            }
        }
    }
}