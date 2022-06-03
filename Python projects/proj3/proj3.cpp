//Name: Proj3.cpp
//Project: CMSC 202 Project 3, Spring 2022
//Author:  Aamil vahora
//Date:    2/22/2022
//Desc: thise links all the files together and runs naviagtor


#include "Navigator.h"
#include <iostream>
using namespace std;

int main (int argc, char* argv[]) {
  if (argc < 2)
    {
      cout << "You are missing a data file." << endl;
      cout << "Expected usage ./proj3 proj3_data.txt" << endl;
      cout << "File 1 should be a file with ports" << endl;
    }
  else
    {
      cout << endl << "***Navigator***" << endl << endl;
      Navigator S = Navigator(argv[1]);
      S.Start();
    }
  return 0;
}
