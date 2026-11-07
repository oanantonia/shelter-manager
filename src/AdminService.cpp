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

	this->undo_stack.push(std::make_unique<ActionAdd>(this->repo, new_dog));
}

void AdminService::delete_dog(const string& breed, const string& name)
{
	int index = this->repo.find_dog(breed, name);
	Dog dog_to_remove = this->repo.get_dog(index); 
	this->repo.delete_dog(dog_to_remove);

	this->undo_stack.push(std::make_unique<ActionRemove>(this->repo, dog_to_remove));
}

void AdminService::update_dog_age(const string& breed, const string& name, int new_age)
{
	int index = this->repo.find_dog(breed, name);
	Dog old_dog = this->repo.get_dog(index);
	Dog new_dog = Dog(breed, name, new_age, old_dog.get_photograph());
	DogValidator::validate(new_dog);
	this->repo.set_dog(old_dog, new_dog);

	this->undo_stack.push(std::make_unique<ActionUpdate>(this->repo, old_dog, new_dog));
}

void AdminService::update_dog_photograph(const std::string& breed, const std::string& name, 
	const std::string& new_photograph)
{
	int index = this->repo.find_dog(breed, name);
	Dog old_dog = this->repo.get_dog(index);
	Dog new_dog = Dog(breed, name, old_dog.get_age(), new_photograph);
	DogValidator::validate(new_dog);
	this->repo.set_dog(old_dog, new_dog);

	this->undo_stack.push(std::make_unique<ActionUpdate>(this->repo, old_dog, new_dog));
}

const std::vector<Dog> AdminService::get_dogs() const
{
	return this->repo.get_dogs();
}

void AdminService::undo()
{
	if (this->undo_stack.empty()) {
		throw ServiceException("Undo stack is empty!");
	}
	unique_ptr<Action> a = move(this->undo_stack.top());
	this->undo_stack.pop();
	a->executeUndo();
	this->redo_stack.push(move(a));
}

void AdminService::redo()
{
	if (this->redo_stack.empty()) {
		throw ServiceException("Redo stack is empty!");
	}
	unique_ptr<Action> a = move(this->redo_stack.top());
	this->redo_stack.pop();
	a->executeRedo();
	this->undo_stack.push(move(a));
}

AdminService::~AdminService()
{}
