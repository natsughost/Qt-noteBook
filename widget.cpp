#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setLayout(ui->verticalLayout);
    ui->widget->setLayout(ui->horizontalLayout);
    QShortcut* shortcutOpen = new QShortcut(QKeySequence(tr("Ctrl+O", "File|Open")), this);
    QShortcut* shortcutSave =new QShortcut(QKeySequence(tr("Ctrl+S","File|Open")),this);
    connect(shortcutOpen,&QShortcut::activated,[=](){
        on_btnopen_clicked();
    });
    connect(shortcutSave,&QShortcut::activated,[=](){
        on_btnSave_clicked();
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnopen_clicked()
{
    QString filename =QFileDialog::getOpenFileName(this,tr("Open File"),"E:/",tr("Text (*.txt)"));
    ui->textEdit->clear();
    file.setFileName(filename);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
        qDebug()<<"file open error";
    this->setWindowTitle(filename+"-noteBook");
    QTextStream in(&file);
    in.setCodec("UTF-8");
    while(!in.atEnd()){
        QString context =in.readLine();
        ///ui->textEdit->setText(context);
        ui->textEdit->append(context);
    }
}


void Widget::on_btnSave_clicked()
{
    if(!file.isOpen()){
        QString filename =QFileDialog::getSaveFileName(this,tr("Save File"),"E:/untitled.txt",tr("Text (*.txt)"));
        file.setFileName(filename);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        qDebug()<<"file open error"<< file.errorString();
    }
    QTextStream out(&file);
    out.setCodec("UTF-8");
    QString context = ui->textEdit->toPlainText();
    out<<context;
}


void Widget::on_btnclose_clicked()
{
    ui->textEdit->clear();
    if(!file.isOpen()){
        QMessageBox msbox;
        int ret = QMessageBox::warning(
            this,
            tr("Notice"),
            tr("The document has been modified. Do you want to save your changes?"),
            QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
            QMessageBox::Save
            );
        switch (ret) {
        case QMessageBox::Save:
            on_btnSave_clicked();
            break;
        case QMessageBox::Discard:
            ui->textEdit->clear();
            if(file.isOpen()){
                file.close();
                this->setWindowTitle("noteBook");
            }
            break;
        case QMessageBox::Cancel:
            break;
        default:
            break;
        }
    }
    if(file.isOpen()){
        file.close();
        this->setWindowTitle("noteBook");
    }
}

