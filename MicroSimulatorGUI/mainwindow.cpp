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
#include <QList>
#include <QFont>
#include <QGridLayout>
#include <stdio.h>
extern "C"
{
#include "assembler.h"
#include "hexconstants.h"
}

#define mem_size 256

QTextEdit** instrMem;
QTextEdit** dataMem;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTextEdit* cells[mem_size], *cells1[mem_size];

    for (int i=0; i<mem_size; i++)
    {
        cells[i] = new QTextEdit(this);
        cells1[i] = new QTextEdit(this);
    }

    instrMem = new QTextEdit*[mem_size] {cells[0], cells[1], cells[2], cells[3], cells[4], cells[5], cells[6], cells[7], cells[8], cells[9], cells[10], cells[11], cells[12], cells[13], cells[14], cells[15], cells[16], cells[17], cells[18], cells[19], cells[20], cells[21], cells[22], cells[23], cells[24], cells[25], cells[26], cells[27], cells[28], cells[29], cells[30], cells[31], cells[32], cells[33], cells[34], cells[35], cells[36], cells[37], cells[38], cells[39], cells[40], cells[41], cells[42], cells[43], cells[44], cells[45], cells[46], cells[47], cells[48], cells[49], cells[50], cells[51], cells[52], cells[53], cells[54], cells[55], cells[56], cells[57], cells[58], cells[59], cells[60], cells[61], cells[62], cells[63], cells[64], cells[65], cells[66], cells[67], cells[68], cells[69], cells[70], cells[71], cells[72], cells[73], cells[74], cells[75], cells[76], cells[77], cells[78], cells[79], cells[80], cells[81], cells[82], cells[83], cells[84], cells[85], cells[86], cells[87], cells[88], cells[89], cells[90], cells[91], cells[92], cells[93], cells[94], cells[95], cells[96], cells[97], cells[98], cells[99], cells[100], cells[101], cells[102], cells[103], cells[104], cells[105], cells[106], cells[107], cells[108], cells[109], cells[110], cells[111], cells[112], cells[113], cells[114], cells[115], cells[116], cells[117], cells[118], cells[119], cells[120], cells[121], cells[122], cells[123], cells[124], cells[125], cells[126], cells[127], cells[128], cells[129], cells[130], cells[131], cells[132], cells[133], cells[134], cells[135], cells[136], cells[137], cells[138], cells[139], cells[140], cells[141], cells[142], cells[143], cells[144], cells[145], cells[146], cells[147], cells[148], cells[149], cells[150], cells[151], cells[152], cells[153], cells[154], cells[155], cells[156], cells[157], cells[158], cells[159], cells[160], cells[161], cells[162], cells[163], cells[164], cells[165], cells[166], cells[167], cells[168], cells[169], cells[170], cells[171], cells[172], cells[173], cells[174], cells[175], cells[176], cells[177], cells[178], cells[179], cells[180], cells[181], cells[182], cells[183], cells[184], cells[185], cells[186], cells[187], cells[188], cells[189], cells[190], cells[191], cells[192], cells[193], cells[194], cells[195], cells[196], cells[197], cells[198], cells[199], cells[200], cells[201], cells[202], cells[203], cells[204], cells[205], cells[206], cells[207], cells[208], cells[209], cells[210], cells[211], cells[212], cells[213], cells[214], cells[215], cells[216], cells[217], cells[218], cells[219], cells[220], cells[221], cells[222], cells[223], cells[224], cells[225], cells[226], cells[227], cells[228], cells[229], cells[230], cells[231], cells[232], cells[233], cells[234], cells[235], cells[236], cells[237], cells[238], cells[239], cells[240], cells[241], cells[242], cells[243], cells[244], cells[245], cells[246], cells[247], cells[248], cells[249], cells[250], cells[251], cells[252], cells[253], cells[254], cells[255]};
    dataMem = new QTextEdit*[mem_size] {cells1[0], cells1[1], cells1[2], cells1[3], cells1[4], cells1[5], cells1[6], cells1[7], cells1[8], cells1[9], cells1[10], cells1[11], cells1[12], cells1[13], cells1[14], cells1[15], cells1[16], cells1[17], cells1[18], cells1[19], cells1[20], cells1[21], cells1[22], cells1[23], cells1[24], cells1[25], cells1[26], cells1[27], cells1[28], cells1[29], cells1[30], cells1[31], cells1[32], cells1[33], cells1[34], cells1[35], cells1[36], cells1[37], cells1[38], cells1[39], cells1[40], cells1[41], cells1[42], cells1[43], cells1[44], cells1[45], cells1[46], cells1[47], cells1[48], cells1[49], cells1[50], cells1[51], cells1[52], cells1[53], cells1[54], cells1[55], cells1[56], cells1[57], cells1[58], cells1[59], cells1[60], cells1[61], cells1[62], cells1[63], cells1[64], cells1[65], cells1[66], cells1[67], cells1[68], cells1[69], cells1[70], cells1[71], cells1[72], cells1[73], cells1[74], cells1[75], cells1[76], cells1[77], cells1[78], cells1[79], cells1[80], cells1[81], cells1[82], cells1[83], cells1[84], cells1[85], cells1[86], cells1[87], cells1[88], cells1[89], cells1[90], cells1[91], cells1[92], cells1[93], cells1[94], cells1[95], cells1[96], cells1[97], cells1[98], cells1[99], cells1[100], cells1[101], cells1[102], cells1[103], cells1[104], cells1[105], cells1[106], cells1[107], cells1[108], cells1[109], cells1[110], cells1[111], cells1[112], cells1[113], cells1[114], cells1[115], cells1[116], cells1[117], cells1[118], cells1[119], cells1[120], cells1[121], cells1[122], cells1[123], cells1[124], cells1[125], cells1[126], cells1[127], cells1[128], cells1[129], cells1[130], cells1[131], cells1[132], cells1[133], cells1[134], cells1[135], cells1[136], cells1[137], cells1[138], cells1[139], cells1[140], cells1[141], cells1[142], cells1[143], cells1[144], cells1[145], cells1[146], cells1[147], cells1[148], cells1[149], cells1[150], cells1[151], cells1[152], cells1[153], cells1[154], cells1[155], cells1[156], cells1[157], cells1[158], cells1[159], cells1[160], cells1[161], cells1[162], cells1[163], cells1[164], cells1[165], cells1[166], cells1[167], cells1[168], cells1[169], cells1[170], cells1[171], cells1[172], cells1[173], cells1[174], cells1[175], cells1[176], cells1[177], cells1[178], cells1[179], cells1[180], cells1[181], cells1[182], cells1[183], cells1[184], cells1[185], cells1[186], cells1[187], cells1[188], cells1[189], cells1[190], cells1[191], cells1[192], cells1[193], cells1[194], cells1[195], cells1[196], cells1[197], cells1[198], cells1[199], cells1[200], cells1[201], cells1[202], cells1[203], cells1[204], cells1[205], cells1[206], cells1[207], cells1[208], cells1[209], cells1[210], cells1[211], cells1[212], cells1[213], cells1[214], cells1[215], cells1[216], cells1[217], cells1[218], cells1[219], cells1[220], cells1[221], cells1[222], cells1[223], cells1[224], cells1[225], cells1[226], cells1[227], cells1[228], cells1[229], cells1[230], cells1[231], cells1[232], cells1[233], cells1[234], cells1[235], cells1[236], cells1[237], cells1[238], cells1[239], cells1[240], cells1[241], cells1[242], cells1[243], cells1[244], cells1[245], cells1[246], cells1[247], cells1[248], cells1[249], cells1[250], cells1[251], cells1[252], cells1[253], cells1[254], cells1[255]};

    for (int i=0; i<mem_size; i++)
    {
        ui->instrMemGrid->addWidget(instrMem[i], i/16, i%16);
        ui->instrMemGrid->setAlignment(Qt::AlignCenter);
        ui->dataMemGrid->addWidget(dataMem[i], i/16, i%16);
        ui->dataMemGrid->setAlignment(Qt::AlignCenter);
    }

    char text[50];

    for (int i=0; i<mem_size; i++)
    {
        sprintf(text, "%.02X", i);

        instrMem[i]->setText(text);
        instrMem[i]->setFont(QFont ("Consolas", 12));
        instrMem[i]->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        instrMem[i]->setAlignment(Qt::AlignHCenter);
        instrMem[i]->setAlignment(Qt::AlignCenter);

        dataMem[i]->setText(text);
        dataMem[i]->setFont(QFont ("Consolas", 12));
        dataMem[i]->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        dataMem[i]->setAlignment(Qt::AlignHCenter);
        dataMem[i]->setAlignment(Qt::AlignCenter);
    }

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
    char instrMemAssemble[MEMSIZE], dataMemAssemble[MEMSIZE];
    assemble(instrMemAssemble, dataMemAssemble, assemblerFile);
    delete [] assemblerFile;
    //QString instrMemFormatted, dataMemFormatted;

    QTextCharFormat highlight;
    highlight.setBackground(Qt::yellow);

    for(int i=0;i<256;i++)
    {
        char temp1[256], temp2[256];
        for(int j=0;j<256;j++)
        {
            temp1[j]='\0';
            temp2[j]='\0';
        }

        sprintf(temp1,"%.02X ",(unsigned char)instrMemAssemble[i]);
        sprintf(temp2,"%.02X ",(unsigned char)dataMemAssemble[i]);

        instrMem[i]->setText(temp1);
        dataMem[i]->setText(temp2);

        QTextCursor instrCursor(instrMem[i]->document());
        instrCursor.setPosition(0, QTextCursor::MoveAnchor);
        instrCursor.setPosition(2, QTextCursor::KeepAnchor);
        instrCursor.setCharFormat(highlight);

        QTextCursor dataCursor(dataMem[i]->document());
        dataCursor.setPosition(0, QTextCursor::MoveAnchor);
        dataCursor.setPosition(2, QTextCursor::KeepAnchor);
        dataCursor.setCharFormat(highlight);

        //instrMemFormatted.append(temp1);
        //dataMemFormatted.append(temp2);
    }

    //ui -> InstructionMemory->setPlainText(instrMemFormatted);
    //ui -> MainMemory->setPlainText(dataMemFormatted);
}

void MainWindow::on_pushButtonStep_clicked()
{
    //call the executive function that runs one cycle
}

void MainWindow::on_pushButtonRun_clicked()
{
    // define conditional character arrays
    QString numbers = "0123456789";

    //get the contents of the break line text box
    QString lineBreaks = ui->lineBreakText->toPlainText();

    //calculate how many lines to run
    QString run = "";
    for (int i=0; i<lineBreaks.length(); i++){
        if (!numbers.contains(lineBreaks[i]))
        {
            //convert 'run' to an int
            int runs = run.toInt();

            //call the executive funtion that runs 'n' number of instructions, where 'n' is 'runs'

            //reset the value of run
            run = "";

            //pause execution; not sure how to implement yet

        }
        else
        {
            run= run + lineBreaks[i];
        }
    }
}
