#ifndef CONFVIEWERDIALOG_H
#define CONFVIEWERDIALOG_H

#include <QDialog>

namespace Ui {
class ConfViewerDialog;
}

class ConfViewerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfViewerDialog(const QString conf, QWidget *parent = nullptr);
    ~ConfViewerDialog();

private:
    Ui::ConfViewerDialog *ui;
};

#endif // CONFVIEWERDIALOG_H
