#pragma once
#include "IRepository.h"

class AdminService {

private:
	IRepository& repo;

public:
	AdminService(IRepository& repo);
	void add_dog(const std::string& breed, const std::string& name, int age, const std::string& photograph);
	void delete_dog(const std::string& breed, const std::string& name);
	void update_dog_age(const std::string& breed, const std::string& name, int new_age);
	void update_dog_photograph(const std::string& breed, const std::string& name, const std::string& new_photograph);
	const std::vector<Dog> get_dogs() const;
	~AdminService();
};
