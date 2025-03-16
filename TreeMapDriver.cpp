#include <iostream>
#include "TreeMap.h"

using namespace std;

int main()
{
    TreeMap map;

    //insertions
    cout << "\n\nA series of insertions are now being performed."
            << "\n\n\nInserting 1...";
    map.insert("0", "1");
    cout << "\n\nTreeMap following insertion: " << map.get_serialization();
    cout << "\n\nSearching for value associated with key 0 yields: " 
            << map.get("0");
    cout << "\n\nTreeMap following search: " << map.get_serialization();

    cout << "\n\n\nInserting 2...";
    map.insert("1", "2");
    cout << "\n\nTreeMap following insertion: " << map.get_serialization();
    cout << "\n\nSearching for value associated with key 1 yields: " 
            << map.get("1");
    cout << "\n\nTreeMap following search: " << map.get_serialization();

    cout << "\n\n\nInserting 3...";
    map.insert("2", "3");
    cout << "\n\nTreeMap following insertion: " << map.get_serialization();
    cout << "\n\nSearching for value associated with key 2 yields: " 
            << map.get("2");
    cout << "\n\nTreeMap following search: " << map.get_serialization();

    cout << "\n\n\nInserting 4...";
    map.insert("3", "4");
    cout << "\n\nTreeMap following insertion: " << map.get_serialization();
    cout << "\n\nSearching for value associated with key 3 yields: " 
            << map.get("3");
    cout << "\n\nTreeMap following search: " << map.get_serialization();

    cout << "\n\n\nInserting 5...";
    map.insert("4", "5");
    cout << "\n\nTreeMap following insertion: " << map.get_serialization();
    cout << "\n\nSearching for value associated with key 4 yields: " 
            << map.get("4");
    cout << "\n\nTreeMap following search: " << map.get_serialization();
    
    //removals
    cout << "\n\n\n\nA series of removals are now being performed."
            << "\n\n\nRemoving key 2...";
    map.remove("2");
    cout << "\n\nTreeMap following removal: " << map.get_serialization();
    cout << "\n\nSearching for value associated with key 2 yields: " 
            << map.get("2");
    cout << "\n\nTreeMap following search: " << map.get_serialization();

    cout << "\n\n\nRemoving key 4...";
    map.remove("4");
    cout << "\n\nTreeMap following removal: " << map.get_serialization();
    cout << "\n\nSearching for value associated with key 4 yields: " 
            << map.get("4");
    cout << "\n\nTreeMap following search: " << map.get_serialization();

    cout << "\n\n\nRemoving key 3...";
    map.remove("3");
    cout << "\n\nTreeMap following removal: " << map.get_serialization();
    cout << "\n\nSearching for value associated with key 3 yields: " 
            << map.get("3");
    cout << "\n\nTreeMap following search: " << map.get_serialization();

    cout << "\n\n\nRemoving key -2...";
    map.remove("-2");
    cout << "\n\nTreeMap following removal: " << map.get_serialization();
    cout << "\n\nSearching for value associated with key -2 yields: " 
            << map.get("-2");
    cout << "\n\nTreeMap following search: " << map.get_serialization()
            << "\n\n";

    return 0;
}
