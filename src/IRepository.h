#pragma once
#include <vector>
#include "Dog.h"

class IRepository {
public:
	virtual void add_dog(const Dog& dog) = 0;
	virtual int find_dog(const std::string& breed, const std::string& name) = 0;
	virtual void delete_dog(const Dog& dog) = 0;
	virtual void set_dog(const Dog& old_dog, const Dog& new_dog) = 0;
	virtual Dog get_dog(int index) = 0;
	virtual const std::vector<Dog> get_dogs() const = 0;
	virtual ~IRepository() = default;
}; 
