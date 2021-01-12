#ifndef __HASHTABLE__
#define __HASHTABLE__

#include "HashUtils.h"
#include "ItemNotFoundException.h"
/* Do not add new libraries or files */

#define BUCKET_SIZE 2

// Do not modify the public interface of this class.
// Otherwise, your code will note compile!
template <class K, class T>
class HashTable {
    struct Entry {
        K Key;             // the key of the entry
        T Value;   // the value of the entry
        bool Deleted;        // flag indicating whether this entry is deleted
        bool Active;         // flag indicating whether this item is currently used

        Entry() : Key(), Value(), Deleted(false), Active(false) {}
    };

    struct Bucket {
        Entry entries[BUCKET_SIZE];
    };

    int _capacity; // INDICATES THE TOTAL CAPACITY OF THE TABLE
    int _size; // INDICATES THE NUMBER OF ITEMS IN THE TABLE

    Bucket* _table; // THE HASH TABLE

    // == DEFINE HELPER METHODS & VARIABLES BELOW ==
    bool searchDuplicate(const K& key, const T& value);
    /*
    void print(std::ostream& out) const;
    void print(Bucket* b, std::ostream& out) const;
    ostream& operator<<(ostream& os, Bucket* b) const {
        for (int i = 0; i < _capacity; i++) {
            for (int j = 0; j < BUCKET_SIZE; j++) {
                os << b[i].entries[j].Key;
                os << " ";
                os << b[i].entries[j].Value;

                os << "\t";
            }
            os << "\n";
        }
        return os;
    }
    */



public:
    // TODO: IMPLEMENT THESE FUNCTIONS.
    // CONSTRUCTORS, ASSIGNMENT OPERATOR, AND THE DESTRUCTOR
    HashTable();
    // COPY THE WHOLE CONTENT OF RHS INCLUDING THE KEYS THAT WERE SET AS DELETED
    HashTable(const HashTable<K, T>& rhs);
    HashTable<K, T>& operator=(const HashTable<K, T>& rhs);
    ~HashTable();

    // TODO: IMPLEMENT THIS FUNCTION.
    // INSERT THE ENTRY IN THE HASH TABLE WITH THE GIVEN KEY & VALUE
    // IF THE GIVEN KEY ALREADY EXISTS, THE NEW VALUE OVERWRITES
    // THE ALREADY EXISTING ONE. IF THE LOAD FACTOR OF THE TABLE IS GREATER THAN 0.6,
    // RESIZE THE TABLE WITH THE NEXT PRIME NUMBER.
    void Insert(const K& key, const T& value);

    // TODO: IMPLEMENT THIS FUNCTION.
    // DELETE THE ENTRY WITH THE GIVEN KEY FROM THE TABLE
    // IF THE GIVEN KEY DOES NOT EXIST IN THE TABLE, THROW ItemNotFoundException()
    void Delete(const K& key);

    // TODO: IMPLEMENT THIS FUNCTION.
    // IT SHOULD RETURN THE VALUE THAT CORRESPONDS TO THE GIVEN KEY.
    // IF THE KEY DOES NOT EXIST, THROW ItemNotFoundException()
    T& Get(const K& key) const;

    // TODO: IMPLEMENT THIS FUNCTION.
    // AFTER THIS FUNCTION IS EXECUTED THE TABLE CAPACITY MUST BE
    // EQUAL TO newCapacity AND ALL THE EXISTING ITEMS MUST BE REHASHED
    // ACCORDING TO THIS NEW CAPACITY.
    // WHEN CHANGING THE SIZE, YOU MUST REHASH ALL OF THE ENTRIES
    void Resize(int newCapacity);

    // THE IMPLEMENTATION OF THESE FUNCTIONS ARE GIVEN TO YOU
    // DO NOT MODIFY!
    int Capacity() const; // RETURN THE TOTAL CAPACITY OF THE TABLE
    int Size() const; // RETURN THE NUMBER OF ACTIVE ITEMS
    void getKeys(K* keys); // PUT THE ACTIVE KEYS TO THE GIVEN INPUT PARAMETER
};

/*

template <class K, class T>
ostream& operator<<(ostream& os, typename HashTable<K,T>::Entry& key)
{
    os << key;
    return os;
}



template<class K, class T>
void HashTable<K, T>::print(HashTable<K,T>::Bucket* b, std::ostream & out) const {
     for (int i = 0; i < _capacity; i++) {
        for (int j = 0; j < BUCKET_SIZE; j++) {
            if (j == 0)
                out << _table[i].entries[j].Key << "&&" << _table[i].entries[j].Value << "&&" << _table[i].entries[j].Deleted << "&&" << _table[i].entries[j].Active << "\t";
            else {
                out << _table[i].entries[j].Key << "&&" << _table[i].entries[j].Value << "&&" << _table[i].entries[j].Deleted << "&&" << _table[i].entries[j].Active << "\n";

                out << " " << std::endl;
            }
        }
    }

}

template<class K, class T>
void HashTable<K, T>::print(std::ostream & out) const {

    print(_table, out);
}

*/
template <class K, class T>
HashTable<K, T>::HashTable() {
    // TODO: IMPLEMENT THIS FUNCTION.
    _capacity = NextCapacity(0);
    _table = new Bucket[_capacity];
    _size = 0;
}

template <class K, class T>
HashTable<K, T>::HashTable(const HashTable<K, T>& rhs) {
    // TODO: IMPLEMENT THIS FUNCTION.
    //delete[] _table;
    _capacity = rhs._capacity;
    _table = new Bucket[_capacity];
    for (int i = 0; i < _capacity; i++) {
        for (int j = 0; j < BUCKET_SIZE; j++) {
            if (rhs._table[i].entries[j].Active || rhs._table[i].entries[j].Deleted) {
                _table[i].entries[j].Value = rhs._table[i].entries[j].Value;
                _table[i].entries[j].Key = rhs._table[i].entries[j].Key;
            }
            _table[i].entries[j].Active = rhs._table[i].entries[j].Active;
            _table[i].entries[j].Deleted = rhs._table[i].entries[j].Deleted;

        }
    }
    _size = rhs.Size();

}

template <class K, class T>
HashTable<K, T>& HashTable<K, T>::operator=(const HashTable<K, T>& rhs) {
    // TODO: IMPLEMENT THIS FUNCTION.
    _capacity = rhs.Capacity();
    _size = rhs.Size();
    delete[] _table;
    _table = new Bucket[_capacity];
    for (int i = 0; i < _capacity; i++) {
        for (int j = 0; j < BUCKET_SIZE; j++) {
            if (rhs._table[i].entries[j].Active || rhs._table[i].entries[j].Deleted) {
                _table[i].entries[j].Value = rhs._table[i].entries[j].Value;
                _table[i].entries[j].Key = rhs._table[i].entries[j].Key;
            }
            _table[i].entries[j].Active = rhs._table[i].entries[j].Active;
            _table[i].entries[j].Deleted = rhs._table[i].entries[j].Deleted;

        }
    }
    /*
    if (_table != nullptr)
        delete[] _table;
    _table = new Bucket[_capacity];
    _capacity = rhs.Capacity();
    for (int i = 0; i < _capacity; i++) {

        for (int j = 0; j < BUCKET_SIZE; j++) {
            if (!(!(rhs._table[i].entries[j].Active) && !(rhs._table[i].entries[j].Deleted))) {
                _table[i].entries[j].Value = rhs._table[i].entries[j].Value;
                _table[i].entries[j].Key = rhs._table[i].entries[j].Key;
            }
            _table[i].entries[j].Deleted = rhs._table[i].entries[j].Deleted;
            _table[i].entries[j].Active = rhs._table[i].entries[j].Active;
        }


    }
    _size = rhs.Size();
    */
    return *this;
}

template <class K, class T>
HashTable<K, T>::~HashTable() {
    // TODO: IMPLEMENT THIS FUNCTION.
    delete[] _table;
    _table = nullptr;

}

template<class K, class T>
bool HashTable<K, T>::searchDuplicate(const K& key, const T& value) {
    int hashVal = Hash(key);
    hashVal %= _capacity;
    for (int i = 0; i < _capacity; i++) {
        hashVal += i * i;
        hashVal %= _capacity;
        for (int j = 0; j < BUCKET_SIZE; j++) {
            if (_table[hashVal].entries[j].Key == key) {
                _table[hashVal].entries[j].Value = value;
                if (_table[hashVal].entries[j].Deleted) {
                    _table[hashVal].entries[j].Active = true;
                    _table[hashVal].entries[j].Deleted = false;
                    _size++;
                }
                return true;
            }
            else if (!_table[hashVal].entries[j].Deleted && !_table[hashVal].entries[j].Active) {
                return false;

            }
        }
    }
    return false;

}


template <class K, class T>
void HashTable<K, T>::Insert(const K& key, const T& value) {
    // TODO: IMPLEMENT THIS FUNCTION.
    Entry insertedEntry = Entry();
    insertedEntry.Key = key;
    insertedEntry.Value = value;
    insertedEntry.Active = true;
    int hashVal = Hash(key);
    hashVal %= _capacity;
    bool inserted = false;
    for (int i = 0; i < _capacity; i++) {
        if (inserted)
            break;
        hashVal += i * i;
        hashVal %= _capacity;
        for (int j = 0; j < BUCKET_SIZE; j++) {
            if (!_table[hashVal].entries[j].Deleted && !_table[hashVal].entries[j].Active) {
                _table[hashVal].entries[j].Value = value;
                _table[hashVal].entries[j].Key = key;
                inserted = true;
                _table[hashVal].entries[j].Active = true;
                _table[hashVal].entries[j].Deleted = false;
                _size++;
                break;
            }
            else if (_table[hashVal].entries[j].Key == key) {
                _table[hashVal].entries[j].Value = value;
                inserted = true;
                if (_table[hashVal].entries[j].Deleted)
                    _size++;

                _table[hashVal].entries[j].Deleted = false;
                _table[hashVal].entries[j].Active = true;

                break;
            }
            else if (_table[hashVal].entries[j].Deleted && !_table[hashVal].entries[j].Active) {
                bool found = searchDuplicate(key, value);
                if (!found) {
                    _table[hashVal].entries[j].Key = key;
                    _table[hashVal].entries[j].Value = value;
                    _table[hashVal].entries[j].Active = true;
                    _table[hashVal].entries[j].Deleted = false;
                    _size++;
                }
                inserted = true;
                break;


            }



        }

    }
    if ((double)_size / (2 * (double)_capacity) > 0.6) {
        Resize(NextCapacity(_capacity));
    }

}

template <class K, class T>
void HashTable<K, T>::Delete(const K& key) {
    // TODO: IMPLEMENT THIS FUNCTION.
    int hashVal = Hash(key);
    hashVal %= _capacity;
    for (int i = 0; i < _capacity; i++) {
        hashVal += i * i;
        hashVal %= _capacity;
        for (int j = 0; j < BUCKET_SIZE; j++) {
            if (_table[hashVal].entries[j].Key == key) {
                _table[hashVal].entries[j].Deleted = true;
                _table[hashVal].entries[j].Active = false;
                _size--;
                return;
            }
            else if (!_table[hashVal].entries[j].Deleted && !_table[hashVal].entries[j].Active) {
                throw ItemNotFoundException();

            }
        }
    }
    throw ItemNotFoundException();


}



template <class K, class T>
T& HashTable<K, T>::Get(const K& key) const {
    // TODO: IMPLEMENT THIS FUNCTION. 
    int hashVal = Hash(key);
    hashVal %= _capacity;
    for (int i = 0; i < _capacity; i++) {
        hashVal += i * i;
        hashVal %= _capacity;
        for (int j = 0; j < BUCKET_SIZE; j++) {
            if (_table[hashVal].entries[j].Key == key)
                if (!_table[hashVal].entries[j].Deleted)
                    return _table[hashVal].entries[j].Value;
                else
                    throw ItemNotFoundException();
            else if (!_table[hashVal].entries[j].Deleted && !_table[hashVal].entries[j].Active) {
                throw ItemNotFoundException();

            }
        }
    }
    throw ItemNotFoundException();

}


template <class K, class T>
void HashTable<K, T>::Resize(int newCapacity) {
    // TODO: IMPLEMENT THIS FUNCTION.
    Bucket* oldTable = _table;
    int oldCapacity = _capacity;
    _size = 0;
    _capacity = newCapacity;
    _table = new Bucket[_capacity];
    for (int i = 0; i < oldCapacity; i++) {
        for (int j = 0; j < BUCKET_SIZE; j++) {
            if (!oldTable[i].entries[j].Deleted && oldTable[i].entries[j].Active) {
                this->Insert(oldTable[i].entries[j].Key, oldTable[i].entries[j].Value);
            }
        }
    }
    delete[] oldTable;

}


template <class K, class T>
int HashTable<K, T>::Capacity() const {
    return _capacity;
}

template <class K, class T>
int HashTable<K, T>::Size() const {
    return _size;
}


template <class K, class T>
void HashTable<K, T>::getKeys(K* keys) {
    int index = 0;

    for (int i = 0; i < _capacity; i++) {
        Bucket& bucket = _table[i];
        for (int j = 0; j < BUCKET_SIZE; j++) {
            if (bucket.entries[j].Active && !bucket.entries[j].Deleted) {
                keys[index++] = bucket.entries[j].Key;
            }
        }
    }
}

#endif