#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QPlainTextEdit>
#include <QTextStream>
#include <QFile>

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

    //outputfile.write(ui->Editor_Window->toPlainText());

    out << ui->Editor_Window->toPlainText();


    outputfile.close();

}

void MainWindow::on_Clear_released()
{
    ui->Editor_Window->clear();
}

void MainWindow::on_Add_to_Debug_clicked()
{
    ui->AssemblyCode->setPlainText(ui->Editor_Window->toPlainText());
}
