#ifndef PRODUCT_H
#define PRODUCT_H

#include <QMenu>

class Product :
        public QObject
{
    Q_OBJECT

public:

    typedef struct info_
    {
        QString code;
        QString company;
        float weight_g;
        float surface_mm2;
        float timePreparation;
        float timePackage;
        float pctReturn;
        float nominalPrice;
        float meanPrice;
        float lastPrice;
    } prodContent;

    Product();
    virtual ~Product();
    void Clear();
    bool ProductParseFromExcel(QString path);

    // getter
    bool GetIsProductFilled() { return isProductNotEmpty == true;}
    prodContent * GetProdContent(int index){ return prodList[index];}
    int GetProdListCnt() {return prodList.count(); }

    QString GetCode(int index) { return prodList[index]->code; }
    QString GetCompany(int index) { return prodList[index]->company;}

    float GetWeight(int index) { return prodList[index]->weight_g;}
    float GetSurface_mm2(int index) { return prodList[index]->surface_mm2;}
    float GetTimePreparation(int index) { return prodList[index]->timePreparation;}
    float GetTimePackage(int index) { return prodList[index]->timePackage;}
    float GetPctReturn(int index) { return prodList[index]->pctReturn;}
    float GetNominalPrice(int index) { return prodList[index]->nominalPrice;}
    float GetMeanPrice(int index) { return prodList[index]->meanPrice;}
    float GetLastPrice(int index) { return prodList[index]->lastPrice;}

    QList < prodContent * > GetCalList() {return prodList;}
    void Append(prodContent * pt) { prodList.append(pt); }

    // Setter
    bool SetPrice(int index, double v) {  prodList[index]->nominalPrice = v; return valueChangeXCP(index);}
    void SetLastValue(int index, double v) {  prodList[index]->lastPrice = v; }
    void SetIsProdListA2LNotEmpty(bool status) {isProductNotEmpty = status;}
    void ClearCalibStruct();

private:
    QString filePath;
    // ProductDisplayer * prodDisp_pt;
    bool isProductNotEmpty;
    QList < prodContent * > prodList;
    bool getValueXCP(int i, double &data);
    bool valueChangeXCP(int i);
};

extern Product g_prod;
#endif // PRODUCT_H
