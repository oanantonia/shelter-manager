#include "CSVAdoptionList.h"
#include <fstream>

using namespace std;

CSVAdoptionList::CSVAdoptionList(const std::string& filename): AdoptionList(filename)
{}

void CSVAdoptionList::write_to_file()
{
    std::ofstream f(this->filename);
    if (!f.is_open()) return;

    for (const auto& dog : this->adoption_list) {
        f << dog.get_breed() << "," << dog.get_name() << "," << dog.get_age() << ","
            << dog.get_photograph() << "\n";
    }
    f.close();
}

void CSVAdoptionList::clear()
{
    this->adoption_list.clear();

    std::ofstream file(this->filename);
    file.close();
}

