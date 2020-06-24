
// ------------------------------ includes ------------------------------
#include <iostream>
#include <string.h>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <numeric>
#include <cmath>
#include <algorithm>

using std::string;
using std::vector;
// -------------------------- const definitions -------------------------
#ifndef CPP_EX2_RECOMMENDERSYSTEM_H
#define CPP_EX2_RECOMMENDERSYSTEM_H

// ------------------------------- methods ------------------------------

/**
 * Implements recommendation system for movies.
 */
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

    /**
     * gets the average of all values in vector.
     */
    double _findAverage(const string& userName) const;

    /**
     * deducts the avg from all values of given vector, doesnt change it, returns a different one.
     * @param vec - original vector.
     * @return  - a normalized version of the given vector.
     */
    vector<double> _normalizeVec(const vector<double>& vec, double avg) const;

    /**
     * returns the users prefrence vector according to the given algorithm.
     * @param normVec - normalized ratings vector of the user.
     * @return - vector of doubles which signify the traits the user likes in movies.
     */
    vector<double> _getPrefVec(const vector<double>& normVec) const;

    /**
     * multiplies all elements of given vec by a scalar.
     */
    void _multByScalar(double val, vector<double>& vec) const;

    /**
     * adds rhs into lhs.
     */
    void  _sumVector(vector<double>& lhs, const vector<double>& rhs) const;

    /**
     * returns the norm of the vector.
     */
    static double _getNorm(const vector<double>& vec);

    /**
     * calculates the angle between 2 given vectors.
     */
    static double _calcAngle(const vector<double>& vec1, const vector<double>& vec2);

    /**
     * implements scalar multiplication of two vectors.
     * @return - the scalar which represents the dot product.
     */
    static double _dotProd(const vector<double>& lhs, const vector<double>& rhs);

    /**
     * find the movie with the highest resemblance rate for given user.
     * @param prefranceVec -vector of preferences for user.
     * @param userName - name of the user.
     * @return - name of the movie with the higest resemblance.
     */
    string _checkResemblance(const vector<double>& prefranceVec, const string& userName);

    /**
     * comparator function for sorting a vector according to resemblance.
     */
    static bool _comparePair(const std::pair<string, double>& pair1, const std::pair<string, double>& pair2);

    /**
     * creates a vector of pairs <movieName, resemblance>
     * @param movieFeaturesVec
     * @param userRatings
     * @param ratedMoviesVec
     */
    void _getResVec(const vector<double> &movieFeaturesVec, const vector<double> &userRatings,
                    vector<std::pair<string, double>> &ratedMoviesVec, std::map<string, int>& idxMap);
    /**
     * get the vector with the best predicted score.
     * @param vec - vector holding name of movie and its predicted rating.
     * @return - the name of the movie.
     */
    static string _getBestPrediction(const vector<std::pair<string, double>>& vec);

public:

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
    string recommendByContent(const string &userName);

    /**
     * predicts the rating the given user will give the movie.
     * @param movieName - movie to rate
     * @param userName - user to predict rating for.
     * @param k - algorithm input.
     * @return - the predicted rating.
     */
    double predictMovieScoreForUser(const string &movieName, const string &userName, const int k);

    /**
     * recommends a movie to given user according to CF algorithm.
     * @param userName - recommend movie to this user
     * @param k - algorithm input.
     * @return - recommendation as string.
     */
    string recommendByCF(const string &userName, const int k);


};
#endif //CPP_EX2_RECOMMENDERSYSTEM_H

