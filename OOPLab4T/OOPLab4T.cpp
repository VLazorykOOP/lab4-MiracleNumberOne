#include <iostream>
#include <cstring>
#include "VectorInt.h"
#include <map>
#include <string>

class VectorInt {
private:
    int* values;
    int size;
    int codeError;
    static int count;

public:
    VectorInt() {
        size = 1;
        values = new int[size];
        values[0] = 0;
        codeError = 0;
    }

    VectorInt(int size) {
        this->size = size;
        values = new int[size];
        for (int i = 0; i < size; i++) {
            values[i] = 0;
        }
        codeError = 0;
    }

    VectorInt(int size, int value) {
        this->size = size;
        values = new int[size];
        for (int i = 0; i < size; i++) {
            values[i] = value;
        }
        codeError = 0;
    }

    VectorInt(const VectorInt& other) {
        size = other.size;
        values = new int[size];
        for (int i = 0; i < size; i++) {
            values[i] = other.values[i];
        }
        codeError = other.codeError;
    }

    ~VectorInt() {
        delete[] values;
    }

    // Перегрузка оператора присвоєння =
    VectorInt& operator=(const VectorInt &v) {
        if (this == &v) {
            return *this;
        }
        delete[] values;
        size = v.size;
        codeError = v.codeError;
        values = new int[size];
        memcpy(values, v.values, size * sizeof(int));
        return *this;
    }
    
    // Унарні операції ++, --, !, ~, -
    VectorInt& operator++() {  // префіксний ++
        for (int i = 0; i < size; i++) {
            ++values[i];
        }
        return *this;
    }
    
    VectorInt operator++(int) {  // постфіксний ++
        VectorInt tmp(*this);
        operator++();
        return tmp;
    }
    
    VectorInt& operator--() {  // префіксний --
        for (int i = 0; i < size; i++) {
            -values[i];
        }
        return *this;
    }
    
    VectorInt operator--(int) {  // постфіксний --
        VectorInt tmp(*this);
        operator--();
        return tmp;
    }
    
    bool operator!() {  // логічне заперечення
        return size == 0;
    }
    
    VectorInt operator~() {  // побітове заперечення
        VectorInt v(*this);
        for (int i = 0; i < size; i++) {
            v[i] = ~v[i];
        }
        return v;
    }
    
    VectorInt operator-() {  // унарний мінус
        VectorInt v(*this);
        for (int i = 0; i < size; i++) {
            v[i] = -v[i];
        }
        return v;
    }

    VectorInt& operator+=(const VectorInt& other) {
        if (size == other.size) {
            for (int i = 0; i < size; i++) {
                values[i] += other.values[i];
            }
        } else {
            codeError = 1;
        }
        return *this;
    }

    VectorInt& operator-=(const VectorInt& other) {
        if (size == other.size) {
            for (int i = 0; i < size; i++) {
                values[i] -= other.values[i];
            }
        } else {
            codeError = 1;
        }
        return *this;
    }

    VectorInt& operator*=(int value) {
        for (int i = 0; i < size; i++) {
            values[i] *= value;
        }
        return *this;
    }

    VectorInt& operator/=(int value) {
        if (value == 0) {
            codeError = 2;
        } else {
            for (int i = 0; i < size; i++) {
                values[i] /= value;
            }
        }
        return *this;
    }

    VectorInt& operator%=(int value) {
        if (value == 0) {
            codeError = 2;
        } else {
            for (int i = 0; i < size; i++) {
                values[i] %= value;
            }
        }
        return *this;
    }

    VectorInt& operator|=(const VectorInt& other) {
        if (size == other.size) {
            for (int i = 0; i < size; i++) {
                values[i] |= other.values[i];
            }
        } else {
            codeError = 1;
        }
        return *this;
    }

    friend VectorInt operator+(const VectorInt &v1, const VectorInt &v2) {
        VectorInt result(v1.size);
        if (v1.size != v2.size) {
            result.codeError = 2;
            return result;
        }
        for (int i = 0; i < v1.size; i++) {
            result.values[i] = v1.values[i] + v2.values[i];
        }
        return result;
    }

    friend VectorInt operator-(const VectorInt &v1, const VectorInt &v2) {
        VectorInt result(v1.size);
        if (v1.size != v2.size) {
            result.codeError = 2;
            return result;
        }
        for (int i = 0; i < v1.size; i++) {
            result.values[i] = v1.values[i] - v2.values[i];
        }
        return result;
    }

    friend VectorInt operator*(const VectorInt &v, int n) {
        VectorInt result(v.size);
        for (int i = 0; i < v.size; i++) {
            result.values[i] = v.values[i] * n;
        }
        return result;
    }

    friend VectorInt operator/(const VectorInt &v, int n) {
        VectorInt result(v.size);
        for (int i = 0; i < v.size; i++) {
            result.values[i] = v.values[i] / n;
        }
        return result;
    }

    friend VectorInt operator%(const VectorInt &v, int n) {
        VectorInt result(v.size);
        for (int i = 0; i < v.size; i++) {
            result.values[i] = v.values[i] % n;
        }
        return result;
    }

    friend VectorInt operator^(const VectorInt& v1, const VectorInt& v2) {
        VectorInt result(v1.size);
        if (v1.size != v2.size) {
            result.codeError = 1;
            return result;
        }
        for (int i = 0; i < v1.size; i++) {
            result.values[i] = (v1.values[i] + v2.values[i]) % 2;
        }
        return result;
    }

    friend VectorInt operator&(const VectorInt& v1, const VectorInt& v2) {
        VectorInt result(v1.size);
        if (v1.size != v2.size) {
            result.codeError = 1;
            return result;
        }
        for (int i = 0; i < v1.size; i++) {
            result[i] = v1.values[i] & v2.values[i];
        }
        return result;
    }

    friend VectorInt operator>>(const VectorInt& v, int shift) {
        VectorInt result(v.size);
        for (int i = 0; i < v.size; i++) {
            result[i] = (i + shift < v.size) ? v.values[i + shift] : 0;
        }
        return result;
    }

    friend VectorInt operator<<(const VectorInt& v, int shift) {
        VectorInt result(v.size);
        for (int i = 0; i < v.size; i++) {
            result[i] = (i - shift >= 0) ? v.values[i - shift] : 0;
        }
        return result;
    }

    friend VectorInt operator|(const VectorInt &v1, const VectorInt &v2) {
        VectorInt result(v1.size);
        if (v1.size != v2.size) {
            result.codeError = 1;
            return result;
        }
        for (int i = 0; i < v1.size; i++) {
            result.values[i] = v1.values[i] | v2.values[i];
        }
        return result;
    }

    bool operator==(const VectorInt& other) const {
        if (size != other.size) return false;
        for (int i = 0; i < size; i++) {
            if (values[i] != other.values[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const VectorInt& other) const {
        return !(*this == other);
    }

    int& operator[](int index) {
        if (index < 0 || index >= size) {
            codeError = 2;
            return values[size - 1];
        }
        return values[index];
    }

    void operator()() {
        for (int i = 0; i < size; i++) {
            std::cout << values[i] << " ";
        }
        std::cout << std::endl;
    }

    bool operator>(const VectorInt& other) const {
        if (size != other.size) {
            return false;
        }
        for (int i = 0; i < size; i++) {
            if (values[i] <= other.values[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator>=(const VectorInt& other) const {
        if (size != other.size) {
            return false;
        }
        for (int i = 0; i < size; i++) {
            if (values[i] < other.values[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator<(const VectorInt& other) const {
        if (size != other.size) {
            return false;
        }
        for (int i = 0; i < size; i++) {
            if (values[i] >= other.values[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator<=(const VectorInt& other) const {
        if (size != other.size) {
            return false;
        }
        for (int i = 0; i < size; i++) {
            if (values[i] > other.values[i]) {
                return false;
            }
        }
        return true;
    }

    void* operator new(std::size_t size) {
        void* ptr = std::malloc(size);
        if (!ptr) {
            throw std::bad_alloc();
        }
        return ptr;
    }

    void operator delete(void* ptr) noexcept {
        std::free(ptr);
    }

    int getSize() const {
    return size;
}

    int getCodeError() const {
        return codeError;
    }

    static int getCount() {
        return count;
    }
};


class EntityMap {
private:
    std::map<int, std::string> intToStr;
    std::map<std::string, int> strToInt;
    int CodeError = 0; // error code, initialized to 0

public:
    // add a new association between an integer and a string
    void add(int i, std::string s) {
        intToStr[i] = s;
        strToInt[s] = i;
    }

    // overloaded [] operator, returns the associated string if the integer exists,
    // sets the error code to 1 if the integer is not found
    std::string operator[](int i) {
        if (intToStr.count(i) > 0) {
            return intToStr[i];
        } else {
            CodeError = 1;
            return "";
        }
    }

    // overloaded function call operator, returns the associated integer if the string exists,
    // sets the error code to 2 if the string is not found
    int operator()(std::string s) {
        if (strToInt.count(s) > 0) {
            return strToInt[s];
        } else {
            CodeError = 2;
            return 0;
        }
    }

    // overloaded insertion operator, prints the contents of the entity map
    friend std::ostream& operator<<(std::ostream& os, const EntityMap& em) {
        for (auto const& [i, s] : em.intToStr) {
            os << i << ": " << s << std::endl;
        }
        return os;
    }

    // overloaded extraction operator, reads in associations from input stream
    friend std::istream& operator>>(std::istream& is, EntityMap& em) {
        int i;
        std::string s;
        while (is >> i >> s) {
            em.add(i, s);
        }
        return is;
    }
};


int main() {
    // Create a vector of size 5 with default value 0
    VectorInt v1(5);

    // Create a vector of size 10 with default value 1
    VectorInt v2(10, 1);

    // Create a copy of v2
    VectorInt v3(v2);

    // Perform some operations
    v1 += v2;
    v2 *= 3;
    v3 /= 2;

    // Print the vectors
    std::cout << "v1: " << v1 << std::endl;
    std::cout << "v2: " << v2 << std::endl;
    std::cout << "v3: " << v3 << std::endl;

    // Test some unary operators
    std::cout << "v1++: " << (v1++) << std::endl;
    std::cout << "++v2: " << (++v2) << std::endl;
    std::cout << "--v3: " << (--v3) << std::endl;
    std::cout << "!v1: " << (!v1) << std::endl;
    std::cout << "~v2: " << (~v2) << std::endl;
    std::cout << "-v3: " << (-v3) << std::endl;

    // Test some binary operators
    VectorInt v4 = v1 + v2;
    VectorInt v5 = v2 - v3;
    VectorInt v6 = v3 | v1;

    std::cout << "v4: " << v4 << std::endl;
    std::cout << "v5: " << v5 << std::endl;
    std::cout << "v6: " << v6 << std::endl;

    // Test subscript operator
    std::cout << "v4[0]: " << v4[0] << std::endl;
    std::cout << "v5[1]: " << v5[1] << std::endl;
    std::cout << "v6[2]: " << v6[2] << std::endl;

    // Test out of range error
    try {
        std::cout << "v6[10]: " << v6[10] << std::endl;
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }

    // Print the number of VectorInt objects created
    std::cout << "Number of VectorInt objects created: " << VectorInt::count << std::endl;


    EntityMap em;
    em.add(1, "один");
    em.add(2, "два");
    em.add(3, "три");
    em.add(4, "чотири");
    em.add(5, "п'ять");

    // test the overloaded [] operator
    std::cout << em[3] << std::endl;
    std::cout << em[6] << std::endl;
    std::cout << "Error code: " << em.CodeError << std::endl;

    // test the overloaded function call operator
    std::cout << em("один") << std::endl;
    std::cout << em("шість") << std::endl;
    std::cout << "Error code: " << em.CodeError << std::endl;

    // test the overloaded insertion operator
    std::cout << em << std::endl;

    // test the overloaded extraction operator
    EntityMap em2;
    std::cin >> em2;
    std::cout << em2 << std::endl;

    return 0;
}