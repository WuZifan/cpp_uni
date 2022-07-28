#include "io_tools.h"
#include "image.h"
#include <string>
#include <iostream>
#include <vector>

std::vector<int> data_ = {1,2,3,4,5};
int& get(){
    return data_[1];
}

int main(){
    std::string image_path = "/Users/zifanwu/VSCodeProjects/cpp_uni/homework/igg_image_homework2/data/lena.ascii.pgm";
    igg::Image my_image;
    bool load_state = my_image.FillFromPgm(image_path);
    std::cout<< my_image.rows() <<"  "<<my_image.cols()<<" "<<load_state<<std::endl;
    std::cout<<my_image.at(10,10)<<std::endl;
    for(int i=100;i<200;i++){
        for(int j=100;j<200;j++){
            my_image.at(i,j)=255;
        }
    }
    // my_image.at(10,10)=255;
    // std::cout<<my_image.at(10,10)<<std::endl;
    my_image.DownScale(2);
    my_image.WriteToPgm("./result_down.pgm");

    my_image.UpScale(4);
    my_image.WriteToPgm("./result_up.pgm");



    // igg::io_tools::ImageData img_data = igg::io_tools::ReadFromPgm("./data.jpeg");

    // std::cout<<img_data.cols<<std::endl;
    // int a =1;
    // int& b=a;
    // int c = b;
    // c = 2;
    // std::cout<<c<<std::endl;
    // std::cout<<a<<std::endl;
    // std::cout<<"666"<<std::endl;
    // int val = get();
    // std::cout<<val<<std::endl;
    // get()=3;
    // int aa=3;
    // int bb=2;
    // std::cout<<"result: "<<aa/bb<<std::endl;


    // for(auto item:data_){
    //     std::cout<<item<<std::endl;
    // }
    
    return 0;
}