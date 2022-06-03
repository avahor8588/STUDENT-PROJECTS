//Title: Chemist.h
//Author: Aamil vahora 
//Date: 2/25/2022
//Discusion : 52
//Description: This is part of the project 2 in CMSC 202 @ UMBC

#include "Chemist.h"



// Name: Chemist() - Default Constructor
// Desc: Used to build a new Chemist
// Preconditions - Requires default values
// Postconditions - Creates a new Chemist (with a default name of "Beaker" and
//       m_numSubstances = 0
Chemist::Chemist(){
    m_myName ="Beaker";
    m_numSubstances = 0;
}




// Name: Chemist(name) - Overloaded constructor
// Desc - Used to build a new Chemist
// Preconditions - Requires name
// Postconditions - Creates a new Chemist (with passed name and m_numSubstance = 0)
Chemist::Chemist(string name){
    // allows for name to change
    m_myName =name;
    m_numSubstances = 0;
    
}





// Name: GetName()
// Desc - Getter for Chemist name
// Preconditions - Chemist exists
// Postconditions - Returns the name of the Chemist


string Chemist::GetName(){
    return m_myName;
}



// Name: SetName(string)
// Desc - Allows the user to change the name of the Chemist
// Preconditions - Chemist exists
// Postconditions - Sets name of Chemist
// May not be used in the project explicitly but please impelement
void Chemist::SetName(string name){
    m_myName = name;
}



// Name: CheckSubstance(Substance)
// Desc - Checks to see if the Chemist has a substance if so, returns
//        the index where it exists, if not returns -1
// Preconditions - Chemist already has substance
// Postconditions - Returns index of substance if Chemist has it else -1
int Chemist::CheckSubstance(Substance chem_item){
    
    for (int i =0; i<PROJ2_SIZE; i++){
    // this returns the index if the substances match else it returns -1
    if (chem_item.m_name == m_mySubstances[i].m_name){
        return  i;
        }
    }
    return -1;
}
// Name: AddSubstance(string)
// Desc - Inserts a material into the Chemist's list of substances. Has
//        to see if it exists in m_mySubstances first to find location.
//        Then adds substance and increments m_numSubstances
// Preconditions - Chemist exists
// Postconditions - Add a substances to the Chemist's m_mySubstances with a quantity of 0
void Chemist::AddSubstance(Substance item){
    int location;
    location = CheckSubstance(item);
    if (location == -1){
        // this is what adds the substance found to the chemists array
        m_mySubstances[m_numSubstances] = item;
        m_numSubstances+=1;
    }
    

}




// Name: IncrementQuantity(Substance)
// Desc - Adds quantity to list of substances the chemist knows.
//        Has to find location in array first. Then increments quantity
// Preconditions - Chemist exists
// Postconditions - Increases quantity of material for chemist
void Chemist::IncrementQuantity(Substance my_item){
    int location;
    location = CheckSubstance(my_item);
    if (location != -1){
        // nncrements quantity when the subtancs is adedd to chemists array
        m_mySubstances[location].m_quantity +=1;
    }

}




// Name: DecrementQuantity(Substance)
// Desc - Reduces quantity from chemist's inventory with true, if no quantity false
// Preconditions - Chemist exists
// Postconditions - Reduces quantity of substance for chemist
bool Chemist::DecrementQuantity(Substance the_size_of){
    int location;
    location = CheckSubstance(the_size_of);
    
    if (location != -1){
        
        if (m_mySubstances[location].m_quantity == 0){
            return false;
            
        }else{
            // this decremnts quantity
            m_mySubstances[location].m_quantity -=1;
            
            
            return true;
            
        }
        
        
    }
    return false;
    
}
// Name: CheckQuantity(Substance)
// Desc - Checks to see if quantity of two merge substances is greater than one.
//        if the quantity of substance 1 is greater than one and the
//        quantity of substance two is greater than one, returns true else false
// Preconditions - Chemist exists with substances
// Postconditions - Returns true if both are available
bool Chemist::CheckQuantity(Substance a, Substance b){
    
    int location_a;
    int location_b;
    location_a = CheckSubstance(a);
    location_b = CheckSubstance(b);
    
    if (location_a != -1 and location_b != -1){
        // make sure the substance exists and the quantity us greater than 1
        if (m_mySubstances[location_a].m_quantity>1 and m_mySubstances[location_b].m_quantity>1){
            return true;
            
        }else{
            return false;
        }
        
    }
    return false;
}


// Name: GetSubstance(int)
// Desc - Returns a substance at at specific index
// Preconditions - Chemist already has substances
// Postconditions - Returns substance at specific index



Substance Chemist::GetSubstance(int index){
    return m_mySubstances[index];
}

// Name: GetTotalSubstances
// Desc - Iterates over m_mySubstances and counts each substance with a quantity higher than 0
// Preconditions - Chemist may have no substances
// Postconditions - Returns number of substances with a quantity greater than 0
int Chemist::GetTotalSubstances(){
    int count = 0;
    for (int i=0; i<PROJ2_SIZE; i++){
       if (m_mySubstances[i].m_quantity >0){
           count +=1;
       }

   }
    // returns the amount of substances found
    return count;
}
