/*****************************************************************************
 ** File: Trivia.cpp
 ** Project: CMSC 202 Project 5, Spring 2022
 ** Author:  Aamil Vahora and CMSC202
 ** Date:    04/05/2022
 ** Email:   aamilv1@umbc.edu
 **
 Description: CPP file for Trivia class. Includes both class definition and
 class function definitions. Loads a file of trivia questions
*****************************************************************************/

#ifndef TRIVIA_CPP
#define TRIVIA_CPP
#include "Lqueue.cpp"
#include "Question.cpp"
#include <fstream>
#include <vector>
using namespace std;

const string DEFAULT_FILE = "proj5_string.txt";
const char DELIMITER = '|';

template <class T>
class Trivia {
public:
  // Name: Default Constructor
  // Desc: Displays the title, Loads Questions and calls menu
  // Indicates if the file was not loaded.
  // Precondition: None
  // Postcondition: User is prompted with assignment menus
  Trivia(string filename= DEFAULT_FILE);
  // Name: Destructor
  // Desc: Deallocates memory allocated for the Questions and
  // resets all variables.
  // Precondition: A Trivia exists.
  // Postcondition: All dynamically allocated memory in Trivia is deleted.
  ~Trivia();
  // Name: LoadQuestions
  // Desc: Each input file will be for a specific type of question (int, double, string)
  //       Reads in Questions from a file and stores them in anLqueue.
  //       An input file will be for exactly one type of question (int, double, string)
  // Precondition: None.
  // Postcondition: Returns true if file was read. Otherwise, it returns false.
  bool LoadQuestions(string filename);
  // Name: MainMenu
  // Desc: Presents user with menu options for showing subjects and allowing
  // user to work on a subject.
  // Precondition: None.
  // Postcondition: The main menu is presented.
  void MainMenu();
  // Name: DisplaySubjects
  // Desc: Presents all Subjects with corresponding numerical identifiers.
  // Precondition: Subjects have been added.
  // Postcondition: All assignments are printed to the screen.
  void DisplaySubjects();
  // Name: StartSubject
  // Desc: Starts working on a selected Subject.
  // Displays the number of questions in subject.
  // Starts at beginning and goes through each question.
  // After all questions have been answered:
  //       displays total correct, incorrect, and percentage correct
  // Precondition: m_questions has been populated
  // Postcondition: Returns to main menu
  void StartSubject();
  // Name: AddSubject
  // Desc: Checks to see if a subject exists in m_subjects.
  //       If not, inserts subject into m_subjects.
  // Precondition: A Subject exists.
  // Postcondition: Add subject to m_subjects if new subject.
  void AddSubject(string subject);
  // Name: ChooseSubject
  // Desc: Allows a user to choose one of the subjects to work on. Lists all subjects
  // in m_subjects and allows use to choose one. Returns value - 1 (location in vector)
  // Precondition: A Subject exists.
  // Postcondition: Returns value entered minus one
  int ChooseSubject();
  // Name: QuestionsPerSubject
  // Desc: Iterates over m_questions and counts how many questions match the subject
  // passed into function
  // Precondition: A Subject exists.
  // Postcondition: Returns number of questions of a particular subject
  int QuestionsPerSubject(string subject);
  // Name: DisplayTitle
  // Desc: Displays opening Welcome message
  // Precondition: None.
  // Postcondition: Title is displayed.
  void DisplayTitle();
private:
  Lqueue<Question<T>* >* m_questions; // Holds questions using a specific data type
  vector<string> m_subjects; //Populated as file is loaded
};

//**********Implement Trivia Class Here***********

// Name: Default Constructor

// Desc: Displays the title, Loads Questions and calls menu
// Indicates if the file was not loaded.
// Precondition: None
// Postcondition: User is prompted with assignment menus
template <class T>
Trivia<T>::Trivia(string filename){
  DisplayTitle();
  m_questions = new Lqueue<Question<T>* >;
  LoadQuestions(filename);
  MainMenu();


}


// Name: Destructor
// Desc: Deallocates memory allocated for the Questions and
// resets all variables.
// Precondition: A Trivia exists.
// Postcondition: All dynamically allocated memory in Trivia is deleted.
template <class T>
Trivia<T>::~Trivia(){
  // loops through the lqueue destroy allocated memory
  int size = m_questions->GetSize();
  for (int i =0; i< size; i++ ){
    delete m_questions->At(i);
    
  }
  delete m_questions;
  m_questions = nullptr;

  
}


// Name: LoadQuestions
// Desc: Each input file will be for a specific type of question (int, double, string)
//       Reads in Questions from a file and stores them in anLqueue.
//       An input file will be for exactly one type of question (int, double, string)
// Precondition: None.
// Postcondition: Returns true if file was read. Otherwise, it returns false.
template <class T>
bool Trivia<T>::LoadQuestions(string filename){
  // for load wuestion we will use Load Questions
  string subject;
  string question;
  string type;
  string difficulty;
  T answer;
  string var;
  Question<T>* object;
  bool flag = false;
  // this flag is used to see if the file was actually passed through
  ifstream myfile(filename);
  if (myfile.is_open()){
    // the loop loops throught the file and puts every thing into the object we created
    while (getline (myfile,subject, DELIMITER ) && getline (myfile,question, DELIMITER) &&
    getline(myfile,type, DELIMITER ) && getline(myfile, difficulty, DELIMITER) && myfile >> answer){
      // make sure to run after one run of the while loop and nnot give a seg fault
      getline(myfile,var);
      // flip flag here
      flag = true;

      AddSubject(subject);
      // creating an object using the quetsion constructor
      object = new Question(subject,question,type,stoi(difficulty),answer);
      // pushing it to the end of lqueue
      m_questions -> Push(object);

    }
    myfile.close();
  }
    if (flag == false){
    cout <<"could not load the file"<<endl;
  }else if (flag == true){
    cout <<"file sucsessfully loaded"<<endl;
  }
  // must return flag becuase return type is bool
  return flag;
}






// Name: MainMenu
// Desc: Presents user with menu options for showing subjects and allowing
// user to work on a subject.
// Precondition: None.
// Postcondition: The main menu is presented.
template <class T>
void Trivia<T>::MainMenu(){
  int choice=0;
  while (choice != 3){
    cout <<"Choose an option. "<<endl;
    cout <<1<<". Display Subjects"<<endl;
    cout <<2<<". Start Subject"<<endl;
    cout <<3<<". Quit"<<endl;
    cin>> choice;
    // below is input validtion
    while (cin.fail()|| choice > 3 || choice < 1){
      cin.clear();
      cin.ignore(256, '\n');
      cout <<"invalid entery enter a number between 1 and 3"<<endl;
      cin>>choice;
    }
    // switch case that loops through the given choices and calls the corect function
    switch(choice){
      case 1:
        DisplaySubjects();
        break;
      case 2:
        StartSubject();
        break;
      case 3:
        return;
    }

  }



}


// Name: DisplaySubjects
// Desc: Presents all Subjects with corresponding numerical identifiers.
// Precondition: Subjects have been added.
// Postcondition: All assignments are printed to the screen.
template <class T>
void Trivia<T>::DisplaySubjects(){
  // loops through the subjects and siaplays them ot the user
  int size = int(m_subjects.size());
  for (int i = 0; i < size; i++){
    cout <<i+1<<". "<<m_subjects.at(i)<<endl;
  }

}


// Name: StartSubject
// Desc: Starts working on a selected Subject.
// Displays the number of questions in subject.
// Starts at beginning and goes through each question.
// After all questions have been answered:
//       displays total correct, incorrect, and percentage correct
// Precondition: m_questions has been populated
// Postcondition: Returns to main menu
template <class T>
void Trivia<T>::StartSubject(){
  // count is used mainly for diaplys the subjects integers correctly
  double count =0;
  // question count is the overall count meaning the whole file itself
  int question_count = 0;
  // coreect increments only and only if the users answer is c oorect
  double correct =0;
  // incoreect increments only and only if the users answer is incoorect
  double incorrect = 0;
  int size = m_questions->GetSize();
  T answer;
  cout <<"What subject would you like to attempt?"<<endl;
  int choice = ChooseSubject();
  
  // questions gives us the amount of question per subject 
  int questions = QuestionsPerSubject(m_subjects[choice]);


  cout <<" There are "<< questions <<" questions in this subject."<<endl;


  while (question_count != size){
    // this condition makes sure that the subjects allign perfectly
    if (m_questions->At(question_count)->m_subject == m_subjects[choice]){
      cout <<count+1<<". "<<*m_questions->At(question_count)<<endl;
      cin>> answer;

      // this bool is used to chekc if the user answer is correct or not use a function from lqueue
      // and a fucntion form question
      bool flag = m_questions ->At(question_count)-> CheckAnswer(answer);
    
    
    
    
    if (flag == true){
      cout << "\033[1;32mcorrect\033[0m"<<endl;
      correct++;

    }else if (flag == false){
      cout << "\033[1;31mIncorrect\033[0m"<<endl;
      incorrect ++;
      cout <<"The correct answer was: "<<m_questions ->At(question_count)->m_answer<<endl;
    }
    count++;




    }    question_count++;
  }
    cout <<"You got "<<  int(correct) <<" answers correct."<<endl;
    cout <<"You got "<<  int(incorrect) <<" answers inocrrect"<<endl;
    cout <<"which is " << (correct/count)*100<<" %"<<endl;




}


// Name: AddSubject
// Desc: Checks to see if a subject exists in m_subjects.
//       If not, inserts subject into m_subjects.
// Precondition: A Subject exists.
// Postcondition: Add subject to m_subjects if new subject.
template <class T>
void Trivia<T>::AddSubject(string subject){
  bool flag = false;
  int size = int(m_subjects.size());
  for (int i =0; i <size; i++){
    // we cannot use pushback here or else it will do it multiple times which is why we use a flag
    if (subject == m_subjects.at(i)){
      flag = true;
    }
  }
  if (flag == false){
    // this pushes the subject back into our vector if it is not already in the linked list
    m_subjects.push_back(subject);
  }

}


// Name: ChooseSubject
// Desc: Allows a user to choose one of the subjects to work on. Lists all subjects
// in m_subjects and allows use to choose one. Returns value - 1 (location in vector)
// Precondition: A Subject exists.
// Postcondition: Returns value entered minus one
template <class T>
int Trivia<T>::ChooseSubject(){
  cout <<"Possible Subjects: "<<endl;
  DisplaySubjects();
  int choice;
  int size = int(m_subjects.size());
  cin>> choice;
  // input validation below
  while (choice<=0 || choice> size){
    cout <<"invalid entery try again"<<endl;
    cin>> choice;
  }
  // by doing chocie -1 it rturn the position in the vector
  return choice - 1;


}


// Name: QuestionsPerSubject
// Desc: Iterates over m_questions and counts how many questions match the subject
// passed into function
// Precondition: A Subject exists.
// Postcondition: Returns number of questions of a particular subject
template <class T>
int Trivia<T>::QuestionsPerSubject(string subject){
  int size =  m_questions->GetSize();
  int count = 0;
  for(int i =0; i<size; i++){
    if (subject == m_questions->At(i)->m_subject){
      // incrmeents count if the subjects match up
      count++;
    }
  }
  // returns our count
  return count;
}


// Name: DisplayTitle
// Desc: Displays opening Welcome message
// Precondition: None.
// Postcondition: Title is displayed.
template <class T>
void Trivia<T>::DisplayTitle(){
  // title for project
  cout <<"Welcome to UMBC Trivia!"<<endl;

}



#endif
