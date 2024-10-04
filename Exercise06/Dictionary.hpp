//
// Created by Ofek Avidan on 09/09/2022.
//

#ifndef EX6_OFEK_AVIDAN_DICTIONARY_HPP
#define EX6_OFEK_AVIDAN_DICTIONARY_HPP
#include <string>
#include "HashMap.hpp"

using std::string;

class InvalidKey : public std::invalid_argument {
public:
    /**
     * our default constructor. uses our "parent-class" method, with
     * an empty message.
     */
    InvalidKey () : std::invalid_argument ("") {}

    // todo - ask if we should inheritance publicly ?

    /**
     * our explicit constructor.  uses our "parent-class" method, with
     * the given message
     * @param message - our message we want to show while error.
     */
    explicit InvalidKey (const std::string &message):
    std::invalid_argument (message) {} //todo check with labsupport if OK
};


class Dictionary : public HashMap<string, string> {
public:
    using HashMap<std::string,std::string>::HashMap; // lab-support

    /**
     * the erase method we asked to implement.
     * gets a key and erase it from the Dictionary (which is type of Hashmap)
     * @param key - the key to erase
     * @return true if erased successfully, false otherwise.
     */
    bool erase(const string &key) override;

    /**
     * the update method we asked to implement.
     * gets two iterators (begin and end).
     * The operation will receive two iterators and
     * put all the members of the iterator into the dictionary
     * @tparam It - the type of the iterator
     * @param begin - begin iterator
     * @param end - end iterator
     */
    template<class It>
    void update(It begin, It end);
};

// See full documentation in the inner class
bool Dictionary::erase(const string &key) {
    if (!contains_key(key)) {
        throw InvalidKey("doesn't contain key you want to erase (Dict)");
    }
    return HashMap::erase(key);
}

// See full documentation in the inner class
template<class It>
void Dictionary::update(It begin, It end) {
    while(begin != end)
    {
        (*this)[(*begin).first] = (*begin).second;
        begin++;
    }
}


#endif //EX6_OFEK_AVIDAN_DICTIONARY_HPP
