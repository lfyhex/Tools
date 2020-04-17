#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QPoint>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void onImport() const;
    void onExport() const;
    void onRun();
    void onEnterted();
    void onDel();
    void funTest();
    void onDelFileInDirAndSub();
    void onCopyXML();
	void onClear();
	void onReNameWithFiles();
	void updateTree();
	void onactEncryString();
	void onactProduct();
	void onactRccGenFiles();
	void onactToRcc();
	void onactHelp();
	void onRenameFileName();
    void onSrcCustomMenu(const QPoint&);
    void onDesCustomMenu(const QPoint&);
    void onOpenFolder();

    void onFiletoDir();
	void onEncodeURL();
	void onDecodeURL();

    void onBase64();
    void onEditBinaryFile();

	//void onDeleteStringInFiles();
    

protected:
    QStringList getSel(QTreeView *tv);
    void cpFiles(QString srcDir,QString destDir);
    void cpDirAndFiles(QString srcDir,QString destDir);
    void deleteAll(QString srcDir);
    void deleteFile(QString srcDir);
    void deleteSpecialFiles(const QString &strDir,const QStringList &lstFiles);
    void copyAffiliate(const QString &strDir);
	void renameWithDirAndFiles(const QString& strDir);
	void rccGenFiles(QString srcDir,QString destDir);
	void renameFile(QString dirPath,QString old,QString newName);
	
private:
    Ui::MainWindow *ui;
    QDirModel *m_pDirModel;
	QSplitter *m_splitter;
	QStringList *m_pLstStr;
	QStringList m_lstProduct;
    QPoint m_Point;
    bool m_bSrc;
};

#endif // MAINWINDOW_H
