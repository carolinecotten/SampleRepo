#include "lliststring.h"
#include <cstdlib>
#include <stdexcept> // See the comment directly below.
#include <iostream>

/**
 * This implementation uses exceptions in both versions of 'get'. 
 * You do not need to change the if-statements that use exceptions, 
 * nor do you need to test for exceptions. 
 *
 * In case you are interested, you can find more information here:
 * http://www.cplusplus.com/doc/tutorial/exceptions/
 * 
 * We will cover exceptions later this semester. 
 */
using namespace std;
LListString::LListString()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LListString::~LListString()
{
  clear();
}

LListString::LListString (const LListString& other){
  //deep copy.. makes new LListString with same values as other
  this->size_=0; 

  for(int i = 0; i < other.size(); i++){
    this->insert(i, other.getNodeAt(i)->val);
  } 

}

LListString& LListString::operator= (const LListString& other){
  //clear all info
  clear(); 
  //copy constructor (essentially)
  this->size_=0; 

  for(int i = 0; i < other.size(); i++){
     this->insert(i, other.getNodeAt(i)->val); 
  }
  return *this; 
} 

LListString LListString::operator+ (const LListString& other) const{
  //returns a new list consisting of other appended to this.
  //does not modify this. 
  LListString newList =LListString(); 
  newList.size_=0;  

  for(int i = 0; i < this->size_; i++){
     newList.insert(i, this->getNodeAt(i)->val);
  } 
  int pos = this->size(); 
  //10 and 10
  //filled out this (0-9)
  //want to fill out 10 which is size, 11 is i+size
  for(int i = 0; i < other.size_; i++){
    newList.insert(i + pos, other.getNodeAt(i)->val); 
  }
  return newList; 
}


bool LListString::empty() const
{
  return (size_ == 0);
}

int LListString::size() const
{
  return size_;
}

void LListString::insert(int pos, const std::string& val)
{
  // TODO: complete the insert function.
  //checking for invalid
  if(pos > size_ + 1 || pos < 0){
    std::cout << "Invlaid position" << std::endl; 
  }
  //Insterting when empty
  else if(size_ == 0){
    Item* n  = new Item(val);
    n -> prev = NULL; 
    n -> next = NULL; 
    head_ = n; 
    tail_ = n; 
    size_++; 
  }
  //Inserting at beginning (update head)
  else if(pos == 0 && size_ > 0){
    Item* n = new Item(val);
    n -> prev = NULL; 
    n -> next = head_;
    head_ -> prev = n;  
    head_ = n; 
    size_++; 
  }
  //Inserting in middle (including tail)
  else if(pos > 0 && pos <= size_ - 1){
    Item* n = new Item(val); 
    n -> prev = getNodeAt(pos) -> prev; 
    n -> next = getNodeAt(pos); 
    getNodeAt(pos) -> prev = n; 
    getNodeAt(pos) -> prev -> prev -> next = n;
    size_++; 
  }
  //inserting at tail(end) (need to adjust size)
  else if(pos == size_){
    Item* n = new Item(val); 
    n -> prev = tail_; 
    n -> next = NULL; 
    tail_-> next = n; 
    tail_ = n; 
    size_++; 
  }
}

void LListString::remove(int pos)
{
  // TODO: complete the remove function.
  //removing when empty(head not equal to null)
  if(size_ == 0){
    std::cout << "Invalid operation, cannot remove when size == 0"; 
    std::cout << std::endl;
  }
  //removing beginning
  else if(pos == 0 && size_ > 1){
    head_ = head_ -> next; 
    delete head_ -> prev; 
    head_ -> prev = NULL; 
    size_--; 
  }
  //removing middle
  else if(pos > 0 && pos < size_ - 1){
    Item* temp = new Item("0");
    getNodeAt(pos) -> next -> prev = getNodeAt(pos) -> prev; 
    temp -> next = NULL; 
    temp -> prev = getNodeAt(pos); 
    getNodeAt(pos) -> prev -> next = getNodeAt(pos) -> next; 
    delete temp -> prev; 
    delete temp; 
    size_--; 
  }
  //removing tail
  else if(pos == size_ - 1 && size_ > 1){
    tail_ = getNodeAt(pos) -> prev; 
    delete tail_ -> next; 
    tail_ -> next = NULL; 
    size_--; 
  } 
  //removing when size == 1; 
  else if(size_ == 1 && pos == 0){
    delete getNodeAt(pos); 
    head_ = NULL; 
    tail_ = NULL; 
    size_--; 
  }
}

void LListString::set(int pos, const std::string& val)
{
  if(pos >= 0 && pos < size_) {
  	Item *temp = getNodeAt(pos);
    temp->val = val;	
  }
}

std::string& LListString::get(int pos)
{
  if(pos < 0 || pos >= size_) {
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(pos);
  return temp->val;
}

std::string const & LListString::get(int pos) const
{
  if(pos < 0 || pos >= size_) {
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(pos);
  return temp->val;
}

void LListString::clear(){
  while(head_ != NULL) {
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

LListString::Item* LListString::getNodeAt(int pos) const
{
  // TODO: complete the getNodeAt function.
  //retuns a pointer ti the i-th node
  //valid locations are 0-SIZE
  Item* p = head_; 
  for(int i = 0; i <= pos; i++){
    if(i == pos){
      return p; 
    }
      p = p -> next; 
  }
  return NULL;
}

