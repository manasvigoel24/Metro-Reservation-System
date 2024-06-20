///Metro Reservation System

/*
    MENU:-
    1) ADMIN:
        (i) Add Train - Add train number(unique), train route. (Give Price according to total distance)
        (ii) Edit Train - Train Number, Train Route
        (iii) Delete Train.
        (iv) Search trains between 2 stations

    2) USER:
        (i) Search Train using (From - Destination)
        (ii) Book Tickets - number of tickets, price of the ticket.
              (Get price function to be used for pricing using total distance)
*/

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <windows.h>
#include <ctime>
using namespace std;

string adminPassword = "admin";

class Train
{
private:
    string trainNo;
    map<string, map<string, int>> stations;
    map<string, map<string, int>> adjacencyMatrix;
    map<string, map<string, int>> distances;

public:
    Train() {}
    Train(string t_no, map<string, map<string, int>> stops, map<string, map<string, int>> adj)
    {
        trainNo = t_no;
        stations = stops;
        adjacencyMatrix = adj;
    }
    void setTrainNo(string t_no)
    {
        trainNo = t_no;
    }
    void setStations(map<string, map<string, int>> stops)
    {
        stations = stops;
    }

    string getTrainNo()
    {
        return trainNo;
    }
    map<string, map<string, int>> getStations()
    {
        return stations;
    }
    const map<string, map<string, int>>& getAdjacencyMatrix() const
    {
        return adjacencyMatrix;
    }
    // Method to get distances (const)
    map<string, map<string, int>>& getDistances()
    {
        return distances;
    }

};

class MetroSystem
{
private:
    const int INF = INT_MAX;
    vector<Train> trains;

public:
    MetroSystem() {}

    void floydWarshall(Train& train)
    {
        // Get adjacency matrix for the train
        const auto& adjacencyMatrix = train.getAdjacencyMatrix();

        // Initialize distances matrix for this train
        auto& distances = train.getDistances();

        // Initialize adjacency matrix
        for (auto &[fromSt, destinations] : adjacencyMatrix)
        {
            for (auto &[toSt, distance] : destinations)
            {
                distances[fromSt][toSt] = distance;
            }
        }

        // Apply Floyd-Warshall algorithm
        for (auto &[midSt, _] : adjacencyMatrix)
        {
            for (auto &[fromSt, _] : adjacencyMatrix)
            {
                for (auto &[toSt, _] : adjacencyMatrix)
                {
                    if (distances[fromSt][midSt] != INF && distances[midSt][toSt] != INF && distances[fromSt][midSt] + distances[midSt][toSt] < distances[fromSt][toSt])
                    {
                        distances[fromSt][toSt] = distances[fromSt][midSt] + distances[midSt][toSt];
                    }
                }
            }
        }
    }

    void printAllTrains()
    {
        if (trains.empty())
        {
            cout << "No trains available." << endl;
            return;
        }

        cout << "List of all trains:" << endl;
        for (auto& train : trains)
        {
            cout << "Train Number: " << train.getTrainNo() << endl;
            const auto& stops = train.getStations();
            cout << "Route:" << endl;
            for (const auto& stop : stops)
            {
                cout << "    " << stop.first << " - ";
                for (const auto& connection : stop.second)
                {
                    cout << connection.first << " (" << connection.second << " km) ";
                }
                cout << endl;
            }
            cout << endl;
        }
    }

    void addTrain()
    {
        // Add Train
        string trainNumber;
        cout << "\t\tEnter train number (unique): ";
        cin >> trainNumber;

        map<string, map<string, int>> stops;

        string fromSt = "";
        string toSt = "";
        int distance = 0;

        cout << "\n\t\tEnter train route:- " << endl;

        while(fromSt != "end")
        {
            cout << "\t\tEnter Source Station('end' to stop): ";
            cin >> fromSt;

            if(fromSt == "end")
            {
                break;
            }

            cout << "\t\tEnter Destination Station: ";
            cin >> toSt;

            cout << "\t\tEnter the distance between these stations: ";
            cin >> distance;

            stops[fromSt][toSt] = distance;
            cout << endl;

        }
        Train t(trainNumber, stops, stops);

        trains.push_back(t);

        Sleep(500);
        cout << "\n*****************************************************************************" << endl;
        Sleep(500);
        cout << "\t\tTrain Added Successfully" << endl;
        Sleep(500);
        cout << "*****************************************************************************" << endl;
        Sleep(500);

        floydWarshall(t);
    }

    void editTrain()
    {
        printAllTrains();
        cout << endl;

        string train_no_to_edit;
        Sleep(500);
        cout << "*****************************************************************************" << endl;
        Sleep(500);
        cout << "\t\tEnter Train Number to Find Train to Edit: ";
        cin >> train_no_to_edit;
        Sleep(500);
        cout << "*****************************************************************************" << endl;
        Sleep(500);

        for (auto &train : trains)
        {
            if (train.getTrainNo() == train_no_to_edit)
            {
                int edit_train_choice = 0;
                while (edit_train_choice != 3)
                {
                    Sleep(500);
                    cout << "*****************************************************************************" << endl;
                    Sleep(500);
                    cout << "\n\t\tWelcome to Edit Train Menu: " << endl;
                    Sleep(500);
                    cout << "*****************************************************************************" << endl;
                    Sleep(500);
                    cout << "\t\t\t1. Edit Train Number." << endl;
                    cout << "\t\t\t2. Edit Train Route." << endl;
                    cout << "\t\t\t3. Exit Menu." << endl;
                    Sleep(500);
                    cout << "*****************************************************************************" << endl;
                    Sleep(500);
                    cout << "\t\t\tEnter your choice: ";
                    cin >> edit_train_choice;
                    Sleep(500);
                    cout << "*****************************************************************************" << endl;
                    Sleep(500);

                    switch (edit_train_choice)
                    {
                    case 1:
                    {
                        string new_train_no;
                        cout << "\n\t\t\tEnter new train number: ";
                        cin >> new_train_no;
                        train.setTrainNo(new_train_no);
                        cout << "\n\t\tTrain number updated successfully." << endl;
                        break;
                    }
                    case 2:
                    {
                        map<string, map<string, int>> stops = train.getStations();
                        stops.clear();

                        string fromSt = "";
                        string toSt = "";
                        int distance = 0;

                        cout << "\n\t\tEnter updated train route (station name, distance from previous station): " << endl;
                        while (fromSt != "end")
                        {
                            cout << "\t\tEnter Source Station ('end' to stop): ";
                            cin >> fromSt;

                            if (fromSt == "end")
                            {
                                break;
                            }

                            cout << "\t\tEnter Destination Station: ";
                            cin >> toSt;

                            cout << "\t\tEnter the distance between these stations: ";
                            cin >> distance;

                            stops[fromSt][toSt] = distance;
                        }

                        train.setStations(stops);
                        cout << "\t\tTrain route updated successfully." << endl;
                        break;
                    }
                    case 3:
                    {
                        Sleep(500);
                        cout << "*****************************************************************************" << endl;
                        Sleep(500);
                        cout << "\n\t\tExiting Edit Train Menu." << endl;
                        Sleep(500);
                        cout << "*****************************************************************************" << endl;
                        Sleep(500);
                        break;
                    }
                    default:
                    {
                        cout << "\n\t\tInvalid choice. Please enter a valid option." << endl;
                    }
                    }
                }
                break;
            }
        }
    }

    void deleteTrain()
    {
        printAllTrains();
        cout << endl;

        string train_no_to_delete;
        cout << "\t\tEnter Train Number to Delete: ";
        cin >> train_no_to_delete;

        for (auto it = trains.begin(); it != trains.end(); ++it)
        {
            if ((*it).getTrainNo() == train_no_to_delete)
            {
                it = trains.erase(it);
                cout << "\n\tTrain " << train_no_to_delete << " deleted successfully." << endl;
                return;
            }
        }
        cout << "\n\tTrain with number " << train_no_to_delete << " not found." << endl;
    }

    void searchTrainWithMinDistance()
    {
        string source_to_search;
        string destination_to_search;

        cout << "\t\tEnter the Source Station: ";
        cin >> source_to_search;

        cout << "\t\tEnter the Destination Station: ";
        cin >> destination_to_search;

        int minDistance = INF;
        string minTrainNo;

        bool sourceFound = false;
        bool destinationFound = false;

        for (auto &train : trains)
        {
            const auto &stops = train.getStations();

            // Check if source and destination stations exist in the current train
            if (stops.find(source_to_search) != stops.end() && stops.find(destination_to_search) != stops.end())
            {
                sourceFound = true;
                destinationFound = true;

                // Calculate total distance of the journey
                int totalDistance = 0;
                string currentStation = source_to_search;
                while (currentStation != destination_to_search)
                {
                    string nextStation = stops.at(currentStation).begin()->first; // Get the first station connected to the current station
                    int distance = stops.at(currentStation).at(nextStation); // Get distance between current and next station
                    totalDistance += distance;
                    currentStation = nextStation;
                }

                if (totalDistance < minDistance)
                {
                    minDistance = totalDistance;
                    minTrainNo = train.getTrainNo();
                }
                cout << "\n\tTrain " << train.getTrainNo() << " has the distance (" << totalDistance << ")km between ";
                cout << source_to_search << " and " << destination_to_search << endl;
            }
        }

        if (!sourceFound)
        {
            cout << "\tSource station '" << source_to_search << "' not found." << endl;
        }

        if (!destinationFound)
        {
            cout << "\tDestination station '" << destination_to_search << "' not found." << endl;
        }

        if (!sourceFound || !destinationFound)
        {
            cout << "\tPlease enter valid station names." << endl;
            return;
        }

        if (minDistance == INF)
        {
            cout << "\tNo train found between " << source_to_search << " and " << destination_to_search << endl;
        }
        else
        {
            cout << "\tTrain " << minTrainNo << " has the minimum distance (" << minDistance << ") between "
                 << source_to_search << " and " << destination_to_search << endl;
        }
    }

    double getPrice(int distance)
    {
        // Calculate price based on distance
        double pricePerKm = 0.1;
        double price = distance * pricePerKm;
        return price;
    }

    void bookTickets()
    {
        string source_to_search;
        string destination_to_search;

        cout << "\t\tEnter the Source Station: ";
        cin >> source_to_search;

        cout << "\t\tEnter the Destination Station: ";
        cin >> destination_to_search;

        int minDistance = INF;
        string minTrainNo;

        bool sourceFound = false;
        bool destinationFound = false;

        for (auto &train : trains)
        {
            const auto &stops = train.getStations();

            // Check if source and destination stations exist in the current train
            if (stops.find(source_to_search) != stops.end() && stops.find(destination_to_search) != stops.end())
            {
                sourceFound = true;
                destinationFound = true;

                // Calculate total distance of the journey
                int totalDistance = 0;
                string currentStation = source_to_search;
                while (currentStation != destination_to_search)
                {
                    string nextStation = stops.at(currentStation).begin()->first; // Get the first station connected to the current station
                    int distance = stops.at(currentStation).at(nextStation); // Get distance between current and next station
                    totalDistance += distance;
                    currentStation = nextStation;
                }

                if (totalDistance < minDistance)
                {
                    minDistance = totalDistance;
                    minTrainNo = train.getTrainNo();
                }

                cout << "\nTrain " << train.getTrainNo() << " has the distance (" << totalDistance << ")km between ";
                cout << source_to_search << " and " << destination_to_search << endl;
            }
        }

        if (minDistance == INF)
        {
            Sleep(500);
            cout << "*****************************************************************************" << endl;
            Sleep(500);
            cout << "\tNo train found between " << source_to_search << " and " << destination_to_search << endl;
            Sleep(500);
            cout << "*****************************************************************************" << endl;
            Sleep(500);
            cout << "\tReturning Back to Previous Menu. " << endl;
            Sleep(500);
            cout << "*****************************************************************************" << endl;
            Sleep(1000);
        }
        else
        {
            cout << "\nTrain " << minTrainNo << " has the minimum distance (" << minDistance << ") between ";
            cout << source_to_search << " and " << destination_to_search << endl;

            int no_of_tickets;
            cout << "\tEnter number of Tickets to Book: ";
            cin >> no_of_tickets;

            double price = getPrice(minDistance);

            cout << "\n\t1 Ticket Price: " << price << endl << endl;
            cout << "\t" << no_of_tickets << " Tickets Price: " << no_of_tickets*price << endl;

            string confirm;
            cout << "\n\t\tConfirm your Booking? (y/n): ";
            cin >> confirm;

            if(confirm == "y" || confirm == "Y")
            {
                Sleep(500);
                cout << "*****************************************************************************" << endl;
                Sleep(500);
                cout << "\n\t\tYour Tickets are being Confirmed! " << endl;
                Sleep(500);
                cout << "*****************************************************************************" << endl;
                Sleep(500);
                cout << "\n\t\tKindly wait for your Metro till it arrives! " << endl;
                Sleep(500);
                cout << "*****************************************************************************" << endl;
                Sleep(1000);
            }
            else
            {
                Sleep(500);
                cout << "*****************************************************************************" << endl;
                Sleep(500);
                cout << "\t\tThank You for your Precious Time! " << endl;
                Sleep(500);
                cout << "*****************************************************************************" << endl;
                Sleep(500);
                cout << "\t\tReturning Back to Previous Menu! " << endl;
                Sleep(500);
                cout << "*****************************************************************************" << endl;
                Sleep(1000);
            }
        }
        return;
    }

    void adminMenu()
    {
        int admin_menu_choice = 0;

        while(admin_menu_choice != 6)
        {
            Sleep(500);
            cout << "\n*****************************************************************************" << endl;
            Sleep(500);
            cout << "\n\t\tWelcome to Admin Menu: " << endl;
            Sleep(500);
            cout << "\n*****************************************************************************" << endl;
            Sleep(500);
            cout << "\t\t\t1. Add New Metro. " << endl;
            cout << "\t\t\t2. Edit Metro Details. " << endl;
            cout << "\t\t\t3. Delete Metro. " << endl;
            cout << "\t\t\t4. Search Metro between Stations. " << endl;
            cout << "\t\t\t5. Print All Trains." << endl;
            cout << "\t\t\t6. Exit Menu. " << endl;
            Sleep(500);
            cout << "*****************************************************************************" << endl;
            Sleep(500);
            cout << "\t\t\tEnter your choice: ";

            cin >> admin_menu_choice;

            switch(admin_menu_choice)
            {
            case 1:
            {
                system("CLS");
                Sleep(500);
                cout << "*****************************************************************************" << endl;
                Sleep(500);
                addTrain();
                Sleep(500);
                cout << "*****************************************************************************" << endl;
                Sleep(500);
                break;
            }
            case 2:
            {
                system("CLS");
                Sleep(500);
                cout << "*****************************************************************************" << endl;
                Sleep(500);
                editTrain();
                Sleep(500);
                cout << "*****************************************************************************" << endl;
                Sleep(500);
                break;
            }
            case 3:
            {
                system("CLS");
                Sleep(500);
                cout << "*****************************************************************************" << endl;
                Sleep(500);
                deleteTrain();
                Sleep(500);
                cout << "*****************************************************************************" << endl;
                Sleep(500);
                break;
            }
            case 4:
            {
                system("CLS");
                Sleep(500);
                cout << "*****************************************************************************" << endl;
                Sleep(500);
                searchTrainWithMinDistance();
                Sleep(500);
                cout << "*****************************************************************************" << endl;
                Sleep(500);
                break;
            }
            case 5:
            {
                system("CLS");
                Sleep(500);
                cout << "*****************************************************************************" << endl;
                Sleep(500);
                printAllTrains();
                Sleep(500);
                cout << "*****************************************************************************" << endl;
                Sleep(500);
                break;
            }
            case 6:
            {
                Sleep(500);
                cout << "*****************************************************************************" << endl;
                Sleep(500);
                cout << "\t\tExiting Edit Train Menu." << endl;
                Sleep(500);
                cout << "*****************************************************************************" << endl;
                Sleep(500);
                break;
            }
            default:
                cout << "\t\tInvalid choice. Please enter a valid option." << endl;
            }
        }
    }

    void userMenu()
    {
        int user_menu_choice = 0;

        while(user_menu_choice != 4)
        {
            Sleep(500);
            cout << "\n*****************************************************************************" << endl;
            Sleep(500);
            cout << "\n\t\t\tWelcome to User Menu: " << endl;
            Sleep(500);
            cout << "\n*****************************************************************************" << endl;
            Sleep(500);
            cout << "\t\t\t1. Search Metro Between Stations. " << endl;
            cout << "\t\t\t2. Book Tickets. " << endl;
            cout << "\t\t\t3. Print All Trains. " << endl;
            cout << "\t\t\t4. Exit Menu. " << endl;
            Sleep(500);
            cout << "*****************************************************************************" << endl;
            Sleep(500);
            cout << "\t\t\tEnter your choice: ";
            cin >> user_menu_choice;
            Sleep(500);

            switch(user_menu_choice)
            {
            case 1:
            {
                system("CLS");
                cout << "\n*****************************************************************************" << endl;
                Sleep(500);
                searchTrainWithMinDistance();
                Sleep(500);
                cout << "*****************************************************************************" << endl;
                Sleep(500);
                break;
            }
            case 2:
            {
                system("CLS");
                cout << "\n*****************************************************************************" << endl;
                Sleep(500);
                bookTickets();
                Sleep(500);
                cout << "*****************************************************************************" << endl;
                Sleep(500);
                break;
            }
            case 3:
            {
                system("CLS");
                Sleep(500);
                cout << "*****************************************************************************" << endl;
                Sleep(500);
                printAllTrains();
                Sleep(500);
                cout << "*****************************************************************************" << endl;
                Sleep(500);
                break;
            }
            case 4:
            {
                system("CLS");
                Sleep(500);
                cout << "\n*****************************************************************************" << endl;
                Sleep(500);
                cout << "\t\t\tExiting Edit Train Menu." << endl;
                Sleep(500);
                cout << "*****************************************************************************" << endl;
                Sleep(1000);
                system("CLS");
                break;
            }
            default:
            {
                system("CLS");
                Sleep(500);
                cout << "\n*****************************************************************************" << endl;
                Sleep(500);
                cout << "\t\tInvalid choice. Please enter a valid option." << endl;
                Sleep(500);
                cout << "*****************************************************************************" << endl;
                Sleep(500);
            }
            }
        }
    }
};

int main()
{
    system("color E0");
    MetroSystem Msystem;

    int main_choice = 0;

    while (main_choice != 3)
    {
        Sleep(500);
        cout << "\n*****************************************************************************" << endl;
        Sleep(500);
        cout << "\n\t\tWELCOME TO METRO TICKET RESERVATION SYSTEM!" << endl;
        Sleep(500);
        cout << "\n*****************************************************************************" << endl;
        Sleep(500);
        cout << "\t\t\tMain Menu: " << endl;
        cout << "\t\t\t1. Admin Menu" << endl;
        cout << "\t\t\t2. User Menu" << endl;
        cout << "\t\t\t3. Exit" << endl;
        Sleep(500);
        cout << "*****************************************************************************" << endl;
        Sleep(500);
        cout << "\t\t\tEnter Main Choice: ";
        cin >> main_choice;

        switch (main_choice)
        {
        case 1:
        {
            string admin_password;
            cout << "\t\t\tEnter Admin Password: ";
            cin >> admin_password;

            if(admin_password == adminPassword)
            {
                system("CLS");
                Sleep(500);
                cout << "*****************************************************************************" << endl;
                Sleep(500);
                cout << "\n\t\tCorrect Password..." << endl;
                Sleep(500);
                cout << "\n*****************************************************************************" << endl;
                Sleep(500);
                cout << "\n\t\tLogging In..." << endl;
                Sleep(500);
                cout << "\n*****************************************************************************" << endl;
                Sleep(1000);
                system("CLS");
                Msystem.adminMenu();
                system("CLS");
            }
            else
            {
                system("CLS");
                Sleep(500);
                cout << "*****************************************************************************" << endl;
                Sleep(500);
                cout << "\n\t\tIncorrect Password!!!" << endl;
                Sleep(500);
                cout << "*****************************************************************************" << endl;
                Sleep(500);
                cout << "\n\t\tTrying Again!!!" << endl;
                Sleep(1000);
                system("CLS");
            }
            break;
        }
        case 2:
        {
            system("CLS");
            Msystem.userMenu();
            system("CLS");
            break;
        }
        case 3:
        {

            Sleep(500);
            cout << "\n*****************************************************************************" << endl;
            Sleep(500);
            cout << "\t\t\tExiting the Portal!" << endl;
            Sleep(500);
            cout << "*****************************************************************************" << endl;
            Sleep(500);
            cout << "\t\t\tThank You for visiting!" << endl;
            Sleep(500);
            cout << "*****************************************************************************" << endl;
            Sleep(1000);
            break;
        }
        default:
        {
            Sleep(500);
            cout << "\n\tWrong Input! Kindly enter the values between 1 to 4!" << endl;
            Sleep(1000);
        }
        }
    }
    return 0;
}
