#include <iostream>
#include <cstdlib>
#include <deque>
#include <ctime>

using namespace std;

class nAryInt{
private:
  const unsigned int base;
  // Digits stored with least significant digit first
  deque<unsigned int> digits;

public:
  // Constructor from single digit
  nAryInt(unsigned int digit, unsigned int base): base(base){
    digits.push_back(digit);
  }

  // Constructor from given deque of digits
  nAryInt(deque<unsigned int> &digitsToCopy,unsigned int base): base(base){
    digits.assign(digitsToCopy.begin(),digitsToCopy.end());
  }

  // Add an extra digit at the least significant place, shifting the existing
  nAryInt appendDigit(unsigned int digit){
    if(digit>=base){
      cout << "The digit to append must be smaller than the base number!" << endl;
      exit(0);
    }
    // Copy the deque and return nAryInt with added digit
    deque<unsigned int> temp(digits.begin(),digits.end());
    temp.push_front(digit);
    return nAryInt(temp,base);
  }

  // Check if some digit is already contained
  bool contains(unsigned int digit){
    if(digit>=base){
      cout << "The digit to append must be smaller than the base number!" << endl;
      exit(0);
    }
    for(auto i=digits.begin();i!=digits.end();i++){
      if(*i==digit){
        return true;
      }
    }
    return false;
  }
  
  // Check if divisible by some digit
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
void expand(nAryInt a){
  if(a.size()==a.getBase()-1){
    cout << a << endl;
    return;
  }
  for(unsigned int digit=1;digit<a.getBase();digit++){
    if(!a.contains(digit) && a.appendDigit(digit).isDivisible(a.size()+1)){
      expand(a.appendDigit(digit));
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
    expand(nAryInt(i,base));
  }
  clock_t endTime=clock();
  cout << "Answer computed in "
       << ((float)(endTime-startTime))/CLOCKS_PER_SEC << " seconds" << endl;
  return 0;
}
