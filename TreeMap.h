#ifndef TREEMAP_H_INC
#define TREEMAP_H_INC

#include <iostream>
#include <string>
#include "SplayTree.h"
#include "KeyValuePair.h"

class TreeMap
{
    private:

    //the SplayTree of KeyValuePairs that makes up a TreeMap
    SplayTree<KeyValuePair> splay_tree;

    public:

    TreeMap()
    :
    splay_tree{}
    {
    }

    //inserts a new KeyValuePair into the SplayTree and then displays the
    //resulting tree as an in-order traversal
    void insert(std::string key, std::string value)
    {
        splay_tree.insert(KeyValuePair(key, value));
    }

    //returns the value associated with a given key if the key is present
    //in the SplayTree
    std::string get(std::string key)
    {
        //search for a KeyValuePair in the SplayTree which has the same key
        //as the key provided (the value associated with the key is
        //irrelevant, so we simply create a KeyValuePair with a value of 0)
        KeyValuePair kvp = splay_tree.find(KeyValuePair(key, "0"));

        if(kvp.get_key() == key)
        {
            return kvp.get_value();
        }
        else
        {
            return "Key not found!";
        }
    }

    //removes a KeyValuePair from the SplayTree (if found) and then displays the
    //resulting tree as an in-order traversal
    void remove(std::string key)
    {
        //search for a KeyValuePair in the SplayTree which has the same key
        //as the key provided (the value associated with the key is
        //irrelevant, so we simply create a KeyValuePair with a value of 0)
        splay_tree.remove(KeyValuePair(key, "0"));
    }

    //returns the in-order traversal of the SplayTree
    std::string get_serialization()
    {
        return splay_tree.serialize();
    }

};

#endif
