#ifndef TEXTFILTER_H
#define TEXTFILTER_H

#include <QTextEdit>
#include <QWidget>
#include <QCompleter>

class TextFilter : public QTextEdit
{
    Q_OBJECT

public:
    TextFilter(int digit, QWidget *parent = nullptr);
    ~TextFilter();

    void setCompleter(QCompleter *c);
    QCompleter *completer() const;

protected:
    void keyPressEvent(QKeyEvent *e) override;
    void focusInEvent(QFocusEvent *e) override;

private slots:
    void insertCompletion(const QString &completion);

private:
    QString textUnderCursor() const;
    int digitNum;

private:
    QCompleter * c;

signals:
    void measurementSelectedSig(QString str);
};

#endif // TEXTFILTER_H
