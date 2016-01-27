#ifndef CLEAR_CHECK_H
#define CLEAR_CHECK_H

#include <QDialog>

namespace Ui {
class Clear_Check;
}

class Clear_Check : public QDialog
{
    Q_OBJECT

public:
    explicit Clear_Check(QWidget *parent = 0);
    ~Clear_Check();

private slots:

private:
    Ui::Clear_Check *ui;
};

#endif // CLEAR_CHECK_H
