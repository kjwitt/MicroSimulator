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
QPushButton** bp;

QTextCharFormat highlight;
QTextCharFormat unhighlight;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTextEdit *cells[mem_size], *cells1[mem_size], *cells2[16], *cells3[16], *cells5[8];
    QPushButton *cells4[8], *cells6[26];
    QString MemAddrLabels[16] = {"0x00", "0x10", "0x20", "0x30", "0x40", "0x50", "0x60", "0x70", "0x80", "0x90", "0xA0", "0xB0", "0xC0", "0xD0", "0xE0", "0xF0"};

    for (int i=0; i<mem_size; i++)
    {
        cells[i] = new QTextEdit(this);
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
    }

    for (int i=0; i<26; i++)
    {
        cells6[i] = new QPushButton(this);
    }

    instrMem = new QTextEdit*[mem_size] {cells[0], cells[1], cells[2], cells[3], cells[4], cells[5], cells[6], cells[7], cells[8], cells[9], cells[10], cells[11], cells[12], cells[13], cells[14], cells[15], cells[16], cells[17], cells[18], cells[19], cells[20], cells[21], cells[22], cells[23], cells[24], cells[25], cells[26], cells[27], cells[28], cells[29], cells[30], cells[31], cells[32], cells[33], cells[34], cells[35], cells[36], cells[37], cells[38], cells[39], cells[40], cells[41], cells[42], cells[43], cells[44], cells[45], cells[46], cells[47], cells[48], cells[49], cells[50], cells[51], cells[52], cells[53], cells[54], cells[55], cells[56], cells[57], cells[58], cells[59], cells[60], cells[61], cells[62], cells[63], cells[64], cells[65], cells[66], cells[67], cells[68], cells[69], cells[70], cells[71], cells[72], cells[73], cells[74], cells[75], cells[76], cells[77], cells[78], cells[79], cells[80], cells[81], cells[82], cells[83], cells[84], cells[85], cells[86], cells[87], cells[88], cells[89], cells[90], cells[91], cells[92], cells[93], cells[94], cells[95], cells[96], cells[97], cells[98], cells[99], cells[100], cells[101], cells[102], cells[103], cells[104], cells[105], cells[106], cells[107], cells[108], cells[109], cells[110], cells[111], cells[112], cells[113], cells[114], cells[115], cells[116], cells[117], cells[118], cells[119], cells[120], cells[121], cells[122], cells[123], cells[124], cells[125], cells[126], cells[127], cells[128], cells[129], cells[130], cells[131], cells[132], cells[133], cells[134], cells[135], cells[136], cells[137], cells[138], cells[139], cells[140], cells[141], cells[142], cells[143], cells[144], cells[145], cells[146], cells[147], cells[148], cells[149], cells[150], cells[151], cells[152], cells[153], cells[154], cells[155], cells[156], cells[157], cells[158], cells[159], cells[160], cells[161], cells[162], cells[163], cells[164], cells[165], cells[166], cells[167], cells[168], cells[169], cells[170], cells[171], cells[172], cells[173], cells[174], cells[175], cells[176], cells[177], cells[178], cells[179], cells[180], cells[181], cells[182], cells[183], cells[184], cells[185], cells[186], cells[187], cells[188], cells[189], cells[190], cells[191], cells[192], cells[193], cells[194], cells[195], cells[196], cells[197], cells[198], cells[199], cells[200], cells[201], cells[202], cells[203], cells[204], cells[205], cells[206], cells[207], cells[208], cells[209], cells[210], cells[211], cells[212], cells[213], cells[214], cells[215], cells[216], cells[217], cells[218], cells[219], cells[220], cells[221], cells[222], cells[223], cells[224], cells[225], cells[226], cells[227], cells[228], cells[229], cells[230], cells[231], cells[232], cells[233], cells[234], cells[235], cells[236], cells[237], cells[238], cells[239], cells[240], cells[241], cells[242], cells[243], cells[244], cells[245], cells[246], cells[247], cells[248], cells[249], cells[250], cells[251], cells[252], cells[253], cells[254], cells[255]};
    dataMem = new QTextEdit*[mem_size] {cells1[0], cells1[1], cells1[2], cells1[3], cells1[4], cells1[5], cells1[6], cells1[7], cells1[8], cells1[9], cells1[10], cells1[11], cells1[12], cells1[13], cells1[14], cells1[15], cells1[16], cells1[17], cells1[18], cells1[19], cells1[20], cells1[21], cells1[22], cells1[23], cells1[24], cells1[25], cells1[26], cells1[27], cells1[28], cells1[29], cells1[30], cells1[31], cells1[32], cells1[33], cells1[34], cells1[35], cells1[36], cells1[37], cells1[38], cells1[39], cells1[40], cells1[41], cells1[42], cells1[43], cells1[44], cells1[45], cells1[46], cells1[47], cells1[48], cells1[49], cells1[50], cells1[51], cells1[52], cells1[53], cells1[54], cells1[55], cells1[56], cells1[57], cells1[58], cells1[59], cells1[60], cells1[61], cells1[62], cells1[63], cells1[64], cells1[65], cells1[66], cells1[67], cells1[68], cells1[69], cells1[70], cells1[71], cells1[72], cells1[73], cells1[74], cells1[75], cells1[76], cells1[77], cells1[78], cells1[79], cells1[80], cells1[81], cells1[82], cells1[83], cells1[84], cells1[85], cells1[86], cells1[87], cells1[88], cells1[89], cells1[90], cells1[91], cells1[92], cells1[93], cells1[94], cells1[95], cells1[96], cells1[97], cells1[98], cells1[99], cells1[100], cells1[101], cells1[102], cells1[103], cells1[104], cells1[105], cells1[106], cells1[107], cells1[108], cells1[109], cells1[110], cells1[111], cells1[112], cells1[113], cells1[114], cells1[115], cells1[116], cells1[117], cells1[118], cells1[119], cells1[120], cells1[121], cells1[122], cells1[123], cells1[124], cells1[125], cells1[126], cells1[127], cells1[128], cells1[129], cells1[130], cells1[131], cells1[132], cells1[133], cells1[134], cells1[135], cells1[136], cells1[137], cells1[138], cells1[139], cells1[140], cells1[141], cells1[142], cells1[143], cells1[144], cells1[145], cells1[146], cells1[147], cells1[148], cells1[149], cells1[150], cells1[151], cells1[152], cells1[153], cells1[154], cells1[155], cells1[156], cells1[157], cells1[158], cells1[159], cells1[160], cells1[161], cells1[162], cells1[163], cells1[164], cells1[165], cells1[166], cells1[167], cells1[168], cells1[169], cells1[170], cells1[171], cells1[172], cells1[173], cells1[174], cells1[175], cells1[176], cells1[177], cells1[178], cells1[179], cells1[180], cells1[181], cells1[182], cells1[183], cells1[184], cells1[185], cells1[186], cells1[187], cells1[188], cells1[189], cells1[190], cells1[191], cells1[192], cells1[193], cells1[194], cells1[195], cells1[196], cells1[197], cells1[198], cells1[199], cells1[200], cells1[201], cells1[202], cells1[203], cells1[204], cells1[205], cells1[206], cells1[207], cells1[208], cells1[209], cells1[210], cells1[211], cells1[212], cells1[213], cells1[214], cells1[215], cells1[216], cells1[217], cells1[218], cells1[219], cells1[220], cells1[221], cells1[222], cells1[223], cells1[224], cells1[225], cells1[226], cells1[227], cells1[228], cells1[229], cells1[230], cells1[231], cells1[232], cells1[233], cells1[234], cells1[235], cells1[236], cells1[237], cells1[238], cells1[239], cells1[240], cells1[241], cells1[242], cells1[243], cells1[244], cells1[245], cells1[246], cells1[247], cells1[248], cells1[249], cells1[250], cells1[251], cells1[252], cells1[253], cells1[254], cells1[255]};
    QTextEdit** instrMemAddr = new QTextEdit*[16] {cells2[0], cells2[1], cells2[2], cells2[3], cells2[4], cells2[5], cells2[6], cells2[7], cells2[8], cells2[9], cells2[10], cells2[11], cells2[12], cells2[13], cells2[14], cells2[15]};
    QTextEdit** dataMemAddr = new QTextEdit*[16] {cells3[0], cells3[1], cells3[2], cells3[3], cells3[4], cells3[5], cells3[6], cells3[7], cells3[8], cells3[9], cells3[10], cells3[11], cells3[12], cells3[13], cells3[14], cells3[15]};

    input2 = new QPushButton*[8] {cells4[0], cells4[1], cells4[2], cells4[3], cells4[4], cells4[5], cells4[6], cells4[7]};
    inputLabels = new QTextEdit*[8] {cells5[0], cells5[1], cells5[2], cells5[3], cells5[4], cells5[5], cells5[6], cells5[7]};

    bp = new QPushButton*[26] {cells6[0], cells6[1], cells6[2], cells6[3], cells6[4], cells6[5], cells6[6], cells6[7], cells6[8], cells6[9], cells6[10], cells6[11], cells6[12], cells6[13], cells6[14], cells6[15], cells6[16], cells6[17], cells6[18], cells6[19], cells6[20], cells6[21], cells6[22], cells6[23], cells6[24], cells6[25]};

    for (int i=0; i<mem_size; i++)
    {
        ui->instrMemGrid->addWidget(instrMem[i], i/16, i%16);
        ui->instrMemGrid->setAlignment(Qt::AlignCenter);
        ui->dataMemGrid->addWidget(dataMem[i], i/16, i%16);
        ui->dataMemGrid->setAlignment(Qt::AlignCenter);
    }

    for (int i=0; i<16; i++)
    {
        ui->instrMemAddrGrid->addWidget(instrMemAddr[i], i, 1);
        ui->instrMemAddrGrid->setAlignment(Qt::AlignCenter);
        instrMemAddr[i]->setText(MemAddrLabels[i]);
        instrMemAddr[i]->setFont(QFont ("Consolas", 12));
        instrMemAddr[i]->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        instrMemAddr[i]->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        instrMemAddr[i]->setAlignment(Qt::AlignHCenter);
        instrMemAddr[i]->setAlignment(Qt::AlignCenter);
        
        ui->dataMemAddrGrid->addWidget(dataMemAddr[i], i, 1);
        ui->dataMemAddrGrid->setAlignment(Qt::AlignCenter);
        dataMemAddr[i]->setText(MemAddrLabels[i]);
        dataMemAddr[i]->setFont(QFont ("Consolas", 12));
        dataMemAddr[i]->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        dataMemAddr[i]->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        dataMemAddr[i]->setAlignment(Qt::AlignHCenter);
        dataMemAddr[i]->setAlignment(Qt::AlignCenter);
    }
    
    for (int i=0; i<mem_size; i++)
    {
        instrMem[i]->setText("00");
        instrMem[i]->setFont(QFont ("Consolas", 12));
        instrMem[i]->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        instrMem[i]->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        instrMem[i]->setAlignment(Qt::AlignHCenter);
        instrMem[i]->setAlignment(Qt::AlignCenter);
        
        dataMem[i]->setText("00");
        dataMem[i]->setFont(QFont ("Consolas", 12));
        dataMem[i]->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        dataMem[i]->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        dataMem[i]->setAlignment(Qt::AlignHCenter);
        dataMem[i]->setAlignment(Qt::AlignCenter);
    }
    for(int i=0;i<256;i++)
    {
        _dataMem[i]=0;
        _instrMem[i]=0;
    }
    for(int i=0;i<8;i++)
    {
        input[i]=0;
    }
    QObject::connect(dataMem[254],SIGNAL(textChanged()),this,SLOT(update_output()));

    update_output();

    QString input_labels[8] = {"I0", "I1", "I2", "I3", "I4", "I5", "I6", "I7"};

    //QRect r;

    for (int i=0; i<8; i++)
    {
        ui->ioGrid->addWidget(inputLabels[i], 0, 7-i);
        inputLabels[i]->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        inputLabels[i]->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        inputLabels[i]->setText(input_labels[i]);
        inputLabels[i]->setFont(QFont ("Consolas", 12));
        inputLabels[i]->setAlignment(Qt::AlignHCenter);
        inputLabels[i]->setAlignment(Qt::AlignCenter);
        //r=inputLabels[i]->geometry();
        ui->ioGrid->addWidget(input2[i], 1, 7-i);
        //input2[i]->setGeometry(r);
        input2[i]->setIconSize(QSize (100, 100));
        ui->ioGrid->setAlignment(Qt::AlignCenter);
    }

    for (int i=0; i<26; i++)
    {
        ui->bpGrid->addWidget(bp[i], i, 1);
        ui->bpGrid->setAlignment(Qt::AlignCenter);
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
    char temp;
    input[0] = !input[0];
    input[0] ? temp='1' : temp='0';
    ui->input1->setText(QString("0:")+QChar(temp));
    update_input_mem();
}

void MainWindow::on_input2_clicked()
{
    char temp;
    input[1] = !input[1];
    input[1] ? temp='1' : temp='0';
    ui->input2->setText(QString("1:")+QChar(temp));
    update_input_mem();
}

void MainWindow::on_input3_clicked()
{
    char temp;
    input[2] = !input[2];
    input[2] ? temp='1' : temp='0';
    ui->input3->setText(QString("2:")+QChar(temp));
    update_input_mem();
}

void MainWindow::on_input4_clicked()
{
    char temp;
    input[3] = !input[3];
    input[3] ? temp='1' : temp='0';
    ui->input4->setText(QString("3:")+QChar(temp));
    update_input_mem();
}

void MainWindow::on_input5_clicked()
{
    char temp;
    input[4] = !input[4];
    input[4] ? temp='1' : temp='0';
    ui->input5->setText(QString("4:")+QChar(temp));
    update_input_mem();
}

void MainWindow::on_input6_clicked()
{
    char temp;
    input[5] = !input[5];
    input[5] ? temp='1' : temp='0';
    ui->input6->setText(QString("5:")+QChar(temp));
    update_input_mem();
}

void MainWindow::on_input7_clicked()
{
    char temp;
    input[6] = !input[6];
    input[6] ? temp='1' : temp='0';
    ui->input7->setText(QString("6:")+QChar(temp));
    update_input_mem();
}

void MainWindow::on_input8_clicked()
{
    char temp;
    input[7] = !input[7];
    input[7] ? temp='1' : temp='0';
    ui->input8->setText(QString("7:")+QChar(temp));
    update_input_mem();
}

void MainWindow::update_input_mem()
{
    char input_hex = 0x00;
    for(int i=0;i<8;i++)
    {
        input_hex |= input[i]<<i;
    }
    _dataMem[255] = input_hex;
    update_dataMem();
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
    //char instrMemAssemble[MEMSIZE], dataMemAssemble[MEMSIZE];
    assemble(_instrMem, _dataMem, assemblerFile);
    delete [] assemblerFile;
    //QString instrMemFormatted, dataMemFormatted;

    update_dataMem();
    update_instrMem();

    //        QTextCursor instrCursor(instrMem[i]->document());
    //        instrCursor.setPosition(0, QTextCursor::MoveAnchor);
    //        instrCursor.setPosition(2, QTextCursor::KeepAnchor);
    //        instrCursor.setCharFormat(highlight);

    //        QTextCursor dataCursor(dataMem[i]->document());
    //        dataCursor.setPosition(0, QTextCursor::MoveAnchor);
    //        dataCursor.setPosition(2, QTextCursor::KeepAnchor);
    //        dataCursor.setCharFormat(highlight);

    //instrMemFormatted.append(temp1);
    //dataMemFormatted.append(temp2);

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
    for (int i=0; i<lineBreaks.length(); i++)
    {
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

//    switch(raw_text[1])
//    {
//    case('a'):case('A'):
//        output=10;
//        break;
//    case('b'):case('B'):
//        output=11;
//        break;
//    case('c'):case('C'):
//        output=12;
//        break;
//    case('d'):case('D'):
//        output=13;
//        break;
//    case('e'):case('E'):
//        output=14;
//        break;
//    case('f'):case('F'):
//        output=15;
//        break;
//    default:
//        output=raw_text[1]-'0';
//        break;
//    }

//    switch(raw_text[0])
//    {
//    case('a'):case('A'):
//        output|=10<<4;
//        break;
//    case('b'):case('B'):
//        output|=11<<4;
//        break;
//    case('c'):case('C'):
//        output|=12<<4;
//        break;
//    case('d'):case('D'):
//        output|=13<<4;
//        break;
//    case('e'):case('E'):
//        output|=14<<4;
//        break;
//    case('f'):case('F'):
//        output|=15<<4;
//        break;
//    default:
//        output|=(raw_text[0]-'0')<<4;
//        break;
//    }

    output = array_to_hex(raw_text);

    if(raw_input.length()!=2) output=0;
    for(int i=0;i<8;i++)
    {
        if(output & 0x01)
        {
            switch(i)
            {
            case(0):
                ui->output1->setText("0: ON");
                break;
            case(1):
                ui->output2->setText("1: ON");
                break;
            case(2):
                ui->output3->setText("2: ON");
                break;
            case(3):
                ui->output4->setText("3: ON");
                break;
            case(4):
                ui->output5->setText("4: ON");
                break;
            case(5):
                ui->output6->setText("5: ON");
                break;
            case(6):
                ui->output7->setText("6: ON");
                break;
            case(7):
                ui->output8->setText("7: ON");
                break;
            }
        }
        else
        {
            switch(i)
            {
            case(0):
                ui->output1->setText("0: OFF");
                break;
            case(1):
                ui->output2->setText("1: OFF");
                break;
            case(2):
                ui->output3->setText("2: OFF");
                break;
            case(3):
                ui->output4->setText("3: OFF");
                break;
            case(4):
                ui->output5->setText("4: OFF");
                break;
            case(5):
                ui->output6->setText("5: OFF");
                break;
            case(6):
                ui->output7->setText("6: OFF");
                break;
            case(7):
                ui->output8->setText("7: OFF");
                break;
            }

        }
        output=output>>1;
    }
}

void MainWindow::update_instrMem()
{
    highlight.setBackground(Qt::yellow);
    unhighlight.setBackground(Qt::white);

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
    highlight.setBackground(Qt::yellow);
    unhighlight.setBackground(Qt::white);

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
