#ifndef BINARYFILEEDITDLG_H
#define BINARYFILEEDITDLG_H

#include <QDialog>

namespace Ui {
    class BinaryFileEditDlg;
}

class BinaryFileEditDlg : public QDialog
{
    Q_OBJECT

public:
    explicit BinaryFileEditDlg(QWidget *parent = 0);
    ~BinaryFileEditDlg();

protected:
    void dropEvent(QDropEvent*);
    void dragEnterEvent(QDragEnterEvent*);

private slots:
    void onEdit();

private:
    Ui::BinaryFileEditDlg *ui;
    QString m_strFilePath;
};

#endif // BINARYFILEEDITDLG_H
