#include "U64SpinBox.h"
#include <QLineEdit>
#include <limits>
#include <QEvent>
#include <QKeyEvent>

U64QSpinBox::U64QSpinBox(Product::prodContent * prod, QWidget *parent) :
    QAbstractSpinBox(parent)
{
    m_minimum = std::numeric_limits<uint64_t>::min();
    m_maximum = std::numeric_limits<uint64_t>::max();
    m_value = 0;
    m_singleStep = 1;
    setValue(m_value);
    prodLink = prod;
}

uint64_t U64QSpinBox::value() const
{
    return m_value;
}

void U64QSpinBox::setValue(uint64_t expectedNewValue)
{
    const uint64_t newValue = qBound(m_minimum, expectedNewValue, m_maximum);
    const QString newValueString = QString::number(newValue);
    lineEdit()->setText(m_prefix + newValueString + m_suffix);
    if (m_value != newValue) {
        m_value = newValue;

        emit valueChanged(newValue, this);
        emit valueChanged(newValueString);
    }
}

QString U64QSpinBox::prefix() const
{
    return m_prefix;
}

void U64QSpinBox::setPrefix(const QString &prefix)
{
    m_prefix = prefix;
    setValue(m_value);
}

QString U64QSpinBox::suffix() const
{
    return m_suffix;
}

void U64QSpinBox::setSuffix(const QString &suffix)
{
    m_suffix = suffix;
    setValue(m_value);
}

QString U64QSpinBox::cleanText() const
{
    return QString::number(m_value);
}

uint64_t U64QSpinBox::singleStep() const
{
    return m_singleStep;
}

void U64QSpinBox::setSingleStep(uint64_t step)
{
    m_singleStep = step;
}

uint64_t U64QSpinBox::minimum() const
{
    return m_minimum;
}

void U64QSpinBox::setMinimum(uint64_t min)
{
    m_minimum = min;
    if (m_maximum < m_minimum) {
        m_maximum = m_minimum;
    }

    setValue(m_value);
}

uint64_t U64QSpinBox::maximum() const
{
    return m_maximum;
}

void U64QSpinBox::setMaximum(uint64_t max)
{
    m_maximum = max;
    if (m_maximum < m_minimum) {
        m_maximum = m_minimum;
    }

    setValue(m_value);
}

void U64QSpinBox::setRange(uint64_t min, uint64_t max)
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

void U64QSpinBox::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Enter:
    case Qt::Key_Return:
        selectCleanText();
        lineEditEditingFinalize();
    }

    QAbstractSpinBox::keyPressEvent(event);
}

void U64QSpinBox::focusOutEvent(QFocusEvent *event)
{
    lineEditEditingFinalize();

    QAbstractSpinBox::focusOutEvent(event);
}

QAbstractSpinBox::StepEnabled U64QSpinBox::stepEnabled() const
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

void U64QSpinBox::stepBy(int steps)
{
    if (isReadOnly()) {
        return;
    }

    if (m_prefix + QString::number(m_value) + m_suffix != lineEdit()->text()) {
        lineEditEditingFinalize();
    }

    uint64_t newValue = m_value + (steps * m_singleStep);
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

QValidator::State U64QSpinBox::validate(QString &input, int &pos) const
{
    // first, we try to interpret as a number without prefixes
    bool ok;
    const uint64_t value = input.toULongLong(&ok);
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
        const uint64_t value = number.toULongLong(&ok);
        if (number.isEmpty() || (ok && value <= m_maximum)) {
            return QValidator::Acceptable;
        }
    }

    // otherwise not acceptable
    return QValidator::Invalid;
}

void U64QSpinBox::lineEditEditingFinalize()
{
    const QString text = lineEdit()->text();

    // first, we try to read as a number without prefixes
    bool ok;
    uint64_t value = text.toULongLong(&ok);
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
        const uint64_t value = text.mid(start, length).toULongLong(&ok);
        if (ok) {
            setValue(value);
            return;
        }
    }

    // otherwise set old value
    setValue(m_value);
}

void U64QSpinBox::selectCleanText()
{
    lineEdit()->setSelection(m_prefix.length(),
                             lineEdit()->text().length()
                             - m_prefix.length()
                             - m_suffix.length());
}
