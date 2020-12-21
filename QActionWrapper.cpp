#include "QActionWrapper.h"

QActionWrapper::QActionWrapper(QString name, QObject *parent)
    : QAction(name, parent)
{
    connect(this, SIGNAL(triggered()), this, SLOT(emitExtendTrigger()));
}

QActionWrapper::~QActionWrapper()
{
    disconnect(this, SIGNAL(triggered()), this, SLOT(emitExtendTrigger()));
}

void QActionWrapper::emitExtendTrigger()
{
    emit extendedTriggered(this);
}
