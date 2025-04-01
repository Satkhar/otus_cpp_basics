// Read files and prints top k word by frequency

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <chrono>

#include <windows.h>
// SetConsoleOutputCP(1251); // Для Windows-1251


const size_t TOPK = 10;

using Counter = std::map<std::string, std::size_t>;

std::string tolower(const std::string &str);

void count_words(std::istream& stream, Counter&);

void count_words_part(const std::vector<std::string>& lines, Counter& local_counter);
void count_words_multithreaded(std::istream& stream, Counter& global_counter, size_t num_threads);

void print_topk(std::ostream& stream, const Counter&, const size_t k);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: topk_words [FILES...]\n";
        return EXIT_FAILURE;
    }

	SetConsoleOutputCP(1251); // Для Windows-1251	1251		CP_UTF8

    auto start = std::chrono::high_resolution_clock::now();
    Counter freq_dict;
	Counter multi_threads_count;

	//-----------------

	// вот эта часть однопоточная
    for (int i = 1; i < argc; ++i) {
        std::ifstream input{argv[i]};
        if (!input.is_open()) {
            return EXIT_FAILURE;
        }
        count_words(input, freq_dict);
    }

    print_topk(std::cout, freq_dict, TOPK);
    auto end_single = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end_single - start);
    std::cout << "Elapsed time of single is " << elapsed_ms.count() << " us\n";

	//-----------------

	// вот эта часть многопоточная
	auto threads_num = std::thread::hardware_concurrency();
	if (threads_num < 2) {
	  threads_num = 2;
	}

	for (int i = 1; i < argc; ++i) {
        std::ifstream input{argv[i]};
        if (!input.is_open()) {
            return EXIT_FAILURE;
        }
        count_words_multithreaded(input, multi_threads_count, threads_num);
    }

	print_topk(std::cout, multi_threads_count, TOPK);
    auto end_multi = std::chrono::high_resolution_clock::now();
    auto elapsed_multi_ms = std::chrono::duration_cast<std::chrono::microseconds>(end_multi - end_single);
    std::cout << "Elapsed time of multi is " << elapsed_multi_ms.count() << " us\n";
   
	auto delta_ms = std::chrono::duration_cast<std::chrono::microseconds>(elapsed_ms - elapsed_multi_ms);
	std::cout << "Delta time is: " << delta_ms.count() << " us\n";
}

std::string tolower(const std::string &str) {
    std::string lower_str;
    std::transform(std::cbegin(str), std::cend(str),
                   std::back_inserter(lower_str),
                   [](unsigned char ch) { return std::tolower(ch); });
    return lower_str;
};

void count_words(std::istream& stream, Counter& counter) {
    std::for_each(std::istream_iterator<std::string>(stream),
                  std::istream_iterator<std::string>(),
                  [&counter](const std::string &s) { ++counter[tolower(s)]; });    
}


// Основная функция для многопоточного подсчета слов
void count_words_multithreaded(std::istream& stream, Counter& global_counter, size_t num_threads) {
    // Шаг 1: Читаем весь файл в вектор строк
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(stream, line)) {
        lines.push_back(line);
    }

    // Шаг 2: Разделяем данные на части
    size_t chunk_size = lines.size() / num_threads;
    std::vector<std::vector<std::string>> chunks(num_threads);
    for (size_t i = 0; i < num_threads; ++i) {
        size_t start = i * chunk_size;
        size_t end = (i == num_threads - 1) ? lines.size() : start + chunk_size;
        chunks[i].insert(chunks[i].end(), lines.begin() + start, lines.begin() + end);
    }

    // Шаг 3: Создаем потоки и локальные счетчики
    std::vector<Counter> local_counters(num_threads);
    std::vector<std::thread> threads;
    for (size_t i = 0; i < num_threads; ++i) {
        threads.emplace_back(count_words_part, std::ref(chunks[i]), std::ref(local_counters[i]));
    }

    // Шаг 4: Ждем завершения всех потоков
    for (auto& thread : threads) {
        thread.join();
    }

    // Шаг 5: Объединяем локальные счетчики в общий
    for (const auto& local_counter : local_counters) {
        for (const auto& [word, count] : local_counter) {
            global_counter[word] += count;
        }
    }
}

void print_topk(std::ostream& stream, const Counter& counter, const size_t k) {
    std::vector<Counter::const_iterator> words;
    words.reserve(counter.size());
    for (auto it = std::cbegin(counter); it != std::cend(counter); ++it) {
        words.push_back(it);
    }

    std::partial_sort(
        std::begin(words), std::begin(words) + k, std::end(words),
        [](auto lhs, auto &rhs) { return lhs->second > rhs->second; });

    std::for_each(
        std::begin(words), std::begin(words) + k,
        [&stream](const Counter::const_iterator &pair) {
            stream << std::setw(4) << pair->second << " " << pair->first
                      << '\n';
        });
}


// Функция для подсчета слов в одной части данных
void count_words_part(const std::vector<std::string>& lines, Counter& local_counter) {
    for (const auto& line : lines) {
        std::istringstream stream(line);
        std::string word;
        while (stream >> word) {
            ++local_counter[tolower(word)];
        }
    }
}