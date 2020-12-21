#ifndef QACTIONWRAPPER_H
#define QACTIONWRAPPER_H

#include <QAction>

class QActionWrapper : public QAction
{
    Q_OBJECT

public:
    explicit QActionWrapper(QString name, QObject *parent = nullptr);
    ~QActionWrapper();

signals:
    void extendedTriggered(QAction*);

private Q_SLOTS:

    void emitExtendTrigger();
};

#endif // QACTIONWRAPPER_H
