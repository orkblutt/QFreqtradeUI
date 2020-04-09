#include "confviewerdialog.h"
#include "ui_confviewerdialog.h"

ConfViewerDialog::ConfViewerDialog(const QString conf, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfViewerDialog)
{
    ui->setupUi(this);
    ui->textEditConfig->setText(conf);
}

ConfViewerDialog::~ConfViewerDialog()
{
    delete ui;
}
