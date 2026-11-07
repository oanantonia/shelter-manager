#include "UserService.h"
#include "Exceptions.h"
#include <exception>
#include <algorithm>
#include <iterator>

using namespace std;

UserService::UserService(IRepository& repo) : repo{ repo }, adoption_list{ nullptr }
{}

void UserService::set_adoption_list(AdoptionList* list)
{
    this->adoption_list = list;
}

void UserService::adopt_dog(const Dog& dog)
{
    auto it = find(this->adoption_list->get_dogs().begin(), this->adoption_list->get_dogs().end(), dog);

    if (it != this->adoption_list->get_dogs().end()) {
        throw ServiceException("This dog is already in your adoption list!");
    }

	this->adoption_list->add_dog(dog);
}

const std::vector<Dog> UserService::get_adoption_list() const
{
	return this->adoption_list->get_dogs();
}

std::vector<Dog> UserService::get_filtered_dogs(const std::string& breed, int max_age) const
{
    vector<Dog> all_dogs = this->repo.get_dogs();
    vector<Dog> filtered_dogs;

    copy_if(all_dogs.begin(), all_dogs.end(), back_inserter(filtered_dogs), [&breed, max_age](const Dog& dog) {
            return (breed.empty() || dog.get_breed() == breed) && dog.get_age() < max_age;
    });

    return filtered_dogs;
}

const std::vector<Dog> UserService::get_dogs() const
{
    return this->repo.get_dogs();
}

void UserService::clear_adoption_list()
{
    if (this->adoption_list != nullptr) {
        this->adoption_list->clear();
    }
}

UserService::~UserService()
{
    delete this->adoption_list;
}
