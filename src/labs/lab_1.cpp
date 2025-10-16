#include "lab_1.h"
#include "iostream"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
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

// Преобразование BGR → Grayscale
cv::Mat Lab1::task2_grayscale(const cv::Mat &bgr_frame) {
  if (bgr_frame.empty()) {
    throw std::invalid_argument("Входной фрейм пустой");
  }

  if (bgr_frame.channels() != 3) {
    throw std::invalid_argument(
        "Входной фрейм должен быть в формате BGR (3 канала)");
  }

  cv::Mat grayscale;
  cv::cvtColor(bgr_frame, grayscale, cv::COLOR_BGR2GRAY);

  return grayscale;
}

// Преобразование BGR → HSV
cv::Mat Lab1::task2_hsv(const cv::Mat &bgr_frame) {
  if (bgr_frame.empty()) {
    throw std::invalid_argument("Входной фрейм пустой");
  }

  if (bgr_frame.channels() != 3) {
    throw std::invalid_argument(
        "Входной фрейм должен быть в формате BGR (3 канала)");
  }

  cv::Mat hsv;
  cv::cvtColor(bgr_frame, hsv, cv::COLOR_BGR2HSV);

  return hsv;
}

void Lab1::task2() {
  // Демонстрационная функция для отображения результатов
  cv::Mat bgr_frame = cv::imread("test_image.jpg");

  if (bgr_frame.empty()) {
    std::cout << "Не удалось загрузить изображение для демонстрации"
              << std::endl;
    return;
  }

  try {
    // Преобразование в Grayscale
    cv::Mat grayscale = task2_grayscale(bgr_frame);

    // Преобразование в HSV
    cv::Mat hsv = task2_hsv(bgr_frame);

    // Отображение результатов
    cv::namedWindow("Original BGR", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Grayscale", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("HSV", cv::WINDOW_AUTOSIZE);

    cv::imshow("Original BGR", bgr_frame);
    cv::imshow("Grayscale", grayscale);
    cv::imshow("HSV", hsv);

    std::cout << "Нажмите любую клавишу для закрытия окон..." << std::endl;
    cv::waitKey(0);

    cv::destroyAllWindows();

  } catch (const std::exception &e) {
    std::cout << "Ошибка: " << e.what() << std::endl;
  }
}

void Lab1::task3() {};
void Lab1::task4() {};
