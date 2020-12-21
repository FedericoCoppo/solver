#ifndef CONFIGURATOR_CPP
#define CONFIGURATOR_CPP

#include <QFileDialog>
#include <QFile>
#include <QStringList>
#include <QDebug>

#include "Product.h"

Product g_prod;

Product::Product(void)
{
   filePath = "";
   isProductNotEmpty = true;
}

Product::~Product()
{
    Clear();
    // prodDisp_pt = nullptr;

}

void Product::Clear()
{
    filePath = "";
    isProductNotEmpty = true;

    // remove calibration
    int iNum = prodList.count();

    for (int i=0; i < iNum; i++)
    {
        delete (prodList.takeAt(0));
    }
}

bool Product::ProductParseFromExcel(QString path)
{
    bool res = false;

    filePath = path;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
        return 1;
    }

    QList<QByteArray> wordList;
    QByteArray line = file.readLine(); // remove header
    while (!file.atEnd())
    {
        line = file.readLine();
        wordList.append(line.split(';'));
        Product::prodContent * tmp_pt = new Product::prodContent();
        tmp_pt->code = wordList.takeAt(0);
        tmp_pt->company = wordList.takeAt(0);
        tmp_pt->weight_g = wordList.takeAt(0).toFloat();
        tmp_pt->surface_mm2 = wordList.takeAt(0).toFloat();
        tmp_pt->timePreparation = wordList.takeAt(0).toUInt();
        tmp_pt->timePackage = wordList.takeAt(0).toUInt();
        tmp_pt->pctReturn = wordList.takeAt(0).toUInt();
        tmp_pt->nominalPrice = wordList.takeAt(0).toFloat();

        wordList.clear();
        prodList.append(tmp_pt);
    }

    res = true;

    return res;
}

#endif // CONFIGURATOR_CPP
