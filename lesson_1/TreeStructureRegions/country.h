#ifndef COUNTRY_H
#define COUNTRY_H

#include <QString>
#include <QPair>
#include <QVector>

#include <memory>

#include "abstractlocality.h"

class City;

using Cities = QVector<std::shared_ptr<City>>;

struct ParamsFile {
    ParamsFile(const QString& nameCity,
               double latitude,
               double longitude,
               const QString& nameCountry,
               const QString& iso2,
               const QString& iso3,
               double population
               ) :
        nameCity_(nameCity), latitude_(latitude), longitude_(longitude),
        nameCountry_(nameCountry), iso2_(iso2), iso3_(iso3), population_(population) {}

    QString nameCity_;
    double latitude_;
    double longitude_;
    QString nameCountry_;
    QString iso2_;
    QString iso3_;
    double population_;
};


class City : public AbstractLocality {
public:
    City(const QString& name);
    City(const QString& name, double population, double latitude, double longitude);
    ~City() {}

    double getPopulation() const;
    std::pair<double, double> coordinate() const;

    void setPopulation(double newPopulation);
    void setCoordinate(std::pair<double, double>& coordinate);

private:
    double population_;
    double latitude_;
    double longitude_;
};

class Country : public AbstractLocality {
public:
    Country();
    Country(const QString& name);
    Country(const QString& name, const QString& iso2, const QString& iso3);
    ~Country() {}

    std::shared_ptr<City> addCity(const QString& nameCity);
    std::shared_ptr<City> addCity(const QString &nameCity,
            double population, double latitude, double longitude);

    bool addCities(const QVector<QString>& namesCity);

    Cities getAllCities() const;

    QString iso2Reduction() const;
    void setIso2Reduction(const QString &newIso2Reduction);

    QString iso3Reduction() const;
    void setIso3Reduction(const QString &newIso3Reduction);

private:
    QVector<std::shared_ptr<City>> cities_;
    QString iso2Reduction_;
    QString iso3Reduction_;
};

#endif // COUNTRY_H
