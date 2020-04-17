#ifndef PRODUCTEXTENDDLG_H
#define PRODUCTEXTENDDLG_H

#include <QDialog>

namespace Ui {
    class productextenddlg;
}

class productextenddlg : public QDialog
{
    Q_OBJECT

		enum OPType{
			Type_Add=0,
			Type_Delete=1,
			Type_Change=2
	};

public:
    explicit productextenddlg(QWidget *parent = 0);
    ~productextenddlg();
	void init(QStringList &lst);

private slots:
	void onStart();
	void onStatusChange(const QString &);

private:
	void changeFiles(QString &filePath,QString &param,QString &value,OPType type);
	void parseDir(QString dirPath);

private:
    Ui::productextenddlg *ui;
	QStringList m_lstFilse;
};

#endif // PRODUCTEXTENDDLG_H
