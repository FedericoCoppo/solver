#include "deleteconfirm.h"
#include "ui_deleteconfirm.h"

DeleteConfirm::DeleteConfirm(QString code, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteConfirm)
{
    ui->setupUi(this);
    ui->label->setText( "OK PER CONFERMARE CANCELLAZIONE DEFINITIVA PRODOTTO CODICE:" + code);
    unicCode = code;
}

DeleteConfirm::~DeleteConfirm()
{
    delete ui;
}
