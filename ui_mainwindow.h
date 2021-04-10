/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLOAD;
    QAction *actionExit;
    QAction *actionConnect;
    QAction *actionStart_Session;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QTabWidget *tabWidget;
    QWidget *viewerTab;
    QPushButton *pushButtonDisplay;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QScrollArea *scrollAreaFilter;
    QWidget *scrollAreaWidgetContents_2;
    QLineEdit *lineEdit;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_3;
    QLineEdit *lineEdit_2;
    QPushButton *pushButtonAdd;
    QLineEdit *lineEditTrace;
    QLabel *label;
    QPushButton *pushButtonSave;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBoxAA;
    QDoubleSpinBox *doubleSpinBoxBB;
    QDoubleSpinBox *doubleSpinBoxCC;
    QDoubleSpinBox *doubleSpinBoxDD;
    QDoubleSpinBox *doubleSpinBoxEE;
    QWidget *calcTab;
    QPushButton *pushButtonCalculate;
    QLineEdit *lineEditTrace_2;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_5;
    QTextBrowser *textBrowser;
    QDoubleSpinBox *doubleSpinBoxA;
    QDoubleSpinBox *doubleSpinBoxB;
    QDoubleSpinBox *doubleSpinBoxC;
    QDoubleSpinBox *doubleSpinBoxD;
    QDoubleSpinBox *doubleSpinBoxE;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QPushButton *pushButtonSaveCoeff;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuRecent_Files;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1297, 1000);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1280, 1000));
        actionLOAD = new QAction(MainWindow);
        actionLOAD->setObjectName(QString::fromUtf8("actionLOAD"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QString::fromUtf8("actionConnect"));
        actionStart_Session = new QAction(MainWindow);
        actionStart_Session->setObjectName(QString::fromUtf8("actionStart_Session"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setHorizontalSpacing(1);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setEnabled(true);
        viewerTab = new QWidget();
        viewerTab->setObjectName(QString::fromUtf8("viewerTab"));
        pushButtonDisplay = new QPushButton(viewerTab);
        pushButtonDisplay->setObjectName(QString::fromUtf8("pushButtonDisplay"));
        pushButtonDisplay->setEnabled(false);
        pushButtonDisplay->setGeometry(QRect(30, 30, 35, 35));
        pushButtonDisplay->setMinimumSize(QSize(0, 35));
        pushButtonDisplay->setMaximumSize(QSize(35, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/images/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/icon/images/stop.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButtonDisplay->setIcon(icon);
        pushButtonDisplay->setIconSize(QSize(35, 27));
        scrollArea = new QScrollArea(viewerTab);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setEnabled(true);
        scrollArea->setGeometry(QRect(-50, 90, 1261, 841));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1259, 839));
        scrollArea->setWidget(scrollAreaWidgetContents);
        scrollAreaFilter = new QScrollArea(viewerTab);
        scrollAreaFilter->setObjectName(QString::fromUtf8("scrollAreaFilter"));
        scrollAreaFilter->setGeometry(QRect(220, 20, 141, 61));
        scrollAreaFilter->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 139, 59));
        scrollAreaFilter->setWidget(scrollAreaWidgetContents_2);
        lineEdit = new QLineEdit(viewerTab);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(220, 0, 141, 21));
        scrollArea_2 = new QScrollArea(viewerTab);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setGeometry(QRect(370, 20, 121, 61));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 119, 59));
        scrollArea_2->setWidget(scrollAreaWidgetContents_3);
        lineEdit_2 = new QLineEdit(viewerTab);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(370, 0, 121, 20));
        pushButtonAdd = new QPushButton(viewerTab);
        pushButtonAdd->setObjectName(QString::fromUtf8("pushButtonAdd"));
        pushButtonAdd->setEnabled(false);
        pushButtonAdd->setGeometry(QRect(80, 30, 35, 35));
        pushButtonAdd->setMinimumSize(QSize(0, 35));
        pushButtonAdd->setMaximumSize(QSize(35, 16777215));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/images/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonAdd->setIcon(icon1);
        pushButtonAdd->setIconSize(QSize(35, 27));
        lineEditTrace = new QLineEdit(viewerTab);
        lineEditTrace->setObjectName(QString::fromUtf8("lineEditTrace"));
        lineEditTrace->setGeometry(QRect(500, 60, 571, 20));
        label = new QLabel(viewerTab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(500, 40, 47, 13));
        pushButtonSave = new QPushButton(viewerTab);
        pushButtonSave->setObjectName(QString::fromUtf8("pushButtonSave"));
        pushButtonSave->setEnabled(false);
        pushButtonSave->setGeometry(QRect(130, 30, 35, 35));
        pushButtonSave->setMinimumSize(QSize(0, 35));
        pushButtonSave->setMaximumSize(QSize(35, 16777215));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonSave->setIcon(icon2);
        pushButtonSave->setIconSize(QSize(35, 27));
        label_3 = new QLabel(viewerTab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(500, 3, 61, 20));
        doubleSpinBoxAA = new QDoubleSpinBox(viewerTab);
        doubleSpinBoxAA->setObjectName(QString::fromUtf8("doubleSpinBoxAA"));
        doubleSpinBoxAA->setEnabled(false);
        doubleSpinBoxAA->setGeometry(QRect(570, 0, 61, 22));
        doubleSpinBoxBB = new QDoubleSpinBox(viewerTab);
        doubleSpinBoxBB->setObjectName(QString::fromUtf8("doubleSpinBoxBB"));
        doubleSpinBoxBB->setEnabled(false);
        doubleSpinBoxBB->setGeometry(QRect(630, 0, 61, 22));
        doubleSpinBoxCC = new QDoubleSpinBox(viewerTab);
        doubleSpinBoxCC->setObjectName(QString::fromUtf8("doubleSpinBoxCC"));
        doubleSpinBoxCC->setEnabled(false);
        doubleSpinBoxCC->setGeometry(QRect(690, 0, 61, 22));
        doubleSpinBoxDD = new QDoubleSpinBox(viewerTab);
        doubleSpinBoxDD->setObjectName(QString::fromUtf8("doubleSpinBoxDD"));
        doubleSpinBoxDD->setEnabled(false);
        doubleSpinBoxDD->setGeometry(QRect(750, 0, 61, 22));
        doubleSpinBoxEE = new QDoubleSpinBox(viewerTab);
        doubleSpinBoxEE->setObjectName(QString::fromUtf8("doubleSpinBoxEE"));
        doubleSpinBoxEE->setEnabled(false);
        doubleSpinBoxEE->setGeometry(QRect(810, 0, 61, 22));
        tabWidget->addTab(viewerTab, QString());
        calcTab = new QWidget();
        calcTab->setObjectName(QString::fromUtf8("calcTab"));
        pushButtonCalculate = new QPushButton(calcTab);
        pushButtonCalculate->setObjectName(QString::fromUtf8("pushButtonCalculate"));
        pushButtonCalculate->setEnabled(false);
        pushButtonCalculate->setGeometry(QRect(10, 10, 35, 35));
        pushButtonCalculate->setMinimumSize(QSize(0, 35));
        pushButtonCalculate->setMaximumSize(QSize(35, 16777215));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icon/images/calculate.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonCalculate->setIcon(icon3);
        pushButtonCalculate->setIconSize(QSize(35, 27));
        lineEditTrace_2 = new QLineEdit(calcTab);
        lineEditTrace_2->setObjectName(QString::fromUtf8("lineEditTrace_2"));
        lineEditTrace_2->setGeometry(QRect(390, 30, 571, 20));
        label_2 = new QLabel(calcTab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(390, 10, 47, 13));
        label_4 = new QLabel(calcTab);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(50, 20, 331, 20));
        label_5 = new QLabel(calcTab);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 50, 91, 21));
        textBrowser = new QTextBrowser(calcTab);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(10, 80, 351, 431));
        doubleSpinBoxA = new QDoubleSpinBox(calcTab);
        doubleSpinBoxA->setObjectName(QString::fromUtf8("doubleSpinBoxA"));
        doubleSpinBoxA->setEnabled(false);
        doubleSpinBoxA->setGeometry(QRect(420, 100, 141, 21));
        doubleSpinBoxB = new QDoubleSpinBox(calcTab);
        doubleSpinBoxB->setObjectName(QString::fromUtf8("doubleSpinBoxB"));
        doubleSpinBoxB->setEnabled(false);
        doubleSpinBoxB->setGeometry(QRect(420, 130, 141, 21));
        doubleSpinBoxC = new QDoubleSpinBox(calcTab);
        doubleSpinBoxC->setObjectName(QString::fromUtf8("doubleSpinBoxC"));
        doubleSpinBoxC->setEnabled(false);
        doubleSpinBoxC->setGeometry(QRect(420, 160, 141, 21));
        doubleSpinBoxD = new QDoubleSpinBox(calcTab);
        doubleSpinBoxD->setObjectName(QString::fromUtf8("doubleSpinBoxD"));
        doubleSpinBoxD->setEnabled(false);
        doubleSpinBoxD->setGeometry(QRect(420, 190, 141, 21));
        doubleSpinBoxE = new QDoubleSpinBox(calcTab);
        doubleSpinBoxE->setObjectName(QString::fromUtf8("doubleSpinBoxE"));
        doubleSpinBoxE->setEnabled(false);
        doubleSpinBoxE->setGeometry(QRect(420, 220, 141, 21));
        label_6 = new QLabel(calcTab);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(390, 100, 21, 21));
        label_7 = new QLabel(calcTab);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(390, 130, 21, 21));
        label_8 = new QLabel(calcTab);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(390, 160, 21, 21));
        label_9 = new QLabel(calcTab);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(390, 190, 21, 21));
        label_10 = new QLabel(calcTab);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(390, 220, 21, 21));
        pushButtonSaveCoeff = new QPushButton(calcTab);
        pushButtonSaveCoeff->setObjectName(QString::fromUtf8("pushButtonSaveCoeff"));
        pushButtonSaveCoeff->setEnabled(false);
        pushButtonSaveCoeff->setGeometry(QRect(420, 250, 141, 23));
        tabWidget->addTab(calcTab, QString());

        formLayout->setWidget(0, QFormLayout::SpanningRole, tabWidget);


        verticalLayout->addLayout(formLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1297, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuRecent_Files = new QMenu(menuFile);
        menuRecent_Files->setObjectName(QString::fromUtf8("menuRecent_Files"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addSeparator();
        menuFile->addAction(actionLOAD);
        menuFile->addAction(menuRecent_Files->menuAction());
        menuFile->addAction(actionExit);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionLOAD->setText(QCoreApplication::translate("MainWindow", "Carica file prodotti (csv)", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Esci", nullptr));
        actionConnect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        actionStart_Session->setText(QCoreApplication::translate("MainWindow", "Start Session", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonDisplay->setToolTip(QCoreApplication::translate("MainWindow", "Start Session", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonDisplay->setText(QString());
        lineEdit->setText(QCoreApplication::translate("MainWindow", "RICERCA PER AZIENDA", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("MainWindow", "RICERCA PER CODICE ", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonAdd->setToolTip(QCoreApplication::translate("MainWindow", "Start Session", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonAdd->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "Info", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonSave->setToolTip(QCoreApplication::translate("MainWindow", "Start Session", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonSave->setText(QString());
        label_3->setText(QCoreApplication::translate("MainWindow", "Coeff", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(viewerTab), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonCalculate->setToolTip(QCoreApplication::translate("MainWindow", "Start Session", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonCalculate->setText(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "Info", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Calcola Modello su file originale", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Output", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "A", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "B", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "D", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "E", nullptr));
        pushButtonSaveCoeff->setText(QCoreApplication::translate("MainWindow", "AGGIORNA COEFFICENTI", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(calcTab), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuRecent_Files->setTitle(QCoreApplication::translate("MainWindow", "File recenti ...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
