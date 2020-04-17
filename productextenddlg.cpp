#include "productextenddlg.h"
#include "ui_productextenddlg.h"
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QTextStream>
#include <QMessageBox>

productextenddlg::productextenddlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::productextenddlg)
{
    ui->setupUi(this);
	setWindowTitle("Modify product_extend files");
	connect(ui->btnStart,SIGNAL(clicked()),this,SLOT(onStart()));
	connect(ui->lineInput,SIGNAL(textEdited(const QString &)),this,SLOT(onStatusChange(const QString &)));
	connect(ui->lineEditValue,SIGNAL(textEdited(const QString &)),this,SLOT(onStatusChange(const QString &)));
}

productextenddlg::~productextenddlg()
{
    delete ui;
}

void productextenddlg::init(QStringList &lst)//lst中可以是文件目录，文件，也可是两者都有
{
	for(int i=0; i<lst.count(); i++)
	{
		QFileInfo info(lst.at(i));
		if(info.isFile())
			m_lstFilse.append(lst.at(i));
		else
		{
			if(info.isDir())
			{
				parseDir(lst.at(i));
			}
		}
	}
}

void productextenddlg::onStart()
{
	QString strIn = ui->lineInput->text();
	QString strValue = ui->lineEditValue->text();
	if(strIn.isEmpty())
		return;
	OPType type = Type_Add;
	if(ui->radioAdd->isChecked())
	{	
		type = Type_Add;
	}
	else if(ui->radioDelete->isChecked())
	{
		type = Type_Delete;
	}
	else
	{
		type =Type_Change;
	}
	for(int i=0; i<m_lstFilse.count(); i++)
	{
		QString str = m_lstFilse.at(i);	
		changeFiles(str,strIn,strValue,type);		
	}
	QMessageBox::information(this,"modify files","Well Done!");
	ui->btnStart->setEnabled(false);
}

void productextenddlg::changeFiles(QString &filePath,QString &param,QString &value,OPType type)
{
	QFile file(filePath);
	if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
		return;
	QTextStream in(&file);
    QString strLine;
	QStringList lstString;
	int line=0;
	int specialLine=0;
	if(type == Type_Add)
	{
		while(!in.atEnd())
		{
			strLine = in.readLine();
			lstString.append(strLine);
			if(strLine.contains(value))
				specialLine = line;
			line++;
		}
		//QString perfect = QString("<Param name=""%1"" value=""%2""></Param>").arg().arg();
		lstString.insert(specialLine+1,param);		
	}
	else if(type == Type_Delete)
	{
		while(!in.atEnd())
		{
			strLine = in.readLine();
			if(strLine.contains(param))
				continue;
			lstString.append(strLine);
		}
	}
	else
	{
		while(!in.atEnd())
		{
			strLine = in.readLine();
			if(strLine.contains(param))
			{
				int pos = strLine.indexOf("value");
				int left =0 , right =0;
				for(int i = pos + 5; i < strLine.count(); i++)
				{
					if(strLine.at(i) == '"')
					{
						if(left == 0)
							left = i;
						else
							right = i;
					}
				}
				strLine.replace(left+1,right - left -1,value);
			}
			lstString.append(strLine);
		}
	}
	QString newContent;
	for(int i=0; i<lstString.count(); i++)
	{
		newContent += lstString.at(i) + "\n";
	}
	file.close();
	if(!file.open(QIODevice::WriteOnly))
		return;
	file.write(newContent.toLocal8Bit());
	file.close();


	/*
	QDomDocument doc;
	
	if(!doc.setContent(data))
		return;
	QDomElement root = doc.documentElement();
	if(type == Type_Add)
	{//value 作为位置指标，新增行放到value后边
		QDomElement newElement = root.createElement("Param");
		newElement.set
		root.insertAfter
	}
	else if(type == Type_Delete)
	{}
	else
	{}*/
}

void productextenddlg::parseDir(QString dirPath)
{
	QDir dir(dirPath);
	if(!dir.exists())
		return;
	QFileInfoList lstFileInfo = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
	for(int j=0; j<lstFileInfo.count(); j++)
    {
        QFileInfo info = lstFileInfo.at(j);
        QString filename = info.fileName();
        QString path = info.absoluteFilePath();
		parseDir(path);
	}
	QFileInfoList lstFileInfoF = dir.entryInfoList(QDir::Files);
	for(int i=0; i<lstFileInfoF.count(); i++)
	{
		QFileInfo f = lstFileInfoF.at(i);
		QString name = f.fileName();
		if(name.contains("product_extend"))
			m_lstFilse.append(f.absoluteFilePath());
	}
}

void productextenddlg::onStatusChange(const QString &)
{
	if(ui->btnStart->isEnabled())
		return;
	else
		ui->btnStart->setEnabled(true);
}