#ifndef HELPDLG_H
#define HELPDLG_H

#include <QDialog>

namespace Ui {
    class HelpDlg;
}

class HelpDlg : public QDialog
{
    Q_OBJECT

public:
    explicit HelpDlg(QWidget *parent = 0);
    ~HelpDlg();
private slots:
	void onHelp_RemoveFile();
	void onHelp_CopyXML();
	void onHelp_ClearOutPut();
	void onHelp_Rename();
	void onHelp_Update();
	void onHelp_EncryString();
	void onHelp_ProductEx();
	void onHelp_GernerateFiles();
	void onHelp_ToRcc();
	void onHelp_RenameFile();
private:
    Ui::HelpDlg *ui;
};

#endif // HELPDLG_H
