#include "ActionAdd.h"

ActionAdd::ActionAdd(IRepository& repo, Dog& dog) : repo{ repo }, dog{ dog }
{}

void ActionAdd::executeUndo()
{
	this->repo.delete_dog(this->dog);
}

void ActionAdd::executeRedo()
{
	this->repo.add_dog(this->dog);
}
