#include "ActionRemove.h"

ActionRemove::ActionRemove(IRepository& repo, Dog& dog) : repo{ repo }, dog{ dog }
{}

void ActionRemove::executeUndo()
{
	this->repo.add_dog(this->dog);
}

void ActionRemove::executeRedo()
{
	this->repo.delete_dog(this->dog);
}
