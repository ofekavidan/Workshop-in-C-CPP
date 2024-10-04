//
// Created on 2/20/2022.
//

#ifndef SCHOOL_SOLUTION_RECOMMENDERSYSTEM_H
#define SCHOOL_SOLUTION_RECOMMENDERSYSTEM_H

#include <map>
#include <algorithm>
#include "RSUser.h"

typedef std::pair<sp_movie, double> pair_spm_double;
typedef std::vector<double> double_vec;

/**
 * struct of comparator, just like we learned on TA.
 * helps to compare between pairs of
 * (sp_movie, double - imagination with movie X).
 * used in sorting of vector that contains imaginations with some movie (X),
 * helps us to get the "closest" movie by imagination
 */
struct pair_compare_by_imagination{
    bool operator()(const pair_spm_double& first_pair,
                    const pair_spm_double& second_pair) const
    {
        return (first_pair.second) > (second_pair.second);
    }
};

class RecommenderSystem
{
public:
    /**
     * "empty" constructor. initialize the movie map
     */
	explicit RecommenderSystem();

    /**
     * adds a new movie to the system
     * @param name name of movie
     * @param year year it was made
     * @param features features for movie
     * @return shared pointer for movie in system
     */
	sp_movie add_movie(const std::string& name,int year,
                       const double_vec& features);


    /**
     * a function that calculates the movie with highest score based on
     * movie features
     * @param ranks user ranking to use for algorithm
     * @return shared pointer to movie in system
     */
	sp_movie recommend_by_content(const RSUser& user);

    /**
     * a function that calculates the movie with highest
     * predicted score based on ranking of other movies
     * @param ranks user ranking to use for algorithm
     * @param k
     * @return shared pointer to movie in system
     */
	sp_movie recommend_by_cf(const RSUser& user, int k);


    /**
     * Predict a user rating for a movie given argument
     * using item cf procedure with k most similar movies.
     * @param user_rankings: ranking to use
     * @param movie: movie to predict
     * @param k:
     * @return score based on algorithm as described in pdf
     */
	double predict_movie_score(const RSUser &user, const sp_movie &movie,
												  int k);

	/**
	 * gets a shared pointer to movie in system
	 * @param name name of movie
	 * @param year year movie was made
	 * @return shared pointer to movie in system
	 */
	sp_movie get_movie(const std::string &name, int year) const;

    /**
     * operator<< for Recommender System.
     * @param os ostream to output info with
     * @param movie Recommender System to output
     */
    friend std::ostream& operator<< (std::ostream &os,
            const RecommenderSystem& RS);


private:
    std::map<sp_movie, std::vector<double>,equal_func> movies_map;

    /**
     * this function gets an user object and calculates its average rate for
     * a movie.
     * @param user - an user object, contains movies and their user's rank.
     * @return the average rate of the gotten user.
     */
    double getavg(const RSUser &user);

    /**
     * this function gets a vector of doubles and a scalar (number, double),
     * and returns its multiplication.
     * @param scalar - a number (double)
     * @param vec - a vector of doubles
     * @return the multiplication of the scalar in the vector.
     */
    double_vec scalar_multiplication(double scalar,
                                              const double_vec &vec);

    /**
     * this function gets two vectors of doubles and
     * returns its sum (as vector of doubles).
     * @param first - the first (left) vector of doubles
     * @param second - the second (right) vector of doubles
     * @return first+second as vector of doubles.
     */
    double_vec sum_two_vecs_into_one(const double_vec &first,
                                  const double_vec &second);

    /**
     * this function gets two vectors of doubles and
     * returns its imagination by the given formula. (angle of two vectors)
     * @param first - the first (left) vector of doubles
     * @param second - the second (right) vector of doubles
     * @return first~second as vectors imagination (of doubles).
     */
    double get_imagination(const double_vec &first,
                       const double_vec &second);
    /**
     * this function multiply each coordination of the given vectors, and sums
     * it to a double variable.
     * @param first - the first (left) vector of doubles
     * @param second - the second (right) vector of doubles
     * @return sum of the multiplication of each coordination.
     */
    double multi_two_vecs_to_double(const double_vec &first,
                                       const double_vec &second);

    /**
     * this function calculates the norm of the given vector
     * @param first - the given vector
     * @return the norm of the given vector
     */
    double norm(const double_vec &first);

    /**
     * this function gets a vector of features (doubles),
     * this vector represent a vector of feature of movie that the user
     * didn't see yet.
     * it calculates imagination with each movie that the user did saw,
     * and returns a vector of <sp_movie (shared_pointer of movie),
     * the imagination with the given movie>
     * @param features_vec -vector of feature of movie that the user
     * didn't see yet.
     * @param user - the given user
     * @return a vector of <sp_movie (shared_pointer of movie),
     * the imagination with the given movie>.
     */
    std::vector<pair_spm_double>
    get_imagination_vec(const double_vec &features_vec,
                        const RSUser &user);

    /**
     * this function checks if the given movie is ranked by the user.
     * @param user - the given user.
     * @param movie - the given movie.
     * @return true if the given user ranked the given movie, false otherwise.
     */
    bool is_ranked_by_user(const RSUser& user, sp_movie movie);

};


#endif //SCHOOL_SOLUTION_RECOMMENDERSYSTEM_H
