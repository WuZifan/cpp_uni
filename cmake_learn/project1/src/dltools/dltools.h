#include <vector>
#pragma once

namespace dl{

struct Box{
    double x1;
    double y1;
    double x2;
    double y2;
};

struct BBOX{
    Box box;
    double score;
};

double IOU(const Box& box1,const Box& box2);

std::vector<BBOX> NMS(std::vector<BBOX>& bboxs,double threshold);

}