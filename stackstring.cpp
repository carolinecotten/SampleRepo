#include "stackstring.h"
#include "lliststring.h"
#include <iostream>

using namespace std; 

StackString::StackString(){
	//do we do anything?  
}

StackString::~StackString(){
	
}

bool StackString::empty() const{
	//returns true if empty
	if(list.size() == 0){
		return true; 
	}
	else return false; 
}

void StackString::push(const string& val){
	list.insert(list.size(), val); 
}

string const & StackString::top () const{
	if(list.size() == 0){
		cout << "Error: stack is empty" << endl;  
		return ""; 
	}
	else{
		return list.get(list.size()-1);
	}
}

void StackString::pop(){
	if(list.size() != 0){
		list.remove(list.size()-1);
	}
}


