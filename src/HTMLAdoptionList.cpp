#include "HTMLAdoptionList.h"
#include <fstream>

using namespace std;

HTMLAdoptionList::HTMLAdoptionList(const std::string& filename): AdoptionList(filename)
{}

void HTMLAdoptionList::write_to_file()
{
    ofstream f(this->filename);
    if (!f.is_open()) return;

    f << "<!DOCTYPE html>\n<html>\n<head>\n<title>Adoption List</title>\n</head>\n<body>\n";
    f << "<table border=\"1\">\n";
    f << "<tr><td>Breed</td><td>Name</td><td>Age</td><td>Photograph</td></tr>\n";

    for (const auto& dog : this->adoption_list) {
        f << "<tr>"
            << "<td>" << dog.get_breed() << "</td>"
            << "<td>" << dog.get_name() << "</td>"
            << "<td>" << dog.get_age() << "</td>"
            << "<td><a href=\"" << dog.get_photograph() << "\">Link</a></td>"
            << "</tr>\n";
    }

    f << "</table>\n</body>\n</html>\n";
    f.close();
}

void HTMLAdoptionList::clear()
{
    this->adoption_list.clear();

    std::ofstream file(this->filename);
    file << "<!DOCTYPE html>\n<html>\n<head>\n<title>Adoption List</title>\n</head>\n<body>\n";
    file << "<table border=\"1\">\n";
    file << "<tr>\n<td>Name</td>\n<td>Breed</td>\n<td>Age</td>\n<td>Photograph</td>\n</tr>\n";
    file << "</table>\n</body>\n</html>\n";
    file.close();
}

