#include <iostream>
#include <cstdlib>
#include <deque>
#include <ctime>
#include <vector>

using namespace std;

class nAryInt{
private:
  const unsigned int base;
  // Digits stored with least significant digit first
  deque<unsigned int> digits;
  vector<bool> digitsUsed;

public:
  // Constructor from single digit
  nAryInt(unsigned int digit, unsigned int base): base(base){
    digitsUsed=vector<bool>(base,false);
    digitsUsed[digit-1]=true;
    digits.push_back(digit);
  }

  // Add an extra digit at the least significant place, shifting the existing
  void appendDigit(unsigned int digit){
    if(digit>=base){
      cout << "The digit to append must be smaller than the base number!" << endl;
      exit(0);
    }
    digits.push_front(digit);
    digitsUsed[digit-1]=true;
  }

  void removeDigit(){
    digitsUsed[digits.front()-1]=false;
    digits.pop_front();
    return;
  }

  // Check if some digit is already contained
  bool contains(unsigned int digit){
    return digitsUsed[digit-1];
  }
  
  // Check if divisible by some digit
  // Mimics the pencil-and-paper division method
  bool isDivisible(unsigned int digit){
    unsigned int remainder=0;
    for(auto i=digits.crbegin();i!=digits.rend();i++){
      remainder=(base*remainder+*i)%digit;
    }
    if(remainder!=0){
      return false;
    }
    return true;
  }

  unsigned int size(){
    return digits.size();
  }

  unsigned int getBase(){
    return base;
  }

  friend std::ostream& operator<< (std::ostream & out, nAryInt const& obj);
};

// Printing of nAryInt-objects
std::ostream& operator<< (std::ostream & out, nAryInt const& obj){
  for(auto i=obj.digits.crbegin();i!=obj.digits.rend();i++){
    out << *i << ", ";
  }
  return out;
}

// Recursive function to check possible digits to add
void expand(nAryInt &a){
  if(a.size()==a.getBase()-1){
    cout << a << endl;
    return;
  }
  for(unsigned int digit=1;digit<a.getBase();digit++){
    if(!a.contains(digit)){
      // Append the digit and expand further if it gives a feasible subsolution
      a.appendDigit(digit);
      if(a.isDivisible(a.size())){
        expand(a);
      }
      a.removeDigit();
    }
  }
  return;
}

int main(int argc, char* argv[]){
  if(argc!=2){
    cout << "The program expects as input the base number" << endl;
    exit(0);
  }
  unsigned int base=strtoul(argv[1],NULL,10);
  cout << "Polydivisible numbers in base " << base << ":" << endl;
  clock_t startTime=clock();
#pragma omp parallel for
  for(unsigned int i=1;i<base;i++){
    nAryInt a(i,base);
    expand(a);
  }
  clock_t endTime=clock();
  cout << "Answer computed in "
       << ((float)(endTime-startTime))/CLOCKS_PER_SEC << " seconds" << endl;
  return 0;
}
