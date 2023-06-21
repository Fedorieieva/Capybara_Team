#include <iostream>

using namespace std;

class B1 {
protected: 
    unsigned int a;

public:
    B1() { a = 0; }

    B1(unsigned int val) { a = val; }

    virtual void print() {
        cout << "class B1: " << a << endl;
    }
};

class B2 {
protected: 
    unsigned int b;

public:
    B2() { b = 0; }

    B2(unsigned int val) { b = val; }

    virtual void print() {
        cout << "class B2: " << b << endl;
    }
};

class D1 : public B2, private B1 { 
private:
    unsigned int d;

public:
    D1() { d = 0; }

    D1(unsigned int val) : B1(val), B2(val) { d = val; } 

    void print() override {
        cout << "class D1: " << d << endl;
    }
};

class D2 : public D1 {
private:
    unsigned int z;

public:
    D2() { z = 0; }

    D2(unsigned int val) : D1(val) { z = val; }

    void print() override {
        cout << "class D2: " << z << endl;
    }
};

class D3 : private D1 {
private:
    unsigned int k;

public:
    D3() { k = 0; }

    D3(unsigned int val) : D1(val) { k = val; }

    void print() override {
        cout << "class D3: " << k << endl;
    }
};

class Mnozhyna {
private:
    string set;

    string unique(string val) {
        string res = "";
        for (int i = 0; i < val.size(); i++) {
            if (res.find(val[i]) == string::npos) {
                res += val[i];
            }
        }
        return res;
    }

    void sort_set() {
        char current;
        int j;
        for (int i = 0; i < set.length(); i++) {
            current = set[i];
            j = i - 1;
            while (j >= 0 && set[j] > current) {
                set[j + 1] = set[j];
                j--;
            }
            set[j + 1] = current;
        }
    }

public:
    Mnozhyna() { set = ""; }

    Mnozhyna(const string& val) { 
        string temp = "";
        for (int i = 0; i < val.size(); i++) {
            if (isdigit(val[i]) && val[i] != ' ') {
                temp += val[i];
            }
        }
        set = unique(temp);
        sort_set();
    }

    friend ostream& operator <<(ostream& os, const Mnozhyna& m) {
        os << "{";
        for (int i = 0; i < m.set.size(); i++) {
            os << "\"" << m.set.substr(i, 1) << "\"";
            if (i != m.set.size() - 1) {
                os << ", ";
            }
        }
        os << "}";
        return os;
    }
};

int main() {

    Mnozhyna a("1h3kuy5o8764bl  1709uf");
    cout << a;


    return 0;
}