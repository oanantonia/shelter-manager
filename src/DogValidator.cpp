#include "DogValidator.h"
#include "Exceptions.h"

using namespace std;

void DogValidator::validate(const Dog& d)
{
	string errors;
    if (d.get_breed().empty()) {
        errors += "Breed cannot be empty!\n";
    }
    if (d.get_name().empty()) {
        errors += "Name cannot be empty!\n";
    }
    if (d.get_photograph().empty()) {
        errors += "Photograph link cannot be empty!\n";
    }
    if (d.get_age() < 0) {
        errors += "Age cannot be negative!\n";
    }
    if (!d.get_photograph().empty()) {
        if (d.get_photograph().find("http") != 0 && d.get_photograph().find("www") != 0) {
            errors += "Photograph must be a valid link starting with 'http' or 'www'!\n";
        }
    }

    if (!errors.empty()) {
        throw ValidationException(errors);
    }

}
