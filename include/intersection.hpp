#pragma once
#include <algorithm>
#include <format>
#include <initializer_list>
#include <stdexcept>
#include <vector>

template <typename T>
struct Intersection {
    float t;
    T obj;
};


template<typename T>
class Intersections {
private:
    std::vector<Intersection<T>> _data;
    bool sorted = false;

public:
    
    Intersections() = default;

    Intersections(std::initializer_list<Intersection<T>> data):_data(data) {
        sort();
    }


    Intersection<T> operator[](int idx) const {
        if( idx < 0 || idx >= _data.size()) {
            throw std::out_of_range(std::format("the index {} is out of range {}", idx, _data.size()-1));
        }
        return _data[idx];
    }

    void sort() {
        std::sort(_data.begin(), _data.end(), [](const Intersection<T> a,const Intersection<T> b) {
            return a.t < b.t;
        });
        sorted = true;
    }


    Intersection<T> hit(std::vector<Intersection<T>> intersections) {
        if(!sorted) {
            sort();
        }
        Intersection<T> hit;
        for (auto i : intersections) {
            if (i.t > 0) {
                hit = i;
                break;
            }
        }
        return hit;
    }

    size_t size() const{
        return _data.size();
    }

    auto& operator=(const std::initializer_list<Intersection<T>> values) {
        if(values.size() > _data.size()) {
            throw std::invalid_argument("error: number of values does not match matrix size.");
        }

        for(int i = 0; i < values.size(); ++i) {
            _data[i] = values[i];
        }
        return *this;

    }
};
