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

#include "TextFilter.h"
#include "deleteconfirm.h"

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
        QPushButton * deletebutton_pt;
        QString oldCode;

    } ProdDisplayer;

public:
    ProductDisplayer(Ui::MainWindow * pt_ui, QWidget* parent = nullptr);
    virtual ~ProductDisplayer();
    void OpenFilters();
    void CloseFilters();
    void DisplayProd();
    void SetDisplayOn(bool val) { displayOn = val;}
    void SetScrollEnable(bool val) { scrollEnabled = val;}

    QList < ProdDisplayer * > prodDisplList;
    void PushButtonDisplayClicked();
    void ClearParamDisplayElement();
    bool isDisplayOn() { return displayOn; }
    Ui::MainWindow * Get_p_ui() {return p_ui;}

    /*
    double getSpinboxValue(int idx);
    void setSpinBoxValue(int idx, uint64_t val);
    void handleButton(int idx);
    */

private:
    Ui::MainWindow * p_ui;
    QButtonGroup btnGroup;
    QButtonGroup btnGroupDelete;
    bool isCalModifyEnabled;
    QVBoxLayout * items_layout;
    QList < QLabel * > titleLabelList;
    bool displayOn;
    bool filterOpened;
    bool titleDisplayed;
    bool isScrollBarConnected;
    bool scrollEnabled;
    int32_t calibrationAdded;
    bool isMeasDisplayTerminated;
    int16_t maxCalibrationForCycle;

    // filter part
    QCompleter *completerCompany = nullptr;
    TextFilter * textEditFilterCompany;
    QCompleter *completerCode = nullptr;
    TextFilter * textEditFilterCode;
    bool buttonConnected;

    void clearTitle();
    void creatMeas(int index, int incrementalElement);
    void displayTitle();
    bool eventFilter(QObject *obj, QEvent *event);

    /*
    void U64slotInputChanged(uint64_t newVal, U64QSpinBox * pt);
    void I64slotInputChanged(int64_t newVal, I64QSpinBox * pt);
    */

private slots:
    void measurementSelectedCompany(QString str);
    void measurementSelectedCode(QString str);
    void vScrollValueChanged(int);
    void handleButton(int idx);
    void handleButtonDelete(int idx);
};

#endif // PRODUCTDISPLAYER_H
