#ifndef BUYDIALOG_H
#define BUYDIALOG_H

#include <QDialog>

namespace Ui {
class BuyDialog;
}

class BuyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BuyDialog(QWidget *parent = nullptr);
    ~BuyDialog();

    QString getPair();
    double  getRate();

private:
    Ui::BuyDialog *ui;
};

#endif // BUYDIALOG_H
