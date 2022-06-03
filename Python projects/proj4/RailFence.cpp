#include "RailFence.h"



// Name: RailFence (Default Constructor)
// Desc: Constructor to build an empty RailFence Cipher (Defaults to 3 rails)
// Preconditions - None
// Postconditions - Creates a RailFence cipher
RailFence::RailFence(){

    // sets default number of rails to 3
    m_rails = 3;

}


// Name: RailFence (Overloaded Constructor)
// Desc: Constructor to build a populated RailFence Cipher (Defaults to 3 rails)
// Preconditions - Pass it the message, isEncrypted, and number of rails (any integer)
// Postconditions - Creates a RailFence cipher to be encrypted
RailFence::RailFence(string my_message, bool encrypted, int rails):Cipher(my_message, encrypted){

    // calls on parent call to get all parameters ebside the key
    m_rails = rails;


}


// Name: RailFence (Destructor)
// Desc: Destructor - Anything specific part of RailFence to delete?
// Preconditions - ~RailFence exists
// Postconditions - RailFence destroyed
RailFence::~RailFence(){

    // no memory needs to be destroyed because no memory was allocated

}


// Name: Encrypt
// Desc: Letters are placed on a fence rail based on the number of rails
//       Letters are read from one rail at a time into a single string
// Preconditions - Message exists
// Postconditions - A single encrypted string is stored
void RailFence::Encrypt(){
    string word  = GetMessage();
    bool flag = false;
    int row= 0;
    int column = 0;
    // the string that we will create
    string mess;

    char my_rail[m_rails][int(word.size())];

    for (int i = 0; i < m_rails; i++){
        for (int j= 0; j< int(word.size()); j++){
            // adding the spaces in the encryption where needed
            my_rail[i][j] = '\n';

            
        }

    }for (int i =0;  i < int(word.size()); i++){
        if(row ==0 || row == (m_rails-1)){
            // flip flag here
            flag = !flag;

        } my_rail[row][column++] = word[i];
        if (flag == 1){
            row +=1;
        }else if(flag == 0){
            row -=1;
        }

    }


    for (int i = 0; i < m_rails; i++){
        for (int j = 0; j<int(word.size()); j++){
            if (my_rail[i][j] != '\n'){
                // if the position is not equal to a (space ) then we will take whatever charecter is at the position and add
                // it to our meesage
                mess.push_back(my_rail[i][j]);
            }

        }
    }
    // we set the message to the word we created
    SetMessage(mess);


    

}


// Name: Decrypt
// Desc: Single encrypted string is pushed back on the rails and reversed
// Preconditions - Message exists
// Postconditions - The decrypted string is stored
void RailFence::Decrypt(){
    string final_word;
    string word  = GetMessage();
    int row = 0;
    int col = 0;
    int num = -1;
    // this is our place holder here we will use the "~"
    char teller = '~';

    int num_index =0;
    int size = int(word.size());
    char rail[m_rails][word.size()];
 

    for (int i=0; i < m_rails; i++){
        for (int j=0; j < size; j++){
            // filling in the spaces here
            rail[i][j] = '\n';
        }
    }
 
 
    int m = 0;
        while(m < size){

            rail[row][col++] = teller; // we place our place holder here

            if(row == 0 || row == m_rails-1){
                num*= (-1);
            }
            row +=num;
            
            m++;
    }
 
    // we create the new grid here
    for (int i=0; i<m_rails; i++){
        for (int j=0; j<size; j++){
            if (rail[i][j] == teller){
                // create the new charceter to add and increase the index so it looks at different charecters
                rail[i][j] = word[num_index++];}
        }
    }

    // we must set the row and column back to zero
    // because we have created our grid now and found teh charecters we need
    row = 0;
    col = 0;
    num= -1 ;
    
    
    
    
    int w = 0;
    while (w < size)
    {
        // we populate our new message here below
        final_word.push_back(rail[row][col++]);
        if(row == 0 || row == m_rails-1){
            num*= (-1);
        }
        row = row + num;
        w++;
    }
 

    // set the message to our new dycripted message
    SetMessage(final_word);
    

}


// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (RailFence in this case)
string RailFence::ToString(){
    // returns type
    return "(RailFence)";

}


// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - r, delimiter, isencrypted, delimiter,
//                  message, delimiter, m_rails are returned for output
string RailFence::FormatOutput(){
    stringstream railfence;
    railfence << "r"<< DELIMITER<< GetIsEncrypted()<<DELIMITER<< GetMessage()<<DELIMITER<<m_rails;
    return railfence.str();
    
}