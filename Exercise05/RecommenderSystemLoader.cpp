//
// Created by Ofek Avidan on 04/09/2022.
//
#include <fstream>
#include <sstream>
#include "RecommenderSystemLoader.h"
#include <iostream>
#include <vector>
#define MAX_FEATURE 10
#define MIN_FEATURE 1

#define FILE_PATH_ERROR "invalid argument, bad file path for RSUsersLoader"
#define FEATURE_ERROR "invalid argument. every feature should be between 1-10"

using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::vector;
using std::istringstream;
//using std::basic_istringstream<char>;
// I used https://cplusplus.com/forum/beginner/176896/ for splitting the words

// See full documentation in header file
up_rs
RecommenderSystemLoader::create_rs_from_movies_file(
        const std::string &movies_file_path) noexcept(false) {
    RecommenderSystem new_rs;
    string filename(movies_file_path);
    string line, word, name, year;

    ifstream input_file(filename);
    if (!input_file.is_open()) {
        throw std::invalid_argument(FILE_PATH_ERROR);
    }
    vector<double> feature;
    while(getline(input_file,line)) {
        istringstream ss(line);
        while (ss >> word) {
            if (std::count(word.begin(), word.end(), '-') !=0) {
                int index_of_hyphen = word.find('-');
                name = word.substr(0, index_of_hyphen);
                year = word.substr(index_of_hyphen+1, word.length());
            }
            else{
                if (std::stoi(word) > MAX_FEATURE ||
                std::stoi(word) < MIN_FEATURE)
                {
                    throw std::invalid_argument(FEATURE_ERROR);
                }
                    feature.push_back(double(std::stoi(word)));
            }
        }
        new_rs.add_movie(name, std::stoi(year), feature);
        feature.clear();
    }
    up_rs new_unique_ptr_rs =
            std::make_unique<RecommenderSystem>(new_rs);
    input_file.close();
    return new_unique_ptr_rs;
}