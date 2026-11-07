#include "ActionUpdate.h"

ActionUpdate::ActionUpdate(IRepository& repo, Dog& old_dog, Dog& new_dog) : repo{ repo }, old_dog{ old_dog }, new_dog{ new_dog }
{}

void ActionUpdate::executeUndo()
{
	this->repo.set_dog(this->new_dog, this->old_dog);
}

void ActionUpdate::executeRedo()
{
	this->repo.set_dog(this->old_dog, this->new_dog);
}
