#include "Menu.h"
#include <iostream>
#include <limits>
#include <unistd.h>

void Menu::showDataSelectionMenu() {
    cout << "_________________________________________________" << endl;
    cout << "Welcome to the railway network management system!" << endl;
    cout << "Please select an option:" << endl;
    cout << "1 - Load the entire network" << endl;
    cout << "2 - Load a subset of the network" << endl;

    int option;
    cin >> option;
    if (cin.fail()) {
        cout << "Invalid input" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        showDataSelectionMenu();
    }
    else {
        switch (option) {
            case 1:
                database.loadWithoutFilters();
                showMainMenu();
                break;
            case 2:
                showSubsetMenu();
                break;
            default:
                cout << "Invalid option" << endl;
                showDataSelectionMenu();
        }
    }
}

void Menu::showSubsetMenu() {
    set<string> stations;
    set<string> lines;

    cout << "_________________________________________________" << endl;
    cout << "Please select an option:" << endl;
    cout << "1 - Filter by lines" << endl;
    cout << "2 - Filter by railway stations" << endl;

    int option = getIntFromUser();

    switch (option) {
        case 1:
            lines = getStringsFromUser();
            break;
        case 2:
            stations = getStringsFromUser();
            break;
        default:
            cout << "Invalid option" << endl;
            break;
    }

    database.loadWithFilters(stations, lines);
    showMainMenu();
}

void Menu::showMainMenu(){

    while (true){
        cout << "_________________________________________________" << endl;
        cout << "Please select an option:" << endl;
        cout << "1 - See information about a single station" << endl;
        cout << "2 - See information about two stations" << endl;
        cout << "3 - See information about the entire network" << endl;
        cout << "4 - Return to data selection menu" << endl;
        cout << "5 - exit" << endl;

        int option = getIntFromUser();
        switch (option) {
            case 1:
                showStationInfoMenu();
                waitForInput();
                break;
            case 2:
                showTwoStationsInfoMenu();
                waitForInput();
                break;
            case 3:
                showNetworkInfoMenu();
                waitForInput();
                break;
            case 4:
                showDataSelectionMenu();
                waitForInput();
                break;
            case 5:
                return;
            default:
                cout << "Invalid option" << endl;
                showMainMenu();
        }
    }
}

set<string> Menu::getStringsFromUser() {
    set<string> strings;
    string input;
    bool firstTime = true;
    cout << "Please enter the strings, one per line. Enter 0 to finish." << endl;

    while (true) {
        getline(cin, input);
        if (input == "0")
            return strings;
        else if (input.empty() && !firstTime) {
            cout << "Invalid input" << endl;
        }
        else {
            strings.insert(input);
        }
        firstTime = false;
    }
}

string Menu::getStringFromUser() {
    string input = "";
    while (input.empty()) {
        getline(cin, input);
    }

    return input;
}

int Menu::getIntFromUser() {
    int input;
    cin >> input;
    if (cin.fail()) {
        cout << "Invalid input" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return getIntFromUser();
    }
    return input;
}

void Menu::waitForInput() {
    usleep(800000);
    string q;
    cout << endl << "Insert any key to continue: ";
    cin >> q;
    cout << endl;
}

void Menu::showStationInfoMenu() {
    cout << "_________________________________________________" << endl;
    cout << "Please enter the name of the station:" << endl;
    string stationName = getStringFromUser();

    Station *station = database.getStation(stationName);
    if (station == nullptr) {
        cout << "Station not found" << endl;
        return showStationInfoMenu();
    }
    cout << "_________________________________________________" << endl;
    cout<< "Please select an option:" << endl;
    cout<< "1 - See the maximum number of trains that can arrive to the station" << endl;
    cout<< "2 - See more information about the station" << endl;
    cout<< "3 - Return to main menu" << endl;

    int option = getIntFromUser();
    int num;

    switch(option){
        case 1:
            num = database.getMaxTrainsStation(station->getName());
            cout << "_________________________________________________" << endl;
            cout << "The maximum number of trains that can arrive to the station is: " << num << endl;
            break;
        case 2:
            cout << "_________________________________________________" << endl;
            cout << "Station name: " << station->getName() << endl;
            cout << "District: " << station->getDistrict() << endl;
            cout << "Municipality: " << station->getMunicipality() << endl;
            cout << "Township: " << station->getTownship() << endl;
            cout << "Line: " << station->getLine() << endl;
            cout << "_________________________________________________" << endl;
            break;
        case 3:
            showMainMenu();
            break;
        default:
            cout << "Invalid option" << endl;
            showStationInfoMenu();
    }
}

void Menu::showTwoStationsInfoMenu() {
    cout << "_________________________________________________" << endl;
    cout << "Please enter the name of the first station:" << endl;
    string stationName1=getStringFromUser();
    Station* station1 = database.getStation(stationName1);
    if (station1 == nullptr) {
        cout << "Station not found" << endl;
        showTwoStationsInfoMenu();
    }

    cout << "Please enter the name of the second station:" << endl;
    string stationName2=getStringFromUser();
    Station* station2 = database.getStation(stationName2);
    if (station2 == nullptr) {
        cout << "Station not found" << endl;
        showTwoStationsInfoMenu();
    }

    cout << "_________________________________________________" << endl;
    cout<< "Please select an option:" << endl;
    cout<< "1 - Maximum number of trains that can travel between the two" << endl;
    cout<< "2 - Maximum number of trains that can travel between the two taking cost into account" << endl;
    cout<< "3 - Return to main menu" << endl;

    int option = getIntFromUser();
    int flow;
    switch(option){
        case 1:
            flow = database.getMaxFlowBetweenStations(stationName1, stationName2);
            cout << "_________________________________________________" << endl;
            cout << "Station 1: " << stationName1 << endl;
            cout << "Station 2: " << stationName2 << endl;
            cout << "The maximum number of trains that can pass between the two stations is: " << flow << endl;
            break;
        case 2:
            cout << "This feature isn't yet implemented" << endl;
            break;
        case 3:
            showMainMenu();
            break;
        default:
            cout << "Invalid option" << endl;
            showTwoStationsInfoMenu();
    }
}

void Menu::showNetworkInfoMenu() {
    cout << "_________________________________________________" << endl;
    cout<< "Please select an option:" << endl;
    cout<< "1 - Pairs of stations with the maximum number of trains that can travel between them" << endl;
    cout<< "2 - Top-k municipalities and districts" << endl;
    cout<< "3 - Return to main menu" << endl;

    int option = getIntFromUser();
    switch(option){
        case 1:
            cout << "This feature isn't yet implemented" << endl;
            break;
        case 2:
            cout << "This feature isn't yet implemented" << endl;
            break;
        case 3:
            showMainMenu();
            break;
        default:
            cout << "Invalid option" << endl;
            showNetworkInfoMenu();
    }
}
