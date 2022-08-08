#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int iCurImg;
    int m_nTimerId;
    void timerEvent ( QTimerEvent *event );
    QStringList listAll;
    QStringList listCur;
    QImage imageshow;

private:
    Ui::MainWindow *ui;
private slots:
    void slot_button_clicked();

};
#endif // MAINWINDOW_H
