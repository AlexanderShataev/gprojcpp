#include "abstractlocality.h"

void AbstractLocality::rename(const QString &newName) {
    name_ = newName;
}

QString AbstractLocality::name() const
{
    return name_;
}
