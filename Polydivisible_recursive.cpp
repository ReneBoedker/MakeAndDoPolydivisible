#include <iostream>
#include <cstdlib>
#include <deque>
#include <chrono>

using namespace std;

class nAryInt{
private:
  const unsigned int base;
  deque<unsigned int> digits; // Digits stored with least significant digit first
  unsigned long digitsUsed; // bit i is 1 if digit i is used

public:
  // Constructor from single digit
  nAryInt(unsigned int digit, unsigned int base): base(base){
    digitsUsed = 1UL<<digit;
    digits.push_back(digit);
  }

  // appendDigit adds an extra digit at the least significant place, shifting the existing
  void appendDigit(unsigned int digit){
    if(digit>=base){
      cout << "The digit to append must be smaller than the base number!" << endl;
      exit(0);
    }
    digits.push_front(digit);
    digitsUsed |= 1UL<<digit;
  }

  void removeDigit(){
    digitsUsed &= ~(1UL<<digits.front());
    digits.pop_front();
    return;
  }

  // contain checks if digit d appears in digits
  bool contains(unsigned int d){
    return digitsUsed & 1UL<<d;
  }
  
  // Check if divisible by some digit
  // Mimics the pencil-and-paper division method
  unsigned int rem(unsigned int m){
    unsigned int r=0;
    for(auto i=digits.crbegin();i!=digits.rend();i++){
      r=(base*r + *i)%m;
    }
    return r;
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

  unsigned int mod = a.size()+1;
  
  unsigned int r = a.getBase()%mod;
  if(r!=0) {
	r*=a.rem(mod);
  }
	
  for(unsigned int digit=1;digit<a.getBase();digit++){
    if(a.contains(digit)){
	  continue;
	}

	if((r+digit)%mod!=0){
	  // Digit does not give zero remainder
	  continue;
	}
	
	// Append the digit and expand further
	a.appendDigit(digit);
	expand(a);
	a.removeDigit();
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
  
  auto startTime=chrono::steady_clock::now();
  
#pragma omp parallel for
  for(unsigned int i=1;i<base;i++){
    nAryInt a(i,base);
    expand(a);
  }
  
  auto endTime=chrono::steady_clock::now();
  cout << "Answer computed in "
       << chrono::duration_cast<chrono::milliseconds>(endTime-startTime).count()/1000.0
	   << " seconds" << endl;
  return 0;
}
