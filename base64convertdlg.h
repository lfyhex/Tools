#ifndef BASE64CONVERTDLG_H
#define BASE64CONVERTDLG_H

#include <QDialog>

namespace Ui {
    class Base64ConvertDlg;
}

class Base64ConvertDlg : public QDialog
{
    Q_OBJECT

public:
    explicit Base64ConvertDlg(QWidget *parent = 0);
    ~Base64ConvertDlg();

private slots:
    void onAddPng();
    void onP2T();
    void onT2P();
    void onSave();

private:
    Ui::Base64ConvertDlg *ui;
    QImage m_img;
    QString m_strImage;
    QByteArray m_ary;
};

#endif // BASE64CONVERTDLG_H
