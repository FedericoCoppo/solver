#ifndef INT64SPINBOX_H
#define INT64SPINBOX_H

#include <QtWidgets/qtwidgetsglobal.h>
#include <QtWidgets/qabstractspinbox.h>
#include <QSpinBox>
#include <QtGlobal>
#include <Product.h>

class I64QSpinBox : public QAbstractSpinBox
{
    Q_OBJECT
public:
    explicit I64QSpinBox(Product::prodContent * prod, QWidget *parent = 0);
    qlonglong value() const;
    QString prefix() const;
    void setPrefix(const QString &prefix);
    QString suffix() const;
    void setSuffix(const QString &suffix);
    QString cleanText() const;
    qlonglong singleStep() const;
    void setSingleStep(qlonglong val);
    qlonglong minimum() const;
    void setMinimum(qlonglong min);
    qlonglong maximum() const;
    void setMaximum(qlonglong max);
    void setRange(qlonglong min, qlonglong max);
    Product::prodContent * getProdLink(){ return prodLink; }
    qlonglong getValue(){ return m_value; }

public slots:
    void setValue(qlonglong value);

signals:
    void valueChanged(qlonglong i, I64QSpinBox * pt);
    void valueChanged(const QString &text);

protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void focusOutEvent(QFocusEvent *event);
    virtual void stepBy(int steps);
    virtual StepEnabled stepEnabled() const;
    virtual QValidator::State validate(QString & input, int &pos) const;

private:
    void lineEditEditingFinalize();
    void selectCleanText();

private:
    QString m_prefix;
    QString m_suffix;
    qlonglong m_singleStep;
    qlonglong m_minimum;
    qlonglong m_maximum;
    qlonglong m_value;
    Product::prodContent * prodLink;

private:
    Q_DISABLE_COPY(I64QSpinBox)
};


#endif // INT64SPINBOX_H
