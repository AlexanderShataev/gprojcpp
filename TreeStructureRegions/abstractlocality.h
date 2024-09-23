#ifndef ABSTRACTLOCALITY_H
#define ABSTRACTLOCALITY_H

#include <QString>

enum class TypeLocation {
    City                = 1,
    Country             = 2,
    Undefined           = -1
};

class AbstractLocality {
public:
    AbstractLocality() = delete;
    AbstractLocality(const QString& name, TypeLocation type = TypeLocation::Undefined)
        : name_(name), type_(type) {}
    virtual ~AbstractLocality() = 0;

    void rename(const QString& newName);
    QString name() const;

private:
    QString name_;
    TypeLocation type_{TypeLocation::Undefined};

};

#endif // ABSTRACTLOCALITY_H
