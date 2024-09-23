#include "country.h"


std::shared_ptr<City> Country::addCity(const QString &nameCity) {
    auto newCity = std::make_shared<City>(nameCity);
    cities_.push_back(newCity);
    return newCity;
}

Cities Country::getAllCities() const {
    return cities_;
}
