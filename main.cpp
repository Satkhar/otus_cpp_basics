#include <algorithm>
#include <atomic>
#include <chrono>
#include <iostream>
#include <limits>
#include <thread>
#include <vector>

#include "CRC32.hpp"
#include "IO.hpp"

/// @brief Переписывает последние 4 байта значением value
void replaceLastFourBytes(std::vector<char> &data, uint32_t value) {
  std::copy_n(reinterpret_cast<const char *>(&value), 4, data.end() - 4);
}

/**
 * @brief Формирует новый вектор с тем же CRC32, добавляя в конец оригинального
 * строку injection и дополнительные 4 байта
 * @details При формировании нового вектора последние 4 байта не несут полезной
 * нагрузки и подбираются таким образом, чтобы CRC32 нового и оригинального
 * вектора совпадали
 * @param original оригинальный вектор
 * @param injection произвольная строка, которая будет добавлена после данных
 * оригинального вектора
 * @return новый вектор
 */
std::vector<char> hack(const std::vector<char> &original,
                       const std::string &injection) {
  const uint32_t originalCrc32 = crc32(original.data(), original.size());

  std::vector<char> result(original.size() + injection.size() + 4);
  auto it = std::copy(original.begin(), original.end(), result.begin());
  std::copy(injection.begin(), injection.end(), it);

  const size_t maxVal = std::numeric_limits<uint32_t>::max();

  auto threads_num = std::thread::hardware_concurrency();
  if (threads_num < 2) {
    threads_num = 2;
  }
  // threads_num = 1;

  const auto range_on_thread = maxVal / threads_num;
  const auto const_result_crc32 = crc32(result.data(), result.size() - 4);
  std::atomic<uint32_t> founded_val{0};
  std::atomic<bool> stop{false};

  auto lambda = [&result, const_result_crc32, originalCrc32, &founded_val,
                 &stop](size_t start, size_t end) {
    std::vector<char> local_res = result;
    for (size_t i = start; (i < end) && (stop != true); ++i) {
      // Заменяем последние четыре байта на значение i
      replaceLastFourBytes(local_res, uint32_t(i));
      // Вычисляем CRC32 текущего вектора result
      auto currentCrc32 = crc32(local_res.data() + (local_res.size() - 4), 4,
                                const_result_crc32);

      if (currentCrc32 == originalCrc32) {
        std::cout << "Success\n";
        uint32_t expected = 0;
        if (founded_val.compare_exchange_strong(expected,
                                                static_cast<uint32_t>(i))) {
          stop = true;
        }
        return;
      }
    }
  };

  std::vector<std::thread> threads;
  for (size_t i = 1; i < threads_num; ++i) {
    auto start = i * range_on_thread;
    auto finish = (i == (threads_num - 1)) ? maxVal : start + range_on_thread;
    threads.emplace_back(lambda, start, finish);
  }

  lambda(0, range_on_thread);

  for (auto &t : threads) {
    t.join();
  }

  if (stop) {
    replaceLastFourBytes(result, founded_val);
    return result;
  }

  throw std::logic_error("Can't hack");
}

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "Call with two args: " << argv[0]
              << " <input file> <output file>\n";
    return 1;
  }

  auto start_time = std::chrono::high_resolution_clock::now();

  try {
    const std::vector<char> data = readFromFile(argv[1]);
    const std::vector<char> badData = hack(data, "He-he-he");
    writeToFile(argv[2], badData);
  } catch (std::exception &ex) {
    std::cerr << ex.what() << '\n';
    return 2;
  }

  auto end_time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end_time - start_time;
  std::cout << "Time is: " << elapsed.count() << " sec" << std::endl;

  return 0;
}
