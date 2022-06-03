#include "Vigenere.h"

  Vigenere::Vigenere(){

  }
  // Name: Vigenere (Overloaded Constructor)
  // Desc: Constructor to build a populated RailFence Cipher (Defaults to 3 rails)
  // Preconditions - Pass it the message, isEncrypted, and number of rails (any integer)
  // Postconditions - Creates a RailFence cipher to be encrypted

  Vigenere::Vigenere(string message , bool encypted, string key): Cipher(message,encypted){
      m_key = key;

  }

  // Name: RailFence (Destructor)
  // Desc: Destructor - Anything specific part of RailFence to delete?
  // Preconditions - ~RailFence exists
  // Postconditions - RailFence destroyed

  Vigenere::~Vigenere(){

  }


  // Name: Encrypt
  // Desc: Letters are placed on a fence rail based on the number of rails
  //       Letters are read from one rail at a time into a single string
  // Preconditions - Message exists
  // Postconditions - A single encrypted string is stored
  void Vigenere::Encrypt(){
    string word = GetMessage();
    string new_key = GetKey();
    string output;
    int count= 0;
    
    // the for loop that will hold all of the code
    for (int i = 0; i< int(word.size()); i++){
        // creating the charecters for key and the message
        char letter = word[i];
        char key = new_key[count];
        
        // this will account for the lower case latters
        if (letter <= 'z' && letter >= 'a'){
            // this line of code sets the letter and key to its alphabet value
            // it mods it by 26 if its over ot get back in alphabet order
            letter = ((letter - 'a') + (tolower(key) -'a')) % 26;
            // puts it back in asci value by adding 'a'
            letter += 'a';
        
        // acoount for lowercase
        }else if (letter <= 'Z' && letter >= 'A'){
            letter = ((letter - 'A') + (toupper(key) -'A')) % 26;
            
            letter += 'A';
            
            
            
        }else{
            count --;
        }
        count++;
        output += letter;
    }
    SetMessage(output);
    
    

  }


  // Name: Decrypt
  // Desc: Single encrypted string is pushed back on the rails and reversed
  // Preconditions - Message exists
  // Postconditions - The decrypted string is stored
  void Vigenere::Decrypt(){
    string word = GetMessage();
    string output;
    string new_key = GetKey();
    int count= 0;
    
    // the for loop that will hold all of the code
    for (int i = 0; i< int(word.size()); i++){
        // creating the charecters for key and the message
        char letter = word[i];
        char key = new_key[count];
        
        // this will account for the lower case latters
        if (letter <= 'z' && letter >= 'a'){
            // this line of code sets the letter and key to its alphabet value
            // it add 26 so its  positive and  mods it by 26 if its over ot get back in alphabet order
            letter = ((letter- 'a') - (tolower(key) -'a')) +26;
            letter = letter % 26;
            // puts it back in asci value by adding 'a'
            letter += 'a';
        
        // acoount for lowercase
        }else if (letter <= 'Z' && letter >= 'A'){
            letter = ((letter - 'A') - (toupper(key) -'A')) +26;
            letter = letter % 26;
            letter += 'A';
            
            
            
        }else{
            count --;
        }
        count++;
        output += letter;
    }
    SetMessage(output);
    
    
  }


  // Name: ToString
  // Desc - A function that returns the string of the object type
  // Preconditions - The object exists
  // Postconditions - The subtype is returned (RailFence in this case)
  string Vigenere::ToString(){
      return("(Vigenere)");

  }



  // Name: FormatOutput()
  // Desc - A function that returns the formatted output for Output function
  // Preconditions - The object exists (use stringstream)
  // Postconditions - r, delimiter, isencrypted, delimiter,
  //                  message, delimiter, m_rails are returned for output
  string Vigenere::FormatOutput(){
    stringstream vig;
    vig << "c"<< DELIMITER<< GetIsEncrypted()<<DELIMITER<< GetMessage()<< DELIMITER<<m_key;
    return vig.str();

  }

  string Vigenere::GetKey(){
      string new_key;
      string word =GetMessage();
    if (word.size() > m_key.size()){
        int num = word.size () - m_key.size();
        for (int i = 0; i< num;i++){
            m_key += m_key[i];
    }
        for (int i = 0; i< int(m_key.size()); i++){
            new_key.push_back(m_key[i]);
        }
        
    }else if (word.size() < m_key.size()){
        for (int i =0; i< int(word.size()); i++){
            new_key += m_key[i];
            
        }
    }
    // set the key and new_key equal to the same thing
    new_key = m_key;
    return new_key;

      
  }