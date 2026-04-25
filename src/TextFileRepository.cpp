#include "TextFileRepository.h"
#include <fstream>

using namespace std;

TextFileRepository::TextFileRepository(const std::string& filename)
{
    this->filename = filename;
    this->read_from_file();
}

void TextFileRepository::read_from_file()
{
    ifstream file(this->filename);

    if (!file.is_open()) {
        return; 
    }

    Dog dog;
    while (file >> dog) {
        this->storage.push_back(dog);
    }

    file.close();
}

void TextFileRepository::write_to_file()
{
    ofstream file(this->filename);

    for (const auto& dog : this->storage) {
        file << dog << "\n";
    }

    file.close();
}

void TextFileRepository::add_dog(const Dog & dog)
{
    int index = find_dog(dog.get_breed(), dog.get_name());
    if (index != -1) {
        throw exception("This dog is already in the shelter!");
    }
    this->storage.push_back(dog);
    this->write_to_file();
}

int TextFileRepository::find_dog(const std::string & breed, const std::string & name)
{
    auto it = find_if(this->storage.begin(), this->storage.end(), [&breed, &name](const Dog& dog) {
        return dog.get_breed() == breed && dog.get_name() == name;
     });

    if (it != this->storage.end()) {
        return it - this->storage.begin();
    }

    return -1;
}

void TextFileRepository::delete_dog(const Dog& dog)
{
    int index = find_dog(dog.get_breed(), dog.get_name());
    if (index == -1) {
        throw exception("This dog is not in the shelter!");
    }
    this->storage.erase(storage.begin() + index);
    this->write_to_file();
}

void TextFileRepository::set_dog(const Dog & old_dog, const Dog & new_dog)
{
    int index = find_dog(old_dog.get_breed(), old_dog.get_name());
    if (index == -1) {
        throw exception("This dog is not in the shelter!");
    }
    this->storage[index] = new_dog;
    this->write_to_file(); 
}

Dog TextFileRepository::get_dog(int index)
{
    return this->storage[index];
}

const std::vector<Dog> TextFileRepository::get_dogs() const
{
    return this->storage;
}

TextFileRepository::~TextFileRepository()
{}
