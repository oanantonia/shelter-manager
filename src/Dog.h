#pragma once
#include <string>
#include <iostream>

class Dog {

private:
	std::string breed;
	std::string name;
	int age;
	std::string photograph;

public:
	Dog(const std::string& breed = "", const std::string& name = "", int age = 0, const std::string& photograph = "");
	std::string get_breed() const;
	std::string get_name() const;
	int get_age() const;
	std::string get_photograph() const;
	void set_age(int new_age);
	void set_photograph(const std::string& new_photograph);
	bool operator==(const Dog& other) const;
	~Dog();

	friend std::istream& operator>>(std::istream& is, Dog& dog);
	friend std::ostream& operator<<(std::ostream& os, const Dog& dog);
};