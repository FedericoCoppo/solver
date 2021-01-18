#ifndef CONFIGURATOR_CPP
#define CONFIGURATOR_CPP

#include <QFileDialog>
#include <QFile>
#include <QStringList>
#include <QDebug>
#include <QMessageBox>

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

    for (int i = 0; i < iNum; i++)
    {
        delete (prodList.takeAt(0));
    }

    prodCodeStrList.clear();
    prodCompanyStrList.clear();
}


void Product::Delete(int idx)
{
   prodContent * p = prodList.takeAt(idx);
   delete p;
}

void Product::RemoveProdCodeStrList(QString s)
{
    if (prodCodeStrList.indexOf(s) >= 0)
    {
        prodCodeStrList.removeAt(prodCodeStrList.indexOf(s));
    }
}

void Product::RemoveProdCompanyStrList(QString s)
{
    if (prodCompanyStrList.indexOf(s) >= 0)
    {
        prodCompanyStrList.removeAt(prodCompanyStrList.indexOf(s));
    }
}

bool Product::ProductParseFromExcel(QString path)
{
    bool res = false;

    filePath = path;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
        return false;
    }

    QList<QByteArray> wordList, coeffList;
    QByteArray line = file.readLine(); // remove header
    line = file.readLine(); // read the coefficient
    coeffList.append(line.split(';'));
    coeff[0] = coeffList[0].replace(",", ".").toFloat();
    coeff[1] = coeffList[1].replace(",", ".").toFloat();
    coeff[2] = coeffList[2].replace(",", ".").toFloat();
    coeff[3] = coeffList[3].replace(",", ".").toFloat();
    coeff[4] = coeffList[4].replace(",", ".").toFloat();

    ClearProdCodeStrList();
    ClearProdCompanyStrList();

    while (!file.atEnd())
    {
        line = file.readLine();
        wordList.append(line.split(';'));
        Product::prodContent * tmp_pt = new Product::prodContent();

        if (wordList.size() == 8)
        {
            tmp_pt->code = wordList.takeAt(0);
            tmp_pt->company = wordList.takeAt(0);
            tmp_pt->weight_g = wordList.takeAt(0).replace(",", ".").toFloat();
            tmp_pt->surface_mm2 = wordList.takeAt(0).replace(",", ".").toFloat();
            tmp_pt->timePreparation = wordList.takeAt(0).toUInt();
            tmp_pt->timePackage = wordList.takeAt(0).toUInt();
            tmp_pt->pctReturn = wordList.takeAt(0).toUInt();
            tmp_pt->nominalPrice = wordList.takeAt(0).replace(",", ".").toFloat();
            prodList.append(tmp_pt);
        }

        wordList.clear();

        AppendProdCodeStrList(tmp_pt->code);
        AppendProdCompanyStrList(tmp_pt->company + " code: " + tmp_pt->code);
    }

    file.close();

    res = true;

    return res;
}

bool Product::saveCSVFile()
{
    QString fname = QFileDialog::getSaveFileName(nullptr, "save ", ".", "csv file prodotti (*.csv)" );

    if (fname.isEmpty())
    {
        return false;
    }
    else
    {
        QFile file(fname);
        file.putChar('c');
        if (!file.open(QIODevice::WriteOnly))         // save the empty file
        {
            return false;
        }

        file.close();

        if ( file.open(QIODevice::ReadWrite) )
        {
            QByteArray QByteArray;
            int max =  g_prod.GetProdListCnt();
            QTextStream stream( &file );
            stream <<  "CODICE;DITTA;PESO[g];SUPERFICE [mm^2];PREPARAZIONE ALLA VERNICIATURA [min];TEMPO IMBALLAGGIO [min];% RICHIAMI;PREZZO" << Qt::endl;


            for (int i = 0; i < max; i++ )
            {
                QString line = g_prod.GetCode(i) + ";" + g_prod.GetCompany(i) + ";" + QString::number(g_prod.GetWeight(i)) + ";" + QString::number(g_prod.GetSurface_mm2(i)) +
                        ";" + QString::number(g_prod.GetTimePreparation(i)) + ";" + QString::number(g_prod.GetTimePackage(i)) + ";"+ QString::number(g_prod.GetPctReturn(i)) + ";" + QString::number(g_prod.GetNominalPrice(i));

                if (i + 1 == max)
                {
                    /* avoid '\n' at the endo of the file */
                }
                else
                {
                    stream << line << Qt::endl;
                }
            }

            file.close();
        }
    }

    return true;
}

void Product::UpdateCoeff(float a, float b, float c, float d, float e)
{
    coeff[0] = a;
    coeff[1] = b;
    coeff[2] = c;
    coeff[3] = d;
    coeff[4] = e;
}

#endif // CONFIGURATOR_CPP
