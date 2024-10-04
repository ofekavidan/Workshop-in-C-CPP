//
// Created on 2/20/2022.
//

// don't change those includes
#include "RSUser.h"
#include "RecommenderSystem.h"
#include <cmath>
#include <algorithm>

// See full documentation in header file
RSUser::RSUser(std::string username, rank_map ranks,
               sp_RS RS_pointer): username(username), ranks(ranks),
               RS_pointer(RS_pointer)
{}

// See full documentation in header file
std::string RSUser::get_name() const {
    return username;
}

// See full documentation in header file
void RSUser::add_movie_to_rs(const std::string &name, int year,
                             const double_vec &features,
                             double rate) {
    sp_movie spm = RS_pointer->add_movie(name,year,features);
    if(std::isnan(rate)) {return;}
    this->ranks[spm] = rate;
}

rank_map RSUser::get_ranks() const {
    return ranks;
}

// See full documentation in header file
sp_movie RSUser::get_recommendation_by_content() const {
    return RS_pointer->recommend_by_content(*this);
}

// See full documentation in header file
sp_movie RSUser::get_recommendation_by_cf(int k) const {
    return RS_pointer->recommend_by_cf(*this, k);
}

// See full documentation in header file
double
RSUser::get_prediction_score_for_movie(const std::string &name, int year,
                                       int k) const {
    sp_movie shared_p_movie = this->RS_pointer->get_movie(name,year);
    return RS_pointer->predict_movie_score(*this,shared_p_movie,k);
}

// See full documentation in header file
std::ostream& operator << (std::ostream &os,const RSUser& rsUser) {
    os << "name: " << rsUser.username << std::endl;
    os << *(rsUser.RS_pointer);
    os << std::endl;
    return os;
}


// implement your cpp code here
