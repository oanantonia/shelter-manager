#pragma once
#include "AdoptionList.h"

class HTMLAdoptionList: public AdoptionList {
public:
	HTMLAdoptionList(const std::string& filename);
	void write_to_file() override;
	void clear() override;
};

