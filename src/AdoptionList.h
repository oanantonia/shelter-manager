#pragma once
#include <vector>
#include <string>
#include "Dog.h"

class AdoptionList {
protected:
    std::string filename;
    std::vector<Dog> adoption_list;

public:
    AdoptionList(const std::string& filename);
    void add_dog(const Dog& dog);
    const std::vector<Dog>& get_dogs() const;
    virtual void write_to_file() = 0;
    virtual void clear() = 0;
    virtual ~AdoptionList() = default;
};
