#include "UserService.h"
#include <exception>
#include <algorithm>
#include <iterator>

using namespace std;

UserService::UserService(IRepository& repo):
	repo{repo}
{}

void UserService::adopt_dog(const Dog& dog) 
{
    auto it = find(this->adoption_list.begin(), this->adoption_list.end(), dog);

    if (it != this->adoption_list.end()) {
        throw exception("This dog is already in your adoption list!");
    }

	this->adoption_list.push_back(dog);
}

const std::vector<Dog> UserService::get_adoption_list() const
{
	return this->adoption_list;
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

UserService::~UserService()
{}
