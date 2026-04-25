#include "Dog.h"

using namespace std;

Dog::Dog(const string& breed, const string& name, int age, const string& photograph):
	breed(breed), name(name), age(age), photograph(photograph)
{
}

string Dog::get_breed() const
{
	return breed;
}

string Dog::get_name() const
{
	return name;
}

int Dog::get_age() const
{
	return age;
}

string Dog::get_photograph() const
{
	return photograph;
}

void Dog::set_age(int new_age)
{
	this->age = new_age;
}

void Dog::set_photograph(const string& new_photograph)
{
	this->photograph = new_photograph;
}

bool Dog::operator==(const Dog& other) const
{
	return (this->breed == other.get_breed() && this->name == other.get_name());
}

Dog::~Dog()
{}

istream& operator>>(istream& is, Dog& dog)
{
	string line;
    if (getline(is, line)) {
        auto pos1 = line.find(',');
        auto pos2 = line.find(',', pos1 + 1);
        auto pos3 = line.find(',', pos2 + 1);

        if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
            string breed = line.substr(0, pos1);
            string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string age_str = line.substr(pos2 + 1, pos3 - pos2 - 1);
            string photograph = line.substr(pos3 + 1);

            dog = Dog(breed, name, stoi(age_str), photograph);
        }
    }

    return is;
}

ostream& operator<<(ostream& os, const Dog& dog)
{
    os << dog.get_breed() << "," << dog.get_name() << "," << dog.get_age() << "," << dog.get_photograph();
    return os;
}
