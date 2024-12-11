#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>
#include <climits>
using namespace std;

class BigInt
{
    private:
        vector<char> v;

    public:
        BigInt() {
            v.push_back(0);
        };

        BigInt(string s) {
            for (int i = s.size() - 1; i >= 0; --i) {
                v.push_back(s[i] - '0');
            }
        };

        BigInt(int n) {
            if (n == 0) {
                v.push_back(0);
            } else {
                while (n > 0) {
                    char digit = (n % 10);
                    v.push_back(digit);
                    n /= 10;
                }
            }
        };

        int size() const {
            return v.size();
        };

        bool operator== (const BigInt& b) const {
            return v == b.v;
        };

        bool operator< (const BigInt& b) const {
            if (v.size() < b.size()) {
                return true;
            } else if (v.size() > b.size()) {
                return false;
            } else {
                for (int i = v.size() - 1; i >= 0; --i) {
                    if (v[i] < b[i]) {
                        return true;
                    } else if (v[i] > b[i]) {
                        return false;
                    }
                }
                return false;
            }
        };

        bool operator>= (const BigInt& b) const {
            if (v.size() > b.size()) {
                return true;
            } else if (v.size() < b.size()) {
                return false;
            } else {
                for (int i = v.size() - 1; i >= 0; --i) {
                    if (v[i] > b[i]) {
                        return true;
                    } else if (v[i] < b[i]) {
                        return false;
                    }
                }
                return true;
            }
        };

        BigInt operator+ (const BigInt b) {
            BigInt result;
            result.v.clear();
            int carry = 0;
            int maxsize = std::max(static_cast<int>(v.size()), static_cast<int>(b.size()));
            for (int i = 0; i < maxsize || carry; ++i) {
                int sum = carry;
                if (i < v.size()) sum += v[i];
                if (i < b.size()) sum += b[i];
                result.v.push_back(sum % 10);
                carry = sum / 10;
            }
            while (result.v.size() > 1 && result.v.back() == 0) {
                result.v.pop_back();
            }
            return result;
        };

        BigInt operator- (const BigInt b) {
            BigInt result;
            result.v.clear();
            int borrow = 0;
            for (int i = 0; i < v.size(); ++i) {
                int difference = v[i] - borrow;
                if (i < b.size()) difference -= b[i];
                if (difference < 0) {
                    difference += 10;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                result.v.push_back(difference);
            }
            while (result.v.size() > 1 && result.v.back() == 0) {
                result.v.pop_back();
            }
            return result;
        };
        
        BigInt operator* (BigInt b) { 
            BigInt result;
            result.v = vector<char>(v.size() + b.size(), 0);
            for (int i = 0; i < v.size(); ++i) {
                int carry = 0;
                for (int j = 0; j < b.size(); ++j) {
                    int product = static_cast<int>(v[i]) * static_cast<int>(b[j]) + static_cast<int>(result.v[i + j]) + carry;
                    result.v[i + j] = static_cast<char>(product % 10);
                    carry = product / 10;
                }
                if (carry) {
                    result.v[i + b.size()] += carry;
                }
            }
            while (result.v.size() > 1 && result.v.back() == 0) {
                result.v.pop_back();
            }
            return result;
        };

        BigInt operator/(const BigInt& other)const{
            BigInt dividend = *this;
            BigInt divisor = other;
            BigInt quotient;
            BigInt remainder;

            remainder.v.clear();

            for (int i = dividend.v.size() - 1; i >= 0; --i) {
                remainder.v.insert(remainder.v.begin(), dividend.v[i]);

                while (remainder.v.size() > 1 && remainder.v.back() == 0) {
                    remainder.v.pop_back();
                }

                int n = 0;
                BigInt p;

                for (int j = 0; j <= 9; ++j) {
                    p = divisor * BigInt(j);
                    if (remainder >= p) {
                        n = j;
                    } else {
                        break;
                    }
                }

                BigInt temp = divisor * BigInt(n);
                remainder = remainder - temp;
                quotient.v.push_back(static_cast<char>(n));
            }

            for (int i = 0; i < quotient.v.size() / 2; ++i) {
                char temp = quotient.v[i];
                quotient.v[i] = quotient.v[quotient.v.size() - i - 1];
                quotient.v[quotient.v.size() - i - 1] = temp;
            }

            while (quotient.v.size() > 1 && quotient.v.back() == 0) {
                quotient.v.pop_back();
            }

            return quotient;
        }

        BigInt operator%(const BigInt& other) const {
            BigInt dividend = *this;
            BigInt divisor = other;
            BigInt quotient;
            BigInt remainder;

            for (int i = dividend.v.size() - 1; i >= 0; --i) {
                remainder.v.insert(remainder.v.begin(), dividend.v[i]);

                int n = 0;

                while (remainder >= divisor) {
                    remainder = remainder - divisor;
                    n++;
                }

                quotient.v.insert(quotient.v.begin(), n);
            }

            return remainder;
        };

        BigInt operator++(int) {
            BigInt temp = *this;
            *this = *this + BigInt(1);
            return temp;
        };

        BigInt operator++() {
            *this = *this + BigInt(1);
            return *this;
        };

        char operator[] (int n) const {
            return v[n];
        };

        void print() {
            for (int i = v.size() - 1; i >= 0; --i) {
                cout << (int)v[i];
            }
        };

        BigInt fibo(BigInt a = 0, BigInt b = 1) {
            if (*this == BigInt(0)) return a;
            if (*this == BigInt(1)) return b;
            return (*this - 1).fibo(b, a + b);
        };

        
        BigInt fact() {
            static map<BigInt, BigInt> factmap;

            if (factmap.find(*this) != factmap.end()) {
                return factmap[*this];
            }

            if (*this == BigInt(0) || *this == BigInt(1)) {
                factmap[*this] = BigInt(1);
                return BigInt(1);
            }

            BigInt current = *this - BigInt(1);
            BigInt result = current.fact();

            factmap[*this] = *this * result;
            return factmap[*this];
        };

        friend ostream& operator<<(ostream& out, const BigInt& b) {
            if (b.size() > 12) {
                out << static_cast<int>(b.v[b.size() - 1]) << ".";
                for (int i = b.size() - 2; i >= b.size() - 7; --i) {
                    out << static_cast<int>(b.v[i]);
                }
                out << "e" << b.size() - 1;
            } else {
                for (int i = b.size() - 1; i >= 0; --i) {
                    out << static_cast<int>(b.v[i]);
                }
            }
            return out;
        };

        friend BigInt operator+ (int n, BigInt b) {
            BigInt result(n);
            return result + b;
        };
};


void testUnit()
{
    int space = 10;
    cout << "\a\nTestUnit:\n"<<flush;
    system("whoami");
    system("date");
    
    BigInt n1(25);
    BigInt s1("25");
    BigInt n2(1234);
    BigInt s2("1234");
    BigInt n3(n2);
    BigInt fibo(12345);
    BigInt fact(50);
    BigInt imax = INT_MAX;
    BigInt big("9223372036854775807");
    
    cout << "n1(int)     :" << setw(space) << n1 << endl;
    cout << "s1(str)     :" << setw(space) << s1 << endl;
    cout << "n2(int)     :" << setw(space) << n2 << endl;
    cout << "s2(str)     :" << setw(space) << s2 << endl;
    cout << "n3(n2)      :" << setw(space) << n3 << endl;
    cout << "fibo(12345) :" << setw(space) << fibo << endl;
    cout << "fact(50)    :" << setw(space) << fact << endl;
    cout << "imax        :" << setw(space) << imax << endl;
    cout << "big         :" << setw(space) << big << endl;
    cout << "big.print() : "; big.print(); cout << endl;

    cout << n2 << "/" << n1 << " = " << n2 / n1 << " rem "<< n2 % n1 << endl;
    cout << "fibo(" << fibo << ") = " << fibo.fibo() << endl;
    cout << "fact(" << fact << ") = " << fact.fact() << endl;

    cout << "10 + n1 = " << 10 + n1 << endl;
    cout << "n1 + 10 = " << n1 + 10 << endl;

    cout << "(n1 == s1)? --> " << ((n1 == s1) ? "true":"false") << endl;
    cout << "n1++ = ? --> before:" << n1++ << " after:" << n1 << endl;
    cout << "++s1 = ? --> before:" << ++s1 << " after:" << s1 << endl;

    cout << "s2 * big = ? --> " << s2 * big << endl;
    cout << "big * s2 = ? --> " << big * s2 << endl;
}

int main()
{
    testUnit();
    return 0;
}