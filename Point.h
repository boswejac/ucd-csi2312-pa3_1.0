//
// Created by Home on 9/15/15.
//


#ifndef PA2_INT_POINT_H
#define PA2_INT_POINT_H

#include <iostream>

class Point {

private:
    int dim;
    double *pArray;

public:
    // Constructors
    Point(){dim=0,pArray = new double[dim];};
    Point(int dime);
    Point(int dime, double pArr[dime]);
    Point(const Point &p);

    ~Point();

    int getDim() const;
    double getArray(int i)const;
    void setArray(int i, double x);

    void setDim(int i);


    double distanceTo(Point otherPoint);

    //Operators
    Point &operator*=(double);
    Point &operator/=(double);
    Point operator*(double) const;
    Point operator/(double) const;




    friend Point &operator+=(Point &, const Point &);
    friend Point &operator-=(Point &, const Point &);
    friend const Point operator+(const Point &, const Point &);
    friend const Point operator-(const Point &, const Point &);

    friend bool operator==(const Point &, const Point &);
    friend bool operator!=(const Point &, const Point &);

    friend bool operator<(const Point &, const Point &);
    friend bool operator>(const Point &, const Point &);
    friend bool operator<=(const Point &, const Point &);
    friend bool operator>=(const Point &, const Point &);

    friend std::ostream &operator<<(std::ostream &, const Point &);
    friend std::istream &operator>>(std::istream &, Point &);

};

#endif //PA2_INT_POINT_H
