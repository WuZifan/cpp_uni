#include "image.h"
#include <iostream>

using namespace igg;

int Image::rows() const{
    return rows_;
}

int Image::cols() const{
    return cols_;
}

Image::Pixel& Image::at(int row,int col){
    return data_[row*rows_+col];
}

void Image::DownScale(int scale){
    int new_row = rows_/scale;
    int new_col = cols_/scale;

    int temp_old_idex = 0;
    std::vector<Image::Pixel> new_data(new_col*new_row);
    for(int row=0;row<new_row;row++){
        for(int col=0;col<new_col;col++){
            temp_old_idex = row*scale*rows_+col*scale;
            new_data[row*new_row+col] = data_[temp_old_idex];
        }
    }
    rows_ = new_row;
    cols_ = new_col;
    data_ = std::move(new_data);
}

void Image::UpScale(int scale){
    int new_col = cols_*scale;
    int new_row = rows_*scale;
    // std::cout<<"aaa: "<<rows_<<std::endl;
    int temp_old_idex = 0;
    std::vector<Image::Pixel> new_data(new_col*new_row);
    for(int row=0;row<new_row;row++){
        for(int col=0;col<new_col;col++){
            temp_old_idex = rows_*((int)row/scale)+(int)col/scale;
            new_data[row*new_row+col] = data_[temp_old_idex];
        }
    }
    rows_ = new_row;
    cols_ = new_col;
    data_ = std::move(new_data);
}

void Image::WriteToDist(const std::string& file_name){
    std::vector<std::vector<int> > saving_data;
    for(auto pixel:data_){
        std::vector<int> temp_pixel{pixel.red,pixel.green,pixel.blue};
        saving_data.push_back(temp_pixel);
    }
    igg::ImageData finla_saving_data = {
        rows_,
        cols_,
        max_val_,
        saving_data
    };
    bool saving_status = io_strategy_.Write(file_name,finla_saving_data);
    if(saving_status){
        std::cout<<"Write to "<<file_name<<" success!"<<std::endl;
    }else{
        std::cout<<"Write to "<<file_name<<" fail!"<<std::endl;
    }
}

bool Image::ReadFromDisk(const std::string& file_name){
    igg::ImageData read_data = io_strategy_.Read(file_name);
    rows_ = read_data.rows;
    cols_ = read_data.cols;
    max_val_ = read_data.max_val;
    for(auto vec_pixel:read_data.data){
        Image::Pixel temp_pixel = {
            vec_pixel[0],
            vec_pixel[1],
            vec_pixel[2]
        };
        data_.push_back(temp_pixel);
    }
    
    if(data_.size()>0){
        return true;
    }else{
        return false;
    }
}