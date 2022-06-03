//Name: Route.cpp
//Project: CMSC 202 Project 3, Spring 2022
//Author:  Aamil vahora
//Date:    2/22/2022
//Desc: This file contains the details for the Route class
//      A route is a linked list that uses ports as nodes


#include "Route.h"

// Name: Route() - Default Constructor
// Desc: Used to build a new Route (linked list) make up of ports
// Preconditions: None
// Postconditions: Creates a new Route where m_head and m_tail point to nullptr and size = 0
Route::Route(){
    // need to set the pointer to null and size to 0
    m_head  = nullptr;
    m_tail = nullptr;
    m_size  = 0;


}



// Name: SetName(string)
// Desc: Sets the name of the route (usually first port to last port)
// Preconditions: None
// Postconditions: Sets name of route

void  Route::SetName(string name){
    m_name = name;

}
// Name: ~Route() - Destructor
// Desc: Used to destruct a strand of Route
// Preconditions: There is an existing Route strand with at least one port
// Postconditions: Route is deallocated (including all dynamically allocated ports)
//                 to have no memory leaks!
Route::~Route(){
    Port* curr = m_head;
    while (curr != nullptr){
        m_head = curr;
        curr  =  curr->GetNext();
        // deltes m_head
        delete m_head;
    }
    // destroys m_head and m_tail
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;



}


// Name: InsertEnd (string, string, double double)
// Desc: Creates a new port using the data passed to it.
//       Inserts the new port at the end of the route
// Preconditions: Takes in a Port
//                Requires a Route
// Postconditions: Adds the new port to the end of a route
void Route::InsertEnd(string name, string location, double north, double west){
    
    Port *temp = new Port(name,location,north,west);
    if (m_head == nullptr){
        m_head = temp;
        m_tail = temp;

    }else{
        // adds to the end of the linked list here
        m_tail->SetNext(temp);
        m_tail = temp;


    }m_size++;

    
}
// Name: RemovePort(int index)

// Desc: Removes a port from the route at the index provided
//       Hint: Special cases (first port, last port, middle port)
// Preconditions: Index must be less than the size of the route
//       Cannot make route less than two ports. If the route has
//       two or fewer ports, fails.
// Postconditions: Name may be updated. Size is reduced. Route has one less port.
void Route::RemovePort(int port){
    Port* curr = m_head;
    Port* prev = m_head;
    int count = 0;
    int end_count  = 0;

    if (m_size <= 2){
        return;
    }

    // this is for begining
    if (port == 0){
        m_head = m_head->GetNext();
        delete curr;
        m_size --;
        return;
    }

    // this is for end
    if (port == m_size-1){
        while (end_count < (port-1) ){
            curr = curr -> GetNext();
            end_count++;
  
        }
        delete m_tail;
        m_tail = curr;
        m_tail ->SetNext(nullptr);
        m_size --;
        return;

    }

    // this is for middle of linked list
    while (curr != nullptr){
        if (count == port){
            prev->SetNext(curr->GetNext());
            m_size--;
            delete curr;
            return;
        }
        prev = curr;
        curr = curr -> GetNext();
        count ++;

        }

}


// Name: GetName()
// Desc: Returns the name of the route (Usually starting port to last port)
//       For example: Baltimore to Brunswick
// Preconditions: Requires a Route
// Postconditions: Returns m_name;
string Route::GetName(){

    Port* curr = m_head;
    if(curr != nullptr){
        // as long as first port in linked list is not equal to nullptr it will return m_name
        return m_name;
    }
    return "";

}


// Name: UpdateName()
// Desc: Updates m_name based on the name of the first port in the route
//       and the last port in the route
//       For example: Baltimore to Brunswick
// Preconditions: Requires a Route with at least two ports
// Postconditions: Returns m_name;
string Route::UpdateName(){
    string start;
    string end;

    if (m_size >= 2){
        start = m_head ->GetName();
        end = m_tail->GetName();

        // create new string that contains name of the route
        m_name = start+" to "+end;

        // returns the newly created string
        return m_name;
    }

    return "";



}
// Name: GetSize()
// Desc: Returns the number of ports in a route
// Preconditions: Requires a Route
// Postconditions: Returns m_size;
int Route::GetSize(){
    Port* curr = m_head;
    if(curr != nullptr){
        // as long as the first port isnt equal to nullptr it reutrns m_size
        return m_size;

    }
    return 0;

}
// Name: ReverseRoute
// Desc: Reverses a route
// Preconditions: Reverses the Route
// Postconditions: Route is reversed in place; nothing returned
void Route::ReverseRoute(){

    Port *curr = m_head;
    Port *prev = NULL;
    Port *next_one;
    // set m_tail to m_head becuse if not the tail doesnt update properly
    m_tail = m_head;

    // loop that actually reverse
    while (curr != nullptr){
        next_one = curr->GetNext();
        curr->SetNext(prev);
        prev = curr;
        curr = next_one;
    }

        m_head = prev;

        // function ends
        return;
}






// Name: GetData (int)
// Desc: Returns a port at a specific index
// Preconditions: Requires a Route
// Postconditions: Returns the port from specific item
Port* Route::GetData(int index){
    int count = 0;
    Port* curr = m_head;
    while(count != index){
        // loops until curr matches index then retrurn curr
        curr = curr -> GetNext();
        count ++;

        
    }
    return curr;

    

}
// Name: DisplayRoute
// Desc: Displays all of the ports in a route
// Preconditions: Requires a Route
// Postconditions: Displays all of the ports in a route
// Formatted: Baltimore, Maryland (N39.209 W76.517)
void Route::DisplayRoute(){
    if (m_size  == 0 ){
        // if no port exists linked list doesnt exist
        cout << "linked list doesnt exist"<<endl;
        return;
    }else{
        Port* temp = m_head;
        int count  = 1;
        while(temp != nullptr){
            // declaring all variables 
            double north = temp ->GetNorth();
            double west = temp ->GetWest();
            string location= temp ->GetLocation();
            string name= temp ->GetName();

            // printing out the route
            cout <<count<<". "<<  name <<", "<<location<<" "<< "(N"<< north<<",  W"<<west<<")"<<endl;

            // setting next route so the loop, loops
            temp  = temp -> GetNext();
            count ++;
        }


    }
    
}
