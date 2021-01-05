#ifndef TEXTFILTER_CPP
#define TEXTFILTER_CPP

#include "TextFilter.h"
#include <QKeyEvent>
#include <QAbstractItemView>
#include <QScrollBar>

TextFilter::TextFilter(int digit, QWidget *parent)
    : QTextEdit(parent)
{
    setPlainText(tr("Scrivi qui.."));
    digitNum = digit;
    c = nullptr;

}

TextFilter::~TextFilter()
{

}

void TextFilter::setCompleter(QCompleter *completer)
{
    /*
    if (c)
        c->disconnect(this);
    */

    c = completer;

    if (!c)
        return;

    c->setWidget(this);
    c->setCompletionMode(QCompleter::PopupCompletion);
    c->setCaseSensitivity(Qt::CaseInsensitive);
    QObject::connect(c, QOverload<const QString &>::of(&QCompleter::activated),
                     this, &TextFilter::insertCompletion);
}

QCompleter * TextFilter::completer() const
{
    return c;
}

void TextFilter::insertCompletion(const QString &completion)
{
    emit measurementSelectedSig(completion);
}

QString TextFilter::textUnderCursor() const
{
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    return tc.selectedText();
}

void TextFilter::focusInEvent(QFocusEvent *e)
{
    if (c)
        c->setWidget(this);
    QTextEdit::focusInEvent(e);
    this->setText("");
}

void TextFilter::keyPressEvent(QKeyEvent *e)
{
    if (c && c->popup()->isVisible()) {
           // The following keys are forwarded by the completer to the widget
          switch (e->key()) {
          case Qt::Key_Enter:
          case Qt::Key_Return:
          case Qt::Key_Escape:
          case Qt::Key_Tab:
          case Qt::Key_Backtab:
               e->ignore();
               return; // let the completer do default behavior
          default:
              break;
          }
       }

       const bool isShortcut = (e->modifiers().testFlag(Qt::ControlModifier) && e->key() == Qt::Key_E); // CTRL+E
       if (!c || !isShortcut) // do not process the shortcut when we have a completer
           QTextEdit::keyPressEvent(e);

       const bool ctrlOrShift = e->modifiers().testFlag(Qt::ControlModifier) ||
                                    e->modifiers().testFlag(Qt::ShiftModifier);
           if (!c || (ctrlOrShift && e->text().isEmpty()))
               return;

           static QString eow("~!@#$%^&*()+{}|:\"<>?,./;'[]\\-="); // end of word
           const bool hasModifier = (e->modifiers() != Qt::NoModifier) && !ctrlOrShift;
           QString completionPrefix = textUnderCursor();

           if (!isShortcut && (hasModifier || e->text().isEmpty()|| completionPrefix.length() < digitNum
                             || eow.contains(e->text().right(1))))
           {
               c->popup()->hide();
               return;
           }

           if (completionPrefix != c->completionPrefix())
           {
               c->setCompletionPrefix(completionPrefix);
               c->popup()->setCurrentIndex(c->completionModel()->index(0, 0));
           }

           QRect cr = cursorRect();
           cr.setWidth(c->popup()->sizeHintForColumn(0) + c->popup()->verticalScrollBar()->sizeHint().width());
           c->complete(cr); // popup it up
}

#endif // TEXTFILTER_CPP
