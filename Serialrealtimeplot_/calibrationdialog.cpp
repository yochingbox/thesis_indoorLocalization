#include "calibrationdialog.h"
#include "ui_calibrationdialog.h"
#include <QtCore>
#include <QLabel>
#include <QCoreApplication>
#include <QDebug>
#include <QMessageBox>
#include <QTextEdit>

/*
float BBmagn[3] = {0, 0, 0};
float MMmagn[3][3] = { 1, 0, 0,
                      0, 1, 0,
                      0, 0, 1};
float BBaccn[3] = {0, 0, 0};
float MMaccn[3][3] = {1,   0,    0,
                     0,    1,    0,
                    0,   0,    1};
float BBgyrn[3] = {0, 0, 0};
float MMgyrn[3][3] = { 1,    0,    0,
                      0,    1,   0,
                      0,    0,    1};

*/
calibrationDialog::calibrationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::calibrationDialog)
{

    ui->setupUi(this);
    ui->textEditmagBx->insertPlainText("0");
    ui->textEditmagBy->insertPlainText("0");
    ui->textEditmagBz->insertPlainText("0");
    ui->textEditaccBx->insertPlainText("0");
    ui->textEditaccBy->insertPlainText("0");
    ui->textEditaccBz->insertPlainText("0");
    ui->textEditgyrBx->insertPlainText("0");
    ui->textEditgyrBy->insertPlainText("0");
    ui->textEditgyrBz->insertPlainText("0");
    ui->textEditmagM11->insertPlainText("1");
    ui->textEditmagM12->insertPlainText("0");
    ui->textEditmagM13->insertPlainText("0");
    ui->textEditmagM21->insertPlainText("0");
    ui->textEditmagM22->insertPlainText("1");
    ui->textEditmagM23->insertPlainText("0");
    ui->textEditmagM31->insertPlainText("0");
    ui->textEditmagM32->insertPlainText("0");
    ui->textEditmagM33->insertPlainText("1");
    ui->textEditaccM11->insertPlainText("1");
    ui->textEditaccM12->insertPlainText("0");
    ui->textEditaccM13->insertPlainText("0");
    ui->textEditaccM21->insertPlainText("0");
    ui->textEditaccM22->insertPlainText("1");
    ui->textEditaccM23->insertPlainText("0");
    ui->textEditaccM31->insertPlainText("0");
    ui->textEditaccM32->insertPlainText("0");
    ui->textEditaccM33->insertPlainText("1");
    ui->textEditgyrM11->insertPlainText("1");
    ui->textEditgyrM12->insertPlainText("0");
    ui->textEditgyrM13->insertPlainText("0");
    ui->textEditgyrM21->insertPlainText("0");
    ui->textEditgyrM22->insertPlainText("1");
    ui->textEditgyrM23->insertPlainText("0");
    ui->textEditgyrM31->insertPlainText("0");
    ui->textEditgyrM32->insertPlainText("0");
    ui->textEditgyrM33->insertPlainText("1");


}

void calibrationDialog::readinput(float BBmagn[3], float MMmagn[3][3], float BBaccn[3], float MMaccn[3][3], float BBgyrn[3], float MMgyrn[3][3])
{
    BBmagn[0] = 0;
    BBmagn[1] = 0;
    BBmagn[2] = 0;

    MMmagn[0][0] = 1;
    MMmagn[0][1] = 0;
    MMmagn[0][2] = 0;
    MMmagn[1][0] = 0;
    MMmagn[1][1] = 1;
    MMmagn[1][2] = 0;
    MMmagn[2][0] = 0;
    MMmagn[2][1] = 0;
    MMmagn[2][2] = 1;

    BBaccn[0] = 0;
    BBaccn[1] = 0;
    BBaccn[2] = 0;

    MMaccn[0][0] = 1;
    MMaccn[0][1] = 0;
    MMaccn[0][2] = 0;
    MMaccn[1][0] = 0;
    MMaccn[1][1] = 1;
    MMaccn[1][2] = 0;
    MMaccn[2][0] = 0;
    MMaccn[2][1] = 0;
    MMaccn[2][2] = 1;

    BBgyrn[0] = 0;
    BBgyrn[1] = 0;
    BBgyrn[2] = 0;

    MMgyrn[0][0] = 1;
    MMgyrn[0][1] = 0;
    MMgyrn[0][2] = 0;
    MMgyrn[1][0] = 0;
    MMgyrn[1][1] = 1;
    MMgyrn[1][2] = 0;
    MMgyrn[2][0] = 0;
    MMgyrn[2][1] = 0;
    MMgyrn[2][2] = 1;

    QString XMAX=ui->textEditmagBx->toPlainText();
    BBmagn[0]=XMAX.toDouble();
    XMAX=ui->textEditmagBy->toPlainText();
    BBmagn[1]=XMAX.toDouble();
    XMAX=ui->textEditmagBz->toPlainText();
    BBmagn[2]=XMAX.toDouble();

    XMAX=ui->textEditmagM11->toPlainText();
    if (ui->textEditmagM11->document()->isModified()){
        MMmagn[0][0]=XMAX.toDouble();}
    else{
        MMmagn[0][0]=1;
    }
    XMAX=ui->textEditmagM12->toPlainText();
    MMmagn[0][1]=XMAX.toDouble();
    XMAX=ui->textEditmagM13->toPlainText();
    MMmagn[0][2]=XMAX.toDouble();
    XMAX=ui->textEditmagM21->toPlainText();
    MMmagn[1][0]=XMAX.toDouble();
    XMAX=ui->textEditmagM22->toPlainText();
    if (ui->textEditmagM22->document()->isModified()){
        MMmagn[1][1]=XMAX.toDouble();}
    else{
        MMmagn[1][1]=1;
    }
    //MMmagn[1][1]=XMAX.toDouble();
    XMAX=ui->textEditmagM23->toPlainText();
    MMmagn[1][2]=XMAX.toDouble();
    XMAX=ui->textEditmagM31->toPlainText();
    MMmagn[2][0]=XMAX.toDouble();
    XMAX=ui->textEditmagM32->toPlainText();
    MMmagn[2][1]=XMAX.toDouble();
    XMAX=ui->textEditmagM33->toPlainText();
    if (ui->textEditmagM33->document()->isModified()){
        MMmagn[2][2]=XMAX.toDouble();}
    else{
        MMmagn[2][2]=1;
    }
    //MMmagn[2][2]=XMAX.toDouble();

    XMAX=ui->textEditaccBx->toPlainText();
    BBaccn[0]=XMAX.toDouble();
    XMAX=ui->textEditaccBy->toPlainText();
    BBaccn[1]=XMAX.toDouble();
    XMAX=ui->textEditaccBz->toPlainText();
    BBaccn[2]=XMAX.toDouble();

    XMAX=ui->textEditaccM11->toPlainText();
    if (ui->textEditaccM11->document()->isModified()){
        MMaccn[0][0]=XMAX.toDouble();}
    else{
        MMaccn[0][0]=1;
    }
    //MMaccn[0][0]=XMAX.toDouble();
    XMAX=ui->textEditaccM12->toPlainText();
    MMaccn[0][1]=XMAX.toDouble();
    XMAX=ui->textEditaccM13->toPlainText();
    MMaccn[0][2]=XMAX.toDouble();
    XMAX=ui->textEditaccM21->toPlainText();
    MMaccn[1][0]=XMAX.toDouble();
    XMAX=ui->textEditaccM22->toPlainText();
    if (ui->textEditaccM22->document()->isModified()){
        MMaccn[1][1]=XMAX.toDouble();}
    else{
        MMaccn[1][1]=1;
    }
    //MMaccn[1][1]=XMAX.toDouble();
    XMAX=ui->textEditaccM23->toPlainText();
    MMaccn[1][2]=XMAX.toDouble();
    XMAX=ui->textEditaccM31->toPlainText();
    MMaccn[2][0]=XMAX.toDouble();
    XMAX=ui->textEditaccM32->toPlainText();
    MMaccn[2][1]=XMAX.toDouble();
    XMAX=ui->textEditaccM33->toPlainText();
    if (ui->textEditaccM33->document()->isModified()){
        MMaccn[2][2]=XMAX.toDouble();}
    else{
        MMaccn[2][2]=1;
    }
    //MMaccn[2][2]=XMAX.toDouble();

    XMAX=ui->textEditgyrBx->toPlainText();
    BBgyrn[0]=XMAX.toDouble();
    XMAX=ui->textEditgyrBy->toPlainText();
    BBgyrn[1]=XMAX.toDouble();
    XMAX=ui->textEditgyrBz->toPlainText();
    BBgyrn[2]=XMAX.toDouble();

    XMAX=ui->textEditgyrM11->toPlainText();
    if (ui->textEditgyrM11->document()->isModified()){
        MMgyrn[0][0]=XMAX.toDouble();}
    else{
        MMgyrn[0][0]=1;
    }
    //MMgyrn[0][0]=XMAX.toDouble();
    XMAX=ui->textEditgyrM12->toPlainText();
    MMgyrn[0][1]=XMAX.toDouble();
    XMAX=ui->textEditgyrM13->toPlainText();
    MMgyrn[0][2]=XMAX.toDouble();
    XMAX=ui->textEditgyrM21->toPlainText();
    MMgyrn[1][0]=XMAX.toDouble();
    XMAX=ui->textEditgyrM22->toPlainText();
    if (ui->textEditgyrM22->document()->isModified()){
        MMgyrn[1][1]=XMAX.toDouble();}
    else{
        MMgyrn[1][1]=1;
    }
    //MMgyrn[1][1]=XMAX.toDouble();
    XMAX=ui->textEditgyrM23->toPlainText();
    MMgyrn[1][2]=XMAX.toDouble();
    XMAX=ui->textEditgyrM31->toPlainText();
    MMgyrn[2][0]=XMAX.toDouble();
    XMAX=ui->textEditgyrM32->toPlainText();
    MMgyrn[2][1]=XMAX.toDouble();
    XMAX=ui->textEditgyrM33->toPlainText();
    if (ui->textEditgyrM33->document()->isModified()){
        MMgyrn[2][2]=XMAX.toDouble();}
    else{
        MMgyrn[2][2]=1;
    }
    //MMgyrn[2][2]=XMAX.toDouble();
}


calibrationDialog::~calibrationDialog()
{
    delete ui;
}

void calibrationDialog::on_pushButtonIMU1_clicked()
{
    ui->textEditmagBx->clear();
    ui->textEditmagBx->insertPlainText("0.1273");
    ui->textEditmagBy->clear();
    ui->textEditmagBy->insertPlainText("0.0037");
    ui->textEditmagBz->clear();
    ui->textEditmagBz->insertPlainText("0.0414");
    ui->textEditaccBx->clear();
    ui->textEditaccBx->insertPlainText("-0.0228");
    ui->textEditaccBy->clear();
    ui->textEditaccBy->insertPlainText("0.1103");
    ui->textEditaccBz->clear();
    ui->textEditaccBz->insertPlainText("0.0297");
    ui->textEditgyrBx->clear();
    ui->textEditgyrBx->insertPlainText("-0.3438");
    ui->textEditgyrBy->clear();
    ui->textEditgyrBy->insertPlainText("0.7105");
    ui->textEditgyrBz->clear();
    ui->textEditgyrBz->insertPlainText("-0.1948");
    ui->textEditmagM11->clear();
    ui->textEditmagM11->insertPlainText("2.9157");
    ui->textEditmagM12->clear();
    ui->textEditmagM12->insertPlainText("0.0813");
    ui->textEditmagM13->clear();
    ui->textEditmagM13->insertPlainText("-0.3152");
    ui->textEditmagM21->clear();
    ui->textEditmagM21->insertPlainText("-0.0909");
    ui->textEditmagM22->clear();
    ui->textEditmagM22->insertPlainText("2.9572");
    ui->textEditmagM23->clear();
    ui->textEditmagM23->insertPlainText("-0.3800");
    ui->textEditmagM31->clear();
    ui->textEditmagM31->insertPlainText("0.2696");
    ui->textEditmagM32->clear();
    ui->textEditmagM32->insertPlainText("0.4259");
    ui->textEditmagM33->clear();
    ui->textEditmagM33->insertPlainText("3.2263");
    ui->textEditaccM11->clear();
    ui->textEditaccM11->insertPlainText("1.0068");
    ui->textEditaccM12->clear();
    ui->textEditaccM12->insertPlainText("0.0011");
    ui->textEditaccM13->clear();
    ui->textEditaccM13->insertPlainText("-0.0947");
    ui->textEditaccM21->clear();
    ui->textEditaccM21->insertPlainText("-0.0070");
    ui->textEditaccM22->clear();
    ui->textEditaccM22->insertPlainText("0.9953");
    ui->textEditaccM23->clear();
    ui->textEditaccM23->insertPlainText("-0.1263");
    ui->textEditaccM31->clear();
    ui->textEditaccM31->insertPlainText("0.0901");
    ui->textEditaccM32->clear();
    ui->textEditaccM32->insertPlainText("0.1224");
    ui->textEditaccM33->clear();
    ui->textEditaccM33->insertPlainText("1.0020");
    ui->textEditgyrM11->clear();
    ui->textEditgyrM11->insertPlainText("0.8841");
    ui->textEditgyrM12->clear();
    ui->textEditgyrM12->insertPlainText("-0.0227");
    ui->textEditgyrM13->clear();
    ui->textEditgyrM13->insertPlainText("-0.0948");
    ui->textEditgyrM21->clear();
    ui->textEditgyrM21->insertPlainText("0.0112");
    ui->textEditgyrM22->clear();
    ui->textEditgyrM22->insertPlainText("0.9253");
    ui->textEditgyrM23->clear();
    ui->textEditgyrM23->insertPlainText("-0.1173");
    ui->textEditgyrM31->clear();
    ui->textEditgyrM31->insertPlainText("0.1033");
    ui->textEditgyrM32->clear();
    ui->textEditgyrM32->insertPlainText("0.1173");
    ui->textEditgyrM33->clear();
    ui->textEditgyrM33->insertPlainText("0.9354");
}

void calibrationDialog::on_pushButtonIMU2_clicked()
{
    ui->textEditmagBx->clear();
    ui->textEditmagBx->insertPlainText("0.0998");
    ui->textEditmagBy->clear();
    ui->textEditmagBy->insertPlainText("-0.0125");
    ui->textEditmagBz->clear();
    ui->textEditmagBz->insertPlainText("0.0001");
    ui->textEditaccBx->clear();
    ui->textEditaccBx->insertPlainText("-0.0726");
    ui->textEditaccBy->clear();
    ui->textEditaccBy->insertPlainText("0.1334");
    ui->textEditaccBz->clear();
    ui->textEditaccBz->insertPlainText("0.0343");
    ui->textEditgyrBx->clear();
    ui->textEditgyrBx->insertPlainText("0.2449");
    ui->textEditgyrBy->clear();
    ui->textEditgyrBy->insertPlainText("10.0001");
    ui->textEditgyrBz->clear();
    ui->textEditgyrBz->insertPlainText("2.3433");
    ui->textEditmagM11->clear();
    ui->textEditmagM11->insertPlainText("2.7470");
    ui->textEditmagM12->clear();
    ui->textEditmagM12->insertPlainText("0.1735");
    ui->textEditmagM13->clear();
    ui->textEditmagM13->insertPlainText("0.0673");
    ui->textEditmagM21->clear();
    ui->textEditmagM21->insertPlainText("-0.1373");
    ui->textEditmagM22->clear();
    ui->textEditmagM22->insertPlainText("2.7339");
    ui->textEditmagM23->clear();
    ui->textEditmagM23->insertPlainText("-0.0588");
    ui->textEditmagM31->clear();
    ui->textEditmagM31->insertPlainText("-0.0651");
    ui->textEditmagM32->clear();
    ui->textEditmagM32->insertPlainText("0.1206");
    ui->textEditmagM33->clear();
    ui->textEditmagM33->insertPlainText("3.1161");
    ui->textEditaccM11->clear();
    ui->textEditaccM11->insertPlainText("1.0102");
    ui->textEditaccM12->clear();
    ui->textEditaccM12->insertPlainText("0.0423");
    ui->textEditaccM13->clear();
    ui->textEditaccM13->insertPlainText("-0.0051");
    ui->textEditaccM21->clear();
    ui->textEditaccM21->insertPlainText("-0.0436");
    ui->textEditaccM22->clear();
    ui->textEditaccM22->insertPlainText("1.0052");
    ui->textEditaccM23->clear();
    ui->textEditaccM23->insertPlainText("-0.0184");
    ui->textEditaccM31->clear();
    ui->textEditaccM31->insertPlainText("0.0060");
    ui->textEditaccM32->clear();
    ui->textEditaccM32->insertPlainText("0.0203");
    ui->textEditaccM33->clear();
    ui->textEditaccM33->insertPlainText("1.0076");
    ui->textEditgyrM11->clear();
    ui->textEditgyrM11->insertPlainText("1.0543");
    ui->textEditgyrM12->clear();
    ui->textEditgyrM12->insertPlainText("0.0468");
    ui->textEditgyrM13->clear();
    ui->textEditgyrM13->insertPlainText("-0.0692");
    ui->textEditgyrM21->clear();
    ui->textEditgyrM21->insertPlainText("-0.0454");
    ui->textEditgyrM22->clear();
    ui->textEditgyrM22->insertPlainText("0.9613");
    ui->textEditgyrM23->clear();
    ui->textEditgyrM23->insertPlainText("-0.0402");
    ui->textEditgyrM31->clear();
    ui->textEditgyrM31->insertPlainText("0.0662");
    ui->textEditgyrM32->clear();
    ui->textEditgyrM32->insertPlainText("0.0467");
    ui->textEditgyrM33->clear();
    ui->textEditgyrM33->insertPlainText("1.0409");

}
