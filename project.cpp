#include <iostream>
#include <string>
#include <ctime>//* to calculate the time used as timestamp
#include <sstream>//* to convert to stringstream
#include <functional>//* for hash 
#include <fstream>//* for filehandling 

using namespace std;

struct Citizens{
    int id;
    string name;
    string address;
    string CNIC;
    int age;


    void inputCitizenData() {
        cout << "Enter ID: ";
        cin >> id;
        cin.ignore(); 
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Address: ";
        getline(cin, address);
        cout << "Enter CNIC: ";
        getline(cin, CNIC);
        cout << "Enter Age: ";
        cin >> age;
}

};

struct Voting {
    string voterCNIC;       
    string candidateCNIC;   

    void inputVotingData() {
        cout<<"Enter VoterCNIC: "<<endl;
        cin>>voterCNIC;
        cout<<"Enter CandidateCNIC: "<< endl;
        cin>>candidateCNIC;
    }
};

string calculateHash(int index, Citizens citizenData, Voting voteData, time_t timestamp, string prevhash, int BlockType) {
    stringstream ss;
    ss << index << timestamp << prevhash << BlockType;

    if (BlockType == 0) { //! REGISTRATION
        ss << citizenData.id << citizenData.name << citizenData.CNIC << citizenData.address << citizenData.age;
    } else if (BlockType == 1) { //! VOTING
        ss << voteData.voterCNIC << voteData.candidateCNIC;
    }

    string combinedData = ss.str();
    hash<string> hasher;
    size_t hashValue = hasher(combinedData);
    return to_string(hashValue);
}


struct block{
    
    enum BlockType{
        REGISTRATION,
        VOTING 
    };

    int Index;
    Citizens data;
    Voting voteData;
    time_t timestamp;
    string hash;
    string prevhash;
    BlockType type;
    block* next;

    block(){
        Index = 0;
        data.id = 0;
        data.name = "";
        data.address = "";
        data.CNIC = "";
        data.age = 0;
        voteData.candidateCNIC = "";
        voteData.voterCNIC = "";
        timestamp = time(0);
        hash = "";
        prevhash = "";
        type = REGISTRATION;
        next = NULL;
    }

    block(int idx, Citizens d, string prevHashVal) {
        Index = idx;
        data = d;
        timestamp = time(0);
        type = REGISTRATION;
        voteData = {};  // empty vote
        prevhash = prevHashVal;
        hash = calculateHash(Index, data, voteData, timestamp, prevhash, type);
        next = nullptr;
    }

    
    block(int idx, Voting v, string prevHashVal) {
        Index = idx;
        voteData = v;
        timestamp = time(0);
        type = VOTING;
        data = {};  // empty citizen data
        prevhash = prevHashVal;
        hash = calculateHash(Index, data, voteData, timestamp, prevhash, type);
        next = nullptr;
    }
};
 
class Blockchain{
    public:
    block* head;
    
};
int main() {
 
 
  return 0;
}