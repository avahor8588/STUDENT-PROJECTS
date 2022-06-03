//Name: Port.cpp
//Project: CMSC 202 Project 3, Spring 2022
//Author:  Aamil Vahora
//Date:    2/22/2022
//Desc: This file contains the details for the Port class
//      The ports are nodes for a route

#include "Port.h"


Port::Port(){
    m_next  = nullptr;

}

// Name: Port(string, string, double, double) - Overloaded Constructor
// Desc: Used to build a new Port passing it a name, location, north, and west
// Preconditions: None
// Postconditions: Creates a new port for use in a Route
Port::Port(string name, string location, double north, double west){

    // overloaded contructor sets the variable to memeber variabel names
    m_name = name;
    m_location = location;
    m_north = north;
    m_west = west;
    m_next  = nullptr;


}
// Name: ~Port() - Destructor
// Desc: Used to destruct a port
//**This function should be empty but must be implemented
// Preconditions: There is an existing port
// Postconditions: Port is deallocated and has no memory leaks!
Port::~Port(){


}
// Name: GetName()
// Desc: Returns the name of the port
// Preconditions: None
// Postconditions: Returns the name of the port

string Port::GetName(){
    return m_name;

}
// Name: GetNext()
// Desc: Returns the pointer to the next port
// Preconditions: None (may return either port or nullptr)
// Postconditions: Returns m_next;

Port* Port::GetNext(){
    return m_next;

}



// Name: GetNorth()
// Desc: Returns the northern coordinates of the port
// Preconditions: None
// Postconditions: Returns the N coordinates of the port
double Port::GetNorth(){
    return m_north;

}
// Name: GetWest()
// Desc: Returns the western coordinates of the port
// Preconditions: None
// Postconditions: Returns the W coordinates of the port
double Port::GetWest(){
    return m_west;

}
// Name: GetLocation()
// Desc: Returns the description of where the port is located
// Preconditions: None
// Postconditions: Returns the description of where the port is located
string Port::GetLocation(){
    return m_location;

}


// Name: SetNext()
// Desc: Updates the pointer to a new target (either a port or nullptr)
// Preconditions: None
// Postconditions: Sets the next port
void Port::SetNext(Port* next){
    m_next = next;
}


