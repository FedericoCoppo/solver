#include <QLineEdit>
#include <limits>
#include <QEvent>
#include <QKeyEvent>
#include "MyCombo.h"

MyCombo::MyCombo(int idx, QWidget* parent) :
    QComboBox(parent)
{
    index = idx;

    QObject::connect(this,SIGNAL(currentIndexChanged(int)),
            this,SLOT (myComboBoxIndexChanged(int)));

}

void MyCombo::myComboBoxIndexChanged(int idxChanged)
{
    emit myComboBoxIndexChangedSig(idxChanged, index);
}
