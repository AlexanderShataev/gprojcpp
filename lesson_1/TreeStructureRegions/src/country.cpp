#include "country.h"


Country::Country(const QString &name) : AbstractLocality(name, TypeLocation::Country) {}

Country::Country(const QString &name, const QString &iso2, const QString &iso3) :
    AbstractLocality(name, TypeLocation::Country),
        iso2Reduction_(iso2), iso3Reduction_(iso3) {}

std::shared_ptr<City> Country::addCity(const QString &nameCity) {
    auto newCity = std::make_shared<City>(nameCity);
    cities_.push_back(newCity);
    return newCity;
}

std::shared_ptr<City> Country::addCity(const QString &nameCity,
                        double population, double latitude, double longitude) {
    auto newCity = std::make_shared<City>(nameCity, population, latitude, longitude);
    cities_.push_back(newCity);
    return newCity;
}

bool Country::addCities(const QVector<QString>& namesCity)
{
    cities_.reserve(namesCity.size());
    for (auto city : namesCity) {
        auto newCity = std::make_shared<City>(city);
        cities_.push_back(newCity);
    }
    return cities_.size() == namesCity.size();
}

Cities Country::getAllCities() const {
    return cities_;
}

QString Country::iso2Reduction() const
{
    return iso2Reduction_;
}

void Country::setIso2Reduction(const QString &newIso2Reduction)
{
    iso2Reduction_ = newIso2Reduction;
}

QString Country::iso3Reduction() const
{
    return iso3Reduction_;
}

void Country::setIso3Reduction(const QString &newIso3Reduction)
{
    iso3Reduction_ = newIso3Reduction;
}

City::City(const QString &name) : AbstractLocality(name, TypeLocation::City) {}

City::City(const QString &name, double population, double latitude, double longitude) :
    AbstractLocality(name, TypeLocation::City),
        population_(population), latitude_(latitude), longitude_(longitude) {}

double City::getPopulation() const
{
    return population_;
}

std::pair<double, double> City::coordinate() const
{
    return std::make_pair(latitude_, longitude_);
}

void City::setPopulation(double newPopulation)
{
    population_ = newPopulation;
}

void City::setCoordinate(std::pair<double, double> &coordinate)
{
    latitude_ = coordinate.first;
    longitude_ = coordinate.second;
}
