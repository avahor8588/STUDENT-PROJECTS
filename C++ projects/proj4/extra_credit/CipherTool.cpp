#include "CipherTool.h"

// Name: CipherTool Constructor
// Desc - Creates a new CipherTool and sets m_filename based on string passed
// Preconditions - Input file passed and populated with Cipher
// Postconditions - CipherTool created
CipherTool::CipherTool(string file){

    // this allows nfor use to pass in different files
    m_filename  = file;

}


// Name: CipherTool Destructor
// Desc - Calls destructor for all ciphers in m_ciphers
// Preconditions - m_ciphers is populated
// Postconditions - m_ciphers deallocated and vector emptied
CipherTool::~CipherTool(){
    for (int i =0; i< int(m_ciphers.size()); i++){

        // deallocate the memory that we had used se there are no leaks
        delete m_ciphers[i];
        m_ciphers[i] = nullptr;

    }
    cout <<"Thanks for using UMBC Encryption"<<endl;

}


// Name: LoadFile
// Desc - Opens file and reads in each Cipher. Each Cipher dynamically allocated
// and put into m_ciphers (c is Caesar, r is RailFence, and o is Ong)
// Preconditions - Input file passed and populated with Ciphers
// Postconditions - m_ciphers populated with Ciphers
void CipherTool::LoadFile(){
    string encrypt;
    string message;
    string type;
    string key;
    Cipher* cipher;
    ifstream myfile(m_filename);
    if (myfile.is_open()){
        // this loops reads in all of the messages from the files
        while (getline(myfile,type, DELIMITER ) && getline(myfile,encrypt, DELIMITER) &&
        getline(myfile,message, DELIMITER ) && getline(myfile,key, '\n')){

            bool encrypted = StringToBoolean(encrypt);

            // for ceaser
            if(type == "c"){
                cipher = new Caesar(message, encrypted, stoi(key));
            }
            // for railfence
            if (type == "r"){
                cipher =  new RailFence(message,encrypted,stoi(key));
            }
            // for ong
            if (type == "o"){
                cipher =  new Ong(message,encrypted);
            }
            if (type == "v"){
                cipher =  new Vigenere(message,encrypted,key);
            }
            // we populate our vector here
            m_ciphers.push_back(cipher);
        }



    }




}


// Name: StringToBoolean
// Desc - Helper function that converts a string to a boolean for reading in file
// Preconditions - Passed string of either 0 or 1
// Postconditions - Returns false if 0 else true
bool CipherTool::StringToBoolean(string input){
    if (input == "1"){
        return true;

    }
    return false;

}


// Name: DisplayCiphers
// Desc - Displays each of the ciphers in the m_ciphers
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - Displays ciphers
void CipherTool::DisplayCiphers(){
    int size = m_ciphers.size();
    for (int i = 0; i <size; i++){
        // using function from our child classes since we declared which classes we use in the load file
        // we can use functions with the same names and they will call on the correct ones from each different class
        cout <<i+1 << ". "<<*m_ciphers[i]<<endl;
        cout <<"\n"<<endl;



    }

}


// Name: EncryptDecrypt
// Desc - Encrypts or decrypts each of the ciphers in the m_ciphers
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - Either Encrypts or Decrypts each cipher in m_ciphers
void CipherTool::EncryptDecrypt(bool flag){
    string word;
    int count =0;
    int count_two = 0;
        for (int i =0; i< int(m_ciphers.size()); i++){
            // this is if the cipher is not encryoted and needs to be
            if (flag == 0 && !m_ciphers.at(i)->GetIsEncrypted()){
                count ++;
                m_ciphers.at(i)->Encrypt();
                cout <<i+1 << ". "<<*m_ciphers[i]<<endl;
                cout <<"\n"<<endl;
                m_ciphers.at(i)->ToggleEncrypted();

            }


            // this is if the cipher is encrypted and needs to be dycrpted
            else if (flag == 1 && m_ciphers.at(i)->GetIsEncrypted()){
                count_two++;
                m_ciphers.at(i)->Decrypt();
                cout <<i+1 << ". "<<*m_ciphers[i]<<endl;
                cout <<"\n"<<endl;
                m_ciphers.at(i)->ToggleEncrypted();

            }
            
            
            // this statements goes over is something is given to use pre drycrpted
            else{
                cout <<i+1 << ". "<<*m_ciphers[i]<<endl;
                cout <<"\n"<<endl;
            }


        }
        if (flag == 0){
            cout << count<< " ciphers encrypted"<<endl;
        }else if (flag == 1){
            cout << count_two << " ciphers dycypted"<<endl;

        }


}
    


        







// Name: Export
// Desc - Exports each of the ciphers in the m_ciphers (so they can be reused)
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - All ciphers exported
void CipherTool::Export(){
    int count  =0;
    string input;
    cout <<"What would you like to call the export file?"<<endl;
    cin >>input;
    // this means out stream which allows us to create files
    ofstream myfile(input);
    for (int i =0; i< int(m_ciphers.size()); i++){

         myfile<<m_ciphers.at(i)->FormatOutput()<<" " <<m_ciphers[i]->ToString()<<endl;
         count ++;
    }
    cout << count <<" ciphers exported to "<<input<<endl;




}


// Name: Menu
// Desc - Displays menu and returns choice
// Preconditions - m_ciphers all populated
// Postconditions - Returns choice
int CipherTool::Menu(){
    int choice;
    cout << 1<<".Display All Ciphers "<<endl;
    cout << 2<<".Encrypt All Ciphers "<<endl;
    cout << 3<<".Decrypt All Ciphers "<<endl;
    cout << 4<<".Export All Ciphers "<<endl;
    cout <<"5.Quit"<<endl;
    cin >> choice;
    return choice;
}


// Name: Start
// Desc - Loads input file, allows user to choose what to do
// Preconditions - m_ciphers populated with ciphers
// Postconditions - none
void CipherTool::Start(){
    int choice=0;
    LoadFile();
    while (choice != 5){
        choice = Menu();
        while (cin.fail() || choice > 5 || choice < 1){
            cout <<"\n"<<endl;
            cin.clear();
            cin.ignore(256, '\n');
            cout <<"invalid entery choose a number betwwen 1-5"<<endl;
            choice = Menu();
            }

        switch (choice){
            case 1:
                DisplayCiphers();
                break;
            case 2:
                // this encrypts it if the boolean is false
                EncryptDecrypt(false);
                break;
            case 3:
            // this dycrypts it if the boolean is true
                EncryptDecrypt(true);
                break;
            case 4:
                Export();
                break;
            case 5:
                // loop stops if 5 is chosen
                return;

            }
    }

}