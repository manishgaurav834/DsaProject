#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

long long pow_mod_calc(long long x, long long i, long long m) {
    long long result = 1;
    x %= m; 
    while (i > 0) {
        if (i % 2 == 1) {
            result = (result * x) % m;
        }
        x = (x * x) % m;
        i /= 2;
    }

    return result;
}

class PhoneRecord {
private:
    string name;
    string organisation;
    vector<string> phoneNumbers;

public:
    // Constructor
    PhoneRecord(const string& n, const string& org, const vector<string>& numbers)
        : name(n), organisation(org), phoneNumbers(numbers) {}

    // Getter methods
    string getName() const {
        return name;
    }

    string getOrganisation() const {
        return organisation;
    }

    vector<string> getPhoneNumbers() const {
        return phoneNumbers;
    }
};

class HashTableRecord {
private:
    int key;
    PhoneRecord* element; // Pointer to PhoneRecord
    HashTableRecord* next;

public:
    // Constructor
    HashTableRecord(int k, PhoneRecord* rec)
        : key(k), element(rec), next(nullptr) {}

    // Getter methods
    int getKey() const {
        return key;
    }

    PhoneRecord* getRecord() const {
        return element;
    }

    HashTableRecord* getNext() const {
        return next;
    }

    void setNext(HashTableRecord* nxt) {
        next = nxt;
    }
};

class PhoneBook {
private:
    static const int HASH_TABLE_SIZE = 263;
    HashTableRecord* hashTable[HASH_TABLE_SIZE];

public:
    // Constructor
    PhoneBook() {
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            hashTable[i] = nullptr;
        }
    }

    // Add your own implementation for hashing
    long long computeHash(const string& str){
        long long hashvalue = 0;
      
        for(int i=0;i<str.size();i++){
            
            hashvalue=hashvalue + ((int)str[i]*(pow_mod_calc(263,i,1000000007)));
        }
        
        return hashvalue % HASH_TABLE_SIZE;
    }

    // Add your own implementation for adding a contact
    void addContact( PhoneRecord* record){
        stringstream sname(record->getName());
        string word;
        while(getline(sname,word,' ')){
           int k=computeHash(word);
         
           HashTableRecord* obj= new HashTableRecord(k,record);
          
            if(hashTable[k]==nullptr){
                hashTable[k]=obj;
               
            }
            else{
              
            HashTableRecord* trav=hashTable[k];
            while(trav->getNext()!=nullptr){
                trav=trav->getNext();
            }
            trav->setNext(obj);
            
             
           }
         
           

        }
        

    }

   

    // Add your own implementation for fetching contacts
    vector<PhoneRecord*> fetchContacts(const string* query){
        stringstream ss(*query);
        string word;
        map<PhoneRecord*,int> sorter ;
       
        while(getline(ss,word,' ')){
            int k=computeHash(word);
            HashTableRecord* trav=hashTable[k];
           
            while(trav!=nullptr){
               
                stringstream ss1(trav->getRecord()->getName());
                string word1;int c=0;
                while(getline(ss1,word1,' ')){
                    if(word1 == word){
                        c++;
                        break;
                    }
                }
               
                if(c>0){
                    sorter[trav->getRecord()]++;
                    if(trav->getRecord()->getName()==*query){
                    sorter[trav->getRecord()]+=1000;
                    }
            }
                trav = trav->getNext();
                  
            }
        }
        
        multimap<int,PhoneRecord*> sorter1;
        for(auto it:sorter){
         
            sorter1.insert({it.second,it.first});
        }
       
        vector<PhoneRecord*> result;
        for(auto it:sorter1){
            result.insert(result.begin(),it.second);
        }
       
        return result;




    }
     // Add your own implementation for deleting a contact
    bool deleteContact(const string* searchName){
        stringstream ss1(*searchName);
        int c=0;string word1;
        while(getline(ss1,word1,' ')){
            c++;
        }
       

        vector<PhoneRecord*> fetched=fetchContacts(searchName);
        if(fetched.empty()){
           return false;
        }
        PhoneRecord* obj=fetched[0];
        if(c>1 && fetched[0]->getName()!=*searchName){
            return false;
        }
        stringstream ss(fetched[0]->getName());
        string word;
       
        while(getline(ss,word,' ')){
            
            int k=computeHash(word);
          
            HashTableRecord* trav=hashTable[k];
            if(trav->getRecord()==fetched[0]){
                hashTable[k]=trav->getNext();
                trav->setNext(nullptr);
            }
            HashTableRecord* prev=trav;
            while(trav->getRecord()!=fetched[0]){
                prev=trav;
                trav=trav->getNext();
            }
           
            prev->setNext(trav->getNext());
            trav->setNext(nullptr);
            delete trav;
        }
        
        return true;

    }

    // Add your own implementation for counting records pointing to a contact
    int countRecordsPointingTo(const PhoneRecord* record) {
        stringstream ss(record->getName());
        string word;int count=0;
        while(getline(ss,word,' ')){
            int key=computeHash(word);
            HashTableRecord* trav=hashTable[key];
            while(trav!=nullptr){
                if(trav->getRecord()==record){
                    count++;
                    break;
                }
            }
        }
        return count;


    }

    // Add your own implementation for reading records from a file
    void readRecordsFromFile(const string& filename){
        ifstream in(filename);
        string line,name,organisation="0",word;
        vector <string> numbers;
        while(getline(in,line)){
            organisation="0";
           stringstream ss(line);
          
           getline(ss,name,',');
          
           while(organisation=="0"){
           getline(ss,word,',');
           if(word[0]>=48 && word[0]<=57){
            numbers.push_back(word);
          
           }
           else{
            organisation=word;
          

           }
          
           }
           
           PhoneRecord* pr_obj=new PhoneRecord(name,organisation,numbers);
          
           addContact(pr_obj);  
         
        }
        
    
   
    }

    // Destructor
    //~PhoneBook();
};

// int main() {
//     PhoneBook phone_book;
//     phone_book.readRecordsFromFile("Details_new.txt");

//     std::vector<PhoneRecord> new_contacts = {
//         PhoneRecord("John", "Benz", {"1111111111"}),
//         PhoneRecord("Atreya", "Tata", {"2222222222"})
//     };

//     std::ofstream resultFile("test_results.txt", std::ios::app);

//     for (PhoneRecord& contact : new_contacts) {
//         phone_book.addContact(&contact);
//     }

//     bool allAdded = true;

//     for (const PhoneRecord& contact : new_contacts) {
//         std::vector<PhoneRecord*> contacts = phone_book.fetchContacts(new std::string(contact.getName()));

//         bool found = false;

//         for (PhoneRecord* record : contacts) {
//             if (record->getName() == contact.getName()) {
//                 found = true;
//                 break;
//             }
//         }

//         if (!found) {
//             allAdded = false;
//             break;
//         }
//     }

//     if (allAdded) {
//         std::cout << "test_add_multiple_contacts: Passed" << std::endl;
//         resultFile << "passed, test_add_multiple_contacts" << std::endl;
//     } else {
//         std::cerr << "test_add_multiple_contacts: Failed" << std::endl;
//         resultFile << "failed, test_add_multiple_contacts" << std::endl;
//     }

//     resultFile.close();

//     return 0;
// }

