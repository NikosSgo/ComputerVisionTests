#ifndef MATH_OPERATIONS_H
#define MATH_OPERATIONS_H
#include "string"
#include <opencv2/core.hpp>

class Lab1 {
public:
  static std::string task1(std::string input_file);
  static void task3();
  static cv::Mat task2_grayscale(const cv::Mat &bgr_frame);
  static cv::Mat task2_hsv(const cv::Mat &bgr_frame);
  static void task4();
  static void task5();
};

#endif
