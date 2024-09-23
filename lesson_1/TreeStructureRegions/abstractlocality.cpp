#include "abstractlocality.h"

void AbstractLocality::rename(const QString &newName) {
    name_ = newName;
}

QString AbstractLocality::name() const
{
    return name_;
}

bool operator<(AbstractLocality a1, AbstractLocality a2) {
    return a1.name() < a2.name();
}
