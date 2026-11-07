#pragma once
#include "IRepository.h"
#include "sqlite3.h"
#include <string>
#include <vector>

class DatabaseRepository : public IRepository {
private:
    sqlite3* db;
    std::string db_file;

    void execute_query(const std::string& query);

public:
    DatabaseRepository(const std::string& db_file);

    void add_dog(const Dog& dog) override;
    int find_dog(const std::string& breed, const std::string& name) override;
    void delete_dog(const Dog& dog) override;
    void set_dog(const Dog& old_dog, const Dog& new_dog) override;
    Dog get_dog(int index) override;
    const std::vector<Dog> get_dogs() const override;

    ~DatabaseRepository() override;
};