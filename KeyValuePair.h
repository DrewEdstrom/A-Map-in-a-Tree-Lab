#ifndef KEYVALUEPAIR_H_INC
#define KEYVALUEPAIR_H_INC

#include <string>

class KeyValuePair
{
    private:

    //the key associated with a value
    std::string key;
    //the value associated with a key
    std::string value;

    public:

    //constructs a key value pair given a key and value
    KeyValuePair(std::string new_key, std::string new_value)
    :
    key{new_key},
    value{new_value}
    {
    }

    //determines if the object's key comes after another alphabetically
    bool operator >(KeyValuePair const&kvp) const
    {
        return key.compare(kvp.get_key()) > 0;
    }

    //determines if the object's key comes before another alphabetically
    bool operator <(KeyValuePair const&kvp) const
    {
        return key.compare(kvp.get_key()) < 0;
    }

    //determines if the object's key comes after another alphabetically or
    //is identical
    bool operator >=(KeyValuePair const&kvp) const
    {
        return key.compare(kvp.get_key()) >= 0;
    }

    //determines if the object's key comes before another alphabetically or
    //is identical
    bool operator <=(KeyValuePair const&kvp) const
    {
        return key.compare(kvp.get_key()) <= 0;
    }

    //determines if the object's key is identical to another
    bool operator ==(KeyValuePair const&kvp) const
    {
        return key.compare(kvp.get_key()) == 0;
    }

    //determines if the object's key is not identical to another
    bool operator !=(KeyValuePair const&kvp) const
    {
        return !(*this == kvp);
    }

    //change the key associated with a KeyValuePair
    inline void set_key(const std::string new_key)
    {
        key = new_key;
    }

    //returns the key associated with a KeyValuePair
    inline std::string get_key() const
    {
        return key;
    }

    //change the value associated with a KeyValuePair
    inline void set_value(const std::string new_value)
    {
        value = new_value;
    }

    //returns the value associated with a KeyValuePair
    inline std::string get_value() const
    {
        return value;
    }

    //allows for the easy output of a KeyValuePair
    inline std::string to_string() const
    {
        return key + ";" + value;
    }
};

#endif
