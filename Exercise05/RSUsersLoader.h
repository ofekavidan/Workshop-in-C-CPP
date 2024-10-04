//
// Created on 2/21/2022.
//




#ifndef SCHOOL_SOLUTION_USERFACTORY_H
#define SCHOOL_SOLUTION_USERFACTORY_H

#include "RSUser.h"
class RSUsersLoader
{
private:


public:
    RSUsersLoader() = delete;
    /**
     *
     * loads users by the given format with their movie's ranks
     * @param users_file_path a path to the file of the users and their
     * movie ranks
     * @param rs RecommendingSystem for the Users
     * @return vector of the users created according to the file
     */
    static std::vector<RSUser> create_users_from_file
    (const std::string& users_file_path,
     std::unique_ptr<RecommenderSystem> rs) noexcept(false);

private:
    /**
     * this function gets the first line of the input text, and a shared
     * pointer to our Recommender System. it collects all the movies that
     * have been written on the first line, and puts them in a vector of
     * shared pointers of movies.
     * @param line - the first line of the input text
     * @param rs - our Recommender System
     * @return a vector of shared pointers of movies (which have been written
     * on the first line of the input text).
     */
    static std::vector<sp_movie> first_line_func(std::string line,
                                     std::shared_ptr<RecommenderSystem> rs);
};


#endif //SCHOOL_SOLUTION_USERFACTORY_H
