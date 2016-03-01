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

    bool input[8];
    char _dataMem[256];
    char _instrMem[256];
    int assemble_length;
    QString data_str;
    bool *bp_array;
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

    void on_pushButtonAssemble_released();

    void on_Editor_Window_textChanged();

    void on_input1_clicked();

    void on_input2_clicked();

    void on_input3_clicked();

    void on_input4_clicked();

    void on_input5_clicked();

    void on_input6_clicked();

    void on_input7_clicked();

    void on_input8_clicked();

    void on_pushButtonAssmble_clicked();

    void on_pushButtonStep_clicked();

    void on_pushButtonRun_clicked();

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
};

#endif // MAINWINDOW_H
