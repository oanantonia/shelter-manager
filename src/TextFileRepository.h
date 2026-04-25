#pragma once
#include <string.h>
#include "IRepository.h"

class TextFileRepository: public IRepository {
private:
	std::vector<Dog> storage;
	std::string filename;

	void read_from_file();
	void write_to_file();

public:
	TextFileRepository(const std::string& filename);
	void add_dog(const Dog& dog) override;
	int find_dog(const std::string& breed, const std::string& name) override;
	void delete_dog(const Dog& dog) override;
	void set_dog(const Dog& old_dog, const Dog& new_dog) override;
	Dog get_dog(int index) override;
	const std::vector<Dog> get_dogs() const override;
	~TextFileRepository() override;
};

