#include "Caesar.h"


Caesar::Caesar(){
    // default amount of shifts
    m_shift  = 3;
    
}
// Name: Caesar (Overloaded Constructor)
// Desc: Constructor to build a populated Caesar Cipher (Defaults to shift 3)
// Preconditions - Pass it the message, isEncrypted, and shift (any integer)
// Postconditions - Creates a Caesar cipher to be encrypted
Caesar::Caesar(string my_message, bool encrypted, int shift):Cipher(my_message, encrypted){
    // calling paramters from overleaded operator in parent class
    m_shift  = shift;

    
}



// Name: Caesar (Destructor)
// Desc: Destructor - Anything specific to Caesar to delete?
// Preconditions - ~Caesar exists
// Postconditions - Caesar destroyed
Caesar::~Caesar(){

    // nothing needs to be destroyed no memory was allocated

}


// Name: Encrypt
// Desc: Shifts characters right based on shift (lower stay lower, upper stay upper)
// Preconditions - Message exists
// Postconditions - Shifts each character "right".
void Caesar::Encrypt(){
    string mess = GetMessage();
    string temp;
    char letter;
    for (int i =0; i<int(mess.size()); i++){
        letter  = mess.at(i);
        // if the letter is a space
        if (letter == 32){
            temp.push_back(letter);
        }
        // for uppercase
        else if (letter < 90 && letter>65 &&letter ){
            // add the number of shifts
            letter+=(m_shift);

            // gets it in ascii value
            letter -= 'A';
            letter = letter%26;
            letter += 'A';
            temp.push_back(letter);
        }
         // if lowercase
        else if(letter <122 && letter >96){
            letter+=(m_shift);
            letter -= 'a';
            letter = letter%26;
            letter += 'a';
            temp.push_back(letter);
        }else{
            temp.push_back(letter);
         }
         

         
     }
     SetMessage(temp);
     




}


// Name: Decrypt
// Desc: Shifts characters left based on shift (lower stay lower, upper stay upper)
// Preconditions - Message exists
// Postconditions - Shifts each character "left".
void Caesar::Decrypt(){
    string temp;
    string mess = GetMessage();
    char letter;
    for (int i =0; i<int(mess.size()); i++){
        letter  = mess.at(i);
        // if the letter is a space
        if (letter == 32){
            temp.push_back(letter);
        }
        // if uppercase
        else if (letter <= 90 && letter>=65){

            // the line below is what does the dycrption for the most part
            letter+=(26-((m_shift)%26));

            letter -= 'A';
            letter = letter%26;
            letter += 'A';
            temp.push_back(letter);
            }
        // if lowercase
        else if(letter <=122 && letter >=97){

            // again thid dycrpts the cipher
            letter+=(26-((m_shift)%26));
            letter -= 'a';
            letter = letter%26;
            letter += 'a';
            temp.push_back(letter);
            }else{
                temp.push_back(letter);
            }
            

            
        }
        SetMessage(temp);
        
    


}


// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (Caesar in this case)
string Caesar::ToString(){
    return "(Caesar)";

}


// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - c, delimiter, isencrypted, delimiter,
//                  message, delimiter, m_shift are returned for output
string Caesar::FormatOutput(){
    stringstream caesar;
    caesar << "c"<< DELIMITER<< GetIsEncrypted()<<DELIMITER<< GetMessage()<< DELIMITER<<m_shift;
    return caesar.str();


}