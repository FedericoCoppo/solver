#ifndef  COMBO
#define COMBO

#include <QtWidgets/qtwidgetsglobal.h>
#include <QtWidgets/qabstractspinbox.h>
#include <QtGlobal>
#include <QComboBox>
#include "ProductDisplayer.h"

class MyCombo : public QComboBox
{
Q_OBJECT
public:
    MyCombo(int idx, QWidget* parent = nullptr);
    uint32_t GetIndex() {return this->index; }

private:
    int index;
private:
    Q_DISABLE_COPY(MyCombo)

private slots:
    void myComboBoxIndexChanged(int);

public :
signals:
    void myComboBoxIndexChangedSig(int,int);

};

#endif
