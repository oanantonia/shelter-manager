#include "DatabaseRepository.h"
#include "Exceptions.h"

using namespace std;

DatabaseRepository::DatabaseRepository(const std::string& db_file) : db_file{ db_file } {
    if (sqlite3_open(db_file.c_str(), &db) != SQLITE_OK) {
        throw RepositoryException("Cannot open database!");
    }

    string query = "CREATE TABLE IF NOT EXISTS Dogs ("
        "breed TEXT NOT NULL, "
        "name TEXT NOT NULL, "
        "age INTEGER, "
        "photograph TEXT);";
    execute_query(query);
}

void DatabaseRepository::execute_query(const std::string& query) {
    char* error_message = nullptr;
    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &error_message) != SQLITE_OK) {
        string error = error_message;
        sqlite3_free(error_message);
        throw RepositoryException(error);
    }
}

void DatabaseRepository::add_dog(const Dog& dog) {
    if (find_dog(dog.get_breed(), dog.get_name()) != -1) {
        throw RepositoryException("This dog is already in the shelter!");
    }

    string query = "INSERT INTO Dogs (breed, name, age, photograph) VALUES ('" +
        dog.get_breed() + "', '" + dog.get_name() + "', " +
        to_string(dog.get_age()) + ", '" + dog.get_photograph() + "');";
    execute_query(query);
}

void DatabaseRepository::delete_dog(const Dog& dog) {
    if (find_dog(dog.get_breed(), dog.get_name()) == -1) {
        throw RepositoryException("This dog is not in the shelter!");
    }

    string query = "DELETE FROM Dogs WHERE breed = '" + dog.get_breed() + "' AND name = '" + dog.get_name() + "';";
    execute_query(query);
}

void DatabaseRepository::set_dog(const Dog& old_dog, const Dog& new_dog) {
    if (find_dog(old_dog.get_breed(), old_dog.get_name()) == -1) {
        throw RepositoryException("This dog is not in the shelter!");
    }

    string query = "UPDATE Dogs SET age = " + to_string(new_dog.get_age()) +
        ", photograph = '" + new_dog.get_photograph() + "' "
        "WHERE breed = '" + old_dog.get_breed() + "' AND name = '" + old_dog.get_name() + "';";
    execute_query(query);
}

const std::vector<Dog> DatabaseRepository::get_dogs() const {
    std::vector<Dog> dogs;
    sqlite3_stmt* stmt;
    string query = "SELECT breed, name, age, photograph FROM Dogs;";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            string breed = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            int age = sqlite3_column_int(stmt, 2);
            string photograph = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

            dogs.push_back(Dog(breed, name, age, photograph));
        }
    }
    sqlite3_finalize(stmt);
    return dogs;
}

int DatabaseRepository::find_dog(const std::string& breed, const std::string& name) {
    vector<Dog> dogs = get_dogs();
    for (int i = 0; i < dogs.size(); i++) {
        if (dogs[i].get_breed() == breed && dogs[i].get_name() == name) {
            return i;
        }
    }
    return -1;
}

Dog DatabaseRepository::get_dog(int index) {
    vector<Dog> dogs = get_dogs();
    return dogs[index];
}

DatabaseRepository::~DatabaseRepository() {
    sqlite3_close(db);
}