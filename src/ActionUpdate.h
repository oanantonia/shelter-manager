#pragma once
#include "Action.h"

class ActionUpdate : public Action
{
private:
	IRepository& repo;
	Dog old_dog;
	Dog new_dog;

public:
	ActionUpdate(IRepository& repo, Dog& old_dog, Dog& new_dog);
	void executeUndo() override;
	void executeRedo() override;
};

