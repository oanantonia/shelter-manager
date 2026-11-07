#pragma once
#include "Action.h"

class ActionAdd : public Action
{
private:
	IRepository& repo;
	Dog dog;

public:
	ActionAdd(IRepository& repo, Dog& dog);
	void executeUndo() override;
	void executeRedo() override;
};

