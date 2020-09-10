#include "set.h"
#include <ostream>
#include <list>
#include <cstdlib>
#include <math.h>

bool equal(const std::string& s1, const std::string& s2)
{
    if (s1.length() != s2.length())
        return false;
    for (size_t i = 0; i < s1.length(); i++) {
        if (tolower(s1[i]) != tolower(s2[i])) {
            return false;
        }
    }
    return true;
}

size_t hash(const std::string& s)
{
    size_t t = 0;
    for (size_t i = 0; i < s.size(); i++) {
        t = t * 67 + tolower(s[i]);
    }
    return t;
}

set::set(const set& s) :
         bucket_array(new std::list<std::string>[s.bucket_array_size]),
         bucket_array_size(s.bucket_array_size),
         set_size(0)
{
    for (size_t i = 0; i < s.bucket_array_size; i++) {
        std::list<std::string> bucket = s.bucket_array[i];
        if (bucket.size() != 0) {
            for (std::string str_from_bucket : bucket) {
                insert(str_from_bucket);
            }
        }
    }
}

set::set(std::initializer_list<std::string> ilist) :
         bucket_array(new std::list<std::string>[ilist.size()]),
         bucket_array_size(ilist.size()),
         set_size(0)
{
    for (std::string str_from_list : ilist) {
        insert(str_from_list);
    }
}

set& set::operator=(const set& s)
{
    if (this != &s) {
        std::list<std::string>* new_bucket_array = new std::list<std::string>[s.bucket_array_size];
        for (size_t i = 0; i < s.bucket_array_size; i++) {
            std::list<std::string> bucket = s.bucket_array[i];
            if (bucket.size() != 0) {
                for (std::string str_from_bucket : bucket) {
                    size_t p = hash(str_from_bucket) % s.bucket_array_size;
                    new_bucket_array[p].push_back(str_from_bucket);
                }
            }
        }
        delete [] bucket_array;
        bucket_array = new_bucket_array;
        bucket_array_size = s.bucket_array_size;
        set_size = s.set_size;
    }
    return *this;
}

bool set::insert(std::string val)
{
    if (contains(val)) {
        return false;
    }

    size_t p = hash(val) % bucket_array_size;
    bucket_array[p].push_back(val);
    set_size++;

    if (loadfactor() >= max_load_factor) {
        size_t new_bucket_array_size = bucket_array_size * 2;
        std::list<std::string>* new_bucket_array = new std::list<std::string>[new_bucket_array_size];
        for (size_t i = 0; i < bucket_array_size; i++) {
            std::list<std::string> bucket = bucket_array[i];
            if (bucket.size() != 0) {
                for (std::string str_from_bucket : bucket) {
                    size_t p = hash(str_from_bucket) % new_bucket_array_size;
                    new_bucket_array[p].push_back(str_from_bucket);
                }
            }
        }
        delete [] bucket_array;
        bucket_array = new_bucket_array;
        bucket_array_size = new_bucket_array_size;
    }

    return true;
}

bool set::contains(std::string val) const
{
    size_t pos = hash(val) % bucket_array_size;
    std::list<std::string> bucket = bucket_array[pos];
    for (std::string str_from_bucket : bucket) {
        if (equal(str_from_bucket, val)) {
            return true;
        }
    }
    return false;
}

bool set::remove(std::string val)
{
    if (!contains(val)) {
        return false;
    }

    size_t pos = hash(val) % bucket_array_size;
    for (std::string str_from_bucket : bucket_array[pos]) {
        if (equal(str_from_bucket, val)) {
            bucket_array[pos].remove(str_from_bucket);
            set_size--;
            return true;
        }
    }

    return true;
}

void set::clear()
{
    for (size_t i = 0; i < bucket_array_size; i++) {
        bucket_array[i].clear();
    }
    set_size = 0;
}

size_t set::size() const
{
    return set_size;
}

bool set::empty() const
{
    return (set_size == 0);
}

set::~set()
{
    delete [] bucket_array;
}
