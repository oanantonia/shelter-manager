#pragma once
#include "AdoptionList.h"

class CSVAdoptionList : public AdoptionList {
public:
    CSVAdoptionList(const std::string& filename);
    void write_to_file() override;
    void clear() override;
};
