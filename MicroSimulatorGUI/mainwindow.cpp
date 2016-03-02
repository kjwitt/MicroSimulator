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
#include <QRect>
#include <QPalette>
#include <stdio.h>
#include <QScrollBar>
#include <QIcon>
//#include "codeeditor.h"
extern "C"
{
#include "assembler.h"
#include "hexconstants.h"
}

#define mem_size 256

QTextEdit** instrMem;
QTextEdit** dataMem;
QPushButton** input2;
QTextEdit** inputLabels;
QPushButton** output2;
QTextEdit** outputLabels;
QPushButton** bp;

QTextCharFormat highlight;
QTextCharFormat unhighlight;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);  

    /* Create highlight and unhighlight backgrounds */
    highlight.setBackground(Qt::yellow);
    unhighlight.setBackground(Qt::white);

    /* Initialize cells for use in grids */
    QTextEdit *cells0[mem_size], *cells1[mem_size], *cells2[16], *cells3[16], *cells5[8], *cells7[8];
    QPushButton *cells4[8], *cells6[26], *cells8[8];
    for (int i=0; i<mem_size; i++)
    {
        cells0[i] = new QTextEdit(this);
        cells1[i] = new QTextEdit(this);
    }
    for (int i=0; i<16; i++)
    {
        cells2[i] = new QTextEdit(this);
        cells3[i] = new QTextEdit(this);
    }
    for (int i=0; i<8; i++)
    {
        cells4[i] = new QPushButton(this);
        cells5[i] = new QTextEdit(this);
        cells7[i] = new QTextEdit(this);
        cells8[i] = new QPushButton(this);
    }
    for (int i=0; i<26; i++)
    {
        cells6[i] = new QPushButton(this);
    }

    /* Set up instruction memory and data memory grids */
    instrMem = new QTextEdit*[mem_size] {cells0[0], cells0[1], cells0[2], cells0[3], cells0[4], cells0[5], cells0[6], cells0[7], cells0[8], cells0[9], cells0[10], cells0[11], cells0[12], cells0[13], cells0[14], cells0[15], cells0[16], cells0[17], cells0[18], cells0[19], cells0[20], cells0[21], cells0[22], cells0[23], cells0[24], cells0[25], cells0[26], cells0[27], cells0[28], cells0[29], cells0[30], cells0[31], cells0[32], cells0[33], cells0[34], cells0[35], cells0[36], cells0[37], cells0[38], cells0[39], cells0[40], cells0[41], cells0[42], cells0[43], cells0[44], cells0[45], cells0[46], cells0[47], cells0[48], cells0[49], cells0[50], cells0[51], cells0[52], cells0[53], cells0[54], cells0[55], cells0[56], cells0[57], cells0[58], cells0[59], cells0[60], cells0[61], cells0[62], cells0[63], cells0[64], cells0[65], cells0[66], cells0[67], cells0[68], cells0[69], cells0[70], cells0[71], cells0[72], cells0[73], cells0[74], cells0[75], cells0[76], cells0[77], cells0[78], cells0[79], cells0[80], cells0[81], cells0[82], cells0[83], cells0[84], cells0[85], cells0[86], cells0[87], cells0[88], cells0[89], cells0[90], cells0[91], cells0[92], cells0[93], cells0[94], cells0[95], cells0[96], cells0[97], cells0[98], cells0[99], cells0[100], cells0[101], cells0[102], cells0[103], cells0[104], cells0[105], cells0[106], cells0[107], cells0[108], cells0[109], cells0[110], cells0[111], cells0[112], cells0[113], cells0[114], cells0[115], cells0[116], cells0[117], cells0[118], cells0[119], cells0[120], cells0[121], cells0[122], cells0[123], cells0[124], cells0[125], cells0[126], cells0[127], cells0[128], cells0[129], cells0[130], cells0[131], cells0[132], cells0[133], cells0[134], cells0[135], cells0[136], cells0[137], cells0[138], cells0[139], cells0[140], cells0[141], cells0[142], cells0[143], cells0[144], cells0[145], cells0[146], cells0[147], cells0[148], cells0[149], cells0[150], cells0[151], cells0[152], cells0[153], cells0[154], cells0[155], cells0[156], cells0[157], cells0[158], cells0[159], cells0[160], cells0[161], cells0[162], cells0[163], cells0[164], cells0[165], cells0[166], cells0[167], cells0[168], cells0[169], cells0[170], cells0[171], cells0[172], cells0[173], cells0[174], cells0[175], cells0[176], cells0[177], cells0[178], cells0[179], cells0[180], cells0[181], cells0[182], cells0[183], cells0[184], cells0[185], cells0[186], cells0[187], cells0[188], cells0[189], cells0[190], cells0[191], cells0[192], cells0[193], cells0[194], cells0[195], cells0[196], cells0[197], cells0[198], cells0[199], cells0[200], cells0[201], cells0[202], cells0[203], cells0[204], cells0[205], cells0[206], cells0[207], cells0[208], cells0[209], cells0[210], cells0[211], cells0[212], cells0[213], cells0[214], cells0[215], cells0[216], cells0[217], cells0[218], cells0[219], cells0[220], cells0[221], cells0[222], cells0[223], cells0[224], cells0[225], cells0[226], cells0[227], cells0[228], cells0[229], cells0[230], cells0[231], cells0[232], cells0[233], cells0[234], cells0[235], cells0[236], cells0[237], cells0[238], cells0[239], cells0[240], cells0[241], cells0[242], cells0[243], cells0[244], cells0[245], cells0[246], cells0[247], cells0[248], cells0[249], cells0[250], cells0[251], cells0[252], cells0[253], cells0[254], cells0[255]};
    dataMem = new QTextEdit*[mem_size] {cells1[0], cells1[1], cells1[2], cells1[3], cells1[4], cells1[5], cells1[6], cells1[7], cells1[8], cells1[9], cells1[10], cells1[11], cells1[12], cells1[13], cells1[14], cells1[15], cells1[16], cells1[17], cells1[18], cells1[19], cells1[20], cells1[21], cells1[22], cells1[23], cells1[24], cells1[25], cells1[26], cells1[27], cells1[28], cells1[29], cells1[30], cells1[31], cells1[32], cells1[33], cells1[34], cells1[35], cells1[36], cells1[37], cells1[38], cells1[39], cells1[40], cells1[41], cells1[42], cells1[43], cells1[44], cells1[45], cells1[46], cells1[47], cells1[48], cells1[49], cells1[50], cells1[51], cells1[52], cells1[53], cells1[54], cells1[55], cells1[56], cells1[57], cells1[58], cells1[59], cells1[60], cells1[61], cells1[62], cells1[63], cells1[64], cells1[65], cells1[66], cells1[67], cells1[68], cells1[69], cells1[70], cells1[71], cells1[72], cells1[73], cells1[74], cells1[75], cells1[76], cells1[77], cells1[78], cells1[79], cells1[80], cells1[81], cells1[82], cells1[83], cells1[84], cells1[85], cells1[86], cells1[87], cells1[88], cells1[89], cells1[90], cells1[91], cells1[92], cells1[93], cells1[94], cells1[95], cells1[96], cells1[97], cells1[98], cells1[99], cells1[100], cells1[101], cells1[102], cells1[103], cells1[104], cells1[105], cells1[106], cells1[107], cells1[108], cells1[109], cells1[110], cells1[111], cells1[112], cells1[113], cells1[114], cells1[115], cells1[116], cells1[117], cells1[118], cells1[119], cells1[120], cells1[121], cells1[122], cells1[123], cells1[124], cells1[125], cells1[126], cells1[127], cells1[128], cells1[129], cells1[130], cells1[131], cells1[132], cells1[133], cells1[134], cells1[135], cells1[136], cells1[137], cells1[138], cells1[139], cells1[140], cells1[141], cells1[142], cells1[143], cells1[144], cells1[145], cells1[146], cells1[147], cells1[148], cells1[149], cells1[150], cells1[151], cells1[152], cells1[153], cells1[154], cells1[155], cells1[156], cells1[157], cells1[158], cells1[159], cells1[160], cells1[161], cells1[162], cells1[163], cells1[164], cells1[165], cells1[166], cells1[167], cells1[168], cells1[169], cells1[170], cells1[171], cells1[172], cells1[173], cells1[174], cells1[175], cells1[176], cells1[177], cells1[178], cells1[179], cells1[180], cells1[181], cells1[182], cells1[183], cells1[184], cells1[185], cells1[186], cells1[187], cells1[188], cells1[189], cells1[190], cells1[191], cells1[192], cells1[193], cells1[194], cells1[195], cells1[196], cells1[197], cells1[198], cells1[199], cells1[200], cells1[201], cells1[202], cells1[203], cells1[204], cells1[205], cells1[206], cells1[207], cells1[208], cells1[209], cells1[210], cells1[211], cells1[212], cells1[213], cells1[214], cells1[215], cells1[216], cells1[217], cells1[218], cells1[219], cells1[220], cells1[221], cells1[222], cells1[223], cells1[224], cells1[225], cells1[226], cells1[227], cells1[228], cells1[229], cells1[230], cells1[231], cells1[232], cells1[233], cells1[234], cells1[235], cells1[236], cells1[237], cells1[238], cells1[239], cells1[240], cells1[241], cells1[242], cells1[243], cells1[244], cells1[245], cells1[246], cells1[247], cells1[248], cells1[249], cells1[250], cells1[251], cells1[252], cells1[253], cells1[254], cells1[255]};
    for (int i=0; i<mem_size; i++)
    {
        ui->instrMemGrid->addWidget(instrMem[i], i/16, i%16);
        instrMem[i]->setText("00");
        instrMem[i]->setFont(QFont ("Consolas", 12));
        instrMem[i]->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        instrMem[i]->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        instrMem[i]->setAlignment(Qt::AlignHCenter);
        instrMem[i]->setAlignment(Qt::AlignCenter);
        _instrMem[i] = 0;

        ui->dataMemGrid->addWidget(dataMem[i], i/16, i%16);
        dataMem[i]->setText("00");
        dataMem[i]->setFont(QFont ("Consolas", 12));
        dataMem[i]->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        dataMem[i]->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        dataMem[i]->setAlignment(Qt::AlignHCenter);
        dataMem[i]->setAlignment(Qt::AlignCenter);
        _dataMem[i] = 0;
    }
    ui->instrMemGrid->setAlignment(Qt::AlignCenter);
    ui->dataMemGrid->setAlignment(Qt::AlignCenter);
    QObject::connect(dataMem[254],SIGNAL(textChanged()),this,SLOT(update_output()));

    /* Set up instruction memory and data memory address grids */
    QTextEdit** instrMemAddr = new QTextEdit*[16] {cells2[0], cells2[1], cells2[2], cells2[3], cells2[4], cells2[5], cells2[6], cells2[7], cells2[8], cells2[9], cells2[10], cells2[11], cells2[12], cells2[13], cells2[14], cells2[15]};
    QTextEdit** dataMemAddr = new QTextEdit*[16] {cells3[0], cells3[1], cells3[2], cells3[3], cells3[4], cells3[5], cells3[6], cells3[7], cells3[8], cells3[9], cells3[10], cells3[11], cells3[12], cells3[13], cells3[14], cells3[15]};
    QString MemAddrLabels[16] = {"0x00", "0x10", "0x20", "0x30", "0x40", "0x50", "0x60", "0x70", "0x80", "0x90", "0xA0", "0xB0", "0xC0", "0xD0", "0xE0", "0xF0"};
    for (int i=0; i<16; i++)
    {
        ui->instrMemAddrGrid->addWidget(instrMemAddr[i], i, 1);
        instrMemAddr[i]->setText(MemAddrLabels[i]);
        instrMemAddr[i]->setFont(QFont ("Consolas", 12));
        instrMemAddr[i]->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        instrMemAddr[i]->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        instrMemAddr[i]->setAlignment(Qt::AlignHCenter);
        instrMemAddr[i]->setAlignment(Qt::AlignCenter);
        instrMemAddr[i]->setReadOnly(true);

        ui->dataMemAddrGrid->addWidget(dataMemAddr[i], i, 1);
        dataMemAddr[i]->setText(MemAddrLabels[i]);
        dataMemAddr[i]->setFont(QFont ("Consolas", 12));
        dataMemAddr[i]->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        dataMemAddr[i]->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        dataMemAddr[i]->setAlignment(Qt::AlignHCenter);
        dataMemAddr[i]->setAlignment(Qt::AlignCenter);
        dataMemAddr[i]->setReadOnly(true);
    }
    ui->instrMemAddrGrid->setAlignment(Qt::AlignCenter);
    ui->dataMemAddrGrid->setAlignment(Qt::AlignCenter);

    /* Set up input and output grid */
    input2 = new QPushButton*[8] {cells4[0], cells4[1], cells4[2], cells4[3], cells4[4], cells4[5], cells4[6], cells4[7]};
    output2 = new QPushButton*[8] {cells8[0], cells8[1], cells8[2], cells8[3], cells8[4], cells8[5], cells8[6], cells8[7]};
    inputLabels = new QTextEdit*[8] {cells5[0], cells5[1], cells5[2], cells5[3], cells5[4], cells5[5], cells5[6], cells5[7]};
    outputLabels = new QTextEdit*[8] {cells7[0], cells7[1], cells7[2], cells7[3], cells7[4], cells7[5], cells7[6], cells7[7]};
    QString input_labels[8] = {"I0", "I1", "I2", "I3", "I4", "I5", "I6", "I7"};
    QString output_labels[8] = {"O0", "O1", "O2", "O3", "O4", "O5", "O6", "O7"};
    for (int i=0; i<8; i++)
    {
        ui->ioGrid->addWidget(inputLabels[i], 0, 7-i);
        inputLabels[i]->setText(input_labels[i]);
        inputLabels[i]->setFont(QFont ("Consolas", 12));
        inputLabels[i]->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        inputLabels[i]->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        inputLabels[i]->setAlignment(Qt::AlignHCenter);
        inputLabels[i]->setAlignment(Qt::AlignCenter);
        inputLabels[i]->setReadOnly(true);

        ui->ioGrid->addWidget(outputLabels[i], 2, 7-i);
        outputLabels[i]->setText(output_labels[i]);
        outputLabels[i]->setFont(QFont ("Consolas", 12));
        outputLabels[i]->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        outputLabels[i]->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        outputLabels[i]->setAlignment(Qt::AlignHCenter);
        outputLabels[i]->setAlignment(Qt::AlignCenter);
        outputLabels[i]->setReadOnly(true);

        ui->ioGrid->addWidget(input2[i], 1, 7-i);
        input2[i]->setText("0");
        input2[i]->setFont(QFont ("Consolas", 12));
        input2[i]->setStyleSheet("background-color: rgb(255, 102, 102);");
        in_array[i] = 0;
        QObject::connect(input2[i], SIGNAL(clicked()), this, SLOT(update_input()));

        ui->ioGrid->addWidget(output2[i], 3, 7-i);
        output2[i]->setText("0");
        output2[i]->setFont(QFont ("Consolas", 12));
        output2[i]->setStyleSheet("background-color: rgb(255, 102, 102); color: black;");
        output2[i]->setDisabled(true);
    }
    ui->ioGrid->setAlignment(Qt::AlignCenter);

    /* Set up breakpoint grid */
    bp = new QPushButton*[26] {cells6[0], cells6[1], cells6[2], cells6[3], cells6[4], cells6[5], cells6[6], cells6[7], cells6[8], cells6[9], cells6[10], cells6[11], cells6[12], cells6[13], cells6[14], cells6[15], cells6[16], cells6[17], cells6[18], cells6[19], cells6[20], cells6[21], cells6[22], cells6[23], cells6[24], cells6[25]};
    for (int i=0; i<26; i++)
    {
        ui->bpGrid->addWidget(bp[i], i, 1);
        ui->bpGrid->setAlignment(Qt::AlignCenter);
        QObject::connect(bp[i],SIGNAL(clicked()),this,SLOT(update_breakpoints()));
    }
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::darkGray);
    ui->widget->setAutoFillBackground(true);
    ui->widget->setPalette(Pal);
    bp_array = NULL;
    assemble_length = 0;
    QScrollBar *vScrollBar_AC = ui->AssemblyCode->verticalScrollBar();
    QObject::connect(vScrollBar_AC,SIGNAL(valueChanged(int)),this,SLOT(assembly_scroll(int)));

    /* Initialize input, output, and breakpoints */
    update_input();
    update_output();
    update_bp_GUI();
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
    QString temp;
    QStringList pieces;
    scroll_offset=0;
    if(bp_array!=NULL)
    {
        delete[] bp_array;
    }
    temp = ui->Editor_Window->toPlainText();
    if(temp.contains(".data",Qt::CaseInsensitive))
    {
        pieces = temp.split( ".data" );
        data_str = "\n\n.data\n\n"+pieces[1];
        temp = pieces[0];
    }
    temp.remove("\n\n");
    assemble_length = temp.count('\n')+1;


    bp_array = new bool[assemble_length];
    for(int i = 0; i<assemble_length;i++)
    {
        bp_array[i] = false;
    }
    update_breakpoints();
    ui->AssemblyCode->setPlainText(temp);
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

void MainWindow::update_input()
{
    QObject* obj = sender();
    for (int i=0; i<8; i++)
    {
        if (obj==input2[i])
        {
            in_array[i] = !in_array[i];
            if (!in_array[i])
            {
                input2[i]->setText("0");
                input2[i]->setStyleSheet("background-color: rgb(255, 102, 102);");
            }
            else if (in_array[i])
            {
                input2[i]->setText("1");
                input2[i]->setStyleSheet("background-color: rgb(102, 255, 102);");
            }
        }
    }
    update_input_mem();
}

void MainWindow::update_input_mem()
{
    char input_hex = 0x00;
    for(int i=0;i<8;i++)
    {
        input_hex |= in_array[i]<<i;
    }
    _dataMem[255] = input_hex;
    update_dataMem();
}

void MainWindow::on_pushButtonAssemble_clicked()
{
    QString assemblerCodeText = ui->AssemblyCode->toPlainText() + data_str;
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
    assemble(_instrMem, _dataMem, assemblerFile);
    delete [] assemblerFile;

    update_dataMem();
    update_instrMem();
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
    for (int i=0; i<lineBreaks.length(); i++)
    {
        if (!numbers.contains(lineBreaks[i]))
        {
            //convert 'run' to an int
            //int runs = run.toInt();

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

char MainWindow::array_to_hex(char array[2])
{
    char hex;
    switch(array[1])
    {
    case('a'):case('A'):
        hex=10;
        break;
    case('b'):case('B'):
        hex=11;
        break;
    case('c'):case('C'):
        hex=12;
        break;
    case('d'):case('D'):
        hex=13;
        break;
    case('e'):case('E'):
        hex=14;
        break;
    case('f'):case('F'):
        hex=15;
        break;
    default:
        hex=array[1]-'0';
        break;
    }
    switch(array[0])
    {
    case('a'):case('A'):
        hex|=10<<4;
        break;
    case('b'):case('B'):
        hex|=11<<4;
        break;
    case('c'):case('C'):
        hex|=12<<4;
        break;
    case('d'):case('D'):
        hex|=13<<4;
        break;
    case('e'):case('E'):
        hex|=14<<4;
        break;
    case('f'):case('F'):
        hex|=15<<4;
        break;
    default:
        hex|=(array[0]-'0')<<4;
        break;
    }
    return hex;
}

void MainWindow::update_output()
{
    unsigned char output;
    char raw_text[2];
    QString raw_input = dataMem[254]->toPlainText();
    QByteArray raw_array = raw_input.toLocal8Bit();

    for(int i = 0; i<2;i++)
    {
        raw_text[i] = raw_array[i];
    }

    output = array_to_hex(raw_text);
    _dataMem[254] = output;

    if(raw_input.length()!=2) output=0;
    for(int i=0;i<8;i++)
    {
        if(output & 0x01)
        {
            output2[i]->setText("1");
            output2[i]->setStyleSheet("background-color: rgb(102, 255, 102); color: black");
        }
        else
        {
            output2[i]->setText("0");
            output2[i]->setStyleSheet("background-color: rgb(255, 102, 102); color: black;");
        }
        output=output>>1;
    }
}

void MainWindow::update_instrMem()
{
    for(int i=0;i<256;i++)
    {
        QString raw_string = instrMem[i]->toPlainText();
        QByteArray raw_array = raw_string.toLocal8Bit();
        char raw_text[2];
        char text;

        for(int j = 0; j<2;j++)
        {
            raw_text[j] = raw_array[j];
        }

        text = array_to_hex(raw_text);

        if(text !=_instrMem[i])
        {
            char temp2[256];
            for(int j=0;j<256;j++)
            {
                temp2[j]='\0';
            }

            sprintf(temp2,"%.02X ",(unsigned char)_instrMem[i]);

            instrMem[i]->setText(temp2);

            QTextCursor cursor(instrMem[i]->document());
            cursor.setPosition(0, QTextCursor::MoveAnchor);
            cursor.setPosition(2, QTextCursor::KeepAnchor);
            cursor.setCharFormat(highlight);

            QPalette p = instrMem[i]->palette();
            p.setColor(QPalette::Base, QColor(255, 255, 0));
            instrMem[i]->setPalette(p);
        }
        else
        {
            QTextCursor cursor(instrMem[i]->document());
            cursor.setPosition(0, QTextCursor::MoveAnchor);
            cursor.setPosition(2, QTextCursor::KeepAnchor);
            cursor.setCharFormat(unhighlight);

            QPalette p = instrMem[i]->palette();
            p.setColor(QPalette::Base, QColor(255, 255, 255));
            instrMem[i]->setPalette(p);
        }
    }
}

void MainWindow::update_dataMem()
{
    for(int i=0;i<256;i++)
    {
        QString raw_string = dataMem[i]->toPlainText();
        QByteArray raw_array = raw_string.toLocal8Bit();
        char raw_text[2];
        char text=0;

        for(int j = 0; j<2;j++)
        {
            raw_text[j] = raw_array[j];
        }

        text = array_to_hex(raw_text);

        if(text !=_dataMem[i])
        {
            char temp2[256];
            for(int j=0;j<256;j++)
            {
                temp2[j]='\0';
            }

            sprintf(temp2,"%.02X ",(unsigned char)_dataMem[i]);

            dataMem[i]->setText(temp2);

            QTextCursor cursor(dataMem[i]->document());
            cursor.setPosition(0, QTextCursor::MoveAnchor);
            cursor.setPosition(2, QTextCursor::KeepAnchor);
            cursor.setCharFormat(highlight);

            QPalette p = dataMem[i]->palette();
            p.setColor(QPalette::Base, QColor(255, 255, 0));
            dataMem[i]->setPalette(p);
        }
        else
        {
            QTextCursor cursor(dataMem[i]->document());
            cursor.setPosition(0, QTextCursor::MoveAnchor);
            cursor.setPosition(2, QTextCursor::KeepAnchor);
            cursor.setCharFormat(unhighlight);

            QPalette p = dataMem[i]->palette();
            p.setColor(QPalette::Base, QColor(255, 255, 255));
            dataMem[i]->setPalette(p);
        }
    }
}

void MainWindow::update_breakpoints()
{
    QObject* obj = sender();
    for(int i=0;i<26;i++)
    {
        if(obj == bp[i] && assemble_length>i+scroll_offset)
        {
            bp_array[i+scroll_offset] = !bp_array[i+scroll_offset];
        }
    }
    update_bp_GUI();
}

void MainWindow::update_bp_GUI()
{
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::darkGray);

    for(int i=0;i<26;i++)
    {
        if(scroll_offset+i<assemble_length)
        {
            if(bp_array[i+scroll_offset])
            {
                QString fileName(":/images/breakpoint.png");
                if(QFile(fileName).exists() == false)
                    QMessageBox::warning(this, "Application", "Wrong file name : " + fileName);
                else
                {
                    bp[i]->setText("");
                    bp[i]->setIcon(QIcon(fileName));
                    bp[i]->setIconSize(QSize(15,15));
                    bp[i]->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
                }
            }
            else
            {
                bp[i]->setText("");
                bp[i]->setIcon(QIcon());
                bp[i]->setIconSize(QSize(15,15));
                bp[i]->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
            }
        }
        else
        {
            bp[i]->setText("");
            bp[i]->setIcon(QIcon());
            bp[i]->setIconSize(QSize(15,15));
            bp[i]->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
        }
    }
}

void MainWindow::assembly_scroll(int index)
{
    scroll_offset=index;
    update_bp_GUI();
}

void MainWindow::on_CSDial_valueChanged(int value)
{
    ui->CSDisplay->setPlainText(QString::number(value));
}

void MainWindow::on_checkBoxFullSpeed_toggled(bool checked)
{
    if(checked)
    {
        ui->CSDisplay->setDisabled(true);
        ui->CSDial->setDisabled(true);
    }
    else
    {
        ui->CSDisplay->setDisabled(false);
        ui->CSDial->setDisabled(false);
    }
}
