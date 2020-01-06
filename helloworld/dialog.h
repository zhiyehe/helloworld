#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QString>
namespace Ui {
class Dialog;
}
enum _Sex{male, female};

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_pushButton_clicked();
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::Dialog *ui;
    QString number;
    QString name;
    QString filename;
    _Sex sex{male};
    bool broot{false};
};

#endif // DIALOG_H
