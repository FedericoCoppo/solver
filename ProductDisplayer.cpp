#include "ProductDisplayer.h"

#include <QtCore/qmath.h>
#include <QMessageBox>
#include <QTextStream>

ProductDisplayer::ProductDisplayer(Ui::MainWindow * pt_ui, QWidget* parent) : QWidget(parent)
{
    isCalModifyEnabled = false;
    p_ui = pt_ui;
    items_layout = new QVBoxLayout (p_ui->scrollAreaWidgetContents); /* this name is decided by uic when it compiles your .ui XML file */
    items_layout->setSpacing (4); /* adjust to taste */

    displayOn = false;
}

ProductDisplayer::~ProductDisplayer()
{
    clearParamDisplayElement();
    delete items_layout;
}

void ProductDisplayer::clearParamDisplayElement()
{
    // remove display element
    int iNum = prodDisplList.count();

    for (int i=0; i < iNum; i++)
    {
        ProdDisplayer * tmp = prodDisplList.takeAt(0);
        tmp->prodContentPt = NULL;
        delete tmp->layout_pt;
        delete tmp->code_pt;
        delete tmp->company_pt;
        delete tmp->weight_pt;
        delete tmp->surface_pt;
        delete tmp->preparation_pt;
        delete tmp->package_time_pt;
        delete tmp->price_pt;
        delete tmp->button_pt;
        delete (tmp);
    }
}

void ProductDisplayer::PushButtonDisplayClicked()
{
    // read file
    if (g_prod.GetIsProductFilled())
    {
        if (displayOn == false)
        {
            clearParamDisplayElement(); // clear previous element
            displayProd();
            displayOn = true;
        }
        else
        {
            clearParamDisplayElement();
        }
    }
}

void ProductDisplayer::displayTitle()
{
    // Title
    QLabel *title_label;
    QHBoxLayout * hbox_layout = new QHBoxLayout ();

    title_label  = new QLabel("");
    title_label->setMinimumWidth (50);
    title_label->setMaximumWidth (60);
    hbox_layout->addWidget (title_label);

    title_label  = new QLabel("CODICE");
    title_label->setMinimumWidth (120);
    title_label->setMaximumWidth (130);
    hbox_layout->addWidget (title_label);

    title_label  = new QLabel("DITTA");
    title_label->setMinimumWidth (120);
    title_label->setMaximumWidth (130);
    hbox_layout->addWidget (title_label);

    title_label  = new QLabel("PESO [g]");
    title_label->setMinimumWidth (120);
    title_label->setMaximumWidth (130);
    hbox_layout->addWidget (title_label);

    title_label  = new QLabel("SUPERFICE [mm^2]");
    title_label->setMinimumWidth (120);
    title_label->setMaximumWidth (130);
    hbox_layout->addWidget (title_label);

    title_label  = new QLabel("PREPARAZIONE [min]");
    title_label->setMinimumWidth (120);
    title_label->setMaximumWidth (130);
    hbox_layout->addWidget (title_label);

    title_label  = new QLabel("IMBALLAGGIO [min]");
    title_label->setMinimumWidth (120);
    title_label->setMaximumWidth (130);
    hbox_layout->addWidget (title_label);

    title_label  = new QLabel("% RICHIAMI");
    title_label->setMinimumWidth (120);
    title_label->setMaximumWidth (130);
    hbox_layout->addWidget (title_label);

    title_label  = new QLabel("PREZZO");
    title_label->setMinimumWidth (120);
    title_label->setMaximumWidth (130);
    hbox_layout->addWidget (title_label);

    title_label  = new QLabel("MODIFICA");
    title_label->setMinimumWidth (120);
    title_label->setMaximumWidth (130);
    hbox_layout->addWidget (title_label);

    items_layout->addLayout (hbox_layout);
}

void ProductDisplayer::displayProd()
{
    if (g_prod.GetIsProductFilled())
    {
        // display
        QLineEdit * line;
        QLabel *items_label;
        QHBoxLayout *hbox_layout;
        items_label = new QLabel ("0x0000000000000"); /* longest possible text for left-hand label */
        items_label->updateGeometry ();
        delete items_label;
        QPushButton *changeBtn;

        displayTitle();

        for (int i = 0; i <  g_prod.GetProdListCnt(); ++i )
        {
            ProdDisplayer * displayTmp = new ProdDisplayer();

            // link displayer with calibration
            displayTmp->prodContentPt = g_prod.GetProdContent(i);

            hbox_layout = new QHBoxLayout ();

            /* code */
            line = new QLineEdit (g_prod.GetCode(i));
            line->setMinimumWidth(70);
            line->setMaximumWidth(80);
            hbox_layout->addWidget (line);
            displayTmp->layout_pt = hbox_layout;
            displayTmp->code_pt = line;
            line->setEnabled(false);

            /* company */
            line = new QLineEdit (g_prod.GetCompany(i));
            line->setMinimumWidth(70);
            line->setMaximumWidth(80);
            hbox_layout->addWidget (line);
            displayTmp->layout_pt = hbox_layout;
            displayTmp->company_pt = line;
            line->setEnabled(false);

            /* weight */
            DOUBLEQSpinBox * doubleSpinBoxEntry = new DOUBLEQSpinBox(g_prod.GetProdContent(i));
            doubleSpinBoxEntry->blockSignals(true);
            doubleSpinBoxEntry->setMinimumWidth(70);
            doubleSpinBoxEntry->setMaximumWidth(80);
            hbox_layout->addWidget (doubleSpinBoxEntry);
            doubleSpinBoxEntry->setValue(g_prod.GetWeight(i));
            doubleSpinBoxEntry->setSingleStep(0.1);
            doubleSpinBoxEntry->setRange(0, std::numeric_limits<float>::max());  // - 3.4 * pow(10, 38) 3.4 * pow(10, 38)
            displayTmp->weight_pt = doubleSpinBoxEntry;
            doubleSpinBoxEntry->blockSignals(false);
            connect(doubleSpinBoxEntry, QOverload<double, DOUBLEQSpinBox * >::of(&DOUBLEQSpinBox::valueChanged) , this, &ProductDisplayer::DoubleSlotInputChanged);
            displayTmp->weight_pt->setEnabled(false);

            /* surface */
            doubleSpinBoxEntry = new DOUBLEQSpinBox(g_prod.GetProdContent(i));
            doubleSpinBoxEntry->blockSignals(true);
            doubleSpinBoxEntry->setMinimumWidth(70);
            doubleSpinBoxEntry->setMaximumWidth(80);
            hbox_layout->addWidget (doubleSpinBoxEntry);
            doubleSpinBoxEntry->setValue(g_prod.GetSurface_mm2(i));
            doubleSpinBoxEntry->setSingleStep(0.1);
            doubleSpinBoxEntry->setRange(0, std::numeric_limits<float>::max());  // - 3.4 * pow(10, 38) 3.4 * pow(10, 38)
            displayTmp->surface_pt = doubleSpinBoxEntry;
            doubleSpinBoxEntry->blockSignals(false);
            connect(doubleSpinBoxEntry, QOverload<double, DOUBLEQSpinBox * >::of(&DOUBLEQSpinBox::valueChanged) , this, &ProductDisplayer::DoubleSlotInputChanged);
            displayTmp->surface_pt->setEnabled(false);

            /* preparation */
            doubleSpinBoxEntry = new DOUBLEQSpinBox(g_prod.GetProdContent(i));
            doubleSpinBoxEntry->blockSignals(true);
            doubleSpinBoxEntry->setMinimumWidth(70);
            doubleSpinBoxEntry->setMaximumWidth(80);
            hbox_layout->addWidget (doubleSpinBoxEntry);
            doubleSpinBoxEntry->setValue(g_prod.GetTimePreparation(i));
            doubleSpinBoxEntry->setSingleStep(0.1);
            doubleSpinBoxEntry->setRange(0, std::numeric_limits<float>::max());  // - 3.4 * pow(10, 38) 3.4 * pow(10, 38)
            displayTmp->preparation_pt = doubleSpinBoxEntry;
            doubleSpinBoxEntry->blockSignals(false);
            connect(doubleSpinBoxEntry, QOverload<double, DOUBLEQSpinBox * >::of(&DOUBLEQSpinBox::valueChanged) , this, &ProductDisplayer::DoubleSlotInputChanged);
            displayTmp->preparation_pt->setEnabled(false);

            /* package */
            doubleSpinBoxEntry = new DOUBLEQSpinBox(g_prod.GetProdContent(i));
            doubleSpinBoxEntry->blockSignals(true);
            doubleSpinBoxEntry->setMinimumWidth(70);
            doubleSpinBoxEntry->setMaximumWidth(80);
            hbox_layout->addWidget (doubleSpinBoxEntry);
            doubleSpinBoxEntry->setValue(g_prod.GetTimePackage(i));
            doubleSpinBoxEntry->setSingleStep(0.1);
            doubleSpinBoxEntry->setRange(0, std::numeric_limits<float>::max());  // - 3.4 * pow(10, 38) 3.4 * pow(10, 38)
            displayTmp->package_time_pt = doubleSpinBoxEntry;
            doubleSpinBoxEntry->blockSignals(false);
            connect(doubleSpinBoxEntry, QOverload<double, DOUBLEQSpinBox * >::of(&DOUBLEQSpinBox::valueChanged) , this, &ProductDisplayer::DoubleSlotInputChanged);
            displayTmp->package_time_pt->setEnabled(false);

            /* return */
            doubleSpinBoxEntry = new DOUBLEQSpinBox(g_prod.GetProdContent(i));
            doubleSpinBoxEntry->blockSignals(true);
            doubleSpinBoxEntry->setMinimumWidth(70);
            doubleSpinBoxEntry->setMaximumWidth(80);
            hbox_layout->addWidget (doubleSpinBoxEntry);
            doubleSpinBoxEntry->setValue(g_prod.GetPctReturn(i));
            doubleSpinBoxEntry->setSingleStep(0.1);
            doubleSpinBoxEntry->setRange(0, std::numeric_limits<float>::max());  // - 3.4 * pow(10, 38) 3.4 * pow(10, 38)
            displayTmp->pctReturn_pt = doubleSpinBoxEntry;
            doubleSpinBoxEntry->blockSignals(false);
            connect(doubleSpinBoxEntry, QOverload<double, DOUBLEQSpinBox * >::of(&DOUBLEQSpinBox::valueChanged) , this, &ProductDisplayer::DoubleSlotInputChanged);
            displayTmp->pctReturn_pt->setEnabled(false);

            /* price */
            doubleSpinBoxEntry = new DOUBLEQSpinBox(g_prod.GetProdContent(i));
            doubleSpinBoxEntry->blockSignals(true);
            doubleSpinBoxEntry->setMinimumWidth(70);
            doubleSpinBoxEntry->setMaximumWidth(80);
            hbox_layout->addWidget (doubleSpinBoxEntry);
            doubleSpinBoxEntry->setValue(g_prod.GetNominalPrice(i));
            doubleSpinBoxEntry->setSingleStep(0.1);
            doubleSpinBoxEntry->setRange(0, std::numeric_limits<float>::max());  // - 3.4 * pow(10, 38) 3.4 * pow(10, 38)
            displayTmp->price_pt = doubleSpinBoxEntry;
            doubleSpinBoxEntry->blockSignals(false);
            connect(doubleSpinBoxEntry, QOverload<double, DOUBLEQSpinBox * >::of(&DOUBLEQSpinBox::valueChanged) , this, &ProductDisplayer::DoubleSlotInputChanged);
            displayTmp->price_pt->setEnabled(false);

            /* button */
            changeBtn = new QPushButton(p_ui->scrollAreaWidgetContents);
            changeBtn->setObjectName(QString::fromUtf8("CHANGE"));
            changeBtn->setMinimumSize(50,30);
            changeBtn->setMaximumSize(60,30);
            changeBtn->setText(QCoreApplication::translate("CalibrationUi", "CHANGE", nullptr));
            changeBtn->setEnabled(false);
            hbox_layout->addWidget (changeBtn);

            items_layout->addLayout (hbox_layout);
            displayTmp->button_pt = changeBtn;

            btnGroup.addButton(changeBtn, i);
            prodDisplList.append(displayTmp);
        }

        connect(&btnGroup, SIGNAL (buttonClicked(int)), this, SLOT (handleButton(int)));
    }
}



void ProductDisplayer::syncCal()
{

    // update calib

    /*
    if (g_prod.getWorkerThread()->IsConnected())
    {
        for (int i = 0; i < g_prod.getCalListCnt(); ++i)
        {
            double data = g_prod.GetValueXCP(i);
            g_calib.getCalContent(i)->value = data;
            g_calib.getCalContent(i)->lastVal = data;
            g_calib.getCalContent(i)->initVal = data;
        }
    }
    */
}

void ProductDisplayer::DoubleSlotInputChanged(double newVal, DOUBLEQSpinBox * pt)
{
    /*
    uint32_t idx = pt->getCalLink()->index;
    ui.traceTxt->append("Cal " + QString::number(idx) + " updated at " + QString::number(newVal));
    if (newVal == pt->getCalLink()->lastVal)
    {
        calDisplList[idx]->isValueUpdatedOnCal = true;
        calDisplList[idx]->button_pt->setEnabled(false);
        if (newVal == pt->getCalLink()->initVal)
        {
            calDisplList[idx]->button_pt->setStyleSheet("background-color: light grey");
            calDisplList[idx]->button_pt->setText(QCoreApplication::translate("CalibrationUi", "CHANGE", nullptr));
        }
        else
        {
            calDisplList[idx]->button_pt->setStyleSheet("background-color: yellow");
            calDisplList[idx]->button_pt->setText(QCoreApplication::translate("CalibrationUi", "CHANGED", nullptr));
        }
    }
    else
    {
        // Allow to change
        calDisplList[idx]->button_pt->setEnabled(true);
        calDisplList[idx]->button_pt->setStyleSheet("background-color: red");
        calDisplList[idx]->button_pt->setText(QCoreApplication::translate("CalibrationUi", "CHANGE?", nullptr));
        calDisplList[idx]->isValueUpdatedOnCal = false;
    }
    */
}

#if 0
void ProductDisplayer::U64slotInputChanged(uint64_t newVal, U64QSpinBox * pt)
{
    uint32_t idx = pt->getCalLink()->index;
    ui.traceTxt->append("Cal " + QString::number(idx) + " updated at " + QString::number(newVal));

    if (newVal == pt->getCalLink()->lastVal)
    {
        calDisplList[idx]->isValueUpdatedOnCal = true;
        calDisplList[idx]->button_pt->setEnabled(false);
        if (newVal == pt->getCalLink()->initVal)
        {
            calDisplList[idx]->button_pt->setStyleSheet("background-color: light grey");
            calDisplList[idx]->button_pt->setText(QCoreApplication::translate("CalibrationUi", "CHANGE", nullptr));
        }
        else
        {
            calDisplList[idx]->button_pt->setStyleSheet("background-color: yellow");
            calDisplList[idx]->button_pt->setText(QCoreApplication::translate("CalibrationUi", "CHANGED", nullptr));
        }
    }
    else
    {
        calDisplList[idx]->button_pt->setEnabled(true);
        calDisplList[idx]->button_pt->setStyleSheet("background-color: red");
        calDisplList[idx]->button_pt->setText(QCoreApplication::translate("CalibrationUi", "CHANGE?", nullptr));
        calDisplList[idx]->isValueUpdatedOnCal = false;
    }
}

void ProductDisplayer::I64slotInputChanged(int64_t newVal, I64QSpinBox * pt)
{
    uint32_t idx = pt->getCalLink()->index;
    ui.traceTxt->append("Cal " + QString::number(idx) + " updated at " + QString::number(newVal));

    if (newVal == pt->getCalLink()->lastVal)
    {
        calDisplList[idx]->isValueUpdatedOnCal = true;
        calDisplList[idx]->button_pt->setEnabled(false);
        if (newVal == pt->getCalLink()->initVal)
        {
            calDisplList[idx]->button_pt->setStyleSheet("background-color: light grey");
            calDisplList[idx]->button_pt->setText(QCoreApplication::translate("CalibrationUi", "CHANGE", nullptr));
        }
        else
        {
            calDisplList[idx]->button_pt->setStyleSheet("background-color: yellow");
            calDisplList[idx]->button_pt->setText(QCoreApplication::translate("CalibrationUi", "CHANGED", nullptr));
        }
    }
    else
    {
        calDisplList[idx]->button_pt->setEnabled(true);
        calDisplList[idx]->button_pt->setStyleSheet("background-color: red");
        calDisplList[idx]->button_pt->setText(QCoreApplication::translate("CalibrationUi", "CHANGE?", nullptr));
        calDisplList[idx]->isValueUpdatedOnCal = false;
    }
}

void ProductDisplayer::handleButton(int idx)
{
    ui.traceTxt->append("CAL " + QString::number(idx) + " <" + calDisplList[idx]->name_pt->text() + "> " + " change request.." );

    if (g_calib.getWorkerThread()->IsConnected()) // Check if connected
    {
        double value = getSpinboxValue(idx);

        // change the value
        if (g_calib.SetValue(idx, value))
        {
            g_calib.SetLastValue(idx, value);

            // update display last value
            calDisplList[idx]->lastVal_pt->setText(QString::number(value));
            calDisplList[idx]->isValueUpdatedOnCal = true;

            // update button
            calDisplList[idx]->button_pt->setEnabled(false);

            if (g_calib.GetLastValue(idx) != g_calib.GetInitValue(idx))
            {
                calDisplList[idx]->button_pt->setStyleSheet("background-color: yellow");
                calDisplList[idx]->button_pt->setText("CHANGED");
            }
            else
            {
                calDisplList[idx]->button_pt->setStyleSheet("background-color: light grey");
                calDisplList[idx]->button_pt->setText("CHANGE");
            }

            uint32_t address = g_calib.GetAddress(idx);
            float val =  g_calib.GetValue(idx);
            Calibrations::Types calType = g_calib.GetType(idx);
            ui.traceTxt->append("ADD: " + QString::number(address, 16) + " VAL: " + QString::number(val) );
        }
        else
        {
            ui.traceTxt->setTextColor(QColor(255, 0, 0)); // RED DISPLAY FOR ERROR
            ui.traceTxt->append("CALIBRATION PROTOCOL ERROR!" );
            ui.traceTxt->setTextColor(QColor(0, 255, 255)); // MAGENTA DISPLAY AFTER AN ERROR
        }
    }
    else
    {
        ui.traceTxt->setTextColor(QColor(255, 0, 0)); // RED DISPLAY FOR ERROR
        ui.traceTxt->append("CAL " + QString::number(idx) + " <" + calDisplList[idx]->name_pt->text() + "> " + " CALIBRATION FAIL!");
        ui.traceTxt->setTextColor(QColor(0, 255, 255)); // MAGENTA DISPLAY AFTER AN ERROR
    }
}

double ProductDisplayer::getSpinboxValue(int idx)
{
    double value = 0;
    switch (g_calib.GetType(idx))
    {
    case Calibrations::Types::CAL_U8:
    case Calibrations::Types::CAL_U16:
    case Calibrations::Types::CAL_U32:
    case Calibrations::Types::CAL_U64:
        value = ( (U64QSpinBox *) calDisplList[idx]->val_pt)->getValue();
        break;
    case Calibrations::Types::CAL_S8:
    case Calibrations::Types::CAL_S16:
    case Calibrations::Types::CAL_S32:
    case Calibrations::Types::CAL_S64:
        value = ( (I64QSpinBox *) calDisplList[idx]->val_pt)->getValue();
        break;
    case Calibrations::Types::CAL_F32:
    case Calibrations::Types::CAL_F64:
        value = ( (DOUBLEQSpinBox *) calDisplList[idx]->val_pt)->getValue();
        break;
    }

    return value;
}

void ProductDisplayer::setSpinBoxValue(int idx, uint64_t val)
{
    double * ptrDouble = nullptr;
    float * ptrFloat = nullptr;

    switch (g_calib.GetType(idx))
    {
    case Calibrations::Types::CAL_U8:
    case Calibrations::Types::CAL_U16:
    case Calibrations::Types::CAL_U32:
    case Calibrations::Types::CAL_U64:
        ( (U64QSpinBox *) calDisplList[idx]->val_pt)->setValue(val);
        break;
    case Calibrations::Types::CAL_S8:
        ( (I64QSpinBox *) calDisplList[idx]->val_pt)->setValue( (int8_t) val);
        break;
    case Calibrations::Types::CAL_S16:
        ( (I64QSpinBox *) calDisplList[idx]->val_pt)->setValue( (int16_t) val);
        break;
    case Calibrations::Types::CAL_S32:
        ( (I64QSpinBox *) calDisplList[idx]->val_pt)->setValue( (int32_t)val);
        break;
    case Calibrations::Types::CAL_S64:
        ( (I64QSpinBox *) calDisplList[idx]->val_pt)->setValue( (int64_t) val);
        break;

    case Calibrations::Types::CAL_F32:
        ptrFloat = (float *) &val;
        ( (DOUBLEQSpinBox *) calDisplList[idx]->val_pt)->setValue( (double) *ptrFloat);
        break;

    case Calibrations::Types::CAL_F64:
        ptrDouble = (double *) &val;
        ( (DOUBLEQSpinBox *) calDisplList[idx]->val_pt)->setValue( (double) *ptrDouble);
        break;
    }
}
#endif
