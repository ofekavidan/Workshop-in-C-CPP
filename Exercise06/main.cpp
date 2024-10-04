#include "LinkedList.h"
#include <iostream>
#include <algorithm>


int main() {
    
    LinkedList l;

    for(int i=0; i<10; i++)
        l.push(i);

    l.erase(9); //first
    l.erase(5); // middle
    l.erase(0); // last
    
    // range based for loop, requires iterators
    for(auto item : l)
        std::cout << item << std::endl;
    
    // find returns an iterator
    auto it = std::find(l.begin(),l.end(),3);
    if (it != l.end()) {
        std::cout << "found 3 in the list!" << std::endl;
    } else {
      std::cout << "no 3 in the list!" << std::endl;
    }

}
