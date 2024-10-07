#include "mywidget.h"
#include "ui_mywidget.h"
#include "des.h"
myWidget::myWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myWidget)
{
    ui->setupUi(this);
}

myWidget::~myWidget()
{
    delete ui;
}

void myWidget::on_pushButton_clicked()
{
    string text=ui->textEdit->toPlainText().toStdString();
   string key=ui->lineEdit->text().toStdString();
   ui->textEdit->clear();
    if(text==""||key==""){
        return;
    }
    int index=ui->comboBox->currentIndex();
    switch (index) {
    case 0:{
        string res=encryptionAPI(text,key);
        QString Qtext=QString::fromStdString(res);
        ui->textEdit_2->setText(Qtext);
    }
        break;
    case 1:{

    }
        break;
    }

}

void myWidget::on_pushButton_2_clicked()
{
    string text=ui->textEdit_2->toPlainText().toStdString();
   string key=ui->lineEdit->text().toStdString();
   ui->textEdit_2->clear();
    if(text==""||key==""){
        return;
    }
    int index=ui->comboBox->currentIndex();
    switch (index) {
    case 0:{
        string res=decryptionAPI(text,key);
        QString Qtext=QString::fromStdString(res);
        ui->textEdit->setText(Qtext);
    }
        break;
    case 1:{

    }
        break;
    }

}
