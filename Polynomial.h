#ifndef Polynomial_H
#define Polynomial_H

#include <iostream>
#include <vector>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef unsigned int uint;

template <typename T> class Polynomial
{
    public:
        Polynomial() : _factors(1){};
        Polynomial(std::vector<T>& factors) : _factors(factors){};
        Polynomial(const Polynomial<T>& other) : _factors(other._factors){};
        virtual ~Polynomial(){};

        //set linear factor at position
        //adds dummy entries, if position is greater than vectorsize
        void setFactor(const uint pos, const T val)
        {
            if(pos >= _factors.size())
                _factors.resize(pos+1);

            _factors[pos] = val;
        };

        //returns y-coordinate corresponding to x
        T getY(const T x) const
        {
            T y=0;
            const uint degree = getDegree();

            if(!degree)
                return 0;

            for(uint i=0; i<degree; ++i)
                y += _factors[i] * pow(x, (T)(int)i);

            return y;
        };

        inline uint getDegree() const {return _factors.size();};

        void derive()
        {
            if(_factors.size() <= 1)
            {
                clear();
                return;
            }

            for(uint i=0; i<_factors.size()-1; ++i)
                _factors[i] = _factors[i+1] * (i+1);

            _factors.pop_back();
        };

        void integrate()
        {
            _factors.push_back(0);
            for(uint i=_factors.size()-1; i>0; --i)
                _factors[i] = _factors[i-1] / i;
        };

        inline void clear()
        {
            _factors.clear();
            _factors.push_back(0);
        };

        void print() const
        {
            const uint degree = getDegree();

            if(!degree)
            {
                std::cout << "polynomial empty" << std::endl;
                return;
            }

            std::cout << _factors[0];
            for(uint i=1; i<_factors.size(); ++i)
                std::cout << " + " << _factors[i] << "*(x^" << i << ")";

            std::cout << std::endl;
        };

        const Polynomial<T>& operator+=(const T add)
        {
            (*this)[0] += add;
            return *this;
        };

        const Polynomial<T>& operator+=(const Polynomial& other)
        {
            T val;
            const uint otherDegree = other.getDegree();

            if(otherDegree > getDegree())
                _factors.resize(otherDegree);

            for(uint i=0; i<otherDegree; ++i)
            {
                val = other._factors[i] + _factors[i];
                setFactor(i, val);
            }

            return *this;
        };

        const Polynomial<T>& operator*=(const T fac)
        {
            for(uint i=0; i<_factors.size(); ++i)
                _factors[i] *= fac;

            return *this;
        };

        const Polynomial<T>& operator*=(const Polynomial& other)
        {
            const uint degree = getDegree();
            const uint otherDegree = other.getDegree();

            std::vector<T> tmp(_factors);
            _factors.clear();
            _factors.resize(degree + otherDegree - 1);

            T entry;
            for(uint i=0; i<degree; ++i)
            {
                for(uint j=0; j<otherDegree; ++j)
                {
                    entry = tmp[i] * other[j];
                    entry += _factors[i+j];
                    setFactor(i+j, entry);
                }
            }

            return *this;
        };

        const Polynomial<T>& operator/=(const T div)
        {
            for(uint i=0; i<_factors.size(); ++i)
                _factors[i] /= div;

            return *this;
        };

        bool operator==(const Polynomial<T>& other)
        {
            return (_factors == other._factors);
        };

        bool operator!=(const Polynomial<T>& other)
        {
            return (_factors != other._factors);
        };

        const Polynomial<T>& operator=(const Polynomial<T>& other)
        {
            if(*this == other)
                return *this;

            _factors = other._factors;

            return *this;
        };

        inline T operator()(T x) const {return getY(x);};

        //no index check, use with caution
        inline const T& operator[](uint i) const {return _factors[i];};
        inline T& operator[](uint i) {return _factors[i];};

    protected:
        std::vector<T> _factors;

    private:
};

#endif // Polynomial_H
