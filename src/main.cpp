#include <iostream>
#include <crtdbg.h>
#include "MemoryRepository.h"
#include "TextFileRepository.h"
#include "UI.h"
#include "Tests.h"

using namespace std;

int main() {
    //Tests test;
    //test.test_all();
    {
        TextFileRepository repo("dogs.txt");
        AdminService admin_service(repo);
        UserService user_service(repo);
        //admin_service.add_dog("Labrador", "Max", 3, "https://upload.wikimedia.org/wikipedia/commons/3/34/Labrador_on_Quantock_%282175262184%29.jpg");
        //admin_service.add_dog("German Shepherd", "Bella", 2, "https://upload.wikimedia.org/wikipedia/commons/6/6a/German_Shepherd_Dog_agility_teeter.jpg");
        //admin_service.add_dog("Golden Retriever", "Charlie", 4, "https://upload.wikimedia.org/wikipedia/commons/5/50/GoldenRetriver_agility_tunnel_wb.jpg");
        //admin_service.add_dog("French Bulldog", "Luna", 1, "https://upload.wikimedia.org/wikipedia/commons/2/2a/Franse_buldog.jpg");
        //admin_service.add_dog("Bulldog", "Cooper", 5, "https://upload.wikimedia.org/wikipedia/commons/1/11/Bulldog_adult_male.jpg");
        //admin_service.add_dog("Poodle", "Daisy", 5, "https://upload.wikimedia.org/wikipedia/commons/f/f8/Full_attention_%288067543690%29.jpg");
        //admin_service.add_dog("Beagle", "Milo", 3, "https://upload.wikimedia.org/wikipedia/commons/5/55/Beagle_600.jpg");
        //admin_service.add_dog("Rottweiler", "Rocky", 4, "https://upload.wikimedia.org/wikipedia/commons/2/26/Rottweiler_standing_facing_left.jpg");
        //admin_service.add_dog("Dachshund", "Zoe", 1, "https://upload.wikimedia.org/wikipedia/commons/2/27/Short-haired-Dachshund.jpg");
        //admin_service.add_dog("Siberian Husky", "Apollo", 6, "https://upload.wikimedia.org/wikipedia/commons/a/a3/Black-Magic-Big-Boy.jpg");
        UI ui(admin_service, user_service);
        ui.start();
        //int* n = new int[10];
    }

    _CrtDumpMemoryLeaks();
	return 0;
}