#pragma once

#include <vector>
#include <string>

namespace igg {

class Image {
 public:
  ///////////////////// Create the public interface here ///////////////////////
  Image(){};
  Image(int rows,int cols): rows_(rows), cols_(cols) {};

  int rows() const;
  int cols() const;
  int& at(int row,int col);
  bool FillFromPgm(const std::string& file_name);
  void WriteToPgm(const std::string& file_name) const;
  std::vector<float> ComputeHistogram(int bins) const;
  void DownScale(int scale);
  void UpScale(int scale);

 private:
  int rows_ = 0;
  int cols_ = 0;
  int max_val_ = 255;
  std::vector<int> data_;
};

}  // namespace igg
