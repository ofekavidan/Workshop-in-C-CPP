
#ifndef RECOMMENDERSYSTEMLOADER_H
#define RECOMMENDERSYSTEMLOADER_H

#include "RecommenderSystem.h"

typedef std::unique_ptr<RecommenderSystem> up_rs;
class RecommenderSystemLoader {

 private:

 public:
  RecommenderSystemLoader () = delete;
  /**
   * loads movies by the given format for movies with their feature's score
   * @param movies_file_path a path to the file of the movies
   * @return smart pointer to a RecommenderSystem which was created with
   * those movies
   */
  static up_rs create_rs_from_movies_file
	  (const std::string &movies_file_path) noexcept (false);
};

#endif //RECOMMENDERSYSTEMLOADER_H
