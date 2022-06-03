#ifndef LQUEUE_CPP
#define LQUEUE_CPP
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//Templated node class used in templated linked list
template <class T>
class Node {
   public:
  Node( const T& data ); //Constructor
  T& GetData(); //Gets data from node
  void SetData( const T& data ); //Sets data in node
  Node<T>* GetNext(); //Gets next pointer
  void SetNext( Node<T>* next ); //Sets next pointer
private:
  T m_data;
  Node<T>* m_next;
};

//Overloaded constructor for Node
template <class T>
Node<T>::Node( const T& data ) {
   m_data = data;
   m_next = NULL;
}

//Returns the data from a Node
template <class T>
T& Node<T>::GetData() {
   return m_data;
}

//Sets the data in a Node
template <class T>
void Node<T>::SetData( const T& data ) {
   m_data = data;
}

//Gets the pointer to the next Node
template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

//Sets the next Node
template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

template <class T>
 class Lqueue {
 public:
  // Name: Lqueue() (Linked List Queue) - Default Constructor
  // Desc: Used to build a new linked queue (as a linked list)
  // Preconditions: None
  // Postconditions: Creates a new lqueue where m_head and m_tail point to nullptr
  // Required
  Lqueue();

  // Name: ~Lqueue() - Destructor
  // Desc: Used to destruct a Lqueue
  // Preconditions: There is an existing lqueue with at least one node
  // Postconditions: An lqueue is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
  // Required
 ~Lqueue();


  // Name: Lqueue (Copy Constructor)
  // Preconditions: Creates a copy of existing LQueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  // Required
  Lqueue(const Lqueue& Lque);


  // Name: operator= (Overloaded Assignment Operator)
  // Preconditions: Copies an Lqueue into an existing Lqueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  // Required
  Lqueue<T>& operator= (Lqueue&);


  // Name: Push
  // Preconditions: Takes in data. Creates new node. 
  //                Requires a Lqueue
  // Postconditions: Adds a new node to the end of the lqueue.
  // Required
  void Push(const T& data);


  // Name: Pop
  // Preconditions: Lqueue with at least one node. 
  // Postconditions: Removes first node in the lqueue, returns data from first node.
  // Required
  T Pop();


  // Name: Display
  // Preconditions: Outputs the lqueue.
  // Postconditions: Displays the data in each node of lqueue
  // Required (used only for testing)
  void Display();


  // Name: Front
  // Preconditions: Requires a populated lqueue
  // Postconditions: Returns whatever data is in front
  // Required
  T Front();


  // Name: IsEmpty
  // Preconditions: Requires a lqueue
  // Postconditions: Returns if the lqueue is empty.
  // Required
  bool IsEmpty();


  // Name: GetSize
  // Preconditions: Requires a lqueue
  // Postconditions: Returns m_size
  // Required
  int GetSize();


  // Name: Find()
  // Preconditions: Requires a lqueue
  // Postconditions: Iterates and if it finds the thing, returns index, else -1
  // Required
  int Find(T&);


  // Name: Swap(int)
  // Preconditions: Requires a lqueue
  // Postconditions: Swaps the nodes at the index with the node prior to it.
  // Required
  void Swap(int);


  // Name: Clear
  // Preconditions: Requires a lqueue
  // Postconditions: Removes all nodes in a lqueue
  // Required
  void Clear();


  // Name: At
  // Precondition: Existing Lqueue
  // Postcondition: Returns object from Lqueue at a specific location
  // Desc: Iterates to node x and returns data from Lqueue
  // Required
  T At (int x);


private:
  Node <T> *m_head; //Node pointer for the head
  Node <T> *m_tail; //Node pointer for the tail
  int m_size; //Number of nodes in queue
};

//**********Implement Lqueue Class Here***********
//**********All Functions Are Required Even If Not Used for Trivia**************
template <class T>
Lqueue<T>::Lqueue() {
   // sets the intial values of the lqueue
   m_head = nullptr;
   m_tail = nullptr;
   m_size =0;

}
// Name: ~Lqueue() - Destructor
// Desc: Used to destruct a Lqueue
// Preconditions: There is an existing lqueue with at least one node
// Postconditions: An lqueue is deallocated (including dynamically allocated nodes)
//                 to have no memory leaks!
// Required
template <class T>
Lqueue<T>::~Lqueue(){
   // the clear function deallocates all memeory
   Clear();
   delete m_head;
   m_head = nullptr;
   delete m_tail;
   m_tail = nullptr;

}




// Name: Lqueue (Copy Constructor)
// Preconditions: Creates a copy of existing LQueue
//                Requires a Lqueue
// Postconditions: Copy of existing Lqueue
// Required
template <class T>
Lqueue<T>::Lqueue(const Lqueue& other){
   cout << "Copy Constructor Called"<<endl;
   // all we do here is we create a copy of the lqueue that we already have
   if (other.m_head == nullptr){
      m_head= nullptr;
      m_tail = nullptr;

   }else{
      // allocate memory for a new node
      m_head =  new Node<T>(other.m_head->GetData());
      Node<T>* curr = m_head;
      Node<T>* Othercurr = other.m_head;


      while (Othercurr->GetNext() != nullptr){
         curr->SetNext(new Node<T>(Othercurr->GetNext()->GetData()));
         curr = curr ->GetNext();
         Othercurr = Othercurr->GetNext();


   }
   m_tail = curr;
   m_size = other.m_size;

   }


}



// Name: operator= (Overloaded Assignment Operator)
// Preconditions: Copies an Lqueue into an existing Lqueue
//                Requires a Lqueue
// Postconditions: Copy of existing Lqueue
// Required
template <class T>
Lqueue<T>& Lqueue<T>::operator= (Lqueue& other){
   cout <<"Assigment operater fired"<<endl;
   if (other.m_head == nullptr){
      // we fist need to clear and eallocate all given memory
      Clear();
      m_head= nullptr;
      m_tail = nullptr;

   }else{
      // then we just copy what we did in tyhe default constructor
      m_head =  new Node<T>(other.m_head->GetData());
      Node<T>* curr = m_head;
      Node<T>* Othercurr = other.m_head;


      while (Othercurr->GetNext() != nullptr){
         curr->SetNext(new Node<T>(Othercurr->GetNext()->GetData()));
         curr = curr ->GetNext();
         Othercurr = Othercurr->GetNext();


   }
   m_tail = curr;
   m_size = other.m_size;

   }return *this;


}


  // Name: Push
  // Preconditions: Takes in data. Creates new node. 
  //                Requires a Lqueue
  // Postconditions: Adds a new node to the end of the lqueue.
  // Required
template <class T>
void Lqueue<T>::Push(const T& data){
   // this adds the data to the end of the linekd list
   Node<T> *temp = new Node<T>(data);
   temp -> SetNext(NULL);
   if (m_head == nullptr){
      m_head = temp;
      m_tail = temp;

   }else{
      // adds to the end of the linked list here
      m_tail->SetNext(temp);
      m_tail = temp;


   }m_size++;

}

// Name: Pop
// Preconditions: Lqueue with at least one node. 
// Postconditions: Removes first node in the lqueue, returns data from first node.
// Required
template <class T>
T Lqueue<T>::Pop(){

    // Move the head pointer to the next node
    Node<T>* temp = m_head;
    if(temp != nullptr){
      m_head = m_head->GetNext();
 
      delete temp;
      m_size --;
 
      return m_head->GetData();

   }return m_head->GetData();
}

// Name: Display
// Preconditions: Outputs the lqueue.
// Postconditions: Displays the data in each node of lqueue
// Required (used only for testing)
template <class T>
void Lqueue<T>::Display(){
   if (m_size  == 0 ){
      // if the isze of the list is empty
        cout << "linked list doesnt exist"<<endl;
        return;
    }else{
        Node<T>* temp = m_head;
        int count  = 1;
        while(temp != nullptr){
           // this loops to the end of the link list
            cout << temp ->GetData()<<"->";
            // sets temp to the next thing in the linked list
            temp  = temp -> GetNext();
            count ++;
        }
        cout<<"END"<<endl;


    }

}

// Name: Front
// Preconditions: Requires a populated lqueue
// Postconditions: Returns whatever data is in front
// Required
template <class T>
T Lqueue<T>::Front(){
   // gets the data stored at the fornt of the linked list
   return m_head ->GetData();
  

}


// Name: IsEmpty
// Preconditions: Requires a lqueue
// Postconditions: Returns if the lqueue is empty.
// Required
template <class T>
bool Lqueue<T>::IsEmpty(){
   Node<T>* temp = m_head;
   if (temp == nullptr){
      return true;
      // returns true if the function is actually empty
   }return false;

}


// Name: GetSize
// Preconditions: Requires a lqueue
// Postconditions: Returns m_size
// Required
template <class T>
int Lqueue<T>::GetSize(){
   // returns the size of lqueue
   return m_size;


}


// Name: Find()
// Preconditions: Requires a lqueue
// Postconditions: Iterates and if it finds the thing, returns index, else -1
// Required
template <class T>
int Lqueue<T>::Find(T& thing){
   for (int i =0; i < m_size; i++){
      // search if the thing we wnat is in the linked list
      if(At(i) == thing){
         return i;
      }
   }return -1;
   



}


// Name: Swap(int)
// Preconditions: Requires a lqueue
// Postconditions: Swaps the nodes at the index with the node prior to it.
// Required
template <class T>
void Lqueue<T>::Swap(int index){
   Node<T>* curr = m_head;
   Node<T>* prev = m_head;
   Node<T>* sec_prev = m_head;
   int count =0;

   // make sure the index is in the range
   if (index > 0 && index <m_size){
      // checks the beginig of the lqueue
      if (index == 1){
         m_head = m_head->GetNext();
      }


      
      
      // middle and end
      while(count != index){
         // loops until curr matches index then retrurn curr
         sec_prev = prev;
         prev = curr;
         curr = curr -> GetNext();
         count ++;
      }
      sec_prev ->SetNext(curr);
      prev->SetNext(curr -> GetNext());
      curr ->SetNext(prev);

      // accounts for the end of the lqueue
      if (index == m_size){
         m_tail = m_tail->GetNext();
      }
   }
   return;

}


// Name: Clear
// Preconditions: Requires a lqueue
// Postconditions: Removes all nodes in a lqueue
// Required
template <class T>
void Lqueue<T>::Clear(){
   // baisccally a destructur
   Node<T>* curr = m_head;
   while (curr != nullptr){
      m_head = curr;
      curr  =  curr->GetNext();
      // deltes m_head
      delete m_head;
    }
   // destroys m_head and m_tail
   m_head = nullptr;
   m_tail = nullptr;
   m_size = 0;

}


// Name: At
// Precondition: Existing Lqueue
// Postcondition: Returns object from Lqueue at a specific location
// Desc: Iterates to node x and returns data from Lqueue
// Required
template <class T>
T Lqueue<T>::At(int index){
   int count = 0;
   Node<T>* curr = m_head;
   while(count != index){
      // loops until curr matches index then retrurn curr
      curr = curr -> GetNext();
      count ++;

        
   }
   // returns the correct data type
   return curr->GetData();

    

}






#endif
