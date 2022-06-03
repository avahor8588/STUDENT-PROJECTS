//Name: Navigator.cpp
//Project: CMSC 202 Project 3, Spring 2022
//Author:  Aamil vahora
//Date:    2/22/2022
//Desc: This file puts together the code from route and ports.cpp

#include "Navigator.h"



Navigator::Navigator(string fileName){

}
// Name: Navigator (destructor)
// Desc: Deallocates all dynamic aspects of a Navigator
// Preconditions: There is an existing Navigator
// Postconditions: All ports and routes are cleared


Navigator::~Navigator(){
    int ports_size = m_ports.size();
    int route_size = m_routes.size();



     // destroys ports and memory of the ports
    for (int i = 0; i< ports_size; i++){
        delete m_ports[i];
        m_ports[i]= nullptr;
     }

    // destroys routes and memory of the routes
    for (int i = 0; i< route_size; i++){
        delete m_routes[i];
        m_routes[i]= nullptr;
     }

    cout<<"Routes removed from memory"<<endl;
    cout <<"Deleting Ports"<<endl;
    cout <<"Deleting Routes"<<endl;
    

}
// Name: Start
// Desc: Loads the file and calls the main menu
// Preconditions: m_fileName is populated
// Postconditions: All ports are loaded and the main menu runs
void Navigator::Start(){
    ReadFile();
    MainMenu();


}
// Name: DisplayPorts
// Desc: Displays each port in m_ports
// Preconditions: At least one port is in m_ports
// Postconditions: Displays all ports. Uses overloaded << provided in Port.h
void Navigator::DisplayPorts(){
    // amount of routes that exsist
    int size = m_ports.size();


    for (int i = 0; i<size; i++){
        // displays the ports that exist and are able to use
        cout << i+1<< ". ";
        // calling overloaded operator here
        cout <<*m_ports.at(i)<<endl;
    }

}
// Name: ReadFileWkakklg7

// Desc: Reads in a file that has data about each port including name, location, degrees
//       north and degrees west. Dynamically allocates ports and stores them in m_ports
//       The vector can hold many ports.
// Preconditions: Valid file name of ports
// Postconditions: Dynamically allocates each port and enters it into m_ports
void Navigator::ReadFile(){
    string temp_n;
    string temp_w;
    string location;
    string name;
    double north;
    double west;
    Port* obj;
    int num =0;
    ifstream port_file("proj3_data.txt");
    if (port_file.is_open()){
        // while loop, loops through the data file and stores the objects into a vector
        while (getline(port_file,name, ',' ) && getline(port_file,location, ',' ) &&
        getline(port_file,temp_n, ',' ) && getline(port_file,temp_w)){

            // converts north and west from strings to numbers
            north = stod(temp_n);
            west = stod(temp_w);

            // dynamically reallocated the memory to create an obj object
            obj  = new Port(name,location,north,west);
            m_ports.push_back(obj);
            num ++;
        }
        cout <<num << " Ports Loaded" << endl;

    }
    port_file.close();





}
// Name: InsertNewRoute
// Desc: Dynamically allocates a new route with the user selecting each port in the route.
//       Route named based on the first and last port automatically
//       For example, Baltimore to Boston
//       Once route is created, inserted into m_routes.
// Preconditions: Populated m_routes
// Postconditions: Inserts a new route into m_routes
void Navigator::InsertNewRoute(){
    string last_name = "";
    // dynamically realocate route
    Route* my_route = new Route;
    DisplayPorts();
    int count = 0;

    int size =  m_ports.size();

    int choice;
    cout <<"Enter the number of the port to add to your Route: (-1 to end)"<<endl;
    cin>> choice;
    // the loop ends if user enter -1
    while (choice != -1){



        // input validation 
         while (cin.fail() || choice > size || choice < -1 || choice == 0 ){
            cout <<"Invalid entery, Enter the number of the port to add to your Route: (-1 to end)"<<endl;
            cin.clear();
            cin.ignore(256, '\n');
            cin>>choice;
            }

        if (choice >= 1 || choice == 0){
            if (last_name  ==  m_ports[choice-1] -> GetName()){
                cout <<"Invalid entery, Enter the number of the port to add to your Route: (-1 to end)"<<endl;
                cin>>choice;
                }
        }


        // if the choice is not -1 then all the code below executes bc then a seg fault isnt given
        if (choice != -1 && choice >= 1){
            choice -=1;


            string location =  m_ports[choice] ->GetLocation();
            string name =  m_ports[choice] ->GetName();
            double north=  m_ports[choice] ->GetNorth();
            double west =  m_ports[choice] ->GetWest();
            my_route -> InsertEnd(name, location, north, west);
            count ++;
            last_name = name;
            cout <<"Enter the number of the port to add to your Route: (-1 to end)"<<endl;
            cin>> choice;

        }

        
    }

    // updates name and adds route to m_routes

    if (count>=2){
        m_routes.push_back(my_route);
        my_route ->UpdateName();
        cout <<"Done Building a New Route named " <<my_route -> GetName()<<endl;

    }else{
        cout <<"not enough ports to create route"<<endl;
    }




}
// Name: MainMenu
// Desc: Displays the main menu and manages exiting
// Preconditions: Populated m_ports
// Postconditions: Exits when someone chooses 5
void Navigator::MainMenu(){
    int choice= 0;
    while(choice != 5){
    cout <<"What would you like to do?: "<<endl;
    cout << 1<< ". Create New Route"<<endl;
    cout << 2<<". Display Route "<<endl;
    cout << 3<<". Remove Port From Route "<<endl;
    cout << 4<<". Reverse Route "<<endl;
    cout <<"5. Exit"<<endl;
    cin>>choice;

    // switch statement for the user input
    switch (choice){
        case 1:
            InsertNewRoute();
            break;
        case 2:
            if (m_routes.size()>0){
                DisplayRoute();
            }else{
                cout <<"no routes available"<<endl;
            }
            break;
        case 3:
            if (m_routes.size()>0){
                RemovePortFromRoute();
            }else{
                cout <<"no routes available"<<endl;
            }
            break;
        case 4:
            if (m_routes.size()>0){
                ReverseRoute();
            }else{
                cout <<"no routes available"<<endl;
            }
            break;


    }


    }

    

}
// Name: ChooseRoute
// Desc: Allows user to choose a specific route to work with by displaying numbered list
// Preconditions: Populated m_routes
// Postconditions: Returns the index of the selected route minus 1
int Navigator::ChooseRoute(){
    int choice;
    int size = m_routes.size();
    
    
    cout <<"Which route would you like to use?"<<endl;
    // displays given routes before the cin statement is given which is why cannot call on diplayroute function
    for (int i =0; i<size; i++){
        cout <<i+1;
        cout <<". "<< m_routes[i]->GetName()<<endl;
    }
    cin>>choice;

    // input validation
    while (cin.fail() || choice > size || choice < 1){
        cout << "invalid response, Which route would you like to use?"<<endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin>>choice;
    }
    choice -=1;
    cout << m_routes[choice]->GetName()<<endl;
    return choice;

}


// Name: DisplayRoute
// Desc: Using ChooseRoute, displays a numbered list of all routes.
//       If no routes, indicates that there are no routes to display
//       User selects a route from list to display
//       Displays numbered list of each port in route
//       Displays total miles of a route using RouteDistance
// Preconditions: Routes has more than one port
// Postconditions: Displays all ports in a route and the total miles of the route
void Navigator::DisplayRoute(){
    double distance;
    int input = ChooseRoute();

    // displays the route at the chosen index
    m_routes[input] -> DisplayRoute();
    distance  = RouteDistance(m_routes[input]);
    cout <<"The total miles of this route is "<<distance<<" miles"<<endl;

}

// Name: RemovePortFromRoute()
// Desc: Using ChooseRoute, displays a numbered list of all routes.
//       User selects one of the routes to remove a port from.
//       Displays a numbered list of all ports in selected route.
//       User selects port to remove from list.
//       Removes port from route. If first or last port removed, updates name of route.
// Preconditions: Routes has more than one port
// Postconditions: Displays updated route with removed port and new name


void Navigator::RemovePortFromRoute(){
    int input = ChooseRoute();
    int size = m_routes[input] ->GetSize();
    int num;

    m_routes[input] -> DisplayRoute();
    cout <<"Which port would you like to remove? "<<endl;
    cin>> num;

    // inpuut validations
    while (cin.fail() || num>size || num <1){
        cout <<"invalid entery, Which port would you like to remove?  "<<endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin>>num;
    }
    if (size == 2){
        cout <<"only two ports in route, cannot be removed"<<endl;
    }else{

    // reduces index by one because vector starts at 0
    num -=1;
    // this removes the port and displays the route
    m_routes[input] -> RemovePort(num);
    m_routes[input] -> DisplayRoute();

    cout <<" Updated Route named "<< m_routes[input] -> GetName() <<endl;
    // changes the name
    m_routes[input] -> UpdateName();
    }





}




// Name: RouteDistance
// Desc: Calculates the total distance of a route
//       Goes from port 1 to port 2 then port 2 to port 3 and repeats for
//       length of route. Calculates the distance using CalcDistance (provided)
//       Aggregates the total and returns the total in miles
// Preconditions: Populated route with more than one port
// Postconditions: Returns the total miles between all ports in a route
double Navigator::RouteDistance(Route* the_route){
    int size = the_route ->GetSize();
    double sum = 0;
   for (int i =0; i < size-1; i ++){
       // adds calc distance of from each two ports until end of route to sum
       sum += CalcDistance(the_route -> GetData(i)->GetNorth(), 
       the_route -> GetData(i)->GetWest(), the_route -> GetData(i+1)->GetNorth(), 
       the_route -> GetData(i+1)->GetWest());
   }
   // returns double
   return sum;



    
}
// Name: ReverseRoute
// Desc: Using ChooseRoute, users chooses route  and the route is reversed
//       If no routes in m_routes, indicates no routes available to reverse
//       Renames route based on new starting port and ending port
//       For example, Baltimore to Boston becomes Boston to Baltimore
// Preconditions: Populated m_routes
// Postconditions: Reverses a specific route by reversing the ports in place
//                 Must move ports, cannot just change data in ports.
void Navigator::ReverseRoute(){

    int input = ChooseRoute();

    // reverses given route
    m_routes[input] -> ReverseRoute();

    // updates route name
    m_routes[input]->UpdateName();

    cout << "done reversing Route "<<input+1<<endl;
}
