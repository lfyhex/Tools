#include "binaryfileeditdlg.h"
#include "ui_binaryfileeditdlg.h"
#include <QMessageBox>
#include <QFile>
#include <QMap>
#include <QDropEvent>
#include <QMimeData>
#include <QUrl>

BinaryFileEditDlg::BinaryFileEditDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BinaryFileEditDlg)
{
    ui->setupUi(this);
    connect(ui->btnEidt,SIGNAL(clicked()),this,SLOT(onEdit()));
    setAcceptDrops(true);
}

BinaryFileEditDlg::~BinaryFileEditDlg()
{
    delete ui;
}

void BinaryFileEditDlg::onEdit()
{
    if (m_strFilePath.isEmpty())
    {
        QMessageBox::information(this, "info", "No input file!");
        return;
    }
    QString strCfg = ui->plainTextEdit->toPlainText();
    QStringList lst = strCfg.split(";", QString::SkipEmptyParts);
    QMap<QString, QString> mapCfg;
    for (int i = 0; i < lst.count(); i++)
    {
        QStringList lstKV = lst.at(i).split("--->", QString::SkipEmptyParts);
        if (lstKV.count() == 2)
        {
            mapCfg.insert(lstKV.at(0).trimmed(), lstKV.at(1).trimmed());
        }
    }
    QMapIterator<QString, QString> iter(mapCfg);
    QString strTxt("config is:");
    while (iter.hasNext())
    {
        iter.next();
        strTxt += QString("\n<key is: %1, value is: %2>").arg(iter.key()).arg(iter.value());
    }
    ui->plainTextEdit->setPlainText(strTxt);
    int nReply = QMessageBox::question(window(), QString("Sure"), QString("Are you sure to edit the file, you may first save it?"), QMessageBox::Yes | QMessageBox::No);
    if (nReply == QMessageBox::Yes)
    {
        QString strErr("Sucess.");
        if (mapCfg.count() > 0)
        {
            QStringList lstNotExsitKey;
            QFile file(m_strFilePath);
            if (file.open(QIODevice::ReadOnly))
            {

                QByteArray ary = file.readAll();
                file.close();
                int nConstFilesSize = ary.count();

                QMapIterator<QString, QString> iter(mapCfg);
                while (iter.hasNext())
                {
                    iter.next();
                    QByteArray aryKey = iter.key().toAscii();
                    QByteArray aryVal = iter.value().toAscii();

                    int nidx = ary.indexOf(aryKey);
                    if (nidx > 0)
                    {
                        int nReplaceIndex = nidx + aryKey.count();
                        ary.replace(nReplaceIndex, aryVal.count(), aryVal);
                    }
                    else
                    {
                        lstNotExsitKey << iter.key();
                    }
                }

                if (nConstFilesSize != ary.count())
                {
                    strErr = "File size changed!!!!";
                }
                else if (lstNotExsitKey.count() > 0)
                {
                    strErr = "cfg:";
                    for (int i = 0; i < lstNotExsitKey.count(); i++)
                    {
                        strErr += lstNotExsitKey.at(i) + ",";
                    }
                    strErr += "Not exist";
                }
                else
                {
                    file.open(QIODevice::WriteOnly);
                    file.write(ary);
                    file.close();
                }
            }
        }
        else
        {
            strErr = "No cfg.";
        }
        QMessageBox::information(this, "Result", strErr);
    }
}

void BinaryFileEditDlg::dropEvent(QDropEvent *pEvent)
{
    QList<QUrl> urls = pEvent->mimeData()->urls();
    if (urls.isEmpty())
        return;

    pEvent->setDropAction(Qt::CopyAction);
    pEvent->accept();

    QStringList lstFiles;
    foreach (QUrl url, urls)
    {
        lstFiles << url.toLocalFile();
    }

    QString strT;
    if (lstFiles.count() > 0)
    {
        strT = lstFiles.at(0);
    }

    if (!strT.isEmpty())
    {
        m_strFilePath = strT;
        ui->lblFileName->setText(strT);
    }
}

void BinaryFileEditDlg::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())//hasFormat("text/uri-list"))
    {
        event->setDropAction(Qt::CopyAction);
        event->accept();
    }
}