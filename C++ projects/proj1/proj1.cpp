/*
 File:        project1.cpp
 Author:      Aamil Vahora
 Date:        Feb/28/2022
 Section:     52
 E-mail:      aamilv1.username@umbc.edu
 Description: the code below plays wordles and loops 6 times until the user has guessed
 the right answer or 6 attempts.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

void main_loop();
int word_counter();
void load_words(string word_list[]);
string check_letter(string random_word, string user);
bool guess_word(int word_count, string list[], string input);

void play_again();

const char CORRECT = '!';
const char PARTIAL = '&';
const char INCORRECT = '-';


int main(){
    play_again();
    return 0;
}

void play_again(){
    /*
     this function doesnt hvae any oarameters but it allows me to be able
     to loop the code if the user waqnts the continue.
     */
    string play_again;
    cout << "welcome to wordle"<< endl;
    cout <<"OK. I am thinking of a 5-letter word"<<endl;
    srand(time(NULL));
    do{
        main_loop();
        cout <<"Another game? y/n"<<endl;
        cin>>play_again;
        if (play_again == "n"){
            cout <<"Thank you"<<endl;
        }
        
    }while(play_again != "n" or play_again == "y");
    
}


void main_loop(){
    string right_or_wrong;
    // right or_wrong is a tring that shows what leters are correct from the wordthrough symbols
    string array_of_inputs[6]= {"_____","_____","_____","_____","_____","_____"};
    string random_word;
    int random_num;
    bool if_found;
    string user_input;
    int word_count;
    int x = 0;
    
    word_count = word_counter();
    // word count allows me to intialize an array to teh size of any given file.
    
    string word_list[word_count];
    
    if (word_count>0){
        // this if statement is only ran through if any words are imported over into the array
        cout<<word_count<<" words imported"<<endl;
        cout <<"The file was Imported !!"<<endl;
        load_words(word_list);
        //cout<<word_list[2315]<<endl;
        
    }else{
        cout <<"unable to retrive file"<<endl;
    }
       
    // the clump of code underneath is what generates the random word everytime
    random_num = rand() % word_count + 0;
    random_word = word_list[random_num];
        
    while(x!=6){
        cout << "what would you like to guess: "<< endl;
        cin>> user_input;
        if_found  = guess_word( word_count, word_list, user_input);
        
        // if found is a boolen that is flipped to false if the word is found in the word list
        if (if_found == 0){
            
            // this if statement ends teh function if the user input is equal to the mystery word
            
            // array of input populates itself with the words the user inputs if they are valid
            array_of_inputs[x] = user_input;

            // this bit of code diplays the grid and if the word is correct
            for (int k=0; k<6;k++){
                cout <<array_of_inputs[k]<<endl;
                if (array_of_inputs[k] != "_____"){
                    right_or_wrong = check_letter(random_word, array_of_inputs[k]);
                    cout <<right_or_wrong<<endl;
                
                }
            }x+=1;
            
        }else if (if_found == 1){
            cout<< "invalid input"<<endl;
        }
        
        if (random_word == user_input){
            cout <<"Congrats you won!"<<endl;
            cout<<"the word was: "<<random_word<<endl;
            return;
        }
        
    }cout <<"you lost"<<endl;
    cout <<"correct word was: "<<random_word<<endl;
}


int word_counter(){
    /*
     param: none
     return: an integer representing the word count of the file
     */
    string word;
    int count = 0;
    ifstream myfile ("proj1_data.txt");
    if (myfile.is_open()){
        while (myfile>>word){
            count++;
        }
    }  return count;
}


void load_words(string list_of_word[]){
    /*
     param: array of strings
     return: void
     */
    string word;
    int count=0;
    ifstream myfile ("proj1_data.txt");
    if (myfile.is_open()){
        while (myfile>>word){
            // the array here is populated by words of the file
            list_of_word[count] = word;
            count++;
        }
    }
    
}
   
string check_letter(string mystery_word, string the_answer){
    /*
     param: the mystery word, the word we are looking for
     param: the user input
     return: string that shows what is right and worng in a string
     */
    
    string check = "-----";
    for (int i=0;i<5;i++){
        for (int j = 0; j<5; j++){
            if (mystery_word[i]== the_answer[j] and check[j] != CORRECT){
                if (i==j){
                    check[j] = CORRECT;
                }else{
                    check[j] = PARTIAL;
                }
            }
    }
        
    }
    return check;
}


bool guess_word(int word_count, string list[], string input){
    /*
     param: an integer of the word count
     param: an array of the words
     param: the user input
     return: a false boolen if a match is found and a true one if not.
     */
    int counter=0;
    bool flag = true;
    
    while(counter < word_count and flag){
        if (input == list[counter]){
            return false;
        }
        counter+=1;
    } return true;
}


