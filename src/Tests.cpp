#include "Tests.h"
#include "Dog.h"
#include "MemoryRepository.h"
#include "AdminService.h"
#include "UserService.h"
#include <cassert>
#include <iostream>

void Tests::test_dog() {
    Dog d1("b1", "n1", 1, "l1");
    assert(d1.get_breed() == "b1");
    assert(d1.get_name() == "n1");
    assert(d1.get_age() == 1);
    assert(d1.get_photograph() == "l1");

    Dog empty;
    assert(empty.get_breed() == "");
    assert(empty.get_age() == 0);

    d1.set_age(5);
    assert(d1.get_age() == 5);
    d1.set_photograph("newl");
    assert(d1.get_photograph() == "newl");

    Dog d2("b1", "n1", 5, "newl");
    Dog d3("b2", "n2", 1, "l2");
    assert(d1 == d2);
}

void Tests::test_repository() {
    MemoryRepository repo;
    Dog d1("b1", "n1", 1, "l1");
    Dog d2("b2", "n2", 2, "l2");

    repo.add_dog(d1);
    assert(repo.get_dogs().size() == 1);

    try {
        repo.add_dog(d1);
    }
    catch (const std::exception& e) {
        assert(std::string(e.what()) == "This dog is already in the shelter!");
    }

    assert(repo.get_dog(0) == d1);
    assert(repo.find_dog("b1", "n1") == 0);
    assert(repo.find_dog("a", "b") == -1);

    repo.set_dog(d1, d2);
    assert(repo.get_dog(0) == d2);

    repo.delete_dog(d2);
    assert(repo.get_dogs().size() == 0);

    try {
        repo.delete_dog(d2);
    }
    catch (const std::exception& e) {
        assert(std::string(e.what()) == "This dog is not in the shelter!");
    }

    try {
        repo.set_dog(d2, d1);
    }
    catch (const std::exception& e) {
        assert(std::string(e.what()) == "This dog is not in the shelter!");
    }
}

void Tests::test_admin_service() {
    MemoryRepository repo;
    AdminService service(repo);

    service.add_dog("b1", "n1", 1, "l1");
    assert(service.get_dogs().size() == 1);

    service.update_dog_age("b1", "n1", 5);
    std::vector<Dog> dogs = service.get_dogs();
    assert(dogs[0].get_age() == 5);

    service.update_dog_photograph("b1", "n1", "newl");
    dogs = service.get_dogs();
    assert(dogs[0].get_photograph() == "newl");

    service.delete_dog("b1", "n1");
    assert(service.get_dogs().size() == 0);

}

void Tests::test_user_service()
{
    MemoryRepository repo;
    AdminService srv(repo);

    srv.add_dog("b1", "n1", 1, "l1");
    srv.add_dog("b2", "n2", 2, "l2");
    srv.add_dog("b3", "n3", 3, "l3");
    srv.add_dog("b4", "n4", 4, "l4");
    srv.add_dog("b5", "n5", 5, "l5");

    UserService service(repo);

    assert(service.get_dogs().size() == 5);
    assert(service.get_adoption_list().size() == 0); 

    Dog dog_to_adopt("b2", "n2", 2, "l2");
    service.adopt_dog(dog_to_adopt);

    assert(service.get_adoption_list().size() == 1);
    assert(service.get_adoption_list()[0].get_name() == "n2");

    try {
        service.adopt_dog(dog_to_adopt);
    }
    catch (const std::exception& e) {
        assert(std::string(e.what()) == "This dog is already in your adoption list!");
    }

    std::vector<Dog> filter = service.get_filtered_dogs("", 4);
    assert(filter.size() == 3);

    std::vector<Dog> filter_specific = service.get_filtered_dogs("b4", 10);
    assert(filter_specific.size() == 1);
    assert(filter_specific[0].get_name() == "n4");

    std::vector<Dog> filter_none = service.get_filtered_dogs("x", 5);
    assert(filter_none.size() == 0);
}

void Tests::test_all() {
    test_dog();
    test_repository();
    test_admin_service();
    test_user_service();
    std::cout << "All tests passed!\n";
}