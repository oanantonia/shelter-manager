#pragma once
#include <vector>
#include "Dog.h"
#include "IRepository.h"

class MemoryRepository: public IRepository {

private:
	std::vector<Dog> storage;

public:
	MemoryRepository();
	void add_dog(const Dog& dog) override;
	int find_dog(const std::string& breed, const std::string& name) override;
	void delete_dog(const Dog& dog) override;
	void set_dog(const Dog& old_dog, const Dog& new_dog) override;
	Dog get_dog(int index) override;
	const std::vector<Dog> get_dogs() const override;
	~MemoryRepository() override;
};
