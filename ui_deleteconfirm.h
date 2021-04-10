/********************************************************************************
** Form generated from reading UI file 'deleteconfirm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DELETECONFIRM_H
#define UI_DELETECONFIRM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_DeleteConfirm
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;

    void setupUi(QDialog *DeleteConfirm)
    {
        if (DeleteConfirm->objectName().isEmpty())
            DeleteConfirm->setObjectName(QString::fromUtf8("DeleteConfirm"));
        DeleteConfirm->resize(435, 94);
        buttonBox = new QDialogButtonBox(DeleteConfirm);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(0, 50, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(DeleteConfirm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 20, 491, 20));

        retranslateUi(DeleteConfirm);
        QObject::connect(buttonBox, SIGNAL(accepted()), DeleteConfirm, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DeleteConfirm, SLOT(reject()));

        QMetaObject::connectSlotsByName(DeleteConfirm);
    } // setupUi

    void retranslateUi(QDialog *DeleteConfirm)
    {
        DeleteConfirm->setWindowTitle(QCoreApplication::translate("DeleteConfirm", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("DeleteConfirm", "PREMERE OK PER CONFERMARE CANCELLAZIONE PRODOTTO", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DeleteConfirm: public Ui_DeleteConfirm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELETECONFIRM_H
