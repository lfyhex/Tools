#include "helpdlg.h"
#include "ui_helpdlg.h"

HelpDlg::HelpDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDlg)
{
    ui->setupUi(this);
	setWindowTitle("Operating Help");
	connect(ui->btnRemoveFileInDir,SIGNAL(clicked()),this,SLOT(onHelp_RemoveFile()));
	connect(ui->btnCopyXml,SIGNAL(clicked()),this,SLOT(onHelp_CopyXML()));
	connect(ui->btnClear,SIGNAL(clicked()),this,SLOT(onHelp_ClearOutPut()));
	connect(ui->btnReName,SIGNAL(clicked()),this,SLOT(onHelp_Rename()));
	connect(ui->btnUpdate,SIGNAL(clicked()),this,SLOT(onHelp_Update()));
	connect(ui->btnEncry,SIGNAL(clicked()),this,SLOT(onHelp_EncryString()));
	connect(ui->btnProductEx,SIGNAL(clicked()),this,SLOT(onHelp_ProductEx()));
	connect(ui->btnGernerate,SIGNAL(clicked()),this,SLOT(onHelp_GernerateFiles()));
	connect(ui->btnToRcc,SIGNAL(clicked()),this,SLOT(onHelp_ToRcc()));
	connect(ui->actRenameFile,SIGNAL(clicked()),this,SLOT(onHelp_RenameFile()));
}

HelpDlg::~HelpDlg()
{
    delete ui;
}

void HelpDlg::onHelp_RemoveFile()
{
	char *str = "�������ѡȡһ������Ŀ¼���ڵ���������Ի���������Ҫɾ�����ļ���Ҫ�к�׺����\
		��ȷ����ͻ���ѡ�е��ļ�Ŀ¼��������������ļ���ɾ��";
	ui->txtEdit->setText(QString::fromLocal8Bit(str));
}
void HelpDlg::onHelp_CopyXML()
{
	char *str = "�������ѡȡһ������Ŀ¼��Ȼ�����ͻ�����ѡ���Ŀ¼��Ѱ��affiliate.xml�ļ���\
		�ҵ���ͻ���ͬ��Ŀ¼������affiliate_regnow.xml�ļ������޸Ĵ���ֵ";
	ui->txtEdit->setText(QString::fromLocal8Bit(str));
}
void HelpDlg::onHelp_ClearOutPut()
{
	char *str = "�����������������";
	ui->txtEdit->setText(QString::fromLocal8Bit(str));
}
void HelpDlg::onHelp_Rename()
{
	char *str = "�����ѡȡһ��Ŀ¼��������ڴ�Ŀ¼�½�Ŀ¼���ļ��д�help�ĵط�ɾ��";
	ui->txtEdit->setText(QString::fromLocal8Bit(str));
}
void HelpDlg::onHelp_Update()
{
	char *str = "�������������Ҳ����Ŀ¼";
	ui->txtEdit->setText(QString::fromLocal8Bit(str));
}
void HelpDlg::onHelp_EncryString()
{
	char *str = "�����������д���ܴ��ģ�������ȡ�������ѡȡ���ļ���Ȼ������ļ����ݣ����չ������ɼ��ܴ�";
	ui->txtEdit->setText(QString::fromLocal8Bit(str));
}
void HelpDlg::onHelp_ProductEx()
{
	char *str = "�޸�product_extend.xml�ļ�����ȡ���ѡ��Ŀ¼�µ�����product_extend.xml,���޸�";
	ui->txtEdit->setText(QString::fromLocal8Bit(str));
}
void HelpDlg::onHelp_GernerateFiles()
{
	char *str = "��ȡ���ѡ�е�rcc�ļ���ֻ��ѡһ���������Ҳ�ѡ�����·����Ĭ�ϻ���ѡ��Ŀ¼������rcc�ļ�����ʵ�ļ��ṹ";
	ui->txtEdit->setText(QString::fromLocal8Bit(str));
}
void HelpDlg::onHelp_ToRcc()
{
	char *str = "��ȡ����ļ�Ŀ¼����������Ŀ¼����һ��rcc�ļ����ļ�λ��������ѡ�е�Ŀ¼��";
	ui->txtEdit->setText(QString::fromLocal8Bit(str));
}

void HelpDlg::onHelp_RenameFile()
{
	char *str = "�����ѡȡһ��Ŀ¼�������ᵯ����ʾ�Ի��򣬰�Ҫ�����뼴��";
	ui->txtEdit->setText(QString::fromLocal8Bit(str));
}