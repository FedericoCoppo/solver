#ifndef DELETECONFIRM_H
#define DELETECONFIRM_H

#include <QDialog>

namespace Ui {
class DeleteConfirm;
}

class DeleteConfirm : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteConfirm(QString code, QWidget *parent = nullptr);
    ~DeleteConfirm();

private:
    Ui::DeleteConfirm *ui;
    QString unicCode;
};

#endif // DELETECONFIRM_H
