
// ------------------------------ includes ------------------------------
#include <iostream>
#include <string.h>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>

using std::string;
using std::vector;
// -------------------------- const definitions -------------------------
#ifndef CPP_EX2_RECOMMENDERSYSTEM_H
#define CPP_EX2_RECOMMENDERSYSTEM_H

// ------------------------------- methods ------------------------------

class RecommenderSystem
{
private:

    /*maps from name to a vector of movie rankings, rank order corresponds to movie order*/
    std::map<string, vector<double>> _userRanks;
    /*maps from movie name to a vector which contains its traits ranked.*/
    std::map<string, vector<double>> _movieFeatures;
    /*holds all movies in given order*/
    vector<string> _movieVec;

    /**
     * loads movieFeatures map and movieVec.
     * @param path  - path to file of movies and rankings.
     */
    int _parser(const string &path);

    /**
     * breaks line according to spaces and inserts to data struct, assumes movie name was removed.
     * @param line - line to parse.
     */
    static void _parseLine(const string &line, vector<double> &vec);

    /**
     * breaks down line and inserts parts into string vector.
     * @param line - line to parse.
     * @param vec  - vector to hold data.s
     */
    static void _parseLine(const string &line, vector<string> &vec);


public:
    void printData();
    /**
     * loads data from files into object.
     * @param moviesAttributesFilePath - first file to load.
     * @param userRanksFilePath - second file to load
     * @return - 1 if successful 0 otherwise.
     */
    int loadData(const string &moviesAttributesFilePath, const string &userRanksFilePath);

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

