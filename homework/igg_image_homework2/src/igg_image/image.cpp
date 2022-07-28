#include "image.h"
#include "io_tools.h"
#include <math.h>
#include <iostream>
using namespace igg;

int Image::rows() const{
    return rows_;
}


int Image::cols() const{
    return cols_;
}


int& Image::at(int row,int col){
    int index = row*rows_+col;
    return data_[index];
}


bool Image::FillFromPgm(const std::string& file_name){
    igg::io_tools::ImageData img_data = igg::io_tools::ReadFromPgm(file_name);
    if(img_data.data.size()==0){
        return false;
    }else{
        cols_ = img_data.cols;
        rows_ = img_data.rows;
        max_val_ = img_data.max_val;
        data_ = std::move(img_data.data);
        return true;
    }

}
void Image::WriteToPgm(const std::string& file_name) const{
    igg::io_tools::ImageData saving_data={
        rows_,
        cols_,
        max_val_,
        data_
    };
    igg::io_tools::WriteToPgm(saving_data,file_name);
}

std::vector<float> Image::ComputeHistogram(int bins) const{
    float bin_size = max_val_*1.0/bins;
    std::vector<float> my_histogram(bins);
    for(auto pixel:data_){
        int bin_idx = (int)floor(pixel/bin_size);
        my_histogram[bin_idx]+=1;
    }
    return my_histogram;
}

void Image::DownScale(int scale){
    int new_row = rows_/scale;
    int new_col = cols_/scale;

    int temp_old_idex = 0;
    std::vector<int> new_data(new_col*new_row);
    for(int row=0;row<new_row;row++){
        for(int col=0;col<new_col;col++){

            temp_old_idex = row*scale*rows_+col*scale;
            new_data[row*new_row+col] = data_[temp_old_idex];
            // std::cout<<row*new_row+col<<" "<<temp_old_idex<<std::endl;
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
    std::vector<int> new_data(new_col*new_row);
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