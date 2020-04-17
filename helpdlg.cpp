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
	char *str = "先在左侧选取一个或多个目录，在弹出的输入对话框中输入要删除的文件（要有后缀），\
		点确定后就会在选中的文件目录中搜索你输入的文件并删除";
	ui->txtEdit->setText(QString::fromLocal8Bit(str));
}
void HelpDlg::onHelp_CopyXML()
{
	char *str = "先在左侧选取一个或多个目录，然后程序就会在你选择的目录中寻找affiliate.xml文件，\
		找到后就会在同级目录下生成affiliate_regnow.xml文件，并修改代理值";
	ui->txtEdit->setText(QString::fromLocal8Bit(str));
}
void HelpDlg::onHelp_ClearOutPut()
{
	char *str = "这个是用来清空输出的";
	ui->txtEdit->setText(QString::fromLocal8Bit(str));
}
void HelpDlg::onHelp_Rename()
{
	char *str = "在左侧选取一个目录，程序会在此目录下将目录和文件中带help的地方删掉";
	ui->txtEdit->setText(QString::fromLocal8Bit(str));
}
void HelpDlg::onHelp_Update()
{
	char *str = "用来更新左侧和右侧的树目录";
	ui->txtEdit->setText(QString::fromLocal8Bit(str));
}
void HelpDlg::onHelp_EncryString()
{
	char *str = "这个是用来填写加密串的，程序会读取你在左侧选取的文件，然后分析文件内容，按照规则生成加密串";
	ui->txtEdit->setText(QString::fromLocal8Bit(str));
}
void HelpDlg::onHelp_ProductEx()
{
	char *str = "修改product_extend.xml文件，读取左侧选中目录下的所有product_extend.xml,并修改";
	ui->txtEdit->setText(QString::fromLocal8Bit(str));
}
void HelpDlg::onHelp_GernerateFiles()
{
	char *str = "读取左侧选中的rcc文件，只能选一个，可在右侧选择输出路径，默认会在选中目录下生成rcc文件的真实文件结构";
	ui->txtEdit->setText(QString::fromLocal8Bit(str));
}
void HelpDlg::onHelp_ToRcc()
{
	char *str = "读取左侧文件目录，程序会给此目录生成一个rcc文件，文件位置在你所选中的目录下";
	ui->txtEdit->setText(QString::fromLocal8Bit(str));
}

void HelpDlg::onHelp_RenameFile()
{
	char *str = "在左侧选取一个目录，点击后会弹出提示对话框，按要求输入即可";
	ui->txtEdit->setText(QString::fromLocal8Bit(str));
}