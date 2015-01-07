#ifndef LAGRANGE_H
#define LAGRANGE_H

#include "Polynomial.h"

template <typename T> class Lagrange : public Polynomial<T>
{
    public:
        Lagrange(const std::vector<T>& xList, const std::vector<T>& yList)
        {
            if(xList.size() != yList.size())
            {
                printf("\nlists with coordinates differ in size\n");
                exit(1);
            }
            std::vector<Polynomial<T> > polys = buildWeightedPolys(xList);
            buildLagrange(polys, yList);
        };

        virtual ~Lagrange(){};

    protected:
        std::vector<Polynomial<T> > buildWeightedPolys(const std::vector<T>& xList)
        {
            T div;
            Polynomial<T> w_i, linFac;
            linFac.setFactor(1, 1);

            std::vector<Polynomial<T> > polys;
            polys.reserve(xList.size()-1);

            for(uint i=0; i<xList.size(); ++i)
            {
                w_i.clear();
                w_i.setFactor(0, 1);

                for(uint j=0; j<xList.size(); ++j)
                {
                    if(j==i)
                        continue;

                    linFac.setFactor(0, ((-1)*xList[j]));
                    w_i *= linFac;
                }

                polys.push_back(w_i);
            }

            for(uint i=0; i<polys.size(); ++i)
            {
                div = polys[i].getY(xList[i]);
                polys[i] /= div;
            }

            return polys;
        };

        void buildLagrange(std::vector<Polynomial<T> >& polys, const std::vector<T>& yList)
        {
            Polynomial<T> res;
            for(uint i=0; i<polys.size(); ++i)
            {
                polys[i] *= yList[i];
                res += polys[i];
            }

            this->_factors.resize(res.getDegree());
            for(uint i=0; i<res.getDegree(); ++i)
                this->_factors[i] = res[i];
        //    _factors = res._factors;
        };

    private:
};

#endif // LAGRANGE_H
