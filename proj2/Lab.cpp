//Title: Lab.cpp
//Author: Aamil Vahora
//Date: 2/25/2022
//Discusion : 52
//Description: This is part of the project 2 in CMSC 202 @ UMBC

#include "Lab.h"


Lab::Lab(){

    

    
} //Default Constructor
// Name: LoadSubstances
// Desc - Loads each substance into m_substances from file
//        The loads all substances from m_substances into m_myChemist's substance array
// Preconditions - Requires file with valid substance data
// Postconditions - m_substance is populated with substance structs
void Lab::LoadSubstances(){
    
    string name;
    string type;
    string form;
    string sub1;
    string sub2;
    int quantity = 0;
    
    
    
    ifstream chem_file("proj2_data.txt");
      if (chem_file.is_open()){
	for (int i =0 ; i < PROJ2_SIZE; i++ ){
        // reading in the file to the array
          getline(chem_file,name, ',' );
          getline(chem_file,type, ',' );
          getline(chem_file,form, ',' );
          getline(chem_file,sub1, ',' );
          getline(chem_file,sub2);

          Substance object(name, type, form, sub1, sub2, quantity);
          m_substances[i] = object;
         
          
        }for (int i= 0; i< PROJ2_SIZE; i++ ){
            m_myChemist.AddSubstance(m_substances[i]);
            
        }


          cout << PROJ2_SIZE << " LOADED " << endl;
      }

}


// Name: StartLab()
// 1. Displays Lab Title (as implemented below)
// 2. Loads all substances and their recipes into m_substances (Load Substances)
// 3. Asks user for their chemist's name (store in m_myChemist as m_myName)
// 4. Copies all substances from m_substances into the chemist's substance array
// 5. Manages the game itself including win conditions continually calling the main menu
// Preconditions - None
// Postconditions - m_substances and m_myChemist's substances populated
void Lab::StartLab(){
    string chemist_name;
    cout << "what is you chemists name"<<endl;
    getline(cin,chemist_name);
    m_myChemist.SetName(chemist_name);
    LabTitle();
    LoadSubstances();
    MainMenu();

}

// Name: DisplayMySubstances()
// Desc - Iterates over m_myChemist's substances
// Preconditions - Player's chemist has substances
// Postconditions - Displays a numbered list of substances
void Lab::DisplaySubstances(){
    int count;
    count  = m_myChemist.GetTotalSubstances();
    cout << "My chemist has "<< count<< " different substances in inventory currently"<<endl;
    for (int i = 0; i<PROJ2_SIZE; i++){
        cout <<i+1<< ".   ";
        cout << m_myChemist.GetSubstance(i).m_name<< " ";
        cout << "("<<m_myChemist.GetSubstance(i).m_substance1<<")" << " ";
        cout << m_myChemist.GetSubstance(i).m_quantity<<endl;

    }
    
}
// Name: MainMenu()
// Desc - Displays and manages menu
// Preconditions - Player has an Chemist
// Postconditions - Returns number including exit
int Lab::MainMenu(){
    int user_input;
    int nums = m_myChemist.GetTotalSubstances();
    while (user_input != 5 and nums != 283){
    cout << "what would you like to do"<<endl;
    cout << 1 <<". display your chemists Substances"<<endl;
    cout << 2 <<". search for elements"<<endl;
    cout << 3 <<". Attempt to merge Substances"<<endl;
    cout << 4 <<". see score"<<endl;
    cout << 5 <<". Quit"<<endl;
    cin >> user_input;

    // the switch statements loop through each of the function to call the ones needed on
    switch (user_input){
        case 1:
            DisplaySubstances();
            break;
        case 2:
            SearchSubstances();
            break;
        case 3:
            CombineSubstances();
            break;
        case 4:
            CalcScore();
            break;

    }
    
    } return user_input;


}
// Name: SearchSubstances()
// Desc - Attempts to search for raw substances (must be type "element")
// Preconditions - Raw substances loaded
// Postconditions - Increases quantity in Chemist's posession of substances

void Lab::SearchSubstances(){
    string random_element;
    int rand_num;
    Substance temp;
    do {
        // this makes sure when generating rand num its only elements
        rand_num = rand() % 283 + 0;
        temp = m_substances[rand_num];
    }
    while (temp.m_type != "element");

    
    random_element = m_substances[rand_num].m_name;
    cout << random_element<< " found!" <<endl;

    // this increments the chemist list, the quantity of the substance
    m_myChemist.IncrementQuantity(m_substances[rand_num]);
    
}


// Name: CombineSubstances()
// Desc - Attempts to combine known substances. If combined, quantity of substance decreased
// 1. Requests user to choose two substances (RequestSubstance)
// 2. Checks to see if formula exists for combining two chosen substances
//     (checks sub1, sub2 and sub2, sub1) using SearchFormula
// 3. If there is an available formula for two chosen substances, checks
//     quantity for two chosen substance.
// If no quantity for two substances, tells user that there is no available quantity
// If quantity is available, decreases quantity for two chosen substances
//     from the chemist then increases new substance
// 4. If there is no available formula, tells user that nothing happens when you try and merge two chosen substances
// Preconditions - Chemist is populated with substances
// Postconditions - Increments quantity of substance "made", decreases quantity of source items
void Lab::CombineSubstances(){
    Substance the_substance_one;
    Substance the_substance_two;
    Substance compound;
    string change_of_quantity;
    int index_of_compound;
    int my_sub1;
    int my_sub2;
    cout << "Which substances would you like to merge?"<<endl;
    cout <<"To list known substances enter -1"<<endl;
    cin >> my_sub1;
    RequestSubstance(my_sub1);


    cout <<"To list known substances enter -1"<<endl;
    cin>> my_sub2;
    RequestSubstance(my_sub2);


    the_substance_one = m_myChemist.GetSubstance(my_sub1);
    the_substance_two = m_myChemist.GetSubstance(my_sub2);

    // this finds teh index of the new compound made and a slong as it is not 0  it craetes the compound
    index_of_compound = SearchFormulas(the_substance_one.m_formula, the_substance_two.m_formula);
    if (index_of_compound == 0){
        index_of_compound = SearchFormulas(the_substance_two.m_formula, the_substance_one.m_formula);


    }
    
    if (index_of_compound != 0 && the_substance_one.m_quantity > 0 && the_substance_two.m_quantity > 0 ){
        compound  = m_myChemist.GetSubstance(index_of_compound);
        // this decrements the quantity after making the new compound
        m_myChemist.DecrementQuantity(the_substance_one);
        m_myChemist.DecrementQuantity(the_substance_two);

        // this increments the quantity of the new compound made
        m_myChemist.IncrementQuantity(compound);

        cout << the_substance_one.m_formula<<" combined with "<<the_substance_two.m_formula<<" to make "<<compound.m_name<<endl;

    }
    else if (index_of_compound == 0){
        // if the two elements dont mix then it tells us it doesnt mix
        cout <<"nothing happened when you try to mix "<<the_substance_one.m_formula<< " and "<< the_substance_two.m_formula<< endl;



    }
    else{
        cout <<"sorry, there is no available quantity"<<endl;
    }
}


// Name: RequestSubstance()
// Desc - Allows the user to choose a substance to try and merge.
//        Returns the index of chosen substance
// Preconditions - Chemist has substances to try and merge
// Postconditions - Returns integer of substance selected by user
void Lab::RequestSubstance(int &choice){      
    while (choice <= -1 or choice >283){

        // if the subtance exists then its goes through and allows user to eneter the substance index
        if (choice == -1){
            DisplaySubstances();
            cout <<"To list known substances enter -1"<<endl;
            cin >> choice;
      
        }else{
        cout << "incorrect bounds, To list known substances enter -1"<<endl;
        cin >> choice;

        }

    }choice -=1;
}



// Name: SearchFormula()
// Desc - Searches formulas for two strings (name of item)
// Preconditions - m_substances is populated
// Postconditions - Returns int index of matching formula
int Lab::SearchFormulas(string f_sub, string s_sub ){
    for (int i = 0; i<PROJ2_SIZE; i++){
        if (m_myChemist.GetSubstance(i).m_type == "compound"){

            // this iterates throug the array and sees if there is a compound with valid elements
            if (m_myChemist.GetSubstance(i).m_substance1 == f_sub and m_myChemist.GetSubstance(i).m_substance2 == s_sub){
                return i;
            }

        }
    }
    return 0;
}



// Name: CalcScore()
// Desc - Displays current score for Chemist
// Preconditions - Chemist is populated with substances
// Postconditions - Displays total number of substances found. Displays
//        percentange found as number found divided by total available
void Lab::CalcScore(){
    float num_elements;
    float score;
    string the_name;
    the_name = m_myChemist.GetName();

    // this gets the total number of elements
    num_elements  = m_myChemist.GetTotalSubstances();
    // the score is the percentage of substances found/ 283 (total availabe)
    score  = (num_elements/PROJ2_SIZE)*100;

    cout <<"The Great Chemist "<<the_name<<endl; 
    cout <<"There are 283 substances available to find"<<endl;
    cout << "You have found "<< num_elements <<" so far."<<endl;
    cout << "your score is "<< score<<"%"<<endl;

}


