#ifndef PRODUCTDISPLAYER_H
#define PRODUCTDISPLAYER_H


#include <QtWidgets/QLabel>
#include <QFileDialog>
#include <QLineEdit>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QSpinBox>

#include <U64SpinBox.h>
#include <I64SpinBox.h>
#include <DOUBLESpinBox.h>

#include "ui_mainwindow.h"
#include "SeriesProperties.h"
#include "Product.h"

#include <QButtonGroup>
#include <QMdiSubWindow>

class ProductDisplayer :
        public QWidget
{
    Q_OBJECT

public:

    typedef struct ProdDisplayer_
    {
        QHBoxLayout * layout_pt;
        QLineEdit * code_pt;
        QLineEdit * company_pt;
        QAbstractSpinBox * weight_pt;
        QAbstractSpinBox * surface_pt;
        QAbstractSpinBox * preparation_pt;
        QAbstractSpinBox * package_time_pt;
        QAbstractSpinBox * pctReturn_pt;
        QAbstractSpinBox * price_pt;
        Product::prodContent * prodContentPt;
        QPushButton * button_pt;

    } ProdDisplayer;

public:
    ProductDisplayer(Ui::MainWindow * pt_ui, QWidget* parent = nullptr);
    virtual ~ProductDisplayer();
    void displayProd();
    void displayTitle();
    QList < ProdDisplayer * > prodDisplList;
    void syncCal();
    void PushButtonDisplayClicked();

    /*
    double getSpinboxValue(int idx);
    void setSpinBoxValue(int idx, uint64_t val);
    void handleButton(int idx);
    */

private:
    Ui::MainWindow * p_ui;
    QButtonGroup btnGroup;
    bool isCalModifyEnabled;
    QVBoxLayout * items_layout;
    bool displayOn;

    void clearParamDisplayElement();
    void DoubleSlotInputChanged(double newVal, DOUBLEQSpinBox * pt);

    /*
    void U64slotInputChanged(uint64_t newVal, U64QSpinBox * pt);
    void I64slotInputChanged(int64_t newVal, I64QSpinBox * pt);
    */
};

#endif // PRODUCTDISPLAYER_H
