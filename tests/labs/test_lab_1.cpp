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
