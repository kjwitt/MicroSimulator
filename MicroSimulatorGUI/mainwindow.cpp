#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clear_check.h"
#include <QFileDialog>
#include <QPlainTextEdit>
#include <QTextStream>
#include <QFile>
#include <QLabel>
#include <QApplication>
#include <QMessageBox>
extern "C"{
#include "assembler.h"
#include "hexconstants.h"
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Load_Text_File_released()
{
    QString inputfilename = QFileDialog::getOpenFileName(this, tr("Open Text File"), "", tr("Text files (*.txt)"));
    QFile inputfile(inputfilename);
    inputfile.open(QFile::ReadOnly | QFile::Text);
    ui->Editor_Window->setPlainText(inputfile.readAll());
    inputfile.close();
}

void MainWindow::on_Save_Text_File_released()
{
    QString outputfilename = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text files (*.txt)"));
    QFile outputfile(outputfilename);
    outputfile.open(QFile::WriteOnly | QFile::Text);
    QTextStream out(&outputfile);
    out << ui->Editor_Window->toPlainText();
    outputfile.close();
}

void MainWindow::on_Clear_released()
{
    Clear_Check clear_check;
    if(clear_check.exec())
    {
        ui->Editor_Window->clear();
    }
}

void MainWindow::on_Add_to_Debug_clicked()
{
    ui->AssemblyCode->setPlainText(ui->Editor_Window->toPlainText());
    ui->AssemblyCodeLabel->setStyleSheet("QLabel {color: black;}");
    ui->AssemblyCodeLabel->setText("Assembly Code");
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::on_actionSave_Text_File_triggered()
{
    ui->tabWidget->setCurrentIndex(0);
    QString outputfilename = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text files (*.txt)"));
    QFile outputfile(outputfilename);
    outputfile.open(QFile::WriteOnly | QFile::Text);
    QTextStream out(&outputfile);
    out << ui->Editor_Window->toPlainText();
    outputfile.close();
}

void MainWindow::on_actionLoad_Text_File_triggered()
{
    ui->tabWidget->setCurrentIndex(0);
    QString inputfilename = QFileDialog::getOpenFileName(this, tr("Open Text File"), "", tr("Text files (*.txt)"));
    QFile inputfile(inputfilename);
    inputfile.open(QFile::ReadOnly | QFile::Text);
    ui->Editor_Window->setPlainText(inputfile.readAll());
    inputfile.close();
}

void MainWindow::on_pushButtonAssemble_released()
{

}

void MainWindow::on_actionAssemble_triggered()
{
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::on_actionRun_triggered()
{
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::on_actionStep_triggered()
{
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::on_actionStop_triggered()
{
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::on_Editor_Window_textChanged()
{
    ui->AssemblyCodeLabel->setStyleSheet("QLabel {color: red;}");
    ui->AssemblyCodeLabel->setText("Assembly Code (not synced)");
}

void MainWindow::on_input1_clicked()
{
    ui->input1->setText("1");

}

void MainWindow::on_input2_clicked()
{
    ui->input2->setText("1");
}

void MainWindow::on_input3_clicked()
{
    ui->input3->setText("1");
}

void MainWindow::on_input4_clicked()
{
    ui->input4->setText("1");
}

void MainWindow::on_input5_clicked()
{
    ui->input5->setText("1");
}

void MainWindow::on_input6_clicked()
{
    ui->input6->setText("1");
}

void MainWindow::on_input7_clicked()
{
    ui->input7->setText("1");
}

void MainWindow::on_input8_clicked()
{
    ui->input8->setText("1");
}



void MainWindow::on_pushButtonAssmble_clicked()
{
    QString assemblerCodeText = ui->AssemblyCode->toPlainText();
    QString workspace_1 = QFileDialog::getExistingDirectory(this, tr("Please Choose a Workspace Directory"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    QString inputFullPath = (workspace_1 + "//inputAssembly.txt");

    QFile inputFile(inputFullPath);
    inputFile.open(QFile::WriteOnly | QFile::Text);
    QTextStream input(&inputFile);
    input << assemblerCodeText;
    inputFile.close();


    QByteArray inputFullPathBytes = inputFullPath.toLocal8Bit();
    char *assemblerFile = new char[inputFullPathBytes.size()+1];
    strcpy(assemblerFile, inputFullPathBytes.data());
    char instrMem[MEMSIZE], dataMem[MEMSIZE];
    assemble(instrMem, dataMem, assemblerFile);
    delete [] assemblerFile;
    QString instrMemFormatted, dataMemFormatted;

    for(int i=0;i<256;i++)
    {
        char temp1[256], temp2[256];
        for(int j=0;j<256;j++)
        {
            temp1[j]='\0';
            temp2[j]='\0';
        }

        sprintf(temp1,"%.02X ",(unsigned char)instrMem[i]);
        sprintf(temp2,"%.02X ",(unsigned char)dataMem[i]);
        instrMemFormatted.append(temp1);
        dataMemFormatted.append(temp2);
    }

    ui -> InstructionMemory->setPlainText(instrMemFormatted);
    ui -> MainMemory->setPlainText(dataMemFormatted);
}
