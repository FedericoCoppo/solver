#include "ProductDisplayer.h"
#include <QtCore/qmath.h>
#include <QMessageBox>
#include <QTextStream>
#include <QScrollBar>
#include <QDebug>

ProductDisplayer::ProductDisplayer(Ui::MainWindow * pt_ui, QWidget* parent) : QWidget(parent)
{
    isCalModifyEnabled = false;
    p_ui = pt_ui;
    items_layout = new QVBoxLayout (p_ui->scrollAreaWidgetContents); /* this name is decided by uic when it compiles your .ui XML file */
    items_layout->setSpacing (4); /* adjust to taste */
    displayOn = false;
    filterOpened = false;
    titleDisplayed = false;

    // filter part
    textEditFilterCompany = new TextFilter(3, p_ui->scrollAreaWidgetContents_2);
    textEditFilterCompany->setObjectName(QString::fromUtf8("textEditFilter"));
    textEditFilterCompany->setGeometry(QRect(0, 0, 220, 31));
    textEditFilterCompany->setEnabled(false);
    textEditFilterCode = new TextFilter(1, p_ui->scrollAreaWidgetContents_3);
    textEditFilterCode->setObjectName(QString::fromUtf8("textEditFilter"));
    textEditFilterCode->setGeometry(QRect(0, 0, 220, 31));
    textEditFilterCode->setEnabled(false);
    isScrollBarConnected = false;
    scrollEnabled = false;
    calibrationAdded = 0;
    isMeasDisplayTerminated = false;
    maxCalibrationForCycle = 25;
    buttonConnected = false;
}

ProductDisplayer::~ProductDisplayer()
{
    ClearParamDisplayElement();
    delete items_layout;

    CloseFilters();

    if (textEditFilterCompany)
    {
        delete textEditFilterCompany;
    }

    if (textEditFilterCode)
    {
        delete textEditFilterCode;
    }
}

void ProductDisplayer::OpenFilters()
{
    if (!filterOpened)
    {
        filterOpened = true;

        // completer set up
        completerCompany = new QCompleter(*(g_prod.GetProdCompanyStrList()), this);
        completerCompany->setCaseSensitivity(Qt::CaseInsensitive);
        textEditFilterCompany->setCompleter(completerCompany);
        QObject::connect(textEditFilterCompany,SIGNAL(measurementSelectedSig(QString)),
                this,SLOT (measurementSelectedCompany(QString)));
        textEditFilterCompany->setEnabled(true);

        // completer set up
        completerCode = new QCompleter(*(g_prod.GetProdCodeStrList()), this);
        completerCode->setCaseSensitivity(Qt::CaseInsensitive);
        textEditFilterCode->setCompleter(completerCode);
        QObject::connect(textEditFilterCode,SIGNAL(measurementSelectedSig(QString)),
                this,SLOT (measurementSelectedCode(QString)));
        textEditFilterCode->setEnabled(true);
    }
}

void ProductDisplayer::CloseFilters()
{
    if (completerCompany)
    {
        delete completerCompany;
        completerCompany = NULL;
    }

    QObject::disconnect(textEditFilterCompany,SIGNAL(measurementSelectedSig(QString)),
                        this,SLOT (measurementSelectedCompany(QString)));

    if (completerCode)
    {
        delete completerCode;
        completerCode = NULL;
    }

    QObject::disconnect(textEditFilterCode,SIGNAL(measurementSelectedSig(QString)),
                        this,SLOT (measurementSelectedCode(QString)));

    filterOpened = false;
}

void ProductDisplayer::ClearParamDisplayElement()
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
        delete tmp->pctReturn_pt;
        delete tmp->price_pt;
        delete tmp->button_pt;
        delete tmp->deletebutton_pt;

        delete (tmp);
    }

    clearTitle();

    if (isScrollBarConnected)
    {
        disconnect(p_ui->scrollArea->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(vScrollValueChanged(int)));
        isScrollBarConnected = false;
    }

     calibrationAdded = 0;
     isMeasDisplayTerminated = false;

     if (buttonConnected)
     {
         disconnect(&btnGroup, SIGNAL (buttonClicked(int)), this, SLOT (handleButton(int)));
         disconnect(&btnGroupDelete, SIGNAL (buttonClicked(int)), this, SLOT (handleButtonDelete(int)));
         buttonConnected = false;
     }
}

void ProductDisplayer::clearTitle()
{
    // title
    if (titleDisplayed)
    {
        int iNum = titleLabelList.count();
        for (int i=0; i < iNum; i++)
        {
            delete titleLabelList.takeAt(0);
        }

        iNum = items_layout->count();
        for (int i=0; i < iNum; i++)
        {
            delete items_layout->takeAt(0);
        }

        titleDisplayed = false;
    }
}

void ProductDisplayer::PushButtonDisplayClicked()
{
    // read file
    if (g_prod.GetIsProductFilled())
    {
        if (displayOn == false)
        {
            ClearParamDisplayElement(); // clear previous element
            scrollEnabled = true;
            DisplayProd();
            displayOn = true;
        }
        else
        {
            ClearParamDisplayElement();
            displayOn = false;
            scrollEnabled = false;
        }
    }
}

void ProductDisplayer::displayTitle()
{
    // Title
    if (!titleDisplayed)
    {
        titleDisplayed = true;

        QLabel *title_label;
        QHBoxLayout * hbox_layout = new QHBoxLayout ();

        title_label  = new QLabel("");
        title_label->setMinimumWidth (50);
        title_label->setMaximumWidth (60);
        hbox_layout->addWidget (title_label);
        titleLabelList.append(title_label);

        title_label  = new QLabel("CODICE");
        title_label->setMinimumWidth (110);
        title_label->setMaximumWidth (120);
        hbox_layout->addWidget (title_label);
        titleLabelList.append(title_label);

        title_label  = new QLabel("DITTA");
        title_label->setMinimumWidth (110);
        title_label->setMaximumWidth (120);
        hbox_layout->addWidget (title_label);
        titleLabelList.append(title_label);

        title_label  = new QLabel("PESO [g]");
        title_label->setMinimumWidth (110);
        title_label->setMaximumWidth (120);
        hbox_layout->addWidget (title_label);
        titleLabelList.append(title_label);

        title_label  = new QLabel("SUPERFICE [mm^2]");
        title_label->setMinimumWidth (110);
        title_label->setMaximumWidth (120);
        hbox_layout->addWidget (title_label);
        titleLabelList.append(title_label);

        title_label  = new QLabel("PREPARAZIONE [min]");
        title_label->setMinimumWidth (110);
        title_label->setMaximumWidth (120);
        hbox_layout->addWidget (title_label);
        titleLabelList.append(title_label);

        title_label  = new QLabel("IMBALLAGGIO [min]");
        title_label->setMinimumWidth (110);
        title_label->setMaximumWidth (120);
        hbox_layout->addWidget (title_label);
        titleLabelList.append(title_label);

        title_label  = new QLabel("% RICHIAMI");
        title_label->setMinimumWidth (110);
        title_label->setMaximumWidth (120);
        hbox_layout->addWidget (title_label);
        titleLabelList.append(title_label);

        title_label  = new QLabel("PREZZO");
        title_label->setMinimumWidth (110);
        title_label->setMaximumWidth (120);
        hbox_layout->addWidget (title_label);
        titleLabelList.append(title_label);

        title_label  = new QLabel("MODIFICA");
        title_label->setMinimumWidth (110);
        title_label->setMaximumWidth (120);
        hbox_layout->addWidget (title_label);
        titleLabelList.append(title_label);

        title_label  = new QLabel("CANCELLA");
        title_label->setMinimumWidth (110);
        title_label->setMaximumWidth (120);
        hbox_layout->addWidget (title_label);
        titleLabelList.append(title_label);

        items_layout->addLayout (hbox_layout);
    }
}

void ProductDisplayer::creatMeas(int index, int incrementalElement)
{
    QLineEdit * line;
    QLabel *items_label;
    QHBoxLayout *hbox_layout;
    items_label = new QLabel ("0x0000000000000"); /* longest possible text for left-hand label */
    items_label->updateGeometry ();
    delete items_label;
    QPushButton *changeBtn;
    QPushButton *deleteBtn;

    ProdDisplayer * displayTmp = new ProdDisplayer();

    // link displayer with calibration
    displayTmp->prodContentPt = g_prod.GetProdContent(index);

    hbox_layout = new QHBoxLayout ();

    /* code */
    line = new QLineEdit (g_prod.GetCode(index));
    line->setMinimumWidth(70);
    line->setMaximumWidth(80);
    hbox_layout->addWidget (line);
    displayTmp->layout_pt = hbox_layout;
    displayTmp->code_pt = line;
    displayTmp->oldCode = displayTmp->code_pt->text();

    line->setEnabled(false);

    /* company */
    line = new QLineEdit (g_prod.GetCompany(index));
    line->setMinimumWidth(70);
    line->setMaximumWidth(80);
    hbox_layout->addWidget (line);
    displayTmp->layout_pt = hbox_layout;
    displayTmp->company_pt = line;
    line->setEnabled(false);

    /* weight */
    DOUBLEQSpinBox * doubleSpinBoxEntry = new DOUBLEQSpinBox(g_prod.GetProdContent(index));
    doubleSpinBoxEntry->blockSignals(true);
    doubleSpinBoxEntry->setMinimumWidth(70);
    doubleSpinBoxEntry->setMaximumWidth(80);
    hbox_layout->addWidget (doubleSpinBoxEntry);
    doubleSpinBoxEntry->setValue(g_prod.GetWeight(index));
    doubleSpinBoxEntry->setSingleStep(0.1);
    doubleSpinBoxEntry->setRange(0, std::numeric_limits<float>::max());  // - 3.4 * pow(10, 38) 3.4 * pow(10, 38)
    displayTmp->weight_pt = doubleSpinBoxEntry;
    doubleSpinBoxEntry->blockSignals(false);
    connect(doubleSpinBoxEntry, QOverload<double, DOUBLEQSpinBox * >::of(&DOUBLEQSpinBox::valueChanged) , this, &ProductDisplayer::DoubleSlotInputChanged);
    displayTmp->weight_pt->setEnabled(false);

    /* surface */
    doubleSpinBoxEntry = new DOUBLEQSpinBox(g_prod.GetProdContent(index));
    doubleSpinBoxEntry->blockSignals(true);
    doubleSpinBoxEntry->setMinimumWidth(70);
    doubleSpinBoxEntry->setMaximumWidth(80);
    hbox_layout->addWidget (doubleSpinBoxEntry);
    doubleSpinBoxEntry->setValue(g_prod.GetSurface_mm2(index));
    doubleSpinBoxEntry->setSingleStep(0.1);
    doubleSpinBoxEntry->setRange(0, std::numeric_limits<float>::max());  // - 3.4 * pow(10, 38) 3.4 * pow(10, 38)
    displayTmp->surface_pt = doubleSpinBoxEntry;
    doubleSpinBoxEntry->blockSignals(false);
    connect(doubleSpinBoxEntry, QOverload<double, DOUBLEQSpinBox * >::of(&DOUBLEQSpinBox::valueChanged) , this, &ProductDisplayer::DoubleSlotInputChanged);
    displayTmp->surface_pt->setEnabled(false);

    /* preparation */
    doubleSpinBoxEntry = new DOUBLEQSpinBox(g_prod.GetProdContent(index));
    doubleSpinBoxEntry->blockSignals(true);
    doubleSpinBoxEntry->setMinimumWidth(70);
    doubleSpinBoxEntry->setMaximumWidth(80);
    hbox_layout->addWidget (doubleSpinBoxEntry);
    doubleSpinBoxEntry->setValue(g_prod.GetTimePreparation(index));
    doubleSpinBoxEntry->setSingleStep(0.1);
    doubleSpinBoxEntry->setRange(0, std::numeric_limits<float>::max());  // - 3.4 * pow(10, 38) 3.4 * pow(10, 38)
    displayTmp->preparation_pt = doubleSpinBoxEntry;
    doubleSpinBoxEntry->blockSignals(false);
    connect(doubleSpinBoxEntry, QOverload<double, DOUBLEQSpinBox * >::of(&DOUBLEQSpinBox::valueChanged) , this, &ProductDisplayer::DoubleSlotInputChanged);
    displayTmp->preparation_pt->setEnabled(false);

    /* package */
    doubleSpinBoxEntry = new DOUBLEQSpinBox(g_prod.GetProdContent(index));
    doubleSpinBoxEntry->blockSignals(true);
    doubleSpinBoxEntry->setMinimumWidth(70);
    doubleSpinBoxEntry->setMaximumWidth(80);
    hbox_layout->addWidget (doubleSpinBoxEntry);
    doubleSpinBoxEntry->setValue(g_prod.GetTimePackage(index));
    doubleSpinBoxEntry->setSingleStep(0.1);
    doubleSpinBoxEntry->setRange(0, std::numeric_limits<float>::max());  // - 3.4 * pow(10, 38) 3.4 * pow(10, 38)
    displayTmp->package_time_pt = doubleSpinBoxEntry;
    doubleSpinBoxEntry->blockSignals(false);
    connect(doubleSpinBoxEntry, QOverload<double, DOUBLEQSpinBox * >::of(&DOUBLEQSpinBox::valueChanged) , this, &ProductDisplayer::DoubleSlotInputChanged);
    displayTmp->package_time_pt->setEnabled(false);

    /* return */
    doubleSpinBoxEntry = new DOUBLEQSpinBox(g_prod.GetProdContent(index));
    doubleSpinBoxEntry->blockSignals(true);
    doubleSpinBoxEntry->setMinimumWidth(70);
    doubleSpinBoxEntry->setMaximumWidth(80);
    hbox_layout->addWidget (doubleSpinBoxEntry);
    doubleSpinBoxEntry->setValue(g_prod.GetPctReturn(index));
    doubleSpinBoxEntry->setSingleStep(0.1);
    doubleSpinBoxEntry->setRange(0, std::numeric_limits<float>::max());  // - 3.4 * pow(10, 38) 3.4 * pow(10, 38)
    displayTmp->pctReturn_pt = doubleSpinBoxEntry;
    doubleSpinBoxEntry->blockSignals(false);
    connect(doubleSpinBoxEntry, QOverload<double, DOUBLEQSpinBox * >::of(&DOUBLEQSpinBox::valueChanged) , this, &ProductDisplayer::DoubleSlotInputChanged);
    displayTmp->pctReturn_pt->setEnabled(false);

    /* price */
    doubleSpinBoxEntry = new DOUBLEQSpinBox(g_prod.GetProdContent(index));
    doubleSpinBoxEntry->blockSignals(true);
    doubleSpinBoxEntry->setMinimumWidth(70);
    doubleSpinBoxEntry->setMaximumWidth(80);
    hbox_layout->addWidget (doubleSpinBoxEntry);
    doubleSpinBoxEntry->setValue(g_prod.GetNominalPrice(index));
    doubleSpinBoxEntry->setSingleStep(0.1);
    doubleSpinBoxEntry->setRange(0, std::numeric_limits<float>::max());  // - 3.4 * pow(10, 38) 3.4 * pow(10, 38)
    displayTmp->price_pt = doubleSpinBoxEntry;
    doubleSpinBoxEntry->blockSignals(false);
    connect(doubleSpinBoxEntry, QOverload<double, DOUBLEQSpinBox * >::of(&DOUBLEQSpinBox::valueChanged) , this, &ProductDisplayer::DoubleSlotInputChanged);
    displayTmp->price_pt->setEnabled(false);

    /* button */
    changeBtn = new QPushButton(p_ui->scrollAreaWidgetContents);
    changeBtn->setObjectName(QString::fromUtf8("MODIFICA"));
    changeBtn->setMinimumSize(50,30);
    changeBtn->setMaximumSize(60,30);
    changeBtn->setText(QCoreApplication::translate("CalibrationUi", "CAMBIA", nullptr));
    changeBtn->setEnabled(true);
    hbox_layout->addWidget (changeBtn);

    /* delete button*/
    deleteBtn = new QPushButton(p_ui->scrollAreaWidgetContents);
    deleteBtn->setObjectName(QString::fromUtf8("CANC"));
    deleteBtn->setMinimumSize(35,30);
    deleteBtn->setMaximumSize(35,30);
    deleteBtn->setGeometry(QRect(30, 30, 35, 35));

    QIcon icon;
    icon.addFile(QString::fromUtf8(":/icon/images/cancel.png"), QSize(), QIcon::Normal, QIcon::On);
    deleteBtn->setIcon(icon);
    deleteBtn->setIconSize(QSize(35, 27));

    deleteBtn->setEnabled(true);
    hbox_layout->addWidget (deleteBtn);

    // hbox_layout->setAlignment(Qt::AlignTop);

    items_layout->addLayout (hbox_layout);
    displayTmp->button_pt = changeBtn;

    btnGroup.addButton(changeBtn, incrementalElement);

    displayTmp->deletebutton_pt = deleteBtn;
    btnGroupDelete.addButton(deleteBtn, incrementalElement);

    prodDisplList.append(displayTmp);


}

void ProductDisplayer::DisplayProd()
{
    if (g_prod.GetIsProductFilled())
    {
        if (!isScrollBarConnected)
        {
            p_ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
            connect(p_ui->scrollArea->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(vScrollValueChanged(int)));
            isScrollBarConnected = true;
        }

        int maxCycleNum = maxCalibrationForCycle;
        int TmpCalAdded = calibrationAdded;

        //  check if last display cycle
        if (maxCycleNum > g_prod.GetProdListCnt() - TmpCalAdded)
        {
            maxCycleNum = g_prod.GetProdListCnt() - TmpCalAdded;
            isMeasDisplayTerminated = true;
        }

        displayTitle();
        for (int i = TmpCalAdded; i < maxCycleNum + TmpCalAdded; ++i )
        {
            creatMeas(i,i);
            calibrationAdded++;
        }

        if (!buttonConnected)
        {
            connect(&btnGroup, SIGNAL (buttonClicked(int)), this, SLOT (handleButton(int)));
            connect(&btnGroupDelete, SIGNAL (buttonClicked(int)), this, SLOT (handleButtonDelete(int)));
            buttonConnected = true;
        }
    }
}

void ProductDisplayer::measurementSelectedCompany(QString str)
{
    bool found = false;
    bool alreadyPresent = false;
    int i;

    ClearParamDisplayElement();
    displayTitle();

    // int index = pt->indexOf(str);
    for (i = 0; i < g_prod.GetProdListCnt(); i++ )
    {
        if ( (g_prod.GetCompany(i) + " code: " + g_prod.GetCode(i)) == str)
        {
            found = true;
            break;
        }
    }

    if (found)
    {
        // check if not alread present into measurement displayer
        for (int j = 0; j <  prodDisplList.size(); j++)
        {
            if (g_prod.GetCompany(i) == prodDisplList[j]->company_pt->text())
            {
                alreadyPresent = true;
                break;
            }
        }

        if (!alreadyPresent)
        {
            creatMeas(i,0);
        }

        if (!buttonConnected)
        {
            connect(&btnGroup, SIGNAL (buttonClicked(int)), this, SLOT (handleButton(int)));
            connect(&btnGroupDelete, SIGNAL (buttonClicked(int)), this, SLOT (handleButtonDelete(int)));
            buttonConnected = true;
        }
    }

    // allign to up
    items_layout->addStretch();

    if (displayOn == false)
    {
        p_ui->pushButtonDisplay->toggle();
        displayOn = true;
    }
}

void ProductDisplayer::measurementSelectedCode(QString str)
{
    bool found = false;
    bool alreadyPresent = false;
    int i;

    ClearParamDisplayElement();
    displayTitle();

    // int index = pt->indexOf(str);
    for (i = 0; i < g_prod.GetProdListCnt(); i++ )
    {
        if (g_prod.GetCode(i) == str)
        {
            found = true;
            break;
        }
    }

    if (found)
    {
        // check if not alread present into measurement displayer
        for (int j = 0; j <  prodDisplList.size(); j++)
        {
            if (g_prod.GetCode(i) == prodDisplList[j]->code_pt->text())
            {
                alreadyPresent = true;
                break;
            }
        }

        if (!alreadyPresent)
        {
            creatMeas(i,0);
        }

        if (!buttonConnected)
        {
            connect(&btnGroup, SIGNAL (buttonClicked(int)), this, SLOT (handleButton(int)));
            connect(&btnGroupDelete, SIGNAL (buttonClicked(int)), this, SLOT (handleButtonDelete(int)));
            buttonConnected = true;
        }
    }

    // allign to up
    items_layout->addStretch();

    if (displayOn == false)
    {
        p_ui->pushButtonDisplay->toggle();
        displayOn = true;
    }
}

void ProductDisplayer::vScrollValueChanged(int val)
{
    if (scrollEnabled)
    {
        int den = p_ui->scrollArea->verticalScrollBar()->maximum();

        if ((val*100)/den > 99)
        {
            qDebug() << QString::number(val*100/den);

            if (!isMeasDisplayTerminated)
            {
                DisplayProd();
            }
        }
    }
}

void ProductDisplayer::handleButtonDelete(int idx)
{


}

void ProductDisplayer::handleButton(int idx)
{
    ProdDisplayer * displayTmp = prodDisplList[idx];
    p_ui->lineEditTrace->setText("");
    displayTmp->button_pt->setStyleSheet("background-color: Light gray");

    if (displayTmp->button_pt->text() == "CAMBIA")
    {
        displayTmp->button_pt->setText("SALVA");
        displayTmp->code_pt->setEnabled(true);
        displayTmp->company_pt->setEnabled(true);
        displayTmp->weight_pt->setEnabled(true);
        displayTmp->surface_pt->setEnabled(true);
        displayTmp->preparation_pt->setEnabled(true);
        displayTmp->package_time_pt->setEnabled(true);
        displayTmp->pctReturn_pt->setEnabled(true);
        displayTmp->price_pt->setEnabled(true);
    }
    else
    {
        int max = g_prod.GetProdList().size();
        bool found = false;
        int i = 0;

        // if code has changed, avoid duplicate
        if (displayTmp->oldCode != displayTmp->code_pt->text())
        {
            for (i = 0; i < max; i++)
            {
                if (displayTmp->code_pt->text() == g_prod.GetCode(i))
                {
                    found = true;
                    break;
                }
            }
        }

        if (!found)
        {
            displayTmp->button_pt->setText("CAMBIA");
            displayTmp->code_pt->setEnabled(false);
            displayTmp->company_pt->setEnabled(false);
            displayTmp->weight_pt->setEnabled(false);
            displayTmp->surface_pt->setEnabled(false);
            displayTmp->preparation_pt->setEnabled(false);
            displayTmp->package_time_pt->setEnabled(false);
            displayTmp->pctReturn_pt->setEnabled(false);
            displayTmp->price_pt->setEnabled(false);

            // search the corrisponding Product obj (index could be not alligned)
            found = false;
            for (i = 0; i < max; i++)
            {
                if (displayTmp->code_pt->text() == g_prod.GetCode(i) || displayTmp->oldCode == g_prod.GetCode(i)) // second condition is needed for code change
                {
                    found = true;
                    break;
                }
            }

            if (found)
            {
                // remove old strings
                g_prod.RemoveProdCodeStrList(g_prod.GetCode(i));
                g_prod.RemoveProdCompanyStrList(g_prod.GetCompany(i) + " code: " + g_prod.GetCode(i));
                g_prod.SetCode(i, displayTmp->code_pt->text());
                displayTmp->oldCode =  displayTmp->code_pt->text();
                g_prod.SetCompany(i, displayTmp->company_pt->text());
                g_prod.SetCode(i, displayTmp->code_pt->text());
                g_prod.SetWeight(i, ((DOUBLEQSpinBox *) displayTmp->weight_pt)->getValue());
                g_prod.SetSurface_mm2(i, ((DOUBLEQSpinBox *) displayTmp->surface_pt)->getValue());
                g_prod.SetTimePreparation(i, ((DOUBLEQSpinBox *) displayTmp->preparation_pt)->getValue());
                g_prod.SetTimePackage(i, ((DOUBLEQSpinBox *) displayTmp->package_time_pt)->getValue());
                g_prod.SetPctReturn(i, ((DOUBLEQSpinBox *) displayTmp->pctReturn_pt)->getValue());
                g_prod.SetPrice(i, ((DOUBLEQSpinBox *) displayTmp->price_pt)->getValue());
                // update new strings
                g_prod.AppendProdCodeStrList(g_prod.GetCode(i));
                g_prod.AppendProdCompanyStrList(g_prod.GetCompany(i) + " code: "  + g_prod.GetCode(i));
                // remove old and update
                this->CloseFilters();
                this->OpenFilters();

            }
        }
        else
        {
            p_ui->lineEditTrace->setText("CODICE PRODOTTO GIA' ESISTENTE, DEVE ESSERE UNIVOCO..");
            displayTmp->button_pt->setStyleSheet("background-color: red");
        }
    }
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
