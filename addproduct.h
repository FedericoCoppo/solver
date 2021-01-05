#ifndef ADDPRODUCT_H
#define ADDPRODUCT_H

#include <QDialog>
#include "ProductDisplayer.h"

namespace Ui {
class addProduct;
}

class addProduct : public QDialog
{
    Q_OBJECT

public:
    explicit addProduct(ProductDisplayer * pt_disp, QWidget *parent = nullptr);
    ~addProduct();

private:
    Ui::addProduct *ui;
    ProductDisplayer * p_disp;

private slots:
    void on_pushButtonSaveAdd_clicked();
};

#endif // ADDPRODUCT_H
