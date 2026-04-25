#pragma once
#include "IRepository.h"

class UserService{
private:
	IRepository& repo;
	std::vector<Dog> adoption_list;

public:
    UserService(IRepository& repo);
    void adopt_dog(const Dog& dog);
    const std::vector<Dog> get_adoption_list() const;
    std::vector<Dog> get_filtered_dogs(const std::string& breed, int max_age) const;
    const std::vector<Dog> get_dogs() const;
    ~UserService();
};

