#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <thread>
#include <QThread>
#include "ProductDisplayer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow;

class myThreadTx : public QThread
{
    Q_OBJECT
protected:
    void run();
    MainWindow * pt;
 public:
    void setMainWindows(MainWindow * pt_windows) {pt = pt_windows;}
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void txRun();

private:
    Ui::MainWindow *ui;
    bool txRunning = false;
    myThreadTx txThread;
    ProductDisplayer * pt_disp;

private slots:
    void on_actionLOAD_triggered();
    void on_actionExit_triggered();
    void on_pushButtonDisplay_clicked();

    void openRecentFile(QAction*);



signals:

};


#endif // MAINWINDOW_H


