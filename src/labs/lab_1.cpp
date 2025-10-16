#include "lab_1.h"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <string>

std::string Lab1::task1(std::string input_file) {
  cv::Mat image = cv::imread(input_file);

  if (image.empty()) {
    return "Ошибка: не удалось загрузить изображение " + input_file;
  }

  cv::namedWindow("Task 1 - Loaded Image", cv::WINDOW_AUTOSIZE);
  cv::imshow("Task 1 - Loaded Image", image);

  std::string output_file = "output_task1.png";
  bool success = cv::imwrite(output_file, image);

  if (success) {
    cv::waitKey(0);
    cv::destroyWindow("Task 1 - Loaded Image");
    return "Изображение успешно загружено и сохранено как: " + output_file;
  } else {
    cv::destroyWindow("Task 1 - Loaded Image");
    return "Ошибка: не удалось сохранить изображение как " + output_file;
  }
}

void Lab1::task2() {};
void Lab1::task3() {};
void Lab1::task4() {};
