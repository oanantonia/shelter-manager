#include "AdminService.h"

using namespace std;

AdminService::AdminService(IRepository& repo): repo{ repo }
{}

void AdminService::add_dog(const string& breed, const string& name, int age, const string& photograph)
{
	Dog new_dog = Dog(breed, name, age, photograph);
	this->repo.add_dog(new_dog);
}

void AdminService::delete_dog(const string& breed, const string& name)
{
	Dog dog_to_remove = Dog(breed, name);
	this->repo.delete_dog(dog_to_remove);
}

void AdminService::update_dog_age(const string& breed, const string& name, int new_age)
{
	int index = this->repo.find_dog(breed, name);
	Dog old_dog = this->repo.get_dog(index);
	Dog new_dog = Dog(breed, name, new_age, old_dog.get_photograph());
	this->repo.set_dog(old_dog, new_dog);
}

void AdminService::update_dog_photograph(const std::string& breed, const std::string& name, 
	const std::string& new_photograph)
{
	int index = this->repo.find_dog(breed, name);
	Dog old_dog = this->repo.get_dog(index);
	Dog new_dog = Dog(breed, name, old_dog.get_age(), new_photograph);
	this->repo.set_dog(old_dog, new_dog);
}

const std::vector<Dog> AdminService::get_dogs() const
{
	return this->repo.get_dogs();
}

AdminService::~AdminService()
{}
