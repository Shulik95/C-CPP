
// ------------------------------ includes ------------------------------
#include <iostream>
#include <string.h>

using std::string;
// -------------------------- const definitions -------------------------
#ifndef CPP_EX2_RECOMMENDERSYSTEM_H
#define CPP_EX2_RECOMMENDERSYSTEM_H

// ------------------------------- methods ------------------------------

class RecommenderSystem
{
private:

public:

    /**
     * loads data from files into object.
     * @param moviesAttributesFilePath - first file to load.
     * @param userRanksFiltPath - second file to load
     * @return - 1 if successful 0 otherwise.
     */
    int loadData(const string &moviesAttributesFilePath, const string &userRanksFiltPath);

    /**
     * recommends a movie to given user according to algorithm.
     * @param userName - recommend according to this user.
     * @return -
     */
    string recommendByContent(const string userName) const;

    /**
     * predicts the rating the given user will give the movie.
     * @param movieName - movie to rate
     * @param userName - user to predict rating for.
     * @param k - algorithm input.
     * @return - the predicted rating.
     */
    double preditcMovieScoreForUser(const string &movieName, const string &userName, const int k);

    /**
     * recommends a movie to given user according to CF algorithm.
     * @param userName - recommend movie to this user
     * @param k - algorithm input.
     * @return - recommendation as string.
     */
    string recommendByCF(const string &userName, const int k);
};
#endif //CPP_EX2_RECOMMENDERSYSTEM_H

