#include "stackstring.h"
#include "lliststring.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;
//helper functions
string adjust(string& line){
	string word = ""; 
	int headNum = 0; 
	int tailNum = 0; 
	for(unsigned int i = 0; i < line.length(); i++){
		if(line[i] >= 'a' && line[i] <= 'z'){
			word += line[i];
		} 
		else if(line[i] == '<'){	//remove end 
			tailNum++;
		}	
		else if(line[i] == '>'){	//remove head
			headNum++; 
		}	

	}
	if(headNum > 0){
		//adjust head
		word = word.substr(headNum);
	}
	if(tailNum > 0){
		//adjust tail
		word = word.substr(0, word.length() - tailNum); 
	}
	return word; 
}

string strMinus(string lhs, string rhs){
	int pos = lhs.find(rhs);
	if(pos >= 0){
		lhs.erase(pos, rhs.length());

		return lhs; 
	}
	else{
		return lhs; 
	}
}

string doOperations(StackString* myStack){
	stringstream ss;
	string line;
	string item1; 
	string item2;    
	bool end = false;
	string oper = ""; 

	while(!end){
		string operCheck;  
	 	item1 = myStack->top(); 
		myStack->pop(); 
		item2 = myStack->top();
		myStack->pop();
//****************MINUS******************//
		if(item2 == "-"){

			if(oper != ""){
				 operCheck = item2; 
				 if(oper != operCheck){
				 	return "Malformed"; 
				 }
			}
			else if(oper == ""){
				oper = item2; 
			} 
			string rhs = item1; 
			string lhs = ""; 
			//creaing lhs
			while(myStack->top() != "(" && myStack->top() != "+" && myStack->top() != "-" && !myStack->empty()){
				lhs = lhs + myStack->top(); 
				myStack->pop(); 
			}
			//adjusting rhs
			if(rhs.find('<') > 0 || rhs.find('>') > 0){
				//call adjust fxn
				rhs = adjust(rhs); 
			}

			//adjusting lhs
			if(lhs.find('<') > 0 || lhs.find('>') > 0){
				//call adjust fxn
				lhs = adjust(lhs); 
			}
			//doing operation
			line = strMinus(lhs, rhs); 
		}

//****************PLUS******************//
		else if(item2 == "+"){
			if(oper != ""){
				 operCheck = item2; 
				 if(oper != operCheck){
				 	return "Malformed"; 
				 }
			}
			else if(oper == ""){
				oper = item2; 
			} 

			string rhs = item1; 
			string lhs = ""; 

			//creating lhs
			while(myStack->top() != "(" && myStack->top() != "+" && myStack->top() != "-" && !myStack->empty()){
				lhs = lhs + myStack->top(); 
				myStack->pop(); 
			}

			//adjusting rhs
			if(rhs.find('<') > 0 || rhs.find('>') > 0){
				//call adjust fxn
				rhs = adjust(rhs); 
			}

			//adjusting lhs
			if(lhs.find('<') > 0 || lhs.find('>') > 0){
				//call adjust fxn
				lhs = adjust(lhs); 
			}
			//doing operation
			line = lhs + rhs;			
		}

//****************ADJUST******************//
		else{	//adjustments to string
			string word = item1 + item2;
			while(myStack->top() != "(" && myStack->top() != "+" && myStack->top() != "-" && !myStack->empty()){
				word = word + myStack->top(); 
				myStack->pop(); 
			}
			line = adjust(word); 
		}

//****************CHECKING FOR MORE OPERATIONS OR REMOVE ( ******************//
		//if mepty or if top is (, need ot exit while loop
		if(myStack->top() == "+" || myStack->top() == "-"){		
			myStack->push(line); 
		}

		else if(myStack->top() == "("){
			myStack->pop();
			end = true;  
		}

		else if(myStack->empty()){ 
			end = true; 
		}

	}
	return line; 
}


int main(int argc, char *argv[]){
 	StackString* myStack = new StackString;   
	ifstream inFile(argv[1]);
	ofstream outFile(argv[2]);
	string line; 
	string output = "";

	while (getline(inFile, line)){
		bool notMalformed = true;  
		if(line == "") {
			output += ""; 
		} 
		//check for malformities
		else if(line != ""){
			int pCount = 0; 
			for(unsigned int i = 0; i < line.length(); i++){
				if(line[i] == '(' || line[i] == ')'){
					pCount++; 
				}
			}
			if(pCount % 2 != 0){
				notMalformed = false; 
				output += "Malformed\n"; 
				while(!myStack->empty()){
						myStack->pop(); 
					}
			}
		} 
		//Parsing
		if(notMalformed && line != "\n"){
			for(unsigned int i = 0; i < line.length() ; i++){
			if(notMalformed){
			//for(unsigned int i = 0; i < line.length(); i++){
				string curr = "";
				if(line[i] == ' '){
					curr = line[i]; 
					//make sure to not add to stack
				}
				else if(line[i] == '(' || line[i] == '<' || line[i] == '>' || line[i] == '+' || line[i] == '-'){
					if(line[i] == '+' || line[i] == '-'){
						if(line[i + 1] == '('){
							output += "Malformed\n";
							notMalformed = false; 
							while(!myStack->empty()){
								myStack->pop(); 
							}

						}
						else{
							curr = line[i];
							myStack->push(curr); 
						}
					}
					else{
						curr = line[i];
						myStack->push(curr);
					}
				}
				else if(line[i] == ')'){
					//call do operation
					curr = doOperations(myStack);
					if(curr == "Malformed"){
						notMalformed = false; 
						output += "Malformed\n";
						while(!myStack->empty()){
							myStack->pop(); 
						}
					}
					//push adjusted string onto stack
					else{myStack->push(curr);} 
				}
				else if(line[i] >= 'a' && line[i] <= 'z'){
					while(line[i] >= 'a' && line[i] <= 'z'){
						curr += line[i]; 
						i++; 
					}
					myStack->push(curr); 
					i--;  
				}
				else if (line[i] >= 'A' && line[i] <= 'Z'){
					notMalformed = false; 
					output += "Malformed\n";
					line = "";  
					while(!myStack->empty()){
						myStack->pop(); 
					}
				} 
			}
			}
			}//done parsing line

		//Cheick if need to parse again or done
		if(notMalformed){
			line = myStack->top(); 
			myStack->pop(); 
			if(!myStack->empty()){
				myStack->push(line);
				line = doOperations(myStack); 
			}

			//output to file 
			if(myStack->empty()){ 
				myStack->push(line); 
				myStack->pop();
				output += line + "\n"; 
			}		
		}
		
	}//while
	
	outFile << output; 

	delete myStack; 
	return 0; 
}