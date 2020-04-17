#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDomDocument>
#include <QDomNode>
#include <QIcon>
#include <QTextStream>
#include "productextenddlg.h"
#include "helpdlg.h"
#include "base64convertdlg.h"
#include "binaryfileeditdlg.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
	,m_pDirModel(NULL)
	,m_splitter(NULL)
	,m_pLstStr(NULL)
{
    ui->setupUi(this);
	setWindowTitle("Dir And Files Operate Tools");
    connect(ui->btnImport,SIGNAL(clicked()),this,SLOT(onImport()));
    connect(ui->btnExport,SIGNAL(clicked()),this,SLOT(onExport()));
    connect(ui->btnRun,SIGNAL(clicked()),this,SLOT(onRun()));
    connect(ui->actDel,SIGNAL(triggered()),this,SLOT(onDel()));
    connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(onEnterted()));
    connect(ui->actTest,SIGNAL(triggered()),this,SLOT(funTest()));
    connect(ui->actRemoveFileInDir,SIGNAL(triggered()),this,SLOT(onDelFileInDirAndSub()));
    connect(ui->actCopyXML,SIGNAL(triggered()),this,SLOT(onCopyXML()));
	connect(ui->actClear,SIGNAL(triggered()),this,SLOT(onClear()));
	connect(ui->actReName,SIGNAL(triggered()),this,SLOT(onReNameWithFiles()));
	connect(ui->actUpdate,SIGNAL(triggered()),this,SLOT(updateTree()));
	connect(ui->actEncryString,SIGNAL(triggered()),this,SLOT(onactEncryString()));
	connect(ui->actProductet,SIGNAL(triggered()),this,SLOT(onactProduct()));
	connect(ui->actRccGenFiles,SIGNAL(triggered()),this,SLOT(onactRccGenFiles()));
	connect(ui->actToRcc,SIGNAL(triggered()),this,SLOT(onactToRcc()));
	connect(ui->actOperateMethod,SIGNAL(triggered()),this,SLOT(onactHelp()));
	connect(ui->actionRenameFileNameInDir,SIGNAL(triggered()),this,SLOT(onRenameFileName()));
	connect(ui->actionDelete_string_in_file,SIGNAL(triggered()),this,SLOT(onDeleteStringInFiles()));

    connect(ui->actionBase64DECoder, SIGNAL(triggered()), this, SLOT(onBase64()));
    connect(ui->actionBinaryFileEditor, SIGNAL(triggered()), this, SLOT(onEditBinaryFile()));

    connect(ui->treeViewSrc,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(onSrcCustomMenu(const QPoint&)));
    connect(ui->treeViewDest,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(onDesCustomMenu(const QPoint&)));
    
    connect(ui->btnFiletoDir,SIGNAL(clicked()),this,SLOT(onFiletoDir()));

	bool a = connect(ui->actionEncodeURL,SIGNAL(triggered()),this,SLOT(onEncodeURL()));
	a = connect(ui->actionDecodeURL,SIGNAL(triggered()),this,SLOT(onDecodeURL()));

    m_pDirModel = new QDirModel;
    m_pDirModel->setSorting(QDir::DirsFirst|QDir::Name|QDir::IgnoreCase);
    ui->treeViewSrc->setModel(m_pDirModel);
    ui->treeViewSrc->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->treeViewSrc->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->treeViewSrc->header()->setSortIndicator(0,Qt::AscendingOrder);
    ui->treeViewSrc->header()->setSortIndicatorShown(true);
    ui->treeViewSrc->resizeColumnToContents(true);
    ui->treeViewSrc->setColumnHidden(1,true);
    ui->treeViewSrc->setColumnHidden(2,true);
    ui->treeViewSrc->setColumnHidden(3,true);
    ui->treeViewSrc->setContextMenuPolicy(Qt::CustomContextMenu);

    ui->treeViewDest->setModel(m_pDirModel);
    ui->treeViewDest->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->treeViewDest->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->treeViewDest->header()->setSortIndicator(0,Qt::AscendingOrder);
    ui->treeViewDest->header()->setSortIndicatorShown(true);
    ui->treeViewDest->setColumnHidden(1,true);
    ui->treeViewDest->setColumnHidden(2,true);
    ui->treeViewDest->setColumnHidden(3,true);
    ui->treeViewDest->setContextMenuPolicy(Qt::CustomContextMenu);

	m_splitter = new QSplitter(Qt::Vertical,this);
	m_splitter->addWidget(ui->frmMain);
	m_splitter->addWidget(ui->resultShow);
	//splitter->show();
	setCentralWidget(m_splitter);

}

MainWindow::~MainWindow()
{
	if(m_pDirModel)
	{
		delete m_pDirModel;
		m_pDirModel = NULL;
	}
	if(m_splitter)
	{
		delete m_splitter;
		m_splitter = NULL;
	}
    delete ui;
}

void MainWindow::onImport() const
{
    QString inPath = QFileDialog::getExistingDirectory(0,tr("Select imported file Path"),tr("."));
    if(inPath.isEmpty())
        return;
    QModelIndex index = m_pDirModel->index(inPath);
    ui->treeViewSrc->expand(index);
    ui->treeViewSrc->scrollTo(index);
}
void MainWindow::onExport() const
{
    QString inPath = QFileDialog::getExistingDirectory(0,tr("Select imported file Path"),tr("."));
    if(inPath.isEmpty())
        return;
    QModelIndex index = m_pDirModel->index(inPath);
    ui->treeViewDest->expand(index);
    ui->treeViewDest->scrollTo(index);
}
void MainWindow::onRun()//需选择产品名称
{
    QStringList lstSrcPath = getSel(ui->treeViewSrc);
    QStringList lstDestPath = getSel(ui->treeViewDest);
    if(lstSrcPath.count() == 0 || lstDestPath.count() == 0)
        return;
    QString spDir = QString("Resource");
    if(ui->chkInstall->checkState() == Qt::Checked)
        spDir = QString("Install");
    int num = 0;
    ui->lineEdit->clear();

	if(ui->chkMac->checkState() == Qt::Checked && ui->chkInstall->checkState() != Qt::Checked)
    {
		QString srcPath = lstSrcPath.at(0);//一下导入四种语言
		for(int i=0; i<lstDestPath.count(); i++)
		{
			QString destDir = lstDestPath.at(i) + "/" + spDir;
			cpDirAndFiles(srcPath,destDir);//srcPath包含多语言的help文件夹
		}
	}
    else
    {
        if (ui->chkEnglish->checkState() != Qt::Checked)
        {
			for(int i = 0; i < lstDestPath.count(); i++)
			{
				QString destPath = lstDestPath.at(i);
				for(int j = 0; j < lstSrcPath.count(); j++)
				{
					QString srcPath = lstSrcPath.at(j);            
					QFile srcFile(srcPath);
					QFileInfo srcInfo(srcPath);
					QString srcName = srcInfo.fileName();
					QString destName = destPath + "/" + spDir + "/" + srcName;
					QFile destFile(destPath + "/" + spDir + "/" + srcName);
					if(!srcFile.open(QIODevice::ReadOnly) || !destFile.open(QIODevice::WriteOnly) )
						continue;
					QByteArray arr = srcFile.readAll();
					destFile.write(arr);
					srcFile.close();
					destFile.close();
					ui->resultShow->append(QString("Copy from %1 to %2").arg(srcPath).arg(destName));
					num++;
				}
			}
		}
		else
		{
			QString commanPath = lstDestPath.at(0);
			for(int i = 0; i < m_lstProduct.count(); i++)
			{
				QString destPath = commanPath + "/" + m_lstProduct.at(i);
				for(int j = 0; j < lstSrcPath.count(); j++)
				{
					QString srcPath = lstSrcPath.at(j);            
					QFile srcFile(srcPath);
					QFileInfo srcInfo(srcPath);
					QString srcName = srcInfo.fileName();
					QString destName = destPath + "/" + spDir + "/" + srcName;
					QFile destFile(destPath + "/" + spDir + "/" + srcName);
					if(!srcFile.open(QIODevice::ReadOnly) || !destFile.open(QIODevice::WriteOnly) )
						continue;
					QByteArray arr = srcFile.readAll();
					destFile.write(arr);
					srcFile.close();
					destFile.close();
					ui->resultShow->append(QString("Copy from %1 to %2").arg(srcPath).arg(destName));
					num++;
				}
			}
		}
        ui->resultShow->append(QString("Total file %1").arg(num));
    }
}

void MainWindow::onEnterted()//根据输入名称，需选择大类而不是产品名称
{
    if(ui->chkMac->checkState() == Qt::Checked)
    {
        QString help = ui->lineEdit->text();
        QStringList srcLst = getSel(ui->treeViewSrc);
        QStringList desLst = getSel(ui->treeViewDest);
        if(srcLst.count() == 0 || desLst.count() == 0)
            return;
        QString spDir = QString("Resource");
        if(ui->chkInstall->checkState() == Qt::Checked)
            spDir = QString("Install");
        ui->lineEdit->clear();
        for(int i = 0; i < desLst.count(); i++)//VideoConverter类而不是产品名称
        {
            QString destPath = desLst.at(i);
            for(int j = 0; j < srcLst.count(); j++)
            {
                QString srcPath = srcLst.at(j); //name产品名称           
                QDir src(srcPath);
                QString name = src.dirName();
                QString destName = destPath + "/" + name +"/" + spDir + "/" + help;
                QDir tmp(destName);
                if(tmp.exists())
                    deleteAll(destName);
                QDir helpDir(destPath + "/" + name +"/" + spDir);
                helpDir.mkdir(help);
                helpDir.cd(help);
   
                cpDirAndFiles(srcPath,destName);     
            }
                //ui->resultShow->append(QString("Copy from %1 to %2").arg(srcPath).arg(destName));
                //num++;

            
        }
    }
    else
    {
        QString name = ui->lineEdit->text();
        QStringList lstSrcPath = getSel(ui->treeViewSrc);
        QStringList lstDestPath = getSel(ui->treeViewDest);
        if(lstSrcPath.count() == 0 || lstDestPath.count() == 0)
            return;
        QString spDir = QString("Resource");
        if(ui->chkInstall->checkState() == Qt::Checked)
            spDir = QString("Install");
        int num=0;
        ui->lineEdit->clear();
        for(int i = 0; i < lstDestPath.count(); i++)
        {
            QString destPath = lstDestPath.at(i);
            for(int j = 0; j < lstSrcPath.count(); j++)
            {
                QString srcPath = lstSrcPath.at(j);            
                QFile srcFile(srcPath);
                QFileInfo srcInfo(srcPath);
                QString srcName = srcInfo.baseName();
				m_lstProduct << srcName;
                QString destDirName = destPath + "/" + srcName + "/" +spDir;
                QDir destDir(destPath);
                if(!destDir.exists())
                    continue;
                QString destName = destDirName + "/" + name;
                QFile destFile(destName);
                if(!srcFile.open(QIODevice::ReadOnly) || !destFile.open(QIODevice::WriteOnly) )
                    continue;
                QByteArray arr = srcFile.readAll();
                destFile.write(arr);
                srcFile.close();
                destFile.close();
                ui->resultShow->append(QString("Copy from %1 to %2").arg(srcPath).arg(destName));
                num++;
            }
        }
        ui->resultShow->append(QString("Total file %1").arg(num));
    }
}

QStringList MainWindow::getSel(QTreeView *tv)
{
    QItemSelectionModel* pItemSrc = tv->selectionModel();
    QModelIndexList indexsSrc = pItemSrc->selectedIndexes();
    QStringList lstSrcPath;
    foreach(QModelIndex index , indexsSrc)
    {
        QString filePath = m_pDirModel->filePath(index);
        lstSrcPath << filePath;
    }
    return lstSrcPath;
}

void MainWindow::onDel()//通过读取输入文件名称来删除目标文件(选取产品名称)
{
    bool ok;
    QString name = QString("");
    QString text = QInputDialog::getText(this, tr("delete files"),
        tr("User name:"), QLineEdit::Normal,
        QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty())
        name = text;
    if(!name.isEmpty())
    {
        QStringList lstDestPath = getSel(ui->treeViewDest);
        if(lstDestPath.count() == 0)
            return;
        QString spDir = QString("Resource");
        if(ui->chkInstall->checkState() == Qt::Checked)
            spDir = QString("Install");
        int num=0;
        ui->lineEdit->clear();
        for(int i=0; i<lstDestPath.count(); i++)
        {
            QString filename = lstDestPath.at(i) + "/" + spDir + "/" + name;
            QFile file(filename);
            if(file.exists())
            {
                QFile::remove(filename);
                num++;
                ui->resultShow->append(QString("Delete file %1").arg(filename));
            }
        }

    }

}

void MainWindow::cpFiles(QString srcDir,QString destDir)
{
    QDir src(srcDir);
    QDir dest(destDir);
    if(!src.exists() || !dest.exists())
        return;
    QFileInfoList lstSrcPath = src.entryInfoList(QDir::Files | QDir::Hidden);
    QString destPath = destDir;
        for(int j = 0; j < lstSrcPath.count(); j++)
        {
            QFileInfo srcInfo = lstSrcPath.at(j);
            QString p = srcInfo.absoluteFilePath();
            QFile srcFile(p);
            QString srcName = srcInfo.fileName();
            QString destName = destPath + "/" + srcName;
            QFile destFile(destName);
            if(!srcFile.open(QIODevice::ReadOnly) || !destFile.open(QIODevice::WriteOnly) )
                    continue;
                QByteArray arr = srcFile.readAll();
                destFile.write(arr);
                srcFile.close();
                destFile.close();
                ui->resultShow->append(QString("Copy from %1 to %2").arg(p).arg(destName));
        }
     
}

void MainWindow::cpDirAndFiles(QString srcDir,QString destDir)
{
    QDir src(srcDir);
    QDir dest(destDir);
    if(!src.exists() || !dest.exists())
        return;
    cpFiles(srcDir,destDir);
    QStringList dirLst = src.entryList(QDir::Dirs);
    for(int i=0; i<dirLst.count(); i++)
    {
        QString name = dirLst.at(i);
        QString p = srcDir + "/" + name;
        //QDir n(p);
        //QString name = n.dirName();
        if(name == "." || name == "..")
            continue;
        QString des = destDir + "/" + name;
        QDir d(destDir);
        d.mkdir(name);
        cpDirAndFiles(p,des);
    }
}

void MainWindow::deleteAll(QString srcDir)
{
    QDir src(srcDir);
   
    if(!src.exists())
        return;
    deleteFile(srcDir);
    QStringList dirLst = src.entryList(QDir::Dirs);
    for(int i=0; i<dirLst.count(); i++)
    {
        QString name = dirLst.at(i);
        QString p = srcDir + "/" + name;
        if(name == "." || name == "..")
            continue;
        deleteAll(p);
        src.rmdir(name);
    }
}

void MainWindow::deleteFile(QString srcDir)
{
    QDir src(srcDir);
    QFileInfoList lstSrcPath = src.entryInfoList(QDir::Files);
        for(int j = 0; j < lstSrcPath.count(); j++)
        {
            QFileInfo srcInfo = lstSrcPath.at(j);
            QString p = srcInfo.absoluteFilePath();
            QFile srcFile(p);
            QString srcName = srcInfo.fileName();
            src.remove(srcName);            
            ui->resultShow->append(QString("Delete file %1").arg(p));
        }     
}

void MainWindow::funTest()
{
    QString filename = QFileDialog::getExistingDirectory(this,"test",".");
    if(filename.isEmpty())
        return;
    deleteAll(filename);

}

void MainWindow::onDelFileInDirAndSub()
{
    bool ok;
    QString name = QString("");
    QString text = QInputDialog::getText(this, tr("delete files"),
		tr("eg:a.txt:b.exe"), QLineEdit::Normal,
        QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty())
        name = text;
    QStringList lstFiles = name.split(";");
    QStringList lstDirs = getSel(ui->treeViewSrc);
    for(int j = 0; j < lstDirs.count(); j++)
    {
            QString strDir = lstDirs.at(j);
            deleteSpecialFiles(strDir,lstFiles);     
    }
}

void MainWindow::deleteSpecialFiles(const QString &strDir,const QStringList &lstFiles)
{
    int num = lstFiles.count();
    QDir dir(strDir);
    for(int i=0; i<num; i++)
    {      
        if(dir.exists(lstFiles.at(i)))
        {
           dir.remove(lstFiles.at(i));
           ui->resultShow->append(QString("remove file %1 from %2").arg(lstFiles.at(i)).arg(strDir));
        }      
    }
    QFileInfoList lstFileInfo = dir.entryInfoList(QDir::Dirs);
    for(int j=0; j<lstFileInfo.count(); j++)
    {
        QFileInfo info = lstFileInfo.at(j);
        QString filename = info.fileName();
        if(filename == "." || filename == "..")
            continue;
        QString path = info.filePath();
        deleteSpecialFiles(path,lstFiles);
    }
}

void MainWindow::onCopyXML()
{
    QStringList lstDirs = getSel(ui->treeViewSrc);
    for(int j = 0; j < lstDirs.count(); j++)
    {
        QString strDir = lstDirs.at(j);
        copyAffiliate(strDir);     
    }
}

void MainWindow::copyAffiliate(const QString &strDir)
{
    QDir dir(strDir);
    if(dir.exists("affiliate.xml"))
    {
        QFile file(strDir + "/" + "affiliate.xml");
        //file.copy("affiliate_regnow.xml");
        //changeXMLContents(strDir + "/" + "affiliate_regnow.xml");
        QString s = strDir + "/" + "affiliate.xml";
        QString destFile = strDir + "/" + "affiliate_regnow.xml";
        QFile::copy(s,destFile);
        QFile nFile(destFile);
        if(!nFile.open(QIODevice::ReadOnly))
            return;
        //QByteArray data = nFile.readAll();
        QTextStream in(&nFile);
        QString data = in.readAll();
        nFile.close();
        QDomDocument doc;
        if(!doc.setContent(data))
            return;
        QDomElement root = doc.documentElement();
        QDomElement element = root.firstChildElement("affiliate_type");
        element.setAttribute("value","regnow_2");
        QString test = element.attribute("value");
        QByteArray d = doc.toByteArray();
        if(!nFile.open(QIODevice::WriteOnly))
            return;
        nFile.write(d);
        nFile.close();
        ui->resultShow->append(QString("change affiliate at %1").arg(destFile));
    }
    QFileInfoList lstDir = dir.entryInfoList(QDir::Dirs);
    for(int j=0; j<lstDir.count(); j++)
    {
        QFileInfo info = lstDir.at(j);
        QString filename = info.fileName();
        if(filename == "." || filename == "..")
            continue;
        QString path = info.filePath();
        copyAffiliate(path);
    }

}

void MainWindow::onReNameWithFiles()
{
	QStringList lstDirs = getSel(ui->treeViewSrc);
    for(int j = 0; j < lstDirs.count(); j++)
    {
        QString strDir = lstDirs.at(j);
			renameWithDirAndFiles(strDir); 
    }
}

void MainWindow::renameWithDirAndFiles(const QString& strDir)
{
	QDir dir(strDir);
	if(!dir.exists())
		return;
	QFileInfoList lstFileInfo = dir.entryInfoList(QDir::Dirs);
	for(int j=0; j<lstFileInfo.count(); j++)
    {
        QFileInfo info = lstFileInfo.at(j);
        QString filename = info.fileName();
        if(filename == "." || filename == "..")
            continue;
        QString path = info.absoluteFilePath();
        renameWithDirAndFiles(path);
		QString newname = filename;
		if(filename.contains(" Help",Qt::CaseInsensitive))
			newname.replace(" Help","",Qt::CaseInsensitive);
		QDir d(path);
		d.rename(path,(info.absolutePath() + "/" + newname));
		ui->resultShow->append(QString("Rename dir %1 to %2").arg(filename).arg(newname));
    }
	QFileInfoList lstFileInfoF = dir.entryInfoList(QDir::Files);
	for(int i=0; i<lstFileInfoF.count(); i++)
	{
		QFileInfo f = lstFileInfoF.at(i);
		QString name = f.fileName();
		QString newname =name;
		if(name.contains(" Help",Qt::CaseInsensitive))
			newname = f.absolutePath() + "/" + newname.replace(" Help","",Qt::CaseInsensitive);
		QFile file(f.absoluteFilePath());
		file.rename(newname);
		ui->resultShow->append(QString("Rename file %1 to %2").arg(name).arg(newname));
	}
}


void MainWindow::updateTree()
{
	if(m_pDirModel)
		m_pDirModel->setFilter(QDir::Dirs | QDir::Files |QDir::NoDotAndDotDot);
}

void MainWindow::onClear()
{
	ui->resultShow->clear();
}

void MainWindow::onactEncryString()
{
	QStringList lstFile = getSel(ui->treeViewSrc);
	for(int i = 0; i < lstFile.count(); i++)
	{
		QString strFilePath = lstFile.at(i);
			if(strFilePath.isEmpty())
				return;
		QFile file(strFilePath);
		if(!file.open(QIODevice::Text | QIODevice::ReadWrite))
			return;
		QTextStream in(&file);
		QString strNewFileContents("");
		QString strLinecontent("");
		QString trimedContent("");
		while(!in.atEnd())
		{
			strLinecontent = in.readLine();
			trimedContent = strLinecontent.trimmed();
			if(trimedContent.isEmpty())
				continue;
			trimedContent.replace(" ","_");
			trimedContent += "_3";
			strNewFileContents = strNewFileContents + trimedContent + "\n";
		}
		in.seek(0);
		in << strNewFileContents;
		file.close();
	}
	QMessageBox::information(this,"encry string from file","Well done",QMessageBox::Ok);

}

void MainWindow::onactProduct()
{
	productextenddlg dlg(this);
    QStringList lst = getSel(ui->treeViewSrc);
    dlg.init(lst);
	dlg.exec();
}

void MainWindow::onactRccGenFiles()
{
	bool showMessage = false;
	QString srcFile("");
	QString destDir("");
	QFileInfo info;
    QFileInfo dInfo;
	if(getSel(ui->treeViewSrc).count() > 0)
	{
		srcFile = getSel(ui->treeViewSrc).at(0);
		if(!getSel(ui->treeViewDest).isEmpty())
			destDir = getSel(ui->treeViewDest).at(0);
		info.setFile(srcFile);
		dInfo.setFile(destDir);
		if(!info.exists() || !info.isFile())
			showMessage = true;
	}
	else
		showMessage = true;
	if(showMessage)
	{
		QMessageBox::information(this,"Rcc File Operate","You must select a rcc file in left");
		return;
	}
	
	QString finalDir(info.absolutePath() + "/" + info.baseName());
	if(dInfo.isDir())
	{
		finalDir = destDir + "/" + info.baseName();
	}
	m_pLstStr = new QStringList();
	QResource::registerResource(srcFile,":/Root");
	m_pLstStr->append(srcFile);
	rccGenFiles(":/Root",finalDir);
	QResource::unregisterResource(srcFile,":/Root");
	for(int i = m_pLstStr->count() -1; i>=0; i--)
		QResource::unregisterResource(m_pLstStr->at(i),":/Root");
	delete m_pLstStr;
	m_pLstStr = NULL;
	QMessageBox::information(this,"Rcc File Generate","well done");
	
}

void MainWindow::rccGenFiles(QString srcDir,QString destDir)
{
	QDir dir(srcDir);
	if(!dir.exists())
		return;
	QStringList lstRCCFiles = dir.entryList(QStringList() << "*.rcc", QDir::Files);
	foreach (QString subFile, lstRCCFiles)
    {
        // rcc文件，来源于以库的形式发布的模块
        QString strFullFilePath = srcDir + "/" + subFile;
		QResource::registerResource(strFullFilePath, ":/Root");
		m_pLstStr->append(strFullFilePath);
        QFileInfo fi(strFullFilePath);
        rccGenFiles(":/Root/" + fi.baseName(), destDir + "/" + fi.baseName());
    }
	foreach(QFileInfo SubFileInfo,dir.entryInfoList(QDir::Files))
	{
		if(SubFileInfo.suffix() == "rcc")
			continue;
        QFile file(SubFileInfo.absoluteFilePath());
		QString a = SubFileInfo.absoluteFilePath();
		if(!file.open(QIODevice::ReadOnly))
			continue;
		QFile dFile(destDir + "/" + SubFileInfo.fileName());
		QString b = destDir + "/" + SubFileInfo.fileName();
		QDir tmpDir(destDir);
		if(!tmpDir.exists())
			tmpDir.mkpath(destDir);
		if(!dFile.open(QIODevice::WriteOnly))
			continue;
		dFile.write(file.readAll());
		file.close();
		dFile.close();
	}
	foreach(QFileInfo SubFileInfo,dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot))
	{
		rccGenFiles(SubFileInfo.absoluteFilePath(),destDir + "/" +SubFileInfo.fileName());
	}

}

void MainWindow::onactToRcc()
{
	bool showMessage = false;
	QString srcDir("");
	QFileInfo info;
	if(getSel(ui->treeViewSrc).count() > 0)
	{
		srcDir = getSel(ui->treeViewSrc).at(0);
		info.setFile(srcDir);
		if(!info.exists() || !info.isDir())
		{
			showMessage = true;
		}
	}
	else
		showMessage = true;
	if(showMessage)
	{
		QMessageBox::information(this,"Generate Rcc File","You must select a Dir in left to make a rcc file");
		return;
	}
	if(!QFile::exists(QApplication::applicationDirPath() + "/" +"rcc.exe"))
	{
		QMessageBox::information(this,"Generate Rcc File","missing rcc.exe file at Application Dir");
		return;
	}
	QMessageBox::StandardButton result = QMessageBox::information(this,"Generate Rcc File","Contain the dir that you have selected? \
		that mean the new rcc basename is the up dirname",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
	QString workingDir("");
	QDir dir(srcDir);
	if(result == QMessageBox::Yes)
		dir.cdUp();
	QProcess process;
	process.setWorkingDirectory(dir.absolutePath());
	QString a = dir.dirName() + ".qrc";
	QString b = dir.dirName() + ".rcc";
    dir.remove(dir.dirName() + ".qrc");
	dir.remove(dir.dirName() + ".rcc");
	QString c = QApplication::applicationDirPath() + "/" +"rcc.exe";
	QStringList args;
	args << "-project" << "-o" << (dir.dirName() + ".qrc");
	process.start(QApplication::applicationDirPath() + "/" +"rcc.exe",args);
	args.clear();
	QProcess process2;
	process2.setWorkingDirectory(dir.absolutePath());
	args << "-binary" << (dir.dirName() + ".qrc") << "-o" << (dir.dirName() + ".rcc");
	process2.start(QApplication::applicationDirPath() + "/" +"rcc.exe",args);
	QMessageBox::information(this,"Generate Rcc File","Well Done");
}

void MainWindow::onactHelp()
{
	HelpDlg dlg(this);
	dlg.exec();
}

void MainWindow::onRenameFileName()
{
	bool ok;
	QStringList fileName;
	QString text = QInputDialog::getText(this, tr("rename file name"),
		tr("Exp:ab.txt->cd.txt"), QLineEdit::Normal,
		QDir::home().dirName(), &ok);
	if (!ok)
	{
       return;
	}
	if (!text.isEmpty())
		fileName = text.split("->");
	if (fileName.count() != 2)
	{
		QMessageBox::information(this,"Rename file","error invalid input!!!");
		return;
	}

    QStringList lst = getSel(ui->treeViewSrc);
	for (int i=0;i<lst.count();i++)
	{
		renameFile(lst.at(i),fileName.at(0),fileName.at(1));
	}
}

void MainWindow::renameFile(QString dirPath,QString old,QString newName)
{
    QDir dir(dirPath);
	if (!dir.exists())
	{
		return;
	}
	QFileInfoList lstInfo = dir.entryInfoList();
	QString tmp;
	for (int i=0;i<lstInfo.count();i++)
	{
        tmp = lstInfo.at(i).fileName();
		if ( tmp == "." || tmp == ".." ) ; // nothing
		else if ( lstInfo.at(i).isDir() )
		{
			QString tempDir = dirPath+("/")+tmp;
			renameFile(tempDir,old,newName);
		}
		else if ( lstInfo.at(i).isFile() ) 
		{
			if (tmp == old)
			{
				
				QFile::copy(lstInfo.at(i).absoluteFilePath(),lstInfo.at(i).absolutePath() + "/" + newName);
				dir.remove(tmp); 
			}   
		}
	}
}

void MainWindow::onSrcCustomMenu(const QPoint &p)
{
    m_bSrc = true;
    m_Point = p;
    QMenu menu(this);
    QAction *pA = menu.addAction("Open folder");
    connect(pA,SIGNAL(triggered()),this,SLOT(onOpenFolder()));
    menu.exec(QCursor::pos());
}
void MainWindow::onDesCustomMenu(const QPoint &p)
{
    m_bSrc = false;
    m_Point = p;
    QMenu menu(this);
    QAction *pA = menu.addAction("Open folder");
    connect(pA,SIGNAL(triggered()),this,SLOT(onOpenFolder()));
    menu.exec(QCursor::pos());
}
void MainWindow::onOpenFolder()
{
    QModelIndex idx;
    QString dir;
    if(m_bSrc)
    {
       idx = ui->treeViewSrc->indexAt(m_Point);
    }
    else
    {
        idx = ui->treeViewDest->indexAt(m_Point);
    }
    dir = m_pDirModel->filePath(idx);
    if(dir.length() > 0)
    {
        QFileInfo info(dir);
        if(info.isDir())
        {
            QUrl url = QUrl::fromLocalFile(dir);
            QDesktopServices::openUrl(url);
        }
        else
        {
            dir = info.dir().absolutePath();
            QUrl url = QUrl::fromLocalFile(dir);
            QDesktopServices::openUrl(url);
        }
    }

}

void MainWindow::onFiletoDir()
{
    QStringList lstSrc = getSel(ui->treeViewSrc);
    QStringList lstTar = getSel(ui->treeViewDest);
    if(lstSrc.count() == 0 || lstTar.count() == 0)
    {
        QMessageBox::information(this,"Copy files to dirs","You must select at least one file on left ,one dir on right");
        return;
    }
    for(int i=0; i< lstTar.count(); i++)
    {
        QString tar = lstTar.at(i);
        QDir dir(tar);
        if(!dir.exists())
            continue;
        for(int j=0; j<lstSrc.count(); j++)
        {
            QFileInfo info(lstSrc.at(j));
            if(info.isFile())
            {
                QString name = info.fileName();
                QFile::copy(lstSrc.at(j), tar + "/" + name);
                ui->resultShow->append(QString("copy %1 to %2").arg(lstSrc.at(j)).arg(tar));
            }
        }
    }
}

void MainWindow::onEncodeURL()
{
	QString strContent = ui->resultShow->toPlainText();
	QByteArray ary = strContent.toUtf8();
	QByteArray strPercent = ary.toPercentEncoding();
	ui->resultShow->clear();
	ui->resultShow->setPlainText(QString::fromUtf8(strPercent.constData()));
}
void MainWindow::onDecodeURL()
{
	QString strContent = ui->resultShow->toPlainText ();
	strContent.replace("%25","%");
	QByteArray ary = strContent.toUtf8();
	QByteArray strPercent = QByteArray::fromPercentEncoding(ary);
	ui->resultShow->clear();
	QString strT = QString::fromUtf8(strPercent.constData());
	strT.replace("\\u0026","&").replace("%2C",",").replace("\\/","/");
	ui->resultShow->setPlainText(strT);
}

void MainWindow::onBase64()
{
    Base64ConvertDlg dlg(this);
    dlg.exec();
}

void MainWindow::onEditBinaryFile()
{
    BinaryFileEditDlg dlg(this);
    dlg.exec();
}