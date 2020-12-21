#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <QVariant>
#include <QtWidgets>

#ifdef __WIN32
#include <shlobj.h> /* get user path */
#endif

#include <fstream>
#include "QActionWrapper.h"
#include "Product.h"

void myThreadTx::run()
{
    pt->txRun();
}

std::vector<QAction*> gvp_actionRecentFiles;
QStringList g_recent_files_paths;
std::string recentFilesPath;
std::ofstream g_recentFileOut;

bool getRecentFilesPath()
{
    bool ret = false;
    char path[ MAX_PATH ];
#ifdef __WIN32 /* get user path */
    /* C:\Users\[User] */
    if (SHGetFolderPathA( NULL, CSIDL_PROFILE, NULL, 0, path ) != S_OK)
    {
        ret = false;
    }
    else
    {
        recentFilesPath = path;
        recentFilesPath += "\\MTRecentFiles";
        ret = true;
    }
#endif
    return ret;
}

void createRecentFile()
{
    g_recentFileOut.open(recentFilesPath.c_str(), std::ofstream::out | std::ofstream::trunc);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSize availableSize = qApp->desktop()->availableGeometry().size();
    QSize newSize( availableSize.width()*0.995, availableSize.height()*0.953 );

    setGeometry(
                QStyle::alignedRect(
                    Qt::LeftToRight,
                    Qt::AlignTop,
                    newSize,
                    qApp->desktop()->availableGeometry()
                    )
                );

    ui->pushButtonDisplay->setEnabled(false);

    /* read recent files paths */

    if ( getRecentFilesPath() )
    {
        std::ifstream g_recentFileIn;

        g_recentFileIn.open(recentFilesPath.c_str());

        g_recent_files_paths.clear();

        int i = 0;
        unsigned j = 0;
        if ( g_recentFileIn.is_open() )
        {
            do
            {
                std::string tmp;
                g_recentFileIn >> tmp;
                if ( tmp != "" )
                {
                    g_recent_files_paths.append(QString::fromStdString(tmp));
                }
                tmp.clear();
            }while( !g_recentFileIn.eof() );

            g_recentFileIn.close();
        }

        /* add action menu for the last 5 recent files */

        for ( i = g_recent_files_paths.size()-1, j = 0; (i >= 0) && (i >= g_recent_files_paths.size()-5); --i )
        {
            gvp_actionRecentFiles.push_back(new QActionWrapper(g_recent_files_paths[i], this));
            connect(gvp_actionRecentFiles[j], SIGNAL(extendedTriggered(QAction*)), this, SLOT(openRecentFile(QAction*))); /* TODO custom QAction signal(QAction* this) in order open the a2l file in Action name from a single slot */
            ui->menuRecent_Files->addAction(gvp_actionRecentFiles[j++]);
        }
    }

    pt_disp = new ProductDisplayer(ui);

    // tx thread
    txRunning = true;
    txThread.start();

}

void MainWindow::on_actionLOAD_triggered()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("excel file (*.csv)"));
    dialog.setViewMode(QFileDialog::Detail);

    QStringList fileNames;
    if (dialog.exec())
    {
        fileNames = dialog.selectedFiles();

        // READ excel
        g_prod.Clear();

        if (g_prod.ProductParseFromExcel(fileNames[0]))
        {
            // enable calibration button
            ui->pushButtonDisplay->setEnabled(true);
        }
        else
        {
            ui->pushButtonDisplay->setEnabled(false);
        }

        // update history
        if ( getRecentFilesPath() && !g_recent_files_paths.contains(fileNames[0]) )
        {
            int i;
            createRecentFile();
            if ( g_recentFileOut.is_open() )
            {
                g_recent_files_paths.append(fileNames[0]);
                if ( g_recent_files_paths.size() < 6 )
                {
                    i = 0;
                }
                else
                {
                    i = g_recent_files_paths.size()-5;
                }
                for ( ; (i < g_recent_files_paths.size()-1) ; ++i )
                {
                    g_recentFileOut << g_recent_files_paths[i].toStdString() << "\n";
                }
                g_recentFileOut << g_recent_files_paths[i].toStdString();
                g_recentFileOut.close();
                g_recentFileOut.clear();
            }
        }
    }
}

void MainWindow::openRecentFile(QAction* file)
{
    // remove previous struct
     g_prod.Clear();

     if (g_prod.ProductParseFromExcel(file->text()))
     {
         // enable calibration button
         ui->pushButtonDisplay->setEnabled(true);
     }
     else
     {
         ui->pushButtonDisplay->setEnabled(false);
     }
}

void MainWindow::on_actionExit_triggered()
{
    QString program("multilinearRegProdotti.exe");
    QStringList parameters;

    QProcess::startDetached(program, parameters);
    // this->close();


}

void MainWindow:: on_pushButtonDisplay_clicked()
{
    qDebug() << "clicked";
    pt_disp->PushButtonDisplayClicked();
}

MainWindow::~MainWindow()
{
    txThread.terminate();
    txRunning = false;

    if (pt_disp)
    {
        delete pt_disp;
        pt_disp = NULL;
    }

    delete ui;
}

void MainWindow::txRun()
{
    auto tStep = std::chrono::milliseconds(5);
    std::chrono::high_resolution_clock::time_point timePoint = std::chrono::high_resolution_clock::now() + tStep;

    while(txRunning)
    {
        // Fill the thread

        std::this_thread::sleep_until(timePoint);
        timePoint += tStep;
    }
}

