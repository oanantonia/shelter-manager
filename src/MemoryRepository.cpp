#include <stdexcept>
#include "MemoryRepository.h"

using namespace std;

MemoryRepository::MemoryRepository()
{}

void MemoryRepository::add_dog(const Dog& dog)
{
	int index = find_dog(dog.get_breed(), dog.get_name());
	if (index != -1) {
		throw exception("This dog is already in the shelter!");
	}
	this->storage.push_back(dog);
}

int MemoryRepository::find_dog(const std::string& breed, const std::string& name)
{
	auto it = find_if(this->storage.begin(), this->storage.end(), [&breed, &name](const Dog& dog) {
			return dog.get_breed() == breed && dog.get_name() == name;
	});

	if (it != this->storage.end()) {
		return it - this->storage.begin();
	}

	return -1;
}

void MemoryRepository::delete_dog(const Dog& dog)
{
	int index = find_dog(dog.get_breed(), dog.get_name());
	if (index == -1) {
		throw exception("This dog is not in the shelter!");
	}
	this->storage.erase(storage.begin() + index);
}

void MemoryRepository::set_dog(const Dog& old_dog, const Dog& new_dog)
{
	int index = find_dog(old_dog.get_breed(), old_dog.get_name());
	if (index == -1) {
		throw exception("This dog is not in the shelter!");
	}
	this->storage[index] = new_dog;
}

Dog MemoryRepository::get_dog(int index)
{
	return this->storage[index];
}

const std::vector<Dog> MemoryRepository::get_dogs() const
{
	return this->storage;
}

MemoryRepository::~MemoryRepository()
{}


