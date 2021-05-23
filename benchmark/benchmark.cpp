#include <fstream>      // ifstream
#include <iostream>     // cout
#include <string>       // string, stoi
#include <string_view>  // string_view
#include <chrono>       // high_resolution_clock, duration_cast, nanoseconds
#include <sstream>      // stringstream

// подключаем вашу структуру данных
#include "data_structure.hpp"
#include "graph.hpp"

using namespace std;
using namespace itis;

// абсолютный путь до набора данных и папки проекта
static constexpr auto kDatasetPath = string_view{PROJECT_DATASET_DIR};

int main() {
  const auto path = string(kDatasetPath);
  cout << "Path to the 'dataset/' folder: " << path << endl;
  // в переменной trials - кол-во прогонов
  int trials = 10;
  // ну тут по имени переменной думаю всё понятно
  string count_of_elements = "100";
  // номер набора данных, тоже меняете)
  string dataset = "01";
  for (int i = 0; i < trials; i++) {

    string line = "1"; // нужна, чтобы прошел первый прогон, так как сначала строка пустая (в следующих операциях точно также)
      // открываем csv файл (в следующих операциях точно также)
    auto input_file = ifstream(path + "/" + dataset + "/" + count_of_elements + ".csv");
    getline(input_file, line);
    Graph_MST g(stoi(line));
      // здесь находится участок кода, время которого необходимо замерить
      // заполнение графа
    if (input_file) {
      while (line != "") {
        getline(input_file, line);
        if (line == "") {
          break;
        }
        vector<int> strvector;
        auto ss = stringstream(line);  // передаете строку (входной аргумент или строку из файла) и обрабатываете ее

        int number = 0;
        ss >> number;
        strvector.push_back(number);
        ss >> number;
        strvector.push_back(number);
        ss >> number;
        strvector.push_back(number);
        g.AddEdge(strvector[0], strvector[1], strvector[2]);
      }
    }
    input_file.close();
    const auto time_point_before = chrono::steady_clock::now();
    g.Prim_MinQueue(0);
    const auto time_point_after = chrono::steady_clock::now();
    const auto time_diff = time_point_after - time_point_before;
    const long time_elapsed_ns = chrono::duration_cast<chrono::microseconds>(time_diff).count();
    cout << time_elapsed_ns << endl;
  }
  return 0;
}
