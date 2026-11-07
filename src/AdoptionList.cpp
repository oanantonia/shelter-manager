#include "AdoptionList.h"

AdoptionList::AdoptionList(const std::string& filename) : filename{ filename } {}

void AdoptionList::add_dog(const Dog& dog) {
    this->adoption_list.push_back(dog);
    this->write_to_file();
}

const std::vector<Dog>& AdoptionList::get_dogs() const {
    return this->adoption_list;
}
