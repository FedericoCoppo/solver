/********************************************************************************
** Form generated from reading UI file 'addproduct.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDPRODUCT_H
#define UI_ADDPRODUCT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_addProduct
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *lineEditCode;
    QLineEdit *lineEditCompany;
    QPushButton *pushButtonSaveAdd;
    QDoubleSpinBox *doubleSpinBoxWeight;
    QDoubleSpinBox *doubleSpinBoxSurface;
    QDoubleSpinBox *doubleSpinBoxPreparation;
    QDoubleSpinBox *doubleSpinBoxPackage;
    QDoubleSpinBox *doubleSpinBoxReturnPct;
    QDoubleSpinBox *doubleSpinBoxPrice;
    QLineEdit *lineEditTrace;

    void setupUi(QDialog *addProduct)
    {
        if (addProduct->objectName().isEmpty())
            addProduct->setObjectName(QString::fromUtf8("addProduct"));
        addProduct->resize(441, 311);
        label = new QLabel(addProduct);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 47, 13));
        label_2 = new QLabel(addProduct);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 50, 47, 13));
        label_3 = new QLabel(addProduct);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 80, 47, 13));
        label_4 = new QLabel(addProduct);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 110, 111, 16));
        label_5 = new QLabel(addProduct);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 140, 131, 16));
        label_6 = new QLabel(addProduct);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 170, 111, 16));
        label_7 = new QLabel(addProduct);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 200, 71, 16));
        label_8 = new QLabel(addProduct);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(20, 230, 47, 13));
        lineEditCode = new QLineEdit(addProduct);
        lineEditCode->setObjectName(QString::fromUtf8("lineEditCode"));
        lineEditCode->setGeometry(QRect(160, 20, 113, 20));
        lineEditCompany = new QLineEdit(addProduct);
        lineEditCompany->setObjectName(QString::fromUtf8("lineEditCompany"));
        lineEditCompany->setGeometry(QRect(160, 50, 113, 20));
        pushButtonSaveAdd = new QPushButton(addProduct);
        pushButtonSaveAdd->setObjectName(QString::fromUtf8("pushButtonSaveAdd"));
        pushButtonSaveAdd->setGeometry(QRect(370, 280, 61, 21));
        doubleSpinBoxWeight = new QDoubleSpinBox(addProduct);
        doubleSpinBoxWeight->setObjectName(QString::fromUtf8("doubleSpinBoxWeight"));
        doubleSpinBoxWeight->setGeometry(QRect(160, 80, 111, 22));
        doubleSpinBoxSurface = new QDoubleSpinBox(addProduct);
        doubleSpinBoxSurface->setObjectName(QString::fromUtf8("doubleSpinBoxSurface"));
        doubleSpinBoxSurface->setGeometry(QRect(160, 110, 111, 22));
        doubleSpinBoxPreparation = new QDoubleSpinBox(addProduct);
        doubleSpinBoxPreparation->setObjectName(QString::fromUtf8("doubleSpinBoxPreparation"));
        doubleSpinBoxPreparation->setGeometry(QRect(160, 140, 111, 22));
        doubleSpinBoxPackage = new QDoubleSpinBox(addProduct);
        doubleSpinBoxPackage->setObjectName(QString::fromUtf8("doubleSpinBoxPackage"));
        doubleSpinBoxPackage->setGeometry(QRect(160, 170, 111, 22));
        doubleSpinBoxReturnPct = new QDoubleSpinBox(addProduct);
        doubleSpinBoxReturnPct->setObjectName(QString::fromUtf8("doubleSpinBoxReturnPct"));
        doubleSpinBoxReturnPct->setGeometry(QRect(160, 200, 111, 22));
        doubleSpinBoxPrice = new QDoubleSpinBox(addProduct);
        doubleSpinBoxPrice->setObjectName(QString::fromUtf8("doubleSpinBoxPrice"));
        doubleSpinBoxPrice->setGeometry(QRect(160, 230, 111, 22));
        lineEditTrace = new QLineEdit(addProduct);
        lineEditTrace->setObjectName(QString::fromUtf8("lineEditTrace"));
        lineEditTrace->setGeometry(QRect(20, 280, 331, 20));

        retranslateUi(addProduct);

        QMetaObject::connectSlotsByName(addProduct);
    } // setupUi

    void retranslateUi(QDialog *addProduct)
    {
        addProduct->setWindowTitle(QCoreApplication::translate("addProduct", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("addProduct", "CODICE", nullptr));
        label_2->setText(QCoreApplication::translate("addProduct", "DITTA", nullptr));
        label_3->setText(QCoreApplication::translate("addProduct", "PESO", nullptr));
        label_4->setText(QCoreApplication::translate("addProduct", "SUPERFICE [mm^2]", nullptr));
        label_5->setText(QCoreApplication::translate("addProduct", "PREPARAZIONE [min/pz]]", nullptr));
        label_6->setText(QCoreApplication::translate("addProduct", "IMBALLAGGIO [min/pz]", nullptr));
        label_7->setText(QCoreApplication::translate("addProduct", "% RICHIAMI", nullptr));
        label_8->setText(QCoreApplication::translate("addProduct", "PREZZO", nullptr));
        pushButtonSaveAdd->setText(QCoreApplication::translate("addProduct", "SALVA", nullptr));
    } // retranslateUi

};

namespace Ui {
    class addProduct: public Ui_addProduct {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDPRODUCT_H
