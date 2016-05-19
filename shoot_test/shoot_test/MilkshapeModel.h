#pragma  once 

#include "Model.h"

struct BoundingBox
{
    float xmin, ymin, zmin;
    float xmax, ymax, zmax;
};

class MilkshapeModel :public Model
{
public :
    MilkshapeModel();

    ~MilkshapeModel();

    bool loadModelData(const char *filename);
     
    void updateTransfMatrix();
    void drawBoundingBox();
    BoundingBox getTBbox(){ return t_bbox; };

private:
    BoundingBox bbox;
    BoundingBox t_bbox;
};