#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

class Hotel;
class Floor;

class Room;

class ConferenceRoom;
class RestRoom;
class ClassRoom;

class Client;
/* ----------------------------HOTEL ----------------------------------------*/
class Hotel
{
    string name;
    map<string, Client *> clients;
    list<Floor *> floors;

public:
    // Constructor
    Hotel();
    Hotel(string name);

    // Setters
    void setName(string name);
    void addClient(Client *client);
    void addFloor(Floor *floor);

    // Getters
    string getName();
    list<Floor *> getFloors();
    map<string, Client *> getClients();

    // Method
    bool checkIn(Client *client);
    bool checkOut(Client *client);
    bool roomExists(Room *room);

    void bookRoom(Client *client, Room *room);
    void cancelBooking(Client *client, Room *room);

    // Display
    void display();

    // Destructor
    ~Hotel();
};

/* ----------------------------FLOOR ----------------------------------------*/
class Floor
{
    string floorNumber;
    map<string, Room *> rooms; // Map to store rooms with room type as key
public:
    // Constructor
    Floor();
    Floor(string floorNumber);
    // Setters
    void setFloorNumber(string floorNumber);
    // Getters
    string getFloorNumber();
    map<string, Room *> getRooms();
    // Method to add a room
    void addRoom(string roomNumber, Room *room);
    // Display
    void display();
    // Destructor
    ~Floor();
};

/* ----------------------------ROOM ----------------------------------------*/
class Room
{
    string roomNumber;
    Floor *floor;
    bool isBooked;
    Client *client;

public:
    // Constructor
    Room();
    Room(string roomNumber);

    // Setters
    void setRoomNumber(string roomNumber);
    void setFloor(Floor *floor);
    void setIsBooked(bool booked);
    void setClient(Client *client);
    // Getters
    string getRoomNumber();
    Floor *getFloor();
    Client *getClient();
    bool getIsBooked();

    // Display
    virtual void display();
};

/* ----------------------------CLIENT ----------------------------------------*/
class Client
{
    string name;
    string ID;
    vector<Room *> bookedRooms; // Vector to store booked rooms

public:
    // Constructor
    Client();
    Client(string name, string ID);

    // Setters
    void setName(string name);
    void setID(string ID);

    // Getters
    string getName();
    string getID();
    vector<Room *> getBookedRooms();

    // Method to book a room
    void addBookedRoom(Room *room);
    void cancelBooking(Room *room);

    // Display
    void display();

    // Destructor
    ~Client();
};

/* ----------------------------CONFERENCE ROOM ----------------------------------------*/
class ConferenceRoom : public Room
{
    string name;
    map<string, ClassRoom *> classRooms;

public:
    // Constructor
    ConferenceRoom();
    ConferenceRoom(string name);
    // Setters
    void setName(string name);
    // Getters
    string getName();
    // Method to add a class room
    void addClassRoom(string roomNumber, ClassRoom *classRoom);
    void removeClassRoom(string roomNumber);
    // Display
    void display();
    // Destructor
    ~ConferenceRoom();
};

/* ----------------------------REST ROOM ----------------------------------------*/
class RestRoom : public Room
{
public:
    // Constructor
    RestRoom();
    RestRoom(string roomNumber);
    // Setters
    void setRoomNumber(string roomNumber);
    // Getters
    string getRoomNumber();
    // Display
    void display();
};

/* ---------------------------- CLASSROOM ----------------------------------------*/
class ClassRoom : public Room
{
    ConferenceRoom *conferenceRoom;

public:
    // Constructor
    ClassRoom();
    ClassRoom(string roomNumber);
    // Setters
    void setConferenceRoom(ConferenceRoom *conferenceRoom);
    // Getters
    ConferenceRoom *getConferenceRoom();
    // Mehod
    void attachConferenceRoom(ConferenceRoom *conferenceRoom);
    void detachConferenceRoom();
    // Display
    void display();
    // Destructor
    ~ClassRoom();
};

/* ----------------------------CLASS HOTEL ----------------------------------------*/
// Constructor
Hotel::Hotel() : name("Default Hotel") {}
Hotel::Hotel(string name)
{
    setName(name);
}
// Setters
void Hotel::setName(string name)
{
    this->name = name;
}
void Hotel::addClient(Client *client)
{
    if (checkIn(client))
    {
        clients[client->getID()] = client;
    }
}
void Hotel::addFloor(Floor *floor)
{
    if (floor)
    {
        floors.push_back(floor); // Add the floor to the list
    }
}
// Getters
string Hotel::getName()
{
    return this->name;
}
list<Floor *> Hotel::getFloors()
{
    return this->floors;
}
map<string, Client *> Hotel::getClients()
{
    return this->clients;
}
// Method to book a room
bool Hotel::checkIn(Client *client)
{
    if (client)
    {
        cout << "Client " << client->getName() << " checked in." << endl;
        return true;
    }
    return false; //
}
bool Hotel::checkOut(Client *client)
{
    if (client)
    {
        for (auto &room : client->getBookedRooms())
        {
            cancelBooking(client, room);
        }
        clients.erase(client->getID()); // Remove client from the hotel
        cout << "Client " << client->getName() << " checked out." << endl;
        return true;
    }
    return false;
}
bool Hotel::roomExists(Room *room)
{
    for (const auto &floor : floors)
    {
        if (floor->getRooms().find(room->getRoomNumber()) != floor->getRooms().end())
        {
            return true;
        }
    }
    return false;
}
void Hotel::bookRoom(Client *client, Room *room)
{
    if (!roomExists(room))
    {
        cout << "Room " << room->getRoomNumber() << " does not exist in the hotel." << endl;
        return;
    }

    if (client && room)
    {
        if (!room->getIsBooked())
        {                                // Check if the room is not already booked
            client->addBookedRoom(room); // Add the room to the client's booked rooms
            room->setIsBooked(true);     // Mark the room as booked
            room->setClient(client);     // Set the client for the room
            cout << "Room " << room->getRoomNumber() << " booked for client " << client->getName() << "." << endl;
        }
        else
        {
            cout << "Room " << room->getRoomNumber() << " is already booked." << endl;
        }
    }
    else
    {
        cout << "Failed to book room: Client or Room is null." << endl;
    }
}
void Hotel::cancelBooking(Client *client, Room *room)
{
    if (!roomExists(room))
    {
        cout << "Room " << room->getRoomNumber() << " does not exist in the hotel." << endl;
        return;
    }

    if (client && room)
    {
        client->cancelBooking(room); // Remove the room from the client's booked rooms
        room->setIsBooked(false);    // Mark the room as not booked
        room->setClient(nullptr);    // Clear the client for the room
        cout << "Booking for room " << room->getRoomNumber() << " cancelled for client " << client->getName() << "." << endl;
    }
    else
    {
        cout << "Failed to cancel booking: Client or Room is null." << endl;
    }
}
// Destructor
Hotel::~Hotel()
{
    for (auto &floor : floors)
    {
        delete floor;
    }
    for (auto &client : clients)
    {
        delete client.second;
    }
    cout << "Hotel " << name << " destroyed." << endl;
}

/* ----------------------------CLASS CLIENT ----------------------------------------*/
// Constructor
Client::Client() : name("Default Client"), ID("0000") {}
Client::Client(string name, string ID)
{
    setName(name);
    setID(ID);
}
// Setters
void Client::setName(string name)
{
    this->name = name;
}
void Client::setID(string ID)
{
    this->ID = ID;
}
// Getters
string Client::getName()
{
    return this->name;
}
string Client::getID()
{
    return this->ID;
}
vector<Room *> Client::getBookedRooms()
{
    return this->bookedRooms;
}
void Client::addBookedRoom(Room *room)
{
    if (room)
    {
        bookedRooms.push_back(room);
        room->setIsBooked(true);
        cout << "Room " << room->getRoomNumber() << " booked for client " << name << "." << endl;
    }
}
void Client::cancelBooking(Room *room)
{
    auto it = find(bookedRooms.begin(), bookedRooms.end(), room);
    if (it != bookedRooms.end())
    {
        bookedRooms.erase(it);
        room->setIsBooked(false);
        room->setClient(nullptr);
        cout << "Booking for room " << room->getRoomNumber() << " cancelled for client " << name << "." << endl;
    }
    else
    {
        cout << "Room " << room->getRoomNumber() << " not found in booked rooms." << endl;
    }
}

// Display
void Client::display()
{
    cout << "Client Name: " << name << ", ID: " << ID << endl;
    cout << "Booked Rooms: " << endl;
    for (const auto &room : bookedRooms)
    {
        room->display();
    }
}

// Destructor
Client::~Client()
{
    for (auto &room : bookedRooms)
    {
        delete room;
    }
}

/* ----------------------------CLASS CONFERENCE ROOM ----------------------------------------*/
ConferenceRoom::ConferenceRoom() : name("Default Conference Room") {}
ConferenceRoom::ConferenceRoom(string name)
{
    setName(name);
}
// Setters
void ConferenceRoom::setName(string name)
{
    this->name = name;
}
// Getters
string ConferenceRoom::getName()
{
    return this->name;
}
// Method to add a class room
void ConferenceRoom::addClassRoom(string roomNumber, ClassRoom *classRoom)
{
    if (this->getFloor() && classRoom->getFloor())
    {
        if (this->getFloor() != classRoom->getFloor())
        {
            cout << " Error: ClassRoom " << roomNumber
                 << " is not on the same floor as ConferenceRoom "
                 << this->getRoomNumber() << endl;
            return;
        }
    }

    classRooms[roomNumber] = classRoom;
}

void ConferenceRoom::removeClassRoom(string roomNumber)
{
    auto it = classRooms.find(roomNumber);
    if (it != classRooms.end())
    {
        delete it->second;    // Clean up the class room
        classRooms.erase(it); // Remove from the map
        cout << "Class Room " << roomNumber << " removed from Conference Room " << name << "." << endl;
    }
    else
    {
        cout << "Class Room " << roomNumber << " not found in Conference Room " << name << "." << endl;
    }
}
// Display
void ConferenceRoom::display()
{
    cout << "Conference Room Name: " << name << endl;
    cout << "       Class Rooms: " << endl;
    for (const auto &classRoom : classRooms)
    {
        cout << "       ";
        classRoom.second->display();
    }
    cout << endl;
}
// Destructor
ConferenceRoom::~ConferenceRoom()
{
    for (auto &classRoom : classRooms)
    {
        delete classRoom.second; // Clean up class rooms
    }
}

/* ----------------------------CLASS FLOOR ----------------------------------------*/
Floor::Floor() : floorNumber("Default Floor") {}
Floor::Floor(string floorNumber)
{
    setFloorNumber(floorNumber);
}
// Setters
void Floor::setFloorNumber(string floorNumber)
{
    this->floorNumber = floorNumber;
}
// Getters
string Floor::getFloorNumber()
{
    return this->floorNumber;
}
map<string, Room *> Floor::getRooms()
{
    return this->rooms;
}
// Method to add a room
void Floor::addRoom(string roomNumber, Room *room)
{
    room->setFloor(this);
    rooms[roomNumber] = room;
}
// Display
void Floor::display()
{
    for (const auto &pair : rooms)
    {
        cout << " - ";
        pair.second->display();
    }
}
// Destructor
Floor::~Floor()
{
    for (auto &pair : rooms)
    {
        delete pair.second; // Clean up rooms
    }
}
/* ----------------------------CLASS ROOM ----------------------------------------*/
// Constructor
Room::Room() : roomNumber("Default Room"), floor(nullptr), isBooked(false) {}
Room::Room(string roomNumber)
{
    setRoomNumber(roomNumber);
    floor = nullptr;
    isBooked = false;
}
// Setters
void Room::setRoomNumber(string roomNumber)
{
    this->roomNumber = roomNumber;
}
void Room::setFloor(Floor *floor)
{
    this->floor = floor;
}
void Room::setIsBooked(bool booked)
{
    this->isBooked = booked; // Set the booking status
}
void Room::setClient(Client *client)
{
    this->client = client;
}
// Getters
string Room::getRoomNumber()
{
    return this->roomNumber;
}
Floor *Room::getFloor()
{
    return this->floor;
}
Client *Room::getClient()
{
    return this->client;
}
bool Room::getIsBooked()
{
    return this->isBooked;
}
// Display
void Room::display()
{
    cout << "Room Number: " << roomNumber << endl;
}

/* ----------------------------CLASS REST ROOM ----------------------------------------*/
RestRoom::RestRoom() : Room("Default Rest Room") {}
RestRoom::RestRoom(string roomNumber) : Room(roomNumber) {}
// Setters
void RestRoom::setRoomNumber(string roomNumber)
{
    Room::setRoomNumber(roomNumber);
}
// Getters
string RestRoom::getRoomNumber()
{
    return Room::getRoomNumber();
}
// Display
void RestRoom::display()
{
    cout << "Rest Room Number: " << getRoomNumber() << endl;
}

/* ----------------------------CLASS CLASSROOM ----------------------------------------*/
// Constructor
ClassRoom::ClassRoom() : Room("Default Class Room"), conferenceRoom(nullptr) {}
ClassRoom::ClassRoom(string roomNumber) : Room(roomNumber), conferenceRoom(nullptr) {}
// Setters
void ClassRoom::setConferenceRoom(ConferenceRoom *conferenceRoom)
{
    this->conferenceRoom = conferenceRoom;
}
// Getters
ConferenceRoom *ClassRoom::getConferenceRoom()
{
    return this->conferenceRoom;
}
// Method
void ClassRoom::attachConferenceRoom(ConferenceRoom *conferenceRoom)
{
    if (conferenceRoom)
    {
        this->conferenceRoom = conferenceRoom;
        conferenceRoom->addClassRoom(getRoomNumber(), this); // Add this class room to the conference room
    }
    else
    {
        cout << "Failed to attach conference room: Conference Room is null." << endl;
    }
}
void ClassRoom::detachConferenceRoom()
{
    if (conferenceRoom)
    {
        conferenceRoom = nullptr; // Detach the conference room
    }
    else
    {
        cout << "No conference room to detach." << endl;
    }
}

// Display
void ClassRoom::display()
{
    cout << "Class Room Number: " << getRoomNumber() << endl;
}
// Destructor
ClassRoom::~ClassRoom()
{
    if (conferenceRoom)
    {
        conferenceRoom->removeClassRoom(getRoomNumber()); // Remove this class room from the conference room
    }
    cout << "Class Room " << getRoomNumber() << " destroyed." << endl;
}

/* --------------------------------------------------------------------*/
int main()
{
    srand(time(0)); // Khởi tạo seed ngẫu nhiên

    Hotel myHotel("AI Grand Hotel");

    // Tạo 5 tầng
    for (int i = 1; i <= 5; ++i)
    {
        Floor *floor = new Floor("Floor " + to_string(i));

        // Thêm 3 ConferenceRoom
        for (int j = 1; j <= 3; ++j)
        {
            string roomNum = "C" + to_string(i) + to_string(j);
            ConferenceRoom *confRoom = new ConferenceRoom("Conference_" + roomNum);
            confRoom->setRoomNumber(roomNum);
            floor->addRoom(roomNum, confRoom);
        }

        // Thêm 6 RestRoom
        for (int j = 1; j <= 6; ++j)
        {
            string roomNum = "R" + to_string(i) + to_string(j);
            RestRoom *restRoom = new RestRoom(roomNum);
            floor->addRoom(roomNum, restRoom);
        }

        // Thêm 11 ClassRoom để tổng cộng 20 phòng / tầng
        for (int j = 1; j <= 11; ++j)
        {
            string roomNum = "CL" + to_string(i) + to_string(j);
            ClassRoom *classRoom = new ClassRoom(roomNum);
            floor->addRoom(roomNum, classRoom);
        }

        // Thêm tầng vào khách sạn
        myHotel.addFloor(floor);
    }

    // Gán một số ClassRoom vào ConferenceRoom cùng tầng (không bắt buộc)
    for (Floor *floor : myHotel.getFloors())
    {
        vector<ConferenceRoom *> confRooms;
        vector<ClassRoom *> clsRooms;

        for (auto &pair : floor->getRooms())
        {
            if (auto *conf = dynamic_cast<ConferenceRoom *>(pair.second))
            {
                confRooms.push_back(conf);
            }
            else if (auto *cls = dynamic_cast<ClassRoom *>(pair.second))
            {
                clsRooms.push_back(cls);
            }
        }

        for (ClassRoom *cls : clsRooms)
        {
            if (!confRooms.empty() && rand() % 2 == 0)
            {
                int index = rand() % confRooms.size();
                cls->attachConferenceRoom(confRooms[index]);
            }
        }
    }

    // Tạo 15 khách hàng
    for (int i = 1; i <= 15; ++i)
    {
        string name = "Client_" + to_string(i);
        string id = "ID" + to_string(1000 + i);
        Client *client = new Client(name, id);
        myHotel.addClient(client);
    }

    // Gán ngẫu nhiên mỗi khách hàng một phòng trống
    vector<Room *> allRooms;
    for (Floor *floor : myHotel.getFloors())
    {
        for (auto &pair : floor->getRooms())
        {
            allRooms.push_back(pair.second);
        }
    }

    int roomIndex = 0;
    for (auto &pair : myHotel.getClients())
    {
        if (roomIndex < allRooms.size())
        {
            Room *room = allRooms[roomIndex];
            if (!room->getIsBooked())
            {
                myHotel.bookRoom(pair.second, room);
            }
            roomIndex++;
        }
    }

    cout << "\n========== DISPLAY HOTEL ==========\n";
    for (Floor *floor : myHotel.getFloors())
    {
        cout << "\n"
             << floor->getFloorNumber() << ":\n";
        floor->display();
    }

    cout << "\n========== DISPLAY CLIENTS ==========\n";
    for (auto &pair : myHotel.getClients())
    {
        pair.second->display();
        cout << "--------------------------\n";
    }

    return 0;
}