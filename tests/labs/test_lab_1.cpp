#include "lab_1.h"
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>

namespace fs = std::filesystem;

// Вспомогательная функция для получения пути к тестовым файлам
std::string getTestFilePath(const std::string &filename) {
  // Файлы уже находятся в build/tests/data/
  return "tests/data/" + filename;
}

bool fileExists(const std::string &filename) { return fs::exists(filename); }

class Lab1Test : public ::testing::Test {
protected:
  Lab1 lab;

  void SetUp() override {
    // Очищаем только выходные файлы
    if (fileExists("output_task1.png")) {
      fs::remove("output_task1.png");
    }
  }

  void TearDown() override {
    // Очищаем только выходные файлы
    if (fileExists("output_task1.png")) {
      fs::remove("output_task1.png");
    }
  }
};

// Тест 1: Успешная загрузка и сохранение JPEG
TEST_F(Lab1Test, Task1_SuccessfulLoadAndSaveJPEG) {
  std::string input_file = getTestFilePath("test_image.jpg");

  if (fileExists(input_file)) {
    std::string result = lab.task1(input_file);

    EXPECT_NE(result.find("успешно"), std::string::npos);
    EXPECT_NE(result.find("output_task1.png"), std::string::npos);
    EXPECT_TRUE(fileExists("output_task1.png"));
  } else {
    ADD_FAILURE() << "Тестовое изображение не найдено: " << input_file;
    std::cout << "Текущая директория: " << fs::current_path() << std::endl;
    std::cout << "Содержимое data директории:" << std::endl;
    for (const auto &entry : fs::directory_iterator("data")) {
      std::cout << "  " << entry.path() << std::endl;
    }
  }
}

// Тест 2: Успешная загрузка и сохранение PNG
TEST_F(Lab1Test, Task1_SuccessfulLoadAndSavePNG) {
  std::string input_file = getTestFilePath("test_image.png");

  if (fileExists(input_file)) {
    std::string result = lab.task1(input_file);

    EXPECT_NE(result.find("успешно"), std::string::npos);
    EXPECT_NE(result.find("output_task1.png"), std::string::npos);
    EXPECT_TRUE(fileExists("output_task1.png"));
  } else {
    ADD_FAILURE() << "Тестовое изображение не найдено: " << input_file;
  }
}

// Тест 3: Успешная загрузка и сохранение BMP
TEST_F(Lab1Test, Task1_SuccessfulLoadAndSaveBMP) {
  std::string input_file = getTestFilePath("test_image.bmp");

  if (fileExists(input_file)) {
    std::string result = lab.task1(input_file);

    EXPECT_NE(result.find("успешно"), std::string::npos);
    EXPECT_NE(result.find("output_task1.png"), std::string::npos);
    EXPECT_TRUE(fileExists("output_task1.png"));
  } else {
    ADD_FAILURE() << "Тестовое изображение не найдено: " << input_file;
  }
}

// Тест 4: Обработка несуществующего файла
TEST_F(Lab1Test, Task1_NonExistentFile) {
  std::string input_file = "non_existent_image.jpg";

  std::string result = lab.task1(input_file);

  EXPECT_NE(result.find("Ошибка"), std::string::npos);
  EXPECT_NE(result.find(input_file), std::string::npos);
  EXPECT_FALSE(fileExists("output_task1.png"));
}

// Тест 5: Проверка формата выходного файла (PNG)
TEST_F(Lab1Test, Task1_OutputIsPNG) {
  std::string input_file = getTestFilePath("test_image.jpg");

  if (fileExists(input_file)) {
    std::string result = lab.task1(input_file);

    EXPECT_NE(result.find(".png"), std::string::npos);
    EXPECT_TRUE(fileExists("output_task1.png"));

    // Проверяем сигнатуру PNG файла
    if (fileExists("output_task1.png")) {
      std::ifstream file("output_task1.png", std::ios::binary);
      if (file) {
        unsigned char header[8];
        file.read(reinterpret_cast<char *>(header), 8);
        // Проверяем сигнатуру PNG: 89 50 4E 47 0D 0A 1A 0A
        EXPECT_EQ(header[0], 0x89);
        EXPECT_EQ(header[1], 0x50); // P
        EXPECT_EQ(header[2], 0x4E); // N
        EXPECT_EQ(header[3], 0x47); // G
      }
    }
  } else {
    ADD_FAILURE() << "Тестовое изображение не найдено: " << input_file;
  }
}

// Тест 6: Пустое имя файла
TEST_F(Lab1Test, Task1_EmptyFilename) {
  std::string result = lab.task1("");

  EXPECT_NE(result.find("Ошибка"), std::string::npos);
  EXPECT_FALSE(fileExists("output_task1.png"));
}

// Тест 7: Поведение при специальных символах в имени файла
TEST_F(Lab1Test, Task1_SpecialCharactersInFilename) {
  std::string input_file = "file with spaces.jpg";

  // Создаем тестовый файл с пробелами для теста
  std::ofstream test_file(input_file);
  if (test_file) {
    test_file << "fake image content";
    test_file.close();

    std::string result = lab.task1(input_file);
    // Проверяем, что не падает с исключением
    EXPECT_FALSE(result.empty());

    // Удаляем временный файл
    fs::remove(input_file);
  }
}
// Тесты для задачи 2: Преобразование цветовых пространств

// Тест 8: Успешное преобразование BGR → Grayscale
TEST_F(Lab1Test, Task2_Grayscale_Success) {
  // Создаем тестовое BGR изображение
  cv::Mat bgr_image(100, 100, CV_8UC3, cv::Scalar(100, 150, 200));

  cv::Mat result = lab.task2_grayscale(bgr_image);

  // Проверяем, что результат не пустой
  EXPECT_FALSE(result.empty());

  // Проверяем, что результат в оттенках серого (1 канал)
  EXPECT_EQ(result.channels(), 1);

  // Проверяем тип данных
  EXPECT_EQ(result.type(), CV_8UC1);

  // Проверяем размеры
  EXPECT_EQ(result.rows, bgr_image.rows);
  EXPECT_EQ(result.cols, bgr_image.cols);
}

// Тест 9: Успешное преобразование BGR → HSV
TEST_F(Lab1Test, Task2_HSV_Success) {
  // Создаем тестовое BGR изображение
  cv::Mat bgr_image(100, 100, CV_8UC3, cv::Scalar(100, 150, 200));

  cv::Mat result = lab.task2_hsv(bgr_image);

  // Проверяем, что результат не пустой
  EXPECT_FALSE(result.empty());

  // Проверяем, что результат в HSV (3 канала)
  EXPECT_EQ(result.channels(), 3);

  // Проверяем тип данных
  EXPECT_EQ(result.type(), CV_8UC3);

  // Проверяем размеры
  EXPECT_EQ(result.rows, bgr_image.rows);
  EXPECT_EQ(result.cols, bgr_image.cols);
}

// Тест 10: Преобразование Grayscale - исключение при пустом фрейме
TEST_F(Lab1Test, Task2_Grayscale_EmptyFrame) {
  cv::Mat empty_frame;

  EXPECT_THROW({ lab.task2_grayscale(empty_frame); }, std::invalid_argument);
}

// Тест 11: Преобразование HSV - исключение при пустом фрейме
TEST_F(Lab1Test, Task2_HSV_EmptyFrame) {
  cv::Mat empty_frame;

  EXPECT_THROW({ lab.task2_hsv(empty_frame); }, std::invalid_argument);
}

// Тест 12: Преобразование Grayscale - исключение при неверном формате
TEST_F(Lab1Test, Task2_Grayscale_WrongFormat) {
  // Создаем изображение с 1 каналом (уже grayscale)
  cv::Mat grayscale_image(100, 100, CV_8UC1, cv::Scalar(128));

  EXPECT_THROW(
      { lab.task2_grayscale(grayscale_image); }, std::invalid_argument);
}

// Тест 13: Преобразование HSV - исключение при неверном формате
TEST_F(Lab1Test, Task2_HSV_WrongFormat) {
  // Создаем изображение с 1 каналом (grayscale)
  cv::Mat grayscale_image(100, 100, CV_8UC1, cv::Scalar(128));

  EXPECT_THROW({ lab.task2_hsv(grayscale_image); }, std::invalid_argument);
}

// Тест 14: Проверка корректности преобразования Grayscale
TEST_F(Lab1Test, Task2_Grayscale_CorrectConversion) {
  // Создаем BGR изображение с известным цветом
  cv::Mat bgr_image(10, 10, CV_8UC3, cv::Scalar(100, 150, 200));

  cv::Mat grayscale = lab.task2_grayscale(bgr_image);

  // Проверяем, что все пиксели имеют одинаковое значение (для однородного
  // изображения)
  cv::Scalar mean = cv::mean(grayscale);
  double first_pixel = grayscale.at<uchar>(0, 0);

  // Допускаем небольшую погрешность
  EXPECT_NEAR(mean[0], first_pixel, 1.0);

  // Проверяем, что значение в допустимом диапазоне
  EXPECT_GE(first_pixel, 0);
  EXPECT_LE(first_pixel, 255);
}

// Тест 15: Проверка корректности преобразования HSV
TEST_F(Lab1Test, Task2_HSV_CorrectConversion) {
  // Создаем BGR изображение с известным цветом
  cv::Mat bgr_image(10, 10, CV_8UC3, cv::Scalar(100, 150, 200));

  cv::Mat hsv = lab.task2_hsv(bgr_image);

  // Проверяем, что значения HSV в правильных диапазонах
  cv::Scalar mean = cv::mean(hsv);

  // H: 0-179, S: 0-255, V: 0-255 в OpenCV
  EXPECT_GE(mean[0], 0); // Hue
  EXPECT_LE(mean[0], 179);
  EXPECT_GE(mean[1], 0); // Saturation
  EXPECT_LE(mean[1], 255);
  EXPECT_GE(mean[2], 0); // Value
  EXPECT_LE(mean[2], 255);
}

// Тест 16: Сравнение преобразований для разных цветов
TEST_F(Lab1Test, Task2_CompareDifferentColors) {
  // Тестируем на разных цветах
  std::vector<cv::Scalar> test_colors = {
      cv::Scalar(255, 0, 0),     // Синий
      cv::Scalar(0, 255, 0),     // Зеленый
      cv::Scalar(0, 0, 255),     // Красный
      cv::Scalar(255, 255, 255), // Белый
      cv::Scalar(0, 0, 0)        // Черный
  };

  for (const auto &color : test_colors) {
    cv::Mat bgr_image(10, 10, CV_8UC3, color);

    cv::Mat grayscale = lab.task2_grayscale(bgr_image);
    cv::Mat hsv = lab.task2_hsv(bgr_image);

    EXPECT_FALSE(grayscale.empty());
    EXPECT_FALSE(hsv.empty());
    EXPECT_EQ(grayscale.channels(), 1);
    EXPECT_EQ(hsv.channels(), 3);
  }
}
