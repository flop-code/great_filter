#include <iostream>
#include <fstream>
#include "trie.cpp"

#define MIN_LINE_LENGTH 8
#define MAX_LINE_LENGTH 32

void filter_insert(Trie &trie, const std::string_view &str) {
    if (str.length() >= MIN_LINE_LENGTH && str.length() <= MAX_LINE_LENGTH)
        trie.insert(str);
}

int main(int argc, char **argv) {
    Trie trie;
    std::string buffer;
    buffer.resize(BUFFER_SIZE);

    for (int filename_ind = 1; filename_ind < argc; filename_ind++) {
        std::ifstream file(argv[filename_ind]);
        file.seekg(0, std::ios::end);
        const std::streampos file_size = file.tellg();
        file.seekg(0, std::ios::beg);

        if (!file.is_open()) {
            std::cerr << "Error while opening the file: " << argv[filename_ind] << std::endl;
            return 1;
        }

        while (file.read(&buffer[0], BUFFER_SIZE) || file.gcount() > 0) {
            const std::streampos current_pos = file.tellg();
            if (current_pos > -1)
                std::cout << "Reading... (~" << (100*current_pos/file_size) << "\% of "
                          << argv[filename_ind] << ")\r" << std::flush;
            else
                std::cout << "Processing... (" << argv[filename_ind] << ")\033[K\r" << std::flush;
                
            size_t start = 0, end = buffer.find('\n');

            while (end != std::string::npos) {
                const std::string_view line(buffer.data() + start, end - start);
                filter_insert(trie, line);
                start = end + 1;
                end = buffer.find('\n', start);
            }
            if (start < buffer.size()) {
                std::string_view line(buffer.data() + start);
                filter_insert(trie, line);
            }
        }

        file.close();

        std::ofstream output_file("output.txt");
        if (!output_file.is_open()) {
            std::cerr << "Error while opening the output file." << std::endl;
            return 1;
        }

        trie.list(output_file);
        std::cout << "\r\033[K" << "Done (" << argv[filename_ind] << ")" << std::endl;
    }
    std::cout << "All done." << std::endl;

    return 0;
}
