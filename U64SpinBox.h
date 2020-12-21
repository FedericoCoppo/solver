
#ifndef U64QSPINBOX_H
#define U64QSPINBOX_H

#include <QtWidgets/qtwidgetsglobal.h>
#include <QtWidgets/qabstractspinbox.h>
#include <QSpinBox>
#include <QtGlobal>
#include <Product.h>

class U64QSpinBox : public QAbstractSpinBox
{
Q_OBJECT
public:
    explicit U64QSpinBox(Product::prodContent * cal, QWidget *parent = 0);
    uint64_t value() const;
    QString prefix() const;
    void setPrefix(const QString &prefix);
    QString suffix() const;
    void setSuffix(const QString &suffix);
    QString cleanText() const;
    uint64_t singleStep() const;
    void setSingleStep(uint64_t val);
    uint64_t minimum() const;
    void setMinimum(uint64_t min);
    uint64_t maximum() const;
    void setMaximum(uint64_t max);
    void setRange(uint64_t min, uint64_t max);
    Product::prodContent * getCalLink(){ return prodLink; }
    uint64_t getValue(){ return m_value; }

public slots:
    void setValue(uint64_t value);

signals:
    void valueChanged(uint64_t i, U64QSpinBox *);
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
    uint64_t m_singleStep;
    uint64_t m_minimum;
    uint64_t m_maximum;
    uint64_t m_value;
    Product::prodContent * prodLink;

private:
    Q_DISABLE_COPY(U64QSpinBox)

};

#endif // QSPINBOX_H



