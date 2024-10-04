//
// Created by Ofek Avidan on 02/09/2022.
//

#include "RecommenderSystem.h"
#include <cmath>

/**
 * comparator for movies_map (helps us to stay
 * @param first
 * @param second
 * @return
 */
bool sp_movie_comparator(const sp_movie& first,
                const sp_movie& second)
{
    return (*first) < (*second);
}

// See full documentation in header file
RecommenderSystem::RecommenderSystem(): movies_map(sp_movie_comparator) {};

sp_movie RecommenderSystem::
add_movie(const std::string &name, int year,
                                      const double_vec &features) {
    Movie new_movie = Movie(name,year);
    sp_movie new_sp_movie = std::make_shared<Movie> (new_movie);
    movies_map[new_sp_movie] = features;
    return new_sp_movie;
}

// See full documentation in header file
sp_movie RecommenderSystem::
get_movie(const std::string &name, int year) const {
    Movie movie_to_find = Movie(name,year);
    sp_movie movie_to_find_sp = std::make_shared<Movie> (movie_to_find);

    if(movies_map.find(movie_to_find_sp) == movies_map.end())
    {
        movie_to_find_sp =  nullptr;
        return movie_to_find_sp;
    }

    return(*movies_map.find(movie_to_find_sp)).first;
}

// See full documentation in header file
double RecommenderSystem::predict_movie_score(const RSUser &user,
                                              const sp_movie &movie, int k) {
    auto recommend_vec =
            get_imagination_vec(movies_map[movie], user);
    double denominator = 0; // mechane
    double numerator = 0; // mone
    for (int i = 0; i < k; ++i) {
        numerator += recommend_vec[i].second *
//                user.get_ranks()[recommend_vec[i].first]
(*(user.get_ranks().find(recommend_vec[i].first))).second;

        denominator += recommend_vec[i].second;
    }
    if (denominator == 0)
    {
        throw std::runtime_error("runtime error, divided by zero");
    }
    return numerator / denominator;
}

// uses predict_movie_score
// See full documentation in header file
sp_movie RecommenderSystem::recommend_by_cf(const RSUser &user, int k) {
    sp_movie max_movie;
    double max = 0;
    bool flag = false;

    for (auto &moviepair : movies_map) {
        if (is_ranked_by_user(user, moviepair.first))
        {
            continue;
        }
        double predict = predict_movie_score(user,moviepair.first, k);
        if (!flag)
        {
            max = predict;
            max_movie = moviepair.first;
            flag = true;
            continue;
        }
        if (max < predict)
        {
            max = predict;
            max_movie = moviepair.first;
        }
    }

    return max_movie;
}

// See full documentation in header file
sp_movie RecommenderSystem::recommend_by_content(const RSUser &user)
{
    double avg = getavg(user);
    double_vec prefers_vec;
    int size_of_prefer_vec = movies_map.begin()->second.size();
    for (int i = 0; i < size_of_prefer_vec; ++i) {
        prefers_vec.push_back(0);
    }

    for (auto &rank :user.get_ranks())
    {
        double normal_rank = rank.second - avg;
        double_vec features = movies_map[rank.first];
        double_vec tmp =
            scalar_multiplication(normal_rank, features);
        prefers_vec = sum_two_vecs_into_one(prefers_vec,
                                            tmp);
    }

    double max = 0;
    bool flag = false;
    sp_movie max_movie;
    for(auto& movie: movies_map)
    {
        if(user.get_ranks().count(movie.first) == 0)
        {
            if (max == 0 && !flag)
            {
                max = get_imagination(prefers_vec, movie.second);
                max_movie = movie.first;
                flag = true;
                continue;
            }
            if (max <get_imagination(prefers_vec, movie.second))
            {
                max = get_imagination(prefers_vec, movie.second);
                max_movie = movie.first;
                continue;
            }
        }
    }
    return max_movie;
}

// See full documentation in header file
double RecommenderSystem::getavg(const RSUser &user) {
    double sum_of_ranks = 0;
    int number_of_ranks = 0;

    for (auto &rank: user.get_ranks()) {
        number_of_ranks++;
        sum_of_ranks += rank.second;
    }
    double avg = sum_of_ranks / number_of_ranks;
    return avg;
}

// See full documentation in header file
double_vec
        RecommenderSystem::scalar_multiplication(double scalar,
                const double_vec &vec) {
    std::vector<double> new_vec;
    for (const auto &element :vec)
    {
        new_vec.push_back(element * scalar);
    }
    return new_vec;
}

// See full documentation in header file
double_vec RecommenderSystem::sum_two_vecs_into_one
(const double_vec &first, const double_vec &second) {
    double_vec sum;
    int i = 1, j = 1;
    for (auto element1 : first)
    {
        j=1;
        for(auto  element2 : second)
        {
            if(i==j) {
                sum.push_back (element1 + element2);
            }
            j++;
        }

        i++;
    }
    return sum;
}

// See full documentation in header file
double RecommenderSystem::get_imagination(const double_vec &first,
                                      const double_vec &second) {
    double upper = multi_two_vecs_to_double(first, second);
    double lower = norm(first) * norm(second);
    return upper / lower;
}

// See full documentation in header file
double
RecommenderSystem::multi_two_vecs_to_double(const double_vec &first,
                                  const double_vec &second) {
   double multi = 0;
    int i = 1, j = 1;
    for (auto element1 : first)
    {
        j=1;
        for(auto  element2 : second)
        {
            if(i==j) {
                multi += (element1 * element2);
            }
            j++;
        }
        i++;
    }
    return multi;
}

// See full documentation in header file
double RecommenderSystem::norm(const double_vec &vec) {
    double sum = 0;
    for (const auto &element : vec) {
        sum += element * element;
    }
    return std::sqrt(sum);

}

// See full documentation in header file
std::vector<pair_spm_double>
RecommenderSystem::get_imagination_vec(const double_vec &features_vec,
                                       const RSUser &user) {

    std::vector<pair_spm_double> vec;
    for (auto &element : movies_map) {
        if (user.get_ranks().count(element.first) != 0) {
            double imagination =
                    get_imagination(features_vec, element.second);
            pair_spm_double pair_to_insert;
            pair_to_insert.first = element.first;
            pair_to_insert.second = imagination;
            vec.push_back(pair_to_insert);
        }
    }

    std::sort(vec.begin(), vec.end(),
              pair_compare_by_imagination());
    return vec;
}

// See full documentation in header file
std::ostream& operator << (std::ostream &os, const RecommenderSystem& RS) {
    for (const auto &pair_movie_features : RS.movies_map)
    {
        os << *(pair_movie_features.first);
    }
    return os;
}

// See full documentation in header file
bool RecommenderSystem::is_ranked_by_user(const RSUser &user, sp_movie movie) {
    return (user.get_ranks().find(movie) != user.get_ranks().end());
}