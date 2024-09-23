#include "country.h"


Country::Country(const QString &name) : AbstractLocality(name, TypeLocation::Country) {}

std::shared_ptr<City> Country::addCity(const QString &nameCity) {
    auto newCity = std::make_shared<City>(nameCity);
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

City::City(const QString &name) : AbstractLocality(name, TypeLocation::City) {}
