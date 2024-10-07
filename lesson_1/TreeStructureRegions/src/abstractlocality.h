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
    //AbstractLocality() = delete;
    AbstractLocality(const QString& name, TypeLocation type = TypeLocation::Undefined)
        : name_(name), type_(type) {}
    virtual ~AbstractLocality() {}

    void rename(const QString& newName);
    QString name() const;

    TypeLocation getType() { return type_; }
private:
    QString name_;
    TypeLocation type_{TypeLocation::Undefined};

};

bool operator<(AbstractLocality a1, AbstractLocality a2);

#endif // ABSTRACTLOCALITY_H
