#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_Load_Text_File_released();

    void on_Save_Text_File_released();

    void on_Clear_released();

    void on_Add_to_Debug_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
