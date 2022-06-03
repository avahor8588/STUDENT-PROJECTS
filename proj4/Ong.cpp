#include "Ong.h"

// Name: Ong (Default Constructor)
// Desc: Constructor to build an empty Ong Cipher
// Preconditions - None
// Postconditions - Creates a Ong cipher to be encrypted
Ong:: Ong(){

}


// Name: Ong (Overloaded Constructor)
// Desc: Constructor to build a populated Ong Cipher
// Preconditions - Pass it the message and isEncrypted
// Postconditions - Creates a Ong cipher to be encrypted
Ong::Ong(string message, bool isEncrypted):Cipher(message, isEncrypted){

}


// Name: Ong (Destructor)
// Desc: Destructor - Anything unique to Ong to delete?
// Preconditions - ~Ong exists
// Postconditions - Ong destroyed
Ong::~Ong(){

    // no memory needs to be deallocated becaus eno new memory was made

}


// Name: IsVowel (Helper function)
// Desc: Returns true if vowel, space, or punctuation
// Preconditions - Message exists
// Postconditions - Returns true or false as above
bool Ong::IsVowel(char charter){
    bool flag= false;
    char vowel_array[14] = {'a','e','i','o','u', 'A','E','I','O','U', ' ', '.', '(', ')'};
    for (int i =0; i<14; i++){
        if (vowel_array[i] == charter){
            flag = true;
        }

    }
    return flag;


}


// Name: Encrypt
// Desc: If vowel then vowel and dash displayed. dog = dong-o-gong
// If consonant then consonant and ong and dash displayed.
// Preconditions - Message exists
// Postconditions - Encrypts as above
void Ong::Encrypt(){
    bool my_bool;
    string word;
    string message = GetMessage();
    int size = int(message.size());
    for (int i =0; i < size; i++){
        my_bool = IsVowel(message[i]);
        if (my_bool == true){
            word = word + message[i];
            
        } else{
            // adds ong to the end of the word
            word = word + message[i] + ong;
            
        }// this statement acounts for the dashes
        if (i != (size -1) && message[i+1] != ' ' && message[i] != ' '){
            word += "-";
            
        }

        }
        // sets our new message to the word we created
        SetMessage(word);
    



}


// Name: Decrypt
// Desc: Removes the dashes and "ong" when necessary cong-a-tong = cat
// Double check words like "wrong" so that they work correctly!
// Preconditions - Message exists
// Postconditions - Original message is displayed
void Ong::Decrypt(){
    string word;

    string message = GetMessage();
    int size = int(message.size());
    for (int i =0; i < size; i++){
        if(message[i+1] =='o' && message[i+2] == 'n' && message[i+3] == 'g' && (IsVowel(message[i]))== false ){
            // adds the charecter to the word we created if there is an ong after
            word+= message[i];
            
        }else if (IsVowel(message[i]) == true){
            // this is an edge case i had to cover
            if (message[i] == 'o'){
                if (message[i+1] != 'n'){
                    word+= message[i];
                }
            }else{
                word+= message[i];
            }
    }
    SetMessage(word);
    }
        


}
    



// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (Ong in this case)
string Ong::ToString(){
    return "(Ong)";

}


// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - o, delimiter, isencrypted, delimiter,
//                  message, delimiter, blank are output
string Ong::FormatOutput(){
    stringstream ongawd;
    ongawd << "o"<< DELIMITER<< GetIsEncrypted()<<DELIMITER<< GetMessage()<< DELIMITER;
    return ongawd.str();
    
}