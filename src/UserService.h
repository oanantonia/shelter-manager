#pragma once
#include "IRepository.h"
#include "AdoptionList.h"

class UserService{
private:
	IRepository& repo;
	AdoptionList* adoption_list;

public:
    UserService(IRepository& repo);
    void set_adoption_list(AdoptionList* list);
    void adopt_dog(const Dog& dog);
    const std::vector<Dog> get_adoption_list() const;
    std::vector<Dog> get_filtered_dogs(const std::string& breed, int max_age) const;
    const std::vector<Dog> get_dogs() const;
    void clear_adoption_list();
    ~UserService();
};

