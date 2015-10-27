//
// Created by Home on 10/9/15.
//

#ifndef PA2_INT_KMEANS_H
#define PA2_INT_KMEANS_H
#include "Cluster.h"
#include <fstream>
#include <iostream>

class KMeans {
    int K;
    Clustering::Cluster* clustArr;
    const double CHANGE_THRESHOLD = 0;

public:
    KMeans(int kk){K=kk;};
    Clustering::Cluster* getClusters() {return clustArr;};
    int getK(){return K;};

    void initialize(Clustering::Cluster &initial, std::string filename);
    void letsCluster();



};

#endif //PA2_INT_KMEANS_H
