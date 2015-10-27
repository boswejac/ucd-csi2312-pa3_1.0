//
// Created by Home on 9/15/15.
//

#include "Cluster.h"
#include <sstream>
#include <algorithm>



namespace Clustering {



    Clustering::Cluster::Cluster(const Clustering::Cluster &cluster) {
        size = cluster.getSize();
        points = cluster.getPtr();
        _id = newID();
    };

    Clustering::Cluster &Clustering::Cluster::operator=(const Clustering::Cluster &cluster) {
        Cluster *clustPtr = new Cluster;
        Cluster newClust(cluster);
        clustPtr = &newClust;
        return *clustPtr;

    };

    Clustering::Cluster::~Cluster() {

    };

    void Clustering::Cluster::add(Clustering::PointPtr const &ptr) {

        LNodePtr newPoint = new LNode;
        newPoint->p = ptr;
        newPoint->next = nullptr;

        if (points == nullptr) {
            points = newPoint;
            size++;
            return;
        }

        LNodePtr current = points;

        LNodePtr previous = nullptr;
        bool inserted = false;



        while (current != nullptr) {

            if (*(current->p) > *ptr && !inserted) {

                if(current == points){    ///if we are trying to insert at front

                    newPoint->next = current;
                    points = newPoint;
                    size++;
                    return;
                }


                newPoint->next = current;
                previous->next = newPoint;
                inserted = true;
                size++;
                return;
            }
            previous = current;
            current = current->next;

        }
        if (inserted==false){
            previous->next=newPoint;
            size++;
            return;}
    };



//must deallocate dynamic node
    Clustering::PointPtr const &Clustering::Cluster::remove(Clustering::PointPtr const &ptr) {

        bool avail = false;
        LNodePtr current = points;

        LNodePtr previous = nullptr;
        while (current != nullptr) {
            if (current->p == ptr) {
                avail = true;
                size--;
                if (previous != nullptr) {
                    previous->next = current->next;
                }
                else {
                    points = points->next;
                }
                return current->p;
            }
            previous = current;
            current = current->next;
        }
        if (avail == false)
            std::cout << "could not perform move function: pointer not found in source" << std::endl;


    };

    Clustering::Cluster::Cluster(int sizee, Clustering::LNodePtr pt, bool rl) {
        size = sizee;
        points = pt;
        _release_points = rl;
        _id = newID();
    };

    bool Clustering::Cluster::operator==(const Cluster &rhs) {
        LNodePtr c1 = points;
        LNodePtr c2 = rhs.getPtr();
        bool status;

        while (c1 != nullptr) {
            if (*(c1->p) == *(c2->p)) {
                status = true;
            }
            if (*(c1->p) != *(c2->p)) {
                return false;
            }
            c1 = c1->next;
            c2 = c2->next;
        }
        return status;
    };

//appends second cluster to end of first
    Clustering::Cluster &Clustering::Cluster::operator+=(const Cluster &rhs) {
        LNodePtr current = points;
        for (int i = 0; i < size; i++) {

            if (current->next == nullptr) {
                current->next = rhs.getPtr();
            }
            current = current->next;
        }
        size += rhs.getSize();
        return *this;
    };


    Clustering::Cluster &Clustering::Cluster::operator-=(const Cluster &rhs) {
        LNodePtr current = points;
        LNodePtr previous = NULL;
        LNodePtr currentrh;

        for (int i = 0; i < size; i++) {
            currentrh = rhs.getPtr();

            for (int j = 0; j < rhs.getSize(); j++) {

                if (current->p == currentrh->p) {
                    if (previous == NULL)
                        points = current->next;
                    else
                        previous->next = current->next;

                }

                if (currentrh->next == nullptr)
                    currentrh->next = rhs.getPtr();
                else
                    currentrh = currentrh->next;
            }
            previous = current;
            current = current->next;
        }

        size -= rhs.getSize();
        return *this;

    };

    Clustering::Cluster &Clustering::Cluster::operator+=(Point &rhs) {
        LNodePtr current = points;
        LNodePtr newNode = new LNode;
        newNode->p = &rhs;
        newNode->next = nullptr;


        for (int i = 0; i <= size; i++) {

            if (current->next == nullptr) {
                current->next = newNode;

            }
            current = current->next;

        }


        size++;
        return *this;

    };


    Clustering::Cluster &Clustering::Cluster::operator-=(Point &rhs) {
        LNodePtr current = points;
        LNodePtr previous;


        while (current != nullptr) {

            if (current->p == &rhs) {
                previous->next = current->next;
                //mem leak
            }

            previous = current;
            current = current->next;
        }

        size--;
        return *this;
    };

    Clustering::Cluster const operator+(Clustering::Cluster const &lhs, Clustering::Cluster const &rhs) {
        Clustering::LNodePtr current = lhs.getPtr();
        Clustering::LNodePtr head = lhs.getPtr();
        Clustering::LNodePtr currentrh=rhs.getPtr();
        Cluster plusClust(lhs);



        bool add = true;  //indicator for function completion

        while (currentrh != nullptr) {        //while not the end of rhs list
            add = true;
            if (current == nullptr)
                current = lhs.getPtr();
            while (current != nullptr) {//while not the end of the lhs list

                if (currentrh->p == current->p) {       //if address of pointer1 is address of pointer2
                    add = false;                        //change indicator
                }

                current = current->next;

            }
            if (add == true) {                      //if indicator unchanged
                plusClust.add(currentrh->p);

            }
        currentrh = currentrh->next;
    }
        Clustering::LNodePtr printer = plusClust.getPtr();
        for (int i=0;i< plusClust.getSize();i++) {
            std::cout << *printer->p << std::endl;
            printer=printer->next;
        }
    return plusClust;

    };


    const Clustering::Cluster operator-(const Clustering::Cluster &lhs, const Clustering::Cluster &rhs) {
        Clustering::LNodePtr current = lhs.getPtr();
        Clustering::LNodePtr currentrh = rhs.getPtr();
        Clustering::Cluster minusClust(lhs);

        while (currentrh != nullptr) {

            current = lhs.getPtr();
            for (int i = 0; i < lhs.getSize(); i++) {
                if (current->p == currentrh->p) {
                    minusClust.remove(currentrh->p);
                }
                current = current->next;

            }
            currentrh = currentrh->next;
        }

        return minusClust;
    };

    const Clustering::Cluster operator+(const Clustering::Cluster &lhs, const Clustering::PointPtr &rhs) {
        Clustering::Cluster newClust(lhs);
        Clustering::LNodePtr current = lhs.getPtr();
        bool status = false;
        for (int i = 0;i<lhs.getSize();i++){
            if (current->p == rhs)
                status = true;
        };
        if (status == false)
            newClust.add(rhs);

        return newClust;
    };

    const Clustering::Cluster operator-(const Clustering::Cluster &lhs, const Clustering::PointPtr &rhs) {
        Clustering::Cluster newClust(lhs);
        Clustering::LNodePtr current = lhs.getPtr();
        bool status = false;
        for (int i = 0;i<lhs.getSize();i++){
            if (current->p == rhs)
                status = true;
            current=current->next;
        };
        if (status == true)
            newClust.remove(rhs);

        return newClust;
    };

    std::ostream &operator<<(std::ostream &ostream, const Cluster &clust){

        Clustering::LNodePtr current = clust.getPtr();

        for (int i=0;i< clust.getSize();i++) {
            ostream << *current->p << " : " << clust.getID() << "\n";
            current=current->next;
        }
        return ostream;

    };

    std::istream &operator>>(std::istream &istream, Cluster &cluster) {
        std::string line;
        getline(istream,line);
        int d = std::count(line.begin(),line.end(),',') + 1;
        std::stringstream lineStream(line);
        PointPtr px = new Point(d);
        lineStream >> *px;
        cluster.add(px);

        while (getline(istream, line)) {
            std::stringstream lineStream(line);
            PointPtr px = new Point(d);

            lineStream >> *px;

            cluster.add(px);

        }

        std::cout << "hi" << std::endl;
        return istream;
    };

    void Cluster::computeCentroid() {
        _valid_centroid = true;
        if (points==nullptr){
            double pArray[(0,0,0,0,0)];
            Point p(5,pArray);
            this->setCentroid(&p);
            return;
        }
        PointPtr cent = new Point(this->getPtr()->p->getDim());

        for(LNodePtr current = points; current != nullptr; current = current->next){
            *cent+= *current->p;
        }

        *cent /= (this->getSize() );
        this->setCentroid(cent);

    };

    void Move::perform() {

        target->add(source->remove(pptr));
        target->set_valid(false);
        source->set_valid(false);

    };

    int Cluster::newID() {
        static int theID = 0;
        return theID++;
    };

    void Cluster::pickPoints(int k, Clustering::PointPtr &pointArray) {

        int step = this->getSize()/(k+1);
        LNodePtr current = points;

        for(int i = 0; i<k; i++){
            for(int i =0;i<step;i++) {
                current = current->next;
            }
            pointArray[i]= *current->p;
        }


    };


    double Cluster::interClusterDistance(const Cluster &c1, const Cluster &c2) {
        if(&c1==&c2){
            return 0;
        }
        double sum = 0;
        for(LNodePtr current = c1.getPtr();current != nullptr;current = current->next){
            for(LNodePtr current2 = c2.getPtr();current2 != nullptr; current2 = current2->next){
                sum += current->p->distanceTo(*current2->p);
            }
        }
        return sum/2;
    };


    double Cluster::intraClusterDistance() {
        double sum = 0;
        for(LNodePtr current = points;current != nullptr;current = current->next){
            for(LNodePtr current2 = points;current2 != nullptr; current2 = current2->next){
                sum += current->p->distanceTo(*current2->p);
            }
        }
        return sum/2;
    }

    int Cluster::getClusterEdges() {
        return size*(size-1)/2;
    }

    void Cluster::setCentroid(PointPtr ptr) {
        _centroid = *ptr;
        _valid_centroid=true;
    }
}
