#include "DOUBLESpinBox.h"
#include <QLineEdit>
#include <limits>
#include <QEvent>
#include <QKeyEvent>

DOUBLEQSpinBox::DOUBLEQSpinBox(Product::prodContent * prod, QWidget *parent) :
    QAbstractSpinBox(parent)
{
    m_minimum = - std::numeric_limits<double>::max();
    m_maximum = std::numeric_limits<double>::max();
    m_value = 0;
    m_singleStep = 1;
    setValue(m_value);
    prodLink = prod;
}

double DOUBLEQSpinBox::value() const
{
    return m_value;
}

void DOUBLEQSpinBox::setValue(double expectedNewValue)
{
    const double newValue = qBound(m_minimum, expectedNewValue, m_maximum);
    const QString newValueString = QString::number(newValue);
    lineEdit()->setText(m_prefix + newValueString + m_suffix);
    if (m_value != newValue) {
        m_value = newValue;

        emit valueChanged(newValue, this);
        emit valueChanged(newValueString);
    }
}

QString DOUBLEQSpinBox::prefix() const
{
    return m_prefix;
}

void DOUBLEQSpinBox::setPrefix(const QString &prefix)
{
    m_prefix = prefix;
    setValue(m_value);
}

QString DOUBLEQSpinBox::suffix() const
{
    return m_suffix;
}

void DOUBLEQSpinBox::setSuffix(const QString &suffix)
{
    m_suffix = suffix;
    setValue(m_value);
}

QString DOUBLEQSpinBox::cleanText() const
{
    return QString::number(m_value);
}

double DOUBLEQSpinBox::singleStep() const
{
    return m_singleStep;
}

void DOUBLEQSpinBox::setSingleStep(double step)
{
    m_singleStep = step;
}

double DOUBLEQSpinBox::minimum() const
{
    return m_minimum;
}

void DOUBLEQSpinBox::setMinimum(double min)
{
    m_minimum = min;
    if (m_maximum < m_minimum) {
        m_maximum = m_minimum;
    }

    setValue(m_value);
}

double DOUBLEQSpinBox::maximum() const
{
    return m_maximum;
}

void DOUBLEQSpinBox::setMaximum(double max)
{
    m_maximum = max;
    if (m_maximum < m_minimum) {
        m_maximum = m_minimum;
    }

    setValue(m_value);
}

void DOUBLEQSpinBox::setRange(double min, double max)
{
    if (min < max) {
        m_minimum = min;
        m_maximum = max;
    }
    else {
        m_minimum = max;
        m_maximum = min;
    }

    setValue(m_value);
}

void DOUBLEQSpinBox::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Enter:
    case Qt::Key_Return:
        selectCleanText();
        lineEditEditingFinalize();
    }

    QAbstractSpinBox::keyPressEvent(event);
}

void DOUBLEQSpinBox::focusOutEvent(QFocusEvent *event)
{
    lineEditEditingFinalize();

    QAbstractSpinBox::focusOutEvent(event);
}

QAbstractSpinBox::StepEnabled DOUBLEQSpinBox::stepEnabled() const
{
    if (isReadOnly()) {
        return 0;
    }

    StepEnabled se = 0;
    if (wrapping() || m_value < m_maximum) {
        se |= StepUpEnabled;
    }
    if (wrapping() || m_value > m_minimum) {
        se |= StepDownEnabled;
    }

    return se;
}

void DOUBLEQSpinBox::stepBy(int steps)
{
    if (isReadOnly()) {
        return;
    }

    if (m_prefix + QString::number(m_value) + m_suffix != lineEdit()->text()) {
        lineEditEditingFinalize();
    }

    double newValue = m_value + (steps * m_singleStep);
    if (wrapping()) {
        // emulating the behavior of QSpinBox
        if (newValue > m_maximum) {
            if (m_value == m_maximum) {
                newValue = m_minimum;
            }
            else {
                newValue = m_maximum;
            }
        }
        else if (newValue < m_minimum) {
            if (m_value == m_minimum) {
                newValue = m_maximum;
            }
            else {
                newValue = m_minimum;
            }
        }
    }
    else {
        newValue = qBound(m_minimum, newValue, m_maximum);
    }

    setValue(newValue);
    selectCleanText();
}

QValidator::State DOUBLEQSpinBox::validate(QString &input, int &pos) const
{
    // first, we try to interpret as a number without prefixes
    bool ok;

    if (input == "-")
    {
        return QValidator::Acceptable;
    }

    const double value = input.toDouble(&ok);
    if (input.isEmpty() || (ok && value <= m_maximum)) {
        input = m_prefix + input + m_suffix;
        pos += m_prefix.length();
        return QValidator::Acceptable;
    }

    // if string of text editor aren't simple number, try to interpret it
    // as a number with prefix and suffix
    bool valid = true;
    if (!m_prefix.isEmpty() && !input.startsWith(m_prefix)) {
        valid = false;
    }
    if (!m_suffix.isEmpty() && !input.endsWith(m_suffix)) {
        valid = false;
    }

    if (valid) {
        const int start = m_prefix.length();
        const int length = input.length() - start - m_suffix.length();

        bool ok;
        const QString number = input.mid(start, length);
        const double value = number.toDouble(&ok);
        if (number.isEmpty() || (ok && value <= m_maximum)) {
            return QValidator::Acceptable;
        }
    }

    // otherwise not acceptable
    return QValidator::Invalid;
}

void DOUBLEQSpinBox::lineEditEditingFinalize()
{
    const QString text = lineEdit()->text();

    // first, we try to read as a number without prefixes
    bool ok;
    double value = text.toDouble(&ok);
    if (ok) {
        setValue(value);
        return;
    }

    // if string of text editor aren't simple number, try to interpret it
    // as a number with prefix and suffix
    bool valid = true;
    if (!m_prefix.isEmpty() && !text.startsWith(m_prefix)) {
        valid = false;
    }
    else if (!m_suffix.isEmpty() && !text.endsWith(m_suffix)) {
        valid = false;
    }

    if (valid) {
        const int start = m_prefix.length();
        const int length = text.length() - start - m_suffix.length();

        bool ok;
        const double value = text.mid(start, length).toDouble(&ok);
        if (ok) {
            setValue(value);
            return;
        }
    }

    // otherwise set old value
    setValue(m_value);
}

void DOUBLEQSpinBox::selectCleanText()
{
    lineEdit()->setSelection(m_prefix.length(),
                             lineEdit()->text().length()
                             - m_prefix.length()
                             - m_suffix.length());
}


