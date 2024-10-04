//
// Created by 24565 on 6/1/2022.
//

#include "RecommenderSystemLoader.h"
#include "RSUsersLoader.h"

using std::string;
int main ()
{

    Movie m ("A", 1999);
    std::cout << m << std::endl;
    try
    {
        auto rs = RecommenderSystemLoader::create_rs_from_movies_file ("RecommenderSystemLoader_input.txt");
        std::cout << *rs << std::endl;
        auto users = RSUsersLoader::create_users_from_file ("RSUsersLoader_input.txt", std::move (rs));
        std::cout << users[0] << std::endl;
    }
    catch (...)
    {
        std::cout << "got_exception" << std::endl;
    }
}