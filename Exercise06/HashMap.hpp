//
// Created by Ofek Avidan on 09/09/2022.
//

#ifndef EX6_OFEK_AVIDAN_HASHMAP_HPP
#define EX6_OFEK_AVIDAN_HASHMAP_HPP

#include <vector>
#include <stdexcept>
#include <algorithm>
#include <cmath>

#define FIRST_CAPACITY 16
#define UPPER_THRESHOLD 0.75
#define LOWER_THRESHOLD 0.25
#define VECS_ERROR "no match between key-vector length to val-vector length"
#define INVALID_KEY "doesn't contain the gotten key"
#define CAPACITY_LOWER_THRESHOLD 1


using std::vector;


template<class KeyT, class ValueT>
class HashMap {
private:
    typedef vector<std::pair<KeyT, ValueT>> Bucket;
    Bucket *_buckets;
    int _size, _capacity;
public:

    class ConstIterator;

    /**
     * the default constructor.
     * initialize an empty HashMap.
     */
    HashMap();

    /**
     * A constructor that gets two vectors,
     * one containing values of KeyT and
     * one that contains values of ValueT and
     * saves the values in the map in order.
     */
    HashMap(const vector<KeyT> &key_vec, const vector<ValueT> &val_vec);

    /**
     * our copy-constructor
     */
    HashMap(const HashMap<KeyT, ValueT> &rhs);

    /**
     * our destructor.
     */
    virtual ~HashMap();

    /**
     * a size getter.
     * @return the amount of elements of the map.
     */
    int size() const;

    /**
     * a capacity getter.
     * @return the capacity the map.
     */
    int capacity() const;

    /**
     * this method checks if the map is empty.
     * @return true if the map is empty, false otherwise.
     */
    bool empty() const;

    /**
     * A method that receives a key and a value,
     * and saves the The resulting mapping.
     * @param key - the key we want to insert
     * @param val - the value we want to insert
     * @return true if the value isn't exist, and added successfully
     * false otherwise.
     */
    bool insert(const KeyT &key, const ValueT &val);

    /**
     * The method receives a key
     * and checks whether it is exists on the map
     * @param key - the key we want to check (if exist)
     * @return
     */
    bool contains_key(const KeyT &key) const;

    /**
     * this method gets a key
     * and returns its appropriate value
     * @param key - key
     * @return value if the key does exist, throw an exception if doesn't
     */
    ValueT &at(const KeyT &key);

    /**
     * this method gets a key
     * and returns its appropriate value
     * @param key - key
     * @return value if the key does exist, throw an exception if doesn't
     */
    const ValueT &at(const KeyT &key) const;

    /**
     * The method receives a key and
     * returns the value associated with it from the map
     * @param key - key
     * @return true if the value erased successfully,
     * false otherwise
     */
    virtual bool erase(const KeyT &key);

    /**
     * this method returns the load factor
     * @return the load factor
     */
    double get_load_factor() const;

    /**
     * this method gets a key,
     * and returns the size of the Bucket.
     * @param key - key
     * @return the size of the Bucket. if the key isn't exist,
     * the method will throw an exception.
     */
    int bucket_size(const KeyT &key) const;

    /**
     * this method gets a key,
     * and returns the index of the Bucket.
     * @param key - key
     * @return the index of the Bucket. if the key isn't exist,
     * the method will throw an exception.
     */
    int bucket_index(const KeyT &key) const;

    /**
     * this method removes all the elements on the map
     * it doesn't change the capacity
     */
    void clear();

    /*******************************************/
    /** iterator - complete!!!!!!!!!!!!!!!!!! **/
    /*******************************************/


    /**
     * our copy assignment
     * @param rhs - the "right" HashMap
     * @return the "right" HashMap, after assignment the "left" one.
     */
    HashMap<KeyT, ValueT> &operator=(const HashMap<KeyT, ValueT> &rhs);

    /**
     * a "subscript" operator
     * this operator gets a key, and returns the value at [key]
     * shouldn't throw an exception here!
     * @param key - key
     * @return value at [key] on the HashMap
     */
    ValueT &operator[](const KeyT &key);

    /**
     * a "subscript" operator
     * this operator gets a key, and returns the value at [key]
     * shouldn't throw an exception here!
     * @param key - key
     * @return value at [key] on the HashMap
     */
    const ValueT &operator[](const KeyT &key) const;

    /**
     * this operator compares between two HashMaps
     * @param rhs - the "right" HashMap
     * @return true if all the elements are equal, false otherwise
     */
    bool operator==(const HashMap<KeyT, ValueT> &rhs) const;

    /**
     * this operator compares between two HashMaps
     * @param rhs - the "right" HashMap
     * @return false if one element isn't equal, true otherwise
     */
    bool operator!=(const HashMap<KeyT, ValueT> &rhs) const;

private:

    /**
     * this function gets a key and returns the appropriate index in our array
     * to "hash" the key in.
     * @param key - key
     * @return the appropriate index in our array
     * to "hash" the key in.
     */
    int hash(const KeyT &key) const;

    /**
     * this function gets a bool (increase) and updates our size and capacity
     * @param increase - bool. true = increase the capacity
     * false = decrease the capacity
     * @return
     */
    bool update_size(bool increase);

public:
    using const_iterator = ConstIterator;

    /**
     * this function returns a pointer (iterator) to the beginning of the
     * hashmap, as a const.
     * @return a pointer (iterator) to the beginning of the
     * hashmap, as a const.
     */
    const_iterator cbegin () const
    {
        return ConstIterator(*this, true);
    }

    /**
     * this function returns a pointer (iterator) to the end of the
     * hashmap, as a const.
     * @return a pointer (iterator) to the end of the
     * hashmap, as a const.
     */
    const_iterator cend () const
    {
        return ConstIterator(*this, false);
    }

    /**
     * this function returns a pointer (iterator) to the beginning of the
     * hashmap, as a const.
     * @return a pointer (iterator) to the beginning of the
     * hashmap, as a const.
     */
    const_iterator begin () const
    {
        return cbegin ();
    }

    /**
     * this function returns a pointer (iterator) to the end of the
     * hashmap, as a const.
     * @return a pointer (iterator) to the end of the
     * hashmap, as a const.
     */
    const_iterator end () const
    {
        return cend ();
    }
};

/**********************************************************************/
/***************************** implementing ***************************/
/**********************************************************************/

// See full documentation in the inner class
template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>::HashMap(): _buckets(), _size(0),
_capacity(FIRST_CAPACITY)       {
    _buckets = new Bucket[FIRST_CAPACITY];
}

// See full documentation in the inner class
template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>::HashMap(const vector<KeyT> &key_vec,
                               const vector<ValueT> &val_vec): HashMap() {

    _buckets = new Bucket[FIRST_CAPACITY];
    if (key_vec.size() != val_vec.size()) {
        throw std::length_error(VECS_ERROR);
    }


    for (int i = 0; i < (int)key_vec.size(); ++i) {
        if (contains_key(key_vec[i])) {
            //If there are duplicate key values - then you must overwrite
            // the old values with the new ones.
            int index = hash(key_vec[i]);
            for (auto &element: _buckets[index]) {
                if (element.first == key_vec[i]) {
                    element.second = val_vec[i];
                }
            }
        } else {
            // if the key isn't appear, hence we don't want to overwrite
            insert(key_vec[i], val_vec[i]);
        }

    }
}

// See full documentation in the inner class
template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>::HashMap(const HashMap<KeyT, ValueT> &rhs) {
    _buckets = nullptr;
    (*this) = rhs;
}

// See full documentation in the inner class
template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>::~HashMap() {
    delete[] _buckets;
}

// See full documentation in the inner class
template<class KeyT, class ValueT>
int HashMap<KeyT, ValueT>::size() const {
    return _size;
}

// See full documentation in the inner class
template<class KeyT, class ValueT>
int HashMap<KeyT, ValueT>::capacity() const {
    return _capacity;
}

// See full documentation in the inner class
template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::empty() const {
    return _size == 0;
}

// See full documentation in the inner class
template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::insert(const KeyT &key, const ValueT &val) {
    // check if contains key
    if (contains_key(key)) {
        return false;
    }

    // get Bucket index from hash func
    int index = hash(key);
    // push back to Bucket at the index
    std::pair<KeyT, ValueT> element = {key, val};
    _buckets[index].push_back(element);

    // check load factor and resize accordingly
    _size++;
    if (get_load_factor() > UPPER_THRESHOLD) {
        if (update_size(true)) {
            return true;
        }
        _size--;
        return false;
    }
    return true;
}

// See full documentation in the inner class
template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::contains_key(const KeyT &key) const {
    int index = hash(key);
    Bucket &tmp = _buckets[index];
    for (const auto &element: tmp) {
        if (element.first == key) {
            return true;
        }
    }
    return false;
}

// See full documentation in the inner class
template<class KeyT, class ValueT>
ValueT &HashMap<KeyT, ValueT>::at(const KeyT &key) {
    if (!contains_key(key)) {
        throw std::invalid_argument(INVALID_KEY);
    }
    int index = hash(key);
    Bucket &tmp = _buckets[index];
    for (auto& element: tmp) {
        if (element.first == key) {
            return element.second;
        }
    }
    throw std::invalid_argument(INVALID_KEY);
}

// See full documentation in the inner class
template<class KeyT, class ValueT>
const ValueT &HashMap<KeyT, ValueT>::at(const KeyT &key) const {
    if (!contains_key(key)) {
        throw std::invalid_argument(INVALID_KEY);
    }
    int index = hash(key);
    Bucket &tmp = _buckets[index];
    for (const auto &element: tmp) {
        if (element.first == key) {
            return element.second;
        }
    }
    throw std::invalid_argument(INVALID_KEY);
}

// See full documentation in the inner class
template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::erase(const KeyT &key) {
    if (!contains_key(key)) {
        return false;
    }
    int index = hash(key);
    Bucket &tmp = _buckets[index];
    ValueT &val = at(key);
    std::pair<KeyT, ValueT> element(key, val);

    tmp.erase(std::find(tmp.begin(), tmp.end(), element));

    _size--;


    if (get_load_factor() < LOWER_THRESHOLD) {
        if (update_size(false)) {
            return true;
        }
        _size++;
        return false;
    }

    return true;
}

// See full documentation in the inner class
template<class KeyT, class ValueT>
double HashMap<KeyT, ValueT>::get_load_factor() const {
    return ((float) _size / (float) _capacity);
}

// See full documentation in the inner class
template<class KeyT, class ValueT>
int HashMap<KeyT, ValueT>::bucket_size(const KeyT &key) const {
    if (!contains_key(key)) {
        throw std::invalid_argument(INVALID_KEY);
    }
    int index = hash(key);
    Bucket &tmp = _buckets[index];
    return tmp.size();
}

// See full documentation in the inner class
template<class KeyT, class ValueT>
int HashMap<KeyT, ValueT>::bucket_index(const KeyT &key) const {
    if (!contains_key(key)) {
        throw std::invalid_argument(INVALID_KEY);
    }
    int index = hash(key);
    return index;
}

// See full documentation in the inner class
template<class KeyT, class ValueT>
void HashMap<KeyT, ValueT>::clear() {
    for (int i = 0; i < _capacity; ++i) {
        _buckets[i].clear();
    }
    _size = 0;
}

// See full documentation in the inner class
template<class KeyT, class ValueT>
int HashMap<KeyT, ValueT>::hash(const KeyT &key) const {
    int x = std::hash<KeyT>{}(key);
    return x & (_capacity - 1);
}

// See full documentation in the inner class
template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::update_size(bool increase) {
    int new_capacity = _capacity * 2;
    if (!increase) {
        while(((float) _size / (float) new_capacity) < LOWER_THRESHOLD)
        {
            new_capacity = (new_capacity / 2);
        }
        if(new_capacity < 1)
        {
            new_capacity = 1;
        }
    }

    Bucket* tmp = new Bucket[new_capacity];
    if (!tmp) {
        return false;
    }
    int old_capacity = _capacity;
    _capacity = new_capacity;
    // todo maybe use iterator
    for (int i = 0; i < old_capacity; ++i) {
        for (auto& element: _buckets[i]) {
            tmp[hash(element.first)].push_back(element);
        }
    }
    delete[] _buckets;
    _buckets = tmp;


    return true;
}

// copy assignment
// See full documentation in the inner class
template<class KeyT, class ValueT>
HashMap<KeyT, ValueT> &
HashMap<KeyT, ValueT>::operator=(const HashMap<KeyT, ValueT> &rhs) {
    if (this == &rhs) {
        return *this;
    }

    delete[] _buckets;


    _buckets = new Bucket[rhs._capacity];
    _capacity = rhs._capacity;
    _size = rhs._size;

    for (int i = 0; i < _capacity; ++i) {
        (*this)._buckets[i] = rhs._buckets[i];
    }
    return *this;
}

// See full documentation in the inner class
template<class KeyT, class ValueT>
ValueT &HashMap<KeyT, ValueT>::operator[](const KeyT &key) {
    int index = hash(key);
    Bucket &tmp = _buckets[index];
    for (auto &element: tmp) {
        if (element.first == key) {
            return element.second;
        }
    }
    this->insert(key, ValueT()); // buckets[non_existing_key] = value;
    return at(key);
}

// See full documentation in the inner class
template<class KeyT, class ValueT>
const ValueT &HashMap<KeyT, ValueT>::operator[](const KeyT &key) const {
    int index = hash(key);
    Bucket &tmp = _buckets[index];
    for (const auto &element: tmp) {
        if (element.first == key) {
            return element.second;
        }
    }
    // buckets[non_existing_key] = value;
    throw std::invalid_argument("non existing key");
}

// See full documentation in the inner class
template<class KeyT, class ValueT>
bool
HashMap<KeyT, ValueT>::operator==(const HashMap<KeyT, ValueT> &rhs) const {

    if (_size != rhs._size) {
        return false;
    }
    for (const auto& element : *this){
            if (!rhs.contains_key(element.first) ||
            element.second != rhs.at(element.first)) {
                return false;
            }
    }
    return true;
}

// See full documentation in the inner class
template<class KeyT, class ValueT>
bool
HashMap<KeyT, ValueT>::operator!=(const HashMap<KeyT, ValueT> &rhs) const {
    return !((*this) == rhs);
}


template<class KeyT, class ValueT>
class HashMap<KeyT, ValueT>::ConstIterator {
    typedef std::pair<KeyT, ValueT> value_type;
    typedef const value_type &reference;
    typedef const value_type *pointer;
    typedef ptrdiff_t difference_type;
    typedef std::forward_iterator_tag iterator_category;

private:
    const HashMap<KeyT, ValueT> &hash_map;
    int bucket_index, within_bucket_index;
public:

        /**
         * our explicit Iterator constructor. gets a hashmap to "iterate",
         * and a bool (tells if we want to be at the begin of the iterator).
         * @param hash_map - hashmap we want to "iterate"
         * @param begin - if true - we want to be at the begin of the
         * iterator. false otherwise.
         */
    explicit ConstIterator(const HashMap<KeyT, ValueT> & hash_map, bool begin)
            : hash_map(hash_map) {
        if (!begin) {
            bucket_index = hash_map._capacity;
            within_bucket_index = 0;
            return;
        }
        for (int i = 0; i < hash_map._capacity; i++) {
            if (!hash_map._buckets[i].empty()) {
                bucket_index = i;
                within_bucket_index = 0;
                return;
            }
        }
        bucket_index = hash_map._capacity;
        within_bucket_index = 0;

    }

    /**
     * another constructor of the Iterator. this time,
     * we'll get a bucket index and within bucket index to start from.
     * (the other constructor initialize those fields with 0.
     * @param hash_map - the hashmap we want to "iterate"
     * @param bucket_index - the bucket index we want to start from.
     * @param within_bucket_index - the within bucket index
     * we want to start from.
     */
    ConstIterator(const HashMap<KeyT, ValueT> &hash_map,
                  int bucket_index,
                  int within_bucket_index)
            : hash_map(hash_map), bucket_index(bucket_index),
              within_bucket_index(within_bucket_index) {}


              /**
               * our prefix-plusplus operator.
               * @return a reference to the Iterator (plussed by one)
               */
    ConstIterator &operator++() {
        if (bucket_index == hash_map._capacity) {
            return *this;
        }

        if (within_bucket_index <
                (int)(hash_map._buckets[bucket_index].size() - 1)) {
            within_bucket_index++;
            return *this;
        }


        for (int i = bucket_index + 1; i < hash_map._capacity; i++) {
            if (!hash_map._buckets[i].empty()) {
                bucket_index = i;
                within_bucket_index = 0;
                return *this;
            }
        }
        within_bucket_index = 0;
        bucket_index = hash_map._capacity;
        return *this;
    }


    /**
               * our postfix-plusplus operator.
               * @return a reference to the Iterator (not plussed by one yet)
               */
    ConstIterator operator++(int) {
        ConstIterator it(*this); // default copy-ctr at work
        this->operator++();
        return it;
    }

    /**
     * our == operator. returns true if the iterators are pointing on
     * the same element. false otherwise.
     * @param rhs - the "right" Iterator
     * @return true if the iterators are pointing on
     * the same element. false otherwise.
     */
    bool operator==(const ConstIterator &rhs) const {
        return (&(this->hash_map) == &(rhs.hash_map) &&
        bucket_index == rhs.bucket_index &&
        within_bucket_index == rhs.within_bucket_index);
    }

    /**
     * our != operator. returns false if the iterators are pointing on
     * the same element. true otherwise.
     * @param rhs - the "right" Iterator
     * @return false if the iterators are pointing on
     * the same element. true otherwise.
     */
    bool operator!=(const ConstIterator &rhs) const {
        return !operator==(rhs);
    }

    /**
     * our * operator. returns a reference to the Iterator that we're now
     * pointing at.
     * @return a reference to the Iterator that we're now
     * pointing at.
     */
    reference operator*() const {
        if (bucket_index == hash_map._capacity) {
            throw std::out_of_range("out of range, end of the iterator");
        }

        return (this->hash_map._buckets[bucket_index])[within_bucket_index];
    }

    /**
     * our -> operator. returns a memory address to the element that we're
     * now pointing at.
     * @return a memory address to the element that we're
     * now pointing at.
     */
    pointer operator->() const {
        return &(operator*());
    }
};


#endif //EX6_OFEK_AVIDAN_HASHMAP_HPP
