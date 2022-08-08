#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_nTimerId = startTimer ( 1000 );
    iCurImg=0;

    connect(ui->button,SIGNAL(clicked()),this,SLOT(slot_button_clicked()));


}

MainWindow::~MainWindow()
{
    delete ui;

}

QStringList enumfile(QString strPath)
{
    QStringList qRet;

    QString dirpath =strPath;

    QDir dir(dirpath);

    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.png"<<"*.bmp" << "*.dcm";
    QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    for(int i = 0; i< files.size(); ++i)
    {
        QString temp =files.at(i);
        qRet.append(strPath+"/"+temp);
        qDebug() << "filename: " << temp;
    }
    return qRet;

}

void MainWindow::slot_button_clicked()
{
    qDebug() << "11";
    if(m_nTimerId)
    {
        killTimer(m_nTimerId);
        m_nTimerId=0;
    }
    //QString fileName = QFileDialog::getOpenFileName(this,QStringLiteral("1"),"F:",QStringLiteral("*png *jpg"));
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    listAll=enumfile(dir);
    iCurImg=0;
    listCur=listAll;
    ui->sum->setText(QString("%1").arg(listCur.size()));

    if(m_nTimerId==0)
    {
        m_nTimerId = startTimer ( 1000 );
    }



}

//遍历播放
void MainWindow::timerEvent(QTimerEvent *event)
{
    if(listCur.size()==0  )
        return;
    if(iCurImg>=listCur.size())
    {
        return;
        iCurImg=0;
    }
    imageshow.load(listCur[iCurImg]);

    iCurImg++;
    QSize size(ui->label->width(),ui->label->height());

    ui->label->setPixmap(QPixmap::fromImage(imageshow.scaled(size)));
}

