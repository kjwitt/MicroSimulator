#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#define MAX_DEBUG_LENGTH 10000

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    char _dataMem[256];
    char _instrMem[256];
    char _progCount;
    char _instrReg;
    char _memAddrBus;
    char _memDataBus;
    char _accum;


    int assemble_length;
    QString data_str;
    bool *bp_array;
    bool in_array[8];
    int scroll_offset;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_Load_Text_File_released();

    void on_Save_Text_File_released();

    void on_Clear_released();

    void on_Add_to_Debug_clicked();

    void on_actionSave_Text_File_triggered();

    void on_actionLoad_Text_File_triggered();

    void on_actionAssemble_triggered();

    void on_actionRun_triggered();

    void on_actionStep_triggered();

    void on_actionStop_triggered();

    void on_Editor_Window_textChanged();

    void update_input();

    void on_pushButtonAssemble_clicked();

    void on_pushButtonStep_clicked();

    void on_pushButtonRun_clicked();

    void on_checkBoxFullSpeed_toggled(bool checked);

    void on_CSDial_valueChanged(int value);

public slots:

    void update_output();
    void update_breakpoints();
    void assembly_scroll(int);

private:
    Ui::MainWindow *ui;
    char array_to_hex(char array[2]);
    void update_input_mem();
    void update_instrMem();
    void update_dataMem();
    void update_bp_GUI();
    void update_registers();
};

#endif // MAINWINDOW_H
