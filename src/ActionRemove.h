#pragma once
#include "Action.h"

class ActionRemove : public Action
{
private:
	IRepository& repo;
	Dog dog;

public:
	ActionRemove(IRepository& repo, Dog& dog);
	void executeUndo() override;
	void executeRedo() override;
};

