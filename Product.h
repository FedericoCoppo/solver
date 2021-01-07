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
    QStringList * GetProdCodeStrList() {return &prodCodeStrList;}
    QStringList * GetProdCompanyStrList() {return &prodCompanyStrList;}

    QList < prodContent * > GetProdList() {return prodList;}
    void Append(prodContent * pt) { prodList.append(pt); }
    void AppendProdCodeStrList(QString s) { prodCodeStrList << s; }
    void AppendProdCompanyStrList(QString s) { prodCompanyStrList << s; }

    void ClearProdCodeStrList() { prodCodeStrList.clear(); }
    void ClearProdCompanyStrList() { prodCompanyStrList.clear(); }

    void RemoveProdCodeStrList(QString s);
    void RemoveProdCompanyStrList(QString s);

    bool ProdCodeStrListContains(QString s) { return prodCodeStrList.contains(s); }
    bool ProdCompanyStrListContains(QString s) { return prodCompanyStrList.contains(s); }

    // Setter
    void SetCode(int index, QString code) {prodList[index]->code = code;}
    void SetCompany(int index, QString company) { prodList[index]->company = company;}
    void SetWeight(int index, float w) { prodList[index]->weight_g = w;}
    void SetSurface_mm2(int index, float s) { prodList[index]->surface_mm2 = s;}
    void SetTimePreparation(int index, float prep) { prodList[index]->timePreparation = prep; }
    void SetTimePackage(int index, float pack) {  prodList[index]->timePackage = pack; }
    void SetPctReturn(int index, float ret) { prodList[index]->pctReturn = ret;}
    void SetNominalPrice(int index, float price) { prodList[index]->nominalPrice = price;}
    void SetPrice(int index, float v) {  prodList[index]->nominalPrice = v;}
    void SetMeanPrice(int index, float price) { prodList[index]->meanPrice = price;}
    void SetLastPrice(int index, float price) { prodList[index]->lastPrice = price;}
    void SetLastValue(int index, double v) {  prodList[index]->lastPrice = v; }
    void SetIsProdListA2LNotEmpty(bool status) {isProductNotEmpty = status;}
    void ClearCalibStruct();

private:
    QString filePath;
    // ProductDisplayer * prodDisp_pt;
    bool isProductNotEmpty;
    QList < prodContent * > prodList;
    QStringList prodCodeStrList;
    QStringList prodCompanyStrList;

    bool getValueXCP(int i, double &data);
    bool valueChangeXCP(int i);
};

extern Product g_prod;
#endif // PRODUCT_H
