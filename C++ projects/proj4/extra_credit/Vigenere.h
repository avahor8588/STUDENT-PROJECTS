//Title: Vigenere.h
//Author: Aamil vahora
//Date: 4/1/2022
//Description: This is part of the Cipher Project in CMSC 202 @ UMBC

#ifndef VIGENERE_H
#define VIGENERE_H
#include "Cipher.h"
#include <istream>
#include <string>
using namespace std;

class Vigenere: public Cipher{
 public:
  // Name: Vigenere (Default Constructor)
  // Preconditions - None
  // Postconditions - Creates a RailFence cipher
  Vigenere();
  // Name: Vigenere (Overloaded Constructor)
  // Preconditions - Pass it the message, isEncrypted, and the key which is a string
  // Postconditions - Creates a Vigenere cipher to be encrypted
  Vigenere(string, bool, string);
  // Name: Vigenere (Destructor)
  // Desc: Destructor - Anything specific part ofVigenere to delete?
  // Preconditions - ~Vigenere exists
  // Postconditions - Vigenere destroyed
  ~Vigenere();
  // Name: Encrypt
  // Desc: letters are added together by thier asciee value and returns astring
  // Preconditions - Message exists
  // Postconditions - A single encrypted string is stored
  void Encrypt();
  // Name: Decrypt
  // Desc: the encryption is reversed
  // Preconditions - Message exists
  // Postconditions - The decrypted string is stored
  void Decrypt();
  // Name: ToString
  // Desc - A function that returns the string of the object type
  // Preconditions - The object exists
  // Postconditions - The subtype is returned (Vigenere in this case)
  string ToString();
  // Name: FormatOutput()
  // Desc - A function that returns the formatted output for Output function
  // Preconditions - The object exists (use stringstream)
  // Postconditions - r, delimiter, isencrypted, delimiter,
  //                  message, delimiter, m_rails are returned for output
  string FormatOutput();

  string GetKey();
private:
  string m_key; /// the key which is a string
};


#endif