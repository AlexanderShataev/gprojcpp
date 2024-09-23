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
    City(const QString& name);
    ~City() {}
};

class Country : public AbstractLocality {
public:
    Country();
    Country(const QString& name);
    ~Country() {}

    std::shared_ptr<City> addCity(const QString& nameCity);
    bool addCities(const QVector<QString>& namesCity);

    Cities getAllCities() const;

private:
    QVector<std::shared_ptr<City>> cities_;
};

#endif // COUNTRY_H
