#ifndef COUNTRY_H
#define COUNTRY_H

#include <QString>
#include <QPair>
#include <QVector>

#include <memory>

#include "abstractlocality.h"

class City;

using Cities = QVector<std::shared_ptr<City>>;

class City : public AbstractLocality {
public:
    City(const QString& name, TypeLocation type = TypeLocation::City) : AbstractLocality(name, type) {}
    ~City() {}
private:
    QString name_;
};

class Country : AbstractLocality {
public:
    Country() = delete;
    Country(const QString& name, TypeLocation type = TypeLocation::Country) : AbstractLocality(name, type) {}

    std::shared_ptr<City> addCity(const QString& nameCity);
    bool addCities(const QVector<QString>& namesCity);

    Cities getAllCities() const;

private:
    QString name_;
    QVector<std::shared_ptr<City>> cities_;
};

#endif // COUNTRY_H
