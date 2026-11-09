#include "AdminService.h"
#include "ActionAdd.h"
#include "ActionRemove.h"
#include "ActionUpdate.h"
#include "DogValidator.h"
#include "Exceptions.h"

using namespace std;

AdminService::AdminService(IRepository& repo): repo{ repo }
{}

void AdminService::add_dog(const string& breed, const string& name, int age, const string& photograph)
{
	Dog new_dog = Dog(breed, name, age, photograph);
	DogValidator::validate(new_dog);
	this->repo.add_dog(new_dog);

	this->record(std::make_unique<ActionAdd>(this->repo, new_dog));
}

void AdminService::delete_dog(const string& breed, const string& name)
{
	int index = this->repo.find_dog(breed, name);
	Dog dog_to_remove = this->repo.get_dog(index); 
	this->repo.delete_dog(dog_to_remove);

	this->record(std::make_unique<ActionRemove>(this->repo, dog_to_remove));
}

void AdminService::update_dog_age(const string& breed, const string& name, int new_age)
{
	int index = this->repo.find_dog(breed, name);
	Dog old_dog = this->repo.get_dog(index);
	Dog new_dog = Dog(breed, name, new_age, old_dog.get_photograph());
	DogValidator::validate(new_dog);
	this->repo.set_dog(old_dog, new_dog);

	this->record(std::make_unique<ActionUpdate>(this->repo, old_dog, new_dog));
}

void AdminService::update_dog_photograph(const std::string& breed, const std::string& name, 
	const std::string& new_photograph)
{
	int index = this->repo.find_dog(breed, name);
	Dog old_dog = this->repo.get_dog(index);
	Dog new_dog = Dog(breed, name, old_dog.get_age(), new_photograph);
	DogValidator::validate(new_dog);
	this->repo.set_dog(old_dog, new_dog);

	this->record(std::make_unique<ActionUpdate>(this->repo, old_dog, new_dog));
}

const std::vector<Dog> AdminService::get_dogs() const
{
	return this->repo.get_dogs();
}

void AdminService::record(std::unique_ptr<Action> action)
{
	this->undo_stack.push(std::move(action));
	this->redo_stack = {};	// a new change makes the old redo history invalid
}

void AdminService::undo()
{
	if (this->undo_stack.empty()) {
		throw ServiceException("Undo stack is empty!");
	}
	this->undo_stack.top()->executeUndo();	// if this throws, the action stays on the stack
	this->redo_stack.push(move(this->undo_stack.top()));
	this->undo_stack.pop();
}

void AdminService::redo()
{
	if (this->redo_stack.empty()) {
		throw ServiceException("Redo stack is empty!");
	}
	this->redo_stack.top()->executeRedo();	// if this throws, the action stays on the stack
	this->undo_stack.push(move(this->redo_stack.top()));
	this->redo_stack.pop();
}

AdminService::~AdminService()
{}
