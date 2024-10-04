//
// Created by Ofek Avidan on 04/09/2022.
//

#include "RSUsersLoader.h"
#include <fstream>
#include "RecommenderSystemLoader.h"
#include <iostream>
#include <vector>
#include <sstream>

#define MAX_RANK 10
#define MIN_RANK 1
#define FILE_PATH_ERROR "invalid argument, bad file path for RSUsersLoader"
#define RANK_ERROR "invalid argument. every rank should be between 1-10"

// i used https://www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/
using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::vector;
using std::istringstream;
typedef std::shared_ptr<RecommenderSystem> sp_rs;
typedef std::vector<sp_movie> sp_movie_vec;

// See full documentation in header file
std::vector <RSUser>
RSUsersLoader::create_users_from_file(const std::string &users_file_path,
              std::unique_ptr<RecommenderSystem> rs) noexcept(false) {
    sp_movie_vec movies_vec; std::vector<RSUser> rsu_vec;
    sp_rs shared_ptr_rs = std::make_shared<RecommenderSystem>(*rs);
    string filename(users_file_path); string line;
    ifstream input_file(filename);
    if (!input_file.is_open()) {
        throw std::invalid_argument(FILE_PATH_ERROR);
    }
    getline(input_file, line);
    movies_vec = first_line_func(line, shared_ptr_rs);
    while (getline(input_file, line)) {
        int counter = 0;
        istringstream ss(line);
        string username;
        string word;
        vector<std::pair<int, double>> ranks_by_index;
        rank_map user_rank_map(0, sp_movie_hash, sp_movie_equal);
        while (ss >> word) {
            if(counter == 0) {
                username = word;
            }
            else {
                if (word == "NA") {
                    counter++;
                    continue;
                }
                if(std::stod(word) > MAX_RANK ||
                std::stod(word) < MIN_RANK) {
                    throw std::invalid_argument(RANK_ERROR);
                }
                std::pair<int,double> rank(counter-1,std::stod(word));
                ranks_by_index.push_back(rank);
            }
            counter++;
        }
        for(auto &pair_of_index_rank: ranks_by_index){
            user_rank_map.insert({movies_vec[pair_of_index_rank.first]
                                         , pair_of_index_rank.second});
        }
        RSUser new_user(username, user_rank_map, shared_ptr_rs);
        rsu_vec.push_back(new_user);
        user_rank_map.clear();
        username = "";
        counter = 0;
    }
    return rsu_vec;
}


// See full documentation in header file
std::vector<sp_movie> RSUsersLoader::first_line_func(std::string line,
                                 std::shared_ptr<RecommenderSystem> rs) {
    sp_movie_vec movies_vec;
    string name, year, word;
    istringstream ss(line);
    while (ss >> word) {
        if (std::count(word.begin(), word.end(), '-') != 0) {
            int index_of_hyphen = word.find('-');
            name = word.substr(0, index_of_hyphen);
            year = word.substr(index_of_hyphen+1, word.length());
            movies_vec.push_back(rs->get_movie(name,
                                               std::stoi(year)));
        }
    }

    return movies_vec;
}
