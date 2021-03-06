#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <statusflags.h>

#define MAX_DEBUG_LENGTH 10000

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    unsigned char _dataMem[256];
    unsigned char _instrMem[256];
    unsigned char _progCount;
    unsigned char _instrReg;
    unsigned char _memAddrBus;
    unsigned char _memDataBus;
    unsigned char _accum;
    Statusflags _sflags;
    bool halted;

    bool is_assembled;
    int clockSpeed;
    bool stopped;
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

    void on_pushButtonRunBP_clicked();

    void on_checkBoxFullSpeed_toggled(bool checked);

    void on_CSDial_valueChanged(int value);

    void on_pushButtonRun_clicked();

    void on_pushButtonReset_clicked();

    void on_pushButtonStop_clicked();

    void on_pushButtonStop_pressed();

    void on_actionRun_to_BP_triggered();

    void on_actionReset_triggered();

    void on_actionExit_triggered();

    void on_actionClear_triggered();

    void on_actionSync_to_Debug_triggered();

public slots:

    void update_output();
    void update_breakpoints();
    void assembly_scroll(int);

private:
    Ui::MainWindow *ui;
    unsigned char array_to_hex( unsigned char array[2]);
    void update_input_mem();
    void update_instrMem();
    void update_dataMem();
    void update_bp_GUI();
    void update_registers();
    void update_status_flags();
    void disable_all();
    void enable_all();
    void run_no_update();
    void run_instruction();
    void run_instruction_no_update();
    void step_one();
};

#endif // MAINWINDOW_H
