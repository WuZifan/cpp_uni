#include "dltools.h"
#include <algorithm>

// using namespace dl;

double dl::IOU(const dl::Box& box1,const dl::Box& box2){
    double max_x1 = std::max(box1.x1,box2.x1);
    double max_y1 = std::max(box1.y1,box2.y1);
    double min_x2 = std::min(box1.x2,box2.x2);
    double min_y2 = std::min(box1.y2,box2.y2);
    double inter_area = std::max(min_x2-max_x1+1,0.0)*std::max(min_y2-max_y1+1,0.0);
    double area1 = (box1.x2-box1.x1+1)*(box1.y2-box1.y1+1);
    double area2 = (box2.x2-box2.x1+1)*(box2.y2-box2.y1+1);
    double iou = inter_area/(area1+area2-inter_area);
    return iou;
}

bool Compare(const dl::BBOX& bbox1, const dl::BBOX& bbox2){
        return bbox1.score>bbox2.score;
}

std::vector<dl::BBOX> dl::NMS(std::vector<dl::BBOX>& bboxs,double threshold){
    std::vector<int> mark_vec(bboxs.size(),0);
    std::sort(bboxs.begin(),bboxs.end(),Compare);
    double temp_iou = 0.0;
    for(int i=0;i<bboxs.size();i++){
        if(mark_vec[i]==0){
            for(int j=i+1;j<bboxs.size();j++){
                temp_iou = IOU(bboxs[i].box,bboxs[j].box);
                if(temp_iou>=threshold){
                    mark_vec[j]=1;
                }
            }
        }
    }
    std::vector<dl::BBOX> ret_bbox;
    for(int i=0;i<mark_vec.size();i++){
        if(mark_vec[i]==0){
            ret_bbox.push_back(bboxs[i]);
        }
    }
    return ret_bbox;
}

