// Copyright Igor Bogoslavskyi, year 2018.
// In case of any problems with the code please contact me.
// Email: igor.bogoslavskyi@uni-bonn.de.

#pragma once

#include <vector>
// #include "strategy.h"
#include "io_strategies/strategy.h"

namespace igg {

class Image {
 public:
  /// A struct within class Image that defines a pixel.
  struct Pixel {
    int red;
    int green;
    int blue;
  };

  // TODO: fill public interface.
  Image(const IoStrategy& io_strategy):io_strategy_(io_strategy){};
  Image(int rows, int cols, const IoStrategy& io_strategy):rows_(rows),cols_(cols),io_strategy_(io_strategy){};
  int rows() const;
  int cols() const;
  Pixel& at(int row,int col);
  void DownScale(int scale);
  void UpScale(int scale);
  bool ReadFromDisk(const std::string& file_name);
  void WriteToDist(const std::string& file_name);

 private:

  // TODO: add missing private members when needed.
  const igg::IoStrategy& io_strategy_;

  int rows_ = 0;
  int cols_ = 0;
  int max_val_ = 255;
  std::vector<Pixel> data_;
};

}  // namespace igg
