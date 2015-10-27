//
// Created by Home on 9/15/15.
//

#include "Point.h"
#include <fstream>
#include <cmath>
#include <iostream>


Point::Point(const int dime) {
    dim=dime;
    pArray = new double[dim];

};

Point::Point(const Point &p){
    dim = p.getDim();
    pArray = new double[dim];
    for (int i=0;i<dim;i++){
        pArray[i]=p.getArray(i);
    }
};

Point::Point(int dime, double *pArr) {
    dim = dime;
    pArray = new double[dim];

    for(int i=0;i<dim;i++)
    {
        pArray[i]=pArr[i];
    }
};


Point::~Point() {
    delete [] pArray;
};


int Point::getDim() const {
    return dim;
};

double Point::getArray(int i)const {
    return pArray[i];
};


double Point::distanceTo(Point otherPoint) {
    if (otherPoint.getDim() == dim){
        double total = 0;
        double diff;
        for (int i =0; i <dim; i++){
            diff = getArray(i) - otherPoint.getArray(i);
            total = total + (diff*diff);
        };
        return sqrt(total);
    }
    return 0;
};



void Point::setDim(int i) {
    dim = i;

};

void Point::setArray(int i, double x){
    pArray[i]=x;
};


Point &Point::operator*=(double d) {
    for(int i =0;i<dim;i++){
        pArray[i]=(pArray[i]*d);
    };
};

Point &Point::operator/=(double d) {
    for(int i =0;i<dim;i++){
        pArray[i] = pArray[i] / d;
};
};


Point Point::operator*(double d) const {
    Point p(this->getDim());
    for(int i =0;i<dim;i++){
        p.setArray(i,pArray[i]*d);
    };
    return p;
};

Point Point::operator/(double d) const {
    Point p(this->getDim());
    for(int i =0;i<dim;i++){
        p.setArray(i,pArray[i]/d);
    };
    return p;
};


Point &operator+=(Point &point, const Point &point1) {
    for (int i=0;i< point.getDim();i++){
        point.setArray(i,point1.getArray(i)+point.getArray(i));
    };
    return point;
};

Point &operator-=(Point &point, const Point &point1) {
    for (int i=0;i< point.getDim();i++){
        point.setArray(i,point.getArray(i)-point1.getArray(i));
    };
    return point;
};

const Point operator+(const Point &point, const Point &point1) {
    Point p2(point.getDim());
    for (int i=0;i< point.getDim();i++){
        p2.setArray(i,point.getArray(i)+point1.getArray(i));
    };
    return p2;
};

const Point operator-(const Point &point, const Point &point1) {
    Point p2(point.getDim());
    for (int i=0;i< point.getDim();i++){
        p2.setArray(i,point1.getArray(i)+point.getArray(i));
    };
    return p2;
};

bool operator<(const Point &point, const Point &point1) {

    for (int i=0;i< point.getDim();i++){
        if (point.getArray(i) < point1.getArray(i)){
            return true;
        };
        if (point.getArray(i) > point1.getArray(i)){
            return false;
        };

    };
    return false;
};

bool operator>(const Point &point, const Point &point1) {
    for (int i=0;i< point.getDim();i++){
        if (point.getArray(i) > point1.getArray(i)){
            return true;
        };
        if (point.getArray(i) < point1.getArray(i)){
            return false;
        };

    };
    return false;
};

bool operator<=(const Point &point, const Point &point1) {
    for (int i=0;i< point.getDim();i++){
        if ((point.getArray(i) < point1.getArray(i))||(point.getArray(i) == point1.getArray(i))){
            return true;
        };
        if (point.getArray(i) > point1.getArray(i)){
            return false;
        };

    };
    return false;
};

bool operator>=(const Point &point, const Point &point1) {
    for (int i=0;i< point.getDim();i++){
        if ((point.getArray(i) > point1.getArray(i))||(point.getArray(i) == point1.getArray(i))){
            return true;
        };
        if (point.getArray(i) < point1.getArray(i)){
            return false;
        };

    };
    return false;
};

bool operator==(const Point &point, const Point &point1) {
    bool status = false;
    for (int i=0;i< point.getDim();i++){
        if (point.getArray(i) == point1.getArray(i)){
            status = true;
        };
        if (point.getArray(i) != point1.getArray(i)){
            return false;
        };

    };
    return status;
};

bool operator!=(const Point &point, const Point &point1) {
    bool status = false;
    for (int i=0;i< point.getDim();i++){
        if (point.getArray(i) == point1.getArray(i)){
            status = false;
        };
        if (point.getArray(i) != point1.getArray(i)){
            return true;
        };

    };
    return status;
};

std::ostream &operator<<(std::ostream &ostream, const Point &point) {

    for (int i=0;i<point.getDim();i++){
        if (i+1 !=point.getDim()) {
            ostream << point.getArray(i) << ", ";
        }
        else {
            ostream << point.getArray(i);
        };
    };

    return ostream;
};

std::istream &operator>>(std::istream &istream, Point &point) {
    std::string value;


    int i = 0;

    double d;
    while (getline(istream, value, ',')) {
        d = stod(value);
        point.setArray(i++, d);
    };
    return istream;
};