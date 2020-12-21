#ifndef DOUBLESPINBOX_H
#define DOUBLESPINBOX_H

#include <QtWidgets/qtwidgetsglobal.h>
#include <QtWidgets/qabstractspinbox.h>
#include <QSpinBox>
#include <QtGlobal>
#include <Product.h>

class DOUBLEQSpinBox : public QAbstractSpinBox
{
Q_OBJECT
public:
    explicit DOUBLEQSpinBox(Product::prodContent * prod, QWidget *parent = 0);
    double value() const;
    QString prefix() const;
    void setPrefix(const QString &prefix);
    QString suffix() const;
    void setSuffix(const QString &suffix);
    QString cleanText() const;
    double singleStep() const;
    void setSingleStep(double val);
    double minimum() const;
    void setMinimum(double min);
    double maximum() const;
    void setMaximum(double max);
    void setRange(double min, double max);
    Product::prodContent * getProdLink(){ return prodLink; }
    double getValue(){ return m_value; }

public slots:
    void setValue(double value);

signals:
    void valueChanged(double i, DOUBLEQSpinBox *);
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
    double m_singleStep;
    double m_minimum;
    double m_maximum;
    double m_value;
    Product::prodContent * prodLink;

private:
    Q_DISABLE_COPY(DOUBLEQSpinBox)

};
#endif // DOUBLESPINBOX_H
