#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clear_check.h"
#include <QFileDialog>
#include <QPlainTextEdit>
#include <QTextStream>
#include <QFile>
#include <QLabel>

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
