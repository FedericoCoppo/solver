#include "addproduct.h"
#include "ui_addproduct.h"
#include "Product.h"


addProduct::addProduct(ProductDisplayer * pt_disp, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addProduct)
{
    ui->setupUi(this);
    p_disp = pt_disp;
    p_disp->Get_p_ui()->lineEditTrace->setText("");
}

addProduct::~addProduct()
{
    delete ui;
}

void addProduct::on_pushButtonSaveAdd_clicked()
{
    Product::prodContent * tmp_pt = new Product::prodContent();
    tmp_pt->code = ui->lineEditCode->text();
    tmp_pt->company = ui->lineEditCompany->text();
    tmp_pt->weight_g = ui->doubleSpinBoxWeight->value();
    tmp_pt->surface_mm2 = ui->doubleSpinBoxSurface->value();
    tmp_pt->timePreparation = ui->doubleSpinBoxPreparation->value();
    tmp_pt->timePackage = ui->doubleSpinBoxPackage->value();
    tmp_pt->pctReturn = ui->doubleSpinBoxReturnPct->value();
    tmp_pt->nominalPrice = ui->doubleSpinBoxPrice->value();

    if (tmp_pt->code != "" && tmp_pt->company != "" && tmp_pt->code != " " &&
            tmp_pt->company != " " && tmp_pt->code != "  " && tmp_pt->company != "  ")
    {

        if (!g_prod.ProdCodeStrListContains(tmp_pt->code))
        {
            g_prod.Append(tmp_pt);

            g_prod.AppendProdCodeStrList(tmp_pt->code);
            g_prod.AppendProdCompanyStrList(tmp_pt->company + " code: " + tmp_pt->code);

            if (p_disp->isDisplayOn())
            {
                if (p_disp)
                {
                    p_disp->ClearParamDisplayElement();
                    p_disp->DisplayProd();
                }
            }

            this->close();

            p_disp->Get_p_ui()->lineEditTrace->setText("NUOVO PRODOTTO codice" + tmp_pt->code + " ( " + tmp_pt->company  + " ) AGGIUNTO");
        }
        else
        {
            ui->lineEditTrace->setText("CODICE PRODOTTO GIA' ESISTENTE");
            ui->pushButtonSaveAdd->setStyleSheet("background-color: red");
        }
    }
    else
    {
        ui->lineEditTrace->setText("CODICE PRODOTTO O AZIENDA MANCANTI");
        ui->pushButtonSaveAdd->setStyleSheet("background-color: red");
    }
}
