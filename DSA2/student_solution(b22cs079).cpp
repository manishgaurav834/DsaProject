#include <bits/stdc++.h>
#include<fstream>
#include<sstream>
using namespace std;

class StudentRecord{
private:
    string studentName;
    string rollNumber;
public:
    string get_studentName() {
        return studentName;
    }
    void set_studentName(string Name) {
        studentName = Name;
    }
    string get_rollNumber() {
        return rollNumber;
    }
    void set_rollNumber(string rollnum) {
        rollNumber = rollnum;
    }
};

class Node{
	private:
		Node* next;
		StudentRecord* element;
	public:
        Node* get_next() {
	        return next; 
	    }
	    StudentRecord* get_element() {
	        return element; 
	    }

	    void set_next(Node* value){
	    	next = value;
	    }
	    void set_element(StudentRecord* student){
	    	element = student;
	    }

};

class Entity {
  private:
    string name;
    Node* iterator;
  public:
    string get_name() {
        return name;
    }
    void set_name(string Name) {
        name = Name;
    }
    Node* get_iterator() {
        return iterator;
    }
    void set_iterator(Node* iter) {
        iterator = iter;
    }
};

vector<StudentRecord> students;
class LinkedList : public Entity {
   public:
        void add_student(StudentRecord student){
          
            Node* node=new Node();
            Node* it=get_iterator();
            StudentRecord *obj=new StudentRecord();
            obj->set_studentName(student.get_studentName());
            obj->set_rollNumber(student.get_rollNumber());
            node->set_element(obj);
            node->set_next(NULL);
            while(it->get_next()!=nullptr){
                it=it->get_next();
            }
            it->set_next(node);
        }

        void delete_student(string studentName){
            
            Node* curr = get_iterator();
            Node* prev = nullptr;
            while(curr->get_element()->get_studentName()!=studentName){
                prev = curr;
                curr = curr -> get_next();
            }
            if(curr!=get_iterator()){ 
            prev -> set_next(curr->get_next());
            curr -> set_next(nullptr);
            }
            else{
                set_iterator(curr->get_next());
                curr->set_next(nullptr);
            }
        }

};

vector<LinkedList> EntityArray;

bool has_student(vector<StudentRecord> v,string name,string roll){
    
    for(int i=0;i<v.size();i++){
        if(name==v[i].get_studentName() && roll==v[i].get_rollNumber()){
            return true;
            
        }

        
    }
    return false;
}

bool has_entity(vector<LinkedList> v,string entity){
    
    for(int i=0;i<v.size();i++){
        if(entity==v[i].get_name()){
            return true;
        }

    }
    return false;
}

void create(vector<LinkedList>v,string word,StudentRecord* obj){

    if(!has_entity(EntityArray,word)){
            LinkedList myl;
            Node* node=new Node();
            node->set_element(obj);
            node->set_next(NULL);
            myl.set_name(word);
            myl.set_iterator(node);
            EntityArray.push_back(myl);
        }

        else{
            for(auto it:EntityArray){
                if(word==it.get_name()){
               
                it.add_student(*obj);
                }
            }
        }
}

void read_input_file(string file_path){
    ifstream in(file_path);
    string line,word;
    int c=0;
    
    //Counting no. of students in file and reserving size for vector students.
    if(in.is_open()){
    while(getline(in,line)){
        c++;
       }
    }
    else{
        cout<<"Error: File not openened"<<endl;
    }
    in.close();
    students.reserve(c);
    
    ifstream ip(file_path);
    if(ip.is_open()){
    
    while(getline(ip,line)){
        
        stringstream ss(line);
        //Reading name.
        getline(ss,word,',');
        string name=word;
        //Reading rollno.
        getline(ss,word,',');
        
        //Checking for duplicates.
        if(!has_student(students,name,word)){
            StudentRecord*obj=new StudentRecord();
            obj->set_studentName(name);
            obj->set_rollNumber(word);
            students.push_back(*obj);

            //Reading department and then adding in linkedlist for that department. 
            getline(ss,word,',');
            create(EntityArray,word,obj);
           
            //Reading courses and then adding in linkedlist for that course.
            string word1;
            getline(ss,word1,'[');
            getline(ss,word1,']');
            stringstream sss(word1);
        
            while(getline(sss,word,',')){
               create(EntityArray,word,obj);

            }
            
            //Removing the leftover comma , reading hostel and adding to the linked list of that hostel.
            getline(ss,word1,',');
            getline(ss,word,',');
            create(EntityArray,word,obj);
        
            //Removing the "[]" and reading the club and add to the linked list of that club.
            getline(ss,word1,'[');
            getline(ss,word1,']');
       
            stringstream ss1(word1);
       
            while(getline(ss1,word,',')){
              create(EntityArray,word,obj);
            }
        }
       
       }
     }
    }

