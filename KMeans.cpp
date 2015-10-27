//
// Created by Home on 10/9/15.
//

#include "KMeans.h"
#include <tgmath.h>

void KMeans::initialize(Clustering::Cluster &initial, std::string filename) {

    //read in points
    Clustering::Cluster* array = new Clustering::Cluster[K];
    clustArr = array;

    std::ifstream file;
    file.open(filename,std::ifstream::in);
    if (file.is_open()) {
        file >> initial;
    }
    else
        std::cout << "cant open file" << std::endl;
    file.close();

    //set initial centroids
    Clustering::PointPtr plist = new Point[K];
    initial.pickPoints(K,plist);



    for(int i = 0; i<K;i++){

        clustArr[i].setCentroid(&plist[i]);
    }

    //fill clusters


    for(Clustering::LNodePtr current = initial.getPtr(); current!=nullptr; current=current->next){         //for each point in cluster


        double min = current->p->distanceTo(clustArr[0].getCentroid());
        int choiceIndex=0;

        for(int z = 0; z < K; z++) {    //for all clusters
            if (current->p->distanceTo(clustArr[z].getCentroid()) < min) {
                min = current->p->distanceTo(clustArr[z].getCentroid());
                choiceIndex = z;
            }
        }

        Clustering::Move(current->p,&initial,&clustArr[choiceIndex]);
        }







};










void KMeans::letsCluster() {

    double score = 1;
    double prevScore;
    double scoreDif = 10;

    while (scoreDif > .01) {

        for (int i = 0; i < K; i++) {         // loop through cluster

            for (Clustering::LNodePtr current = clustArr[i].getPtr();
                 current != nullptr; current = current->next) {         //loop through points
                    double min = current->p->distanceTo(clustArr[0].getCentroid());

                    int choiceIndex = 0;

                    for (int z = 0; z < K; z++) {    //check distance to each cluster, pick destination cluster

                        if (current->p->distanceTo(clustArr[z].getCentroid()) < min) {
                            min = current->p->distanceTo(clustArr[z].getCentroid());
                            choiceIndex = z;
                        }
                 }

                if (choiceIndex != i){//if we need to move to a new cluster

                    Clustering::Move(current->p, &clustArr[i], &clustArr[choiceIndex]);}/////////////////////////////////////////////////

                //reset centroids
                for (int i = 0; i < K; i++) {
                    if (clustArr[i].getValid() == false){

                        clustArr[i].computeCentroid();}
                }
            }


        }
        //calc score
        double intraSum = 0;
        double interSum = 0;

        for (int i = 0; i < K; i++) {
            intraSum += clustArr[i].intraClusterDistance();
            for (int j = 0; j < K; j++) {
                interSum += clustArr[i].interClusterDistance(clustArr[i], clustArr[j]);
            };
        };

        interSum /= 2;
        double interAvg = interSum / K;
        double intraAvg = intraSum / K;

        prevScore = score;
        score = intraAvg / interAvg;
        scoreDif = fabs(score - prevScore);
        std::cout << "score: " << score << std::endl;



   };

};
