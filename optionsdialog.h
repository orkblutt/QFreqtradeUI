#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>

namespace Ui {
class OptionsDialog;
}

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(const QString& address, const int& port, const QString& username, const QString& password, const bool& remember, const int& interval, const bool& oneclick, QWidget *parent = nullptr);
    ~OptionsDialog();

    void getOptions(QString& address, int& port, QString& username, QString& password, bool& remember, int& interval, bool& oneclick);

private:
    Ui::OptionsDialog *ui;
};

#endif // OPTIONSDIALOG_H
