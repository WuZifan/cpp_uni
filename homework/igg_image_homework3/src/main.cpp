#include <iostream>
#include "image.h"
#include "io_strategies/dummy_strategy.h"
#include "io_strategies/png_strategy.h"

int main(){
    igg::DummyIoStrategy dummy_io_strategy;
    // igg::Image image_1(dummy_io_strategy);
    igg::PngIoStrategy png_io_strategy;
    igg::Image image_1(png_io_strategy);

    std::string image_path = "/Users/zifanwu/VSCodeProjects/cpp_uni/homework/igg_image_homework3/data/test.png";
    bool read_status = image_1.ReadFromDisk(image_path);
    // std::cout<<read_status<<std::endl;
}