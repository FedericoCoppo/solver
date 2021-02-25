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
#include "addproduct.h"

static bool taskIsRunning = true;

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
    ui->tabWidget->setTabText(0, "Visualizzatore");
    ui->tabWidget->setTabText(1, "Calcolatore Prezzi");

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

    taskIsRunning = true;
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
        pt_disp->ClearParamDisplayElement();
        if (pt_disp->isDisplayOn())
        {
           ui->pushButtonDisplay->toggle();
           pt_disp->SetDisplayOn(false);
        }

        if (g_prod.ProductParseFromExcel(fileNames[0]))
        {
            // enable calibration button
            ui->pushButtonDisplay->setEnabled(true);
            ui->pushButtonDisplay->setCheckable(true);
            ui->pushButtonAdd->setEnabled(true);
            pt_disp->CloseFilters();
            pt_disp->OpenFilters();
            ui->lineEditTrace->setText("FILE CORRETTAMENTE IMPORTATO");

            ui->pushButtonCalculate->setEnabled(true);
            modelFileName = fileNames[0];
            displayLcdCoeff();
            ui->label_4->setText("calcola modello su file: " + modelFileName);
        }
        else
        {
            ui->pushButtonDisplay->setEnabled(false);
            ui->pushButtonAdd->setEnabled(false);
            ui->lineEditTrace->setText("FILE NON TROVATO O FORMATO INCORRETTO");
            pt_disp->ClearParamDisplayElement();

            ui->pushButtonCalculate->setEnabled(false);
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
     pt_disp->ClearParamDisplayElement();

     if (pt_disp->isDisplayOn())
     {
        ui->pushButtonDisplay->toggle();
        pt_disp->SetDisplayOn(false);
     }

     if (g_prod.ProductParseFromExcel(file->text()))
     {
         // enable calibration button
         ui->pushButtonDisplay->setEnabled(true);
         ui->pushButtonDisplay->setCheckable(true);
         ui->pushButtonAdd->setEnabled(true);
         pt_disp->CloseFilters();
         pt_disp->OpenFilters();
         ui->lineEditTrace->setText("FILE " + file->text()  + " CORRETTAMENTE IMPORTATO");

         ui->pushButtonCalculate->setEnabled(true);
         modelFileName = file->text();
         displayLcdCoeff();
         ui->label_4->setText("calcola modello su file: " + modelFileName);
     }
     else
     {
         ui->pushButtonDisplay->setEnabled(false);
         ui->pushButtonAdd->setEnabled(false);
         ui->lineEditTrace->setText("FILE NON TROVATO O FORMATO INCORRETTO");

         ui->pushButtonCalculate->setEnabled(false);
     }
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow:: on_pushButtonDisplay_clicked()
{
    pt_disp->PushButtonDisplayClicked();
}

void MainWindow:: on_pushButtonAdd_clicked()
{
    // Remove all displayer ?

    addProduct* d = new addProduct(pt_disp, this);

    d->setWindowTitle("Aggiungi i dati di un nuovo prodotto");

    if (d->exec() == QDialog::Rejected)
    {
    }
    else
    {
    }

    delete d;

    // Update the filter
    pt_disp->CloseFilters();
    pt_disp->OpenFilters();
}

void MainWindow:: on_pushButtonSave_clicked()
{
    ui->pushButtonSave->clearFocus();
    if (g_prod.saveCSVFile() == false)
    {
        ui->lineEditTrace->setText("FILE NON SALVATO");
    }
    else
    {
         ui->lineEditTrace->setText("NUOVO FILE CORRETTAMENTE SALVATO");
    }
}

MainWindow::~MainWindow()
{
    txThread.terminate();
    taskIsRunning = false;

    if (pt_disp)
    {
        delete pt_disp;
        pt_disp = NULL;
    }

    delete ui;
}

void MainWindow::displayLcdCoeff()
{
    ui->doubleSpinBoxAA->setValue(g_prod.GetCoefficient(0));
    ui->doubleSpinBoxBB->setValue(g_prod.GetCoefficient(1));
    ui->doubleSpinBoxCC->setValue(g_prod.GetCoefficient(2));
    ui->doubleSpinBoxDD->setValue(g_prod.GetCoefficient(3));
    ui->doubleSpinBoxEE->setValue(g_prod.GetCoefficient(4));
}

void MainWindow::txRun()
{
    auto tStep = std::chrono::milliseconds(5);
    std::chrono::high_resolution_clock::time_point timePoint = std::chrono::high_resolution_clock::now() + tStep;
    // qDebug() << "task entrato";

    while(taskIsRunning)
    {
        // Fill the thread

        /*
        if (updateFilters)
        {
            updateFilters = false;

            // Update the filter
            pt_disp->CloseFilters();
            pt_disp->OpenFilters();

        }

        if (pt_disp)
        {
            if (pt_disp->CheckFilterUpdateNeeded())
            {
                // Update the filter
                pt_disp->CloseFilters();
                pt_disp->OpenFilters();
            }
        }
        */
        std::this_thread::sleep_until(timePoint);
        timePoint += tStep;
    }
}

void MainWindow::on_pushButtonCalculate_clicked()
{
    ui->textBrowser->setText("ATTENDERE IL CALCOLO DEL MODELLO");
    QString program = "C:/Federico/pers/solverTool/multilinearRegProdotti.exe";
    QStringList arguments;
    arguments << modelFileName << "fixed" << "0.5";

    //QProcess *myProcess = new QProcess();
    //myProcess->start(program, arguments);
    //myProcess->kill();
    //myProcess->waitForFinished();
    //delete myProcess;
    QProcess process;
    process.startDetached(program, arguments);

    // wait
    QThread::sleep(20);


    // READ FILE
    QString line;
    QFile inputFile("Coefficent.txt");
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
         line += in.readLine();
       }
       inputFile.close();
    }

    line.remove("[");
    line.remove("]");
    QString data = line;
    QStringList list;
    list = data.split(' ');

    for (int i = 0; i < list.size(); i++)
    {
        if(list.at(i) == "")
        {
            list.removeAt(i);
        }
    }




    //QString out_string(data);
    // Output the data
    ui->textBrowser->setText(data);
    ui->lineEditTrace->setText("MODELLO PRODOTTI CALCOLATO CORRETTAMENTE");

    // Search the coefficient
    int idx_a = list.indexOf("coeff_a:\r");
    QString coeffAStr = list[idx_a + 1];
    float a = coeffAStr.remove(coeffAStr.size() -1, 1).toFloat();

    int idx_b = list.indexOf("coeff_b:\r");
    QString coeffBStr = list[idx_b + 1];
    float b = coeffBStr.remove(coeffBStr.size() -1, 1).toFloat();

    int idx_c = list.indexOf("coeff_c:\r");
    QString coeffCStr = list[idx_c + 1];
    float c = coeffCStr.remove(coeffCStr.size() -1, 1).toFloat();

    int idx_d = list.indexOf("coeff_d:\r");
    QString coeffDStr = list[idx_d + 1];
    float d = coeffDStr.remove(coeffDStr.size() -1, 1).toFloat();

    int idx_e = list.indexOf("coeff_e:\r");
    QString coeffEStr = list[idx_e + 1];
    float e = coeffEStr.remove(coeffEStr.size() -1, 1).toFloat();


    a = list.at(0).toFloat();
    b = list.at(1).toFloat();
    c = list.at(2).toFloat();
    d = list.at(3).toFloat();
    e = list.at(4).toFloat();


    // keep only 6 digit
    a = ((float) qRound(a*1000000))/ (float) 1000000;
    b = ((float) qRound(b*1000000))/ (float) 1000000;
    c = ((float) qRound(c*1000000))/ (float) 1000000;
    d = ((float) qRound(d*1000000))/ (float) 1000000;
    e = ((float) qRound(e*1000000))/ (float) 1000000;

    ui->doubleSpinBoxA->setValue(a);
    ui->doubleSpinBoxB->setValue(b);
    ui->doubleSpinBoxC->setValue(c);
    ui->doubleSpinBoxD->setValue(d);
    ui->doubleSpinBoxE->setValue(e);

    ui->pushButtonSaveCoeff->setEnabled(true);
}

void MainWindow::on_pushButtonSaveCoeff_clicked()
{
    ui->pushButtonSaveCoeff->setEnabled(false);

/*
    QFile file(modelFileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
    }

    QFile ofile(modelFileName + "Tmp.csv");
    if (!ofile.open(QIODevice::ReadWrite)) {
        qDebug() << file.errorString();
    }

    uint32_t cnt = 0;
    bool coefficientCopyDone = false;
    QString s = ui->doubleSpinBoxA->text() + ";" + ui->doubleSpinBoxB->text() + ";" + ui->doubleSpinBoxC->text()
            + ";"  + ui->doubleSpinBoxD->text() + ";"  +  ui->doubleSpinBoxE->text() + '\n';
    QByteArray ba = s.toLocal8Bit();
    const char *c_s = ba.data();

    while (!file.atEnd())
    {
        if(cnt != 1)
        {
            ofile.write( file.readLine() );
        }
        else
        {
            file.readLine();
            ofile.write(c_s);
            coefficientCopyDone = true;
            cnt++;
        }

        if (!coefficientCopyDone)
        {
            cnt++;
        }
    }

    ofile.close();
    file.close();
    file.remove();
    ofile.rename(modelFileName);
*/
    g_prod.UpdateCoeff(ui->doubleSpinBoxA->value(), ui->doubleSpinBoxB->value(), ui->doubleSpinBoxC->value(), ui->doubleSpinBoxD->value(), ui->doubleSpinBoxE->value());
    ui->doubleSpinBoxAA->setValue(g_prod.GetCoefficient(0));
    ui->doubleSpinBoxBB->setValue(g_prod.GetCoefficient(1));
    ui->doubleSpinBoxCC->setValue(g_prod.GetCoefficient(2));
    ui->doubleSpinBoxDD->setValue(g_prod.GetCoefficient(3));
    ui->doubleSpinBoxEE->setValue(g_prod.GetCoefficient(4));

    if (pt_disp->isDisplayOn())
    {
        pt_disp->PushButtonDisplayClicked();
        pt_disp->PushButtonDisplayClicked();
    }
}




