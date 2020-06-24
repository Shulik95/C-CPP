
// ------------------------------ includes ------------------------------

#include "RecommenderSystem.h"
// -------------------------- const definitions -------------------------
#define PARSER(action)\
std::istringstream iss(line);\
do\
{\
string tempWord;\
iss >> tempWord;\
if(!tempWord.empty())\
{\
    action\
}\
} while(iss);

#define SUCCESS 0
#define FAIL -1
#define NORATE 0
#define FIRSTLINE 1
#define FIRST 0
#define MINTHETA -1
#define SQUARED 2.0

const string FILE_ERR_MSG = "Unable to open file ";
const string BAD_USER_ERR = "USER NOT FOUND";
/*indicates that were reading the 2nd file*/
bool gUserFile = false;
// ------------------------------- methods ------------------------------

/**
 *
 * @param moviesAttributesFilePath
 * @param userRanksFilePath
 * @return
 */
int RecommenderSystem::loadData(const string &moviesAttributesFilePath, const string &userRanksFilePath)
{
    int firstRead = _parser(moviesAttributesFilePath);
    gUserFile = true;
    int secondRead = _parser(userRanksFilePath);
    if(firstRead + secondRead == SUCCESS)
    {
        return SUCCESS;
    }
    return FAIL;

}

/**
 * loads movieFeatures map and movieVec.
 * @param path  - path to file of movies and rankings.
 */
int RecommenderSystem::_parser(const string &path)
{
    std::ifstream is;
    is.open(path);
    int lineCounter = 0;
    if(!is.is_open())
    {
        std::cout << FILE_ERR_MSG << path << std::endl;
        return FAIL;
    }
    std::string line;
    while(std::getline(is, line))
    {
        lineCounter ++;
        if(gUserFile && (lineCounter == FIRSTLINE)) //first line holds movies, store them in vector
        {
            _parseLine(line, _movieVec); //add movies to vector for future use.
        }
        else
        {
            string name = line.substr(0, line.find_first_of(' ')); //get name of movie/user
            line = line.substr(line.find_first_of(" \t") + 1); //remove movie/user name from string.
            vector<double> ratingVec;
            _parseLine(line, ratingVec);
            if(gUserFile)
            {
                _userRanks[name] = ratingVec;
            }
            else
            {
                _movieFeatures[name] = ratingVec;
            }
        }
    }
    is.close();
    return SUCCESS;
}

/**
 * breaks line according to spaces and inserts to data struct, assumes movie name was removed and that the rest are
 * doubles.
 * @param line - line to parse.
 * @param vec - double vector to hold data.
 */
void RecommenderSystem::_parseLine(const string &line, vector<double> &vec)
{
    PARSER(tempWord == "NA" ? vec.push_back(NORATE) : vec.push_back(std::stod(tempWord));)
}

/**
* breaks down line and inserts parts into string vector.
* @param line - line to parse.
* @param vec  - vector to hold data.s
*/
void RecommenderSystem::_parseLine(const string &line, vector<string> &vec)
{
    PARSER(vec.push_back(tempWord);)
}


void RecommenderSystem::printData()
{
    std::cout << "Printing movie vector" << std::endl;
    for (const auto & i : this->_movieVec)
    {
        std::cout << i << " ";
    }
    std::cout << "\n" << std::endl;
    std::cout << "Printing movie ratings: " << std::endl;
    for(const auto& element : this->_movieFeatures)
    {
        std::cout << element.first << " ";
        std::cout << "";
        for (const auto &i : this->_movieFeatures[element.first])
        {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    std::cout << "Printing users: " << std::endl;
    for(const auto& elem : this->_userRanks)
    {
        std::cout << elem.first << " ";
        std::cout << "";
        for (const auto &i : this->_userRanks[elem.first])
        {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
}

/**
 * returns average of given users ratings.
 */
double RecommenderSystem::findAverage(const string& userName) const
{
    vector<double> tempVec = this->_userRanks.at(userName);
    double sum = std::accumulate(tempVec.begin(), tempVec.end(), 0.0);
    int vecSize  = 0;
    for(double i : tempVec)
    {
        if(i != NORATE)
        {
            vecSize++;
        }
    }
    return sum / vecSize;
}

/**
 * recommends a movie to given user according to algorithm.
 * @param userName - recommend according to this user.
 * @return -
 */
string RecommenderSystem::recommendByContent(const string &userName)
{
    if(this->_userRanks.find(userName) == this->_userRanks.end()) //user doesnt exist.
    {
        return BAD_USER_ERR;
    }
    double avg = this->findAverage(userName);
    vector<double> normalizedVec = this->normalizeVec(this->_userRanks.at(userName), avg);
    vector<double> prefVec = this->getPrefVec(normalizedVec);
    return checkResemblance(prefVec, userName);
}

/**
 * deducts the avg from all values of given vector, doesnt change it, returns a different one.
 * @param vec - original vector.
 * @return  - a normalized version of the given vector.
 */
vector<double> RecommenderSystem::normalizeVec(const vector<double>& vec, double avg) const
{
    vector<double> ret;
    for(auto &i : vec)
    {
        if(i != 0)
        {
            ret.push_back(i - avg);
        }
        else
        {
            ret.push_back(i); //its zero no need to normalize
        }

    }
    return ret;
}

/**
 * returns the users prefrence vector according to the given algorithm.
 * @param normVec - normalized ratings vector of the user.
 * @return - vector of doubles which signify the traits the user likes in movies.
 */
vector<double> RecommenderSystem::getPrefVec(const vector<double> &normVec) const
{
    const string tempString = this->_movieVec[FIRST];
    int vecLength = (this->_movieFeatures.at(tempString)).size();
    vector<double> ret(vecLength, 0.0);
    for(long unsigned int i = 0 ; i < normVec.size(); i++)
    {
        double w = normVec[i];
        if(w != 0) //only if user rated this film
        {
            string name = this->_movieVec[i]; //get name
            vector<double> temp = this->_movieFeatures.at(name); //get features vector of the movie
            _multByScalar(w, temp);
            _sumVector(ret, temp);
        }
    }
    return ret;
}

/**
* multiplies all elements of given vec by a scalar.
*/
void RecommenderSystem::_multByScalar(double val, vector<double> &vec) const
{
    for(auto &i: vec)
    {
        i *= val;
    }
}

/**
 * adds rhs into lhs.
 */
void RecommenderSystem::_sumVector(vector<double> &lhs,const vector<double> &rhs) const
{
    for(long unsigned int i = 0; i < lhs.size(); i++)
    {
        lhs[i] += rhs[i];
    }
}
/**
 * returns the norm of the vector.
 */
double RecommenderSystem::_getNorm(const vector<double>& vec)
{
    double norm = 0;
    for(auto &item : vec)
    {
        norm += pow(item, SQUARED);
    }
    return sqrt(norm);
}

/**
 * calculates the angle between 2 given vectors.
 */
double RecommenderSystem::calcAngle(const vector<double> &vec1, const vector<double> &vec2)
{
    return (dotProd(vec1, vec2) / (_getNorm(vec1) * _getNorm(vec2)));
}

/**
 * implements scalar multiplication of two vectors.
 * @return - the scalar which represents the dot product.
 */
double RecommenderSystem::dotProd(const vector<double>& lhs, const vector<double>& rhs)
{
    double dotProduct = 0.0;
    for(long unsigned int i = 0; i < lhs.size(); i++)
    {
        dotProduct  += (lhs[i] * rhs[i]);
    }
    return dotProduct;
}

string RecommenderSystem::checkResemblance(const vector<double> &prefrenceVec,const string &userName)
{
    string retMovie;
    double maxAngle = MINTHETA;
    vector<double> userRatings = this->_userRanks[userName]; //get rating vector.
    for(long unsigned int i = 0; i < userRatings.size(); i++)
    {
        if(userRatings[i] == NORATE) //movie is unrated
        {
            string movieName = this->_movieVec[i]; //get name of unwatched movie
            double angle = calcAngle(prefrenceVec, this->_movieFeatures[movieName]);
            if(angle > maxAngle)
            {
                maxAngle = angle;
                retMovie = movieName;
            }
        }
    }
    return retMovie;
}

/**
 * predicts the rating the given user will give the movie.
 * @param movieName - movie to rate
 * @param userName - user to predict rating for.
 * @param k - algorithm input.
 * @return - the predicted rating.
 */
double RecommenderSystem::predictMovieScoreForUser(const string &movieName, const string &userName, const int k)
{
    double upperSum = 0, lowerSum = 0;
    if(this->_movieFeatures.find(movieName) == this->_movieFeatures.end() ||
       this->_userRanks.find(userName) == this->_movieFeatures.end())
    {
        return FAIL;
    }
    vector<double> movieFeaturesVec = this->_movieFeatures[movieName];
    vector<double> userRatings = this->_userRanks[userName]; //get ratings vectors.
    vector<std::pair<string, double>> ratedMoviesVec; //holds movie name and resemblance to given movie.
    std::map<string, int> indexMap;
    getResVec(movieFeaturesVec, userRatings, ratedMoviesVec, indexMap);
    std::sort(ratedMoviesVec.begin(), ratedMoviesVec.end(), comparePair);
    for (int i = 0; i < k; ++i)
    {
        int idx = indexMap[ratedMoviesVec[i].first];
        upperSum += (this->_userRanks[userName][idx] * ratedMoviesVec[i].second);
        lowerSum += ratedMoviesVec[i].second;
    }
    return (upperSum / lowerSum);
}

/**
 * creates a vector which holds <movieName, resemblance> to given movie.
 * @param movieFeaturesVec - features the movie to compare against.
 * @param userRatings - vector of rating for movies by given user.
 * @param ratedMoviesVec - the vector to hold pairs.
 */
void RecommenderSystem::getResVec(const vector<double> &movieFeaturesVec, const vector<double> &userRatings,
                                  vector<std::pair<string, double>> &ratedMoviesVec, std::map<string, int>& idxMap)
{
    for(long unsigned int i = 0; i < userRatings.size(); i++)
    {
        if(userRatings[i] != NORATE) //user has watched the movies.
        {
            vector<double> tempVec = _movieFeatures[_movieVec[i]]; //get vector of movie features.
            std::pair<string, double> tempPair;
            double res = calcAngle(movieFeaturesVec, tempVec);
            tempPair.first = _movieVec[i]; //movieName
            tempPair.second = res; // resemblance
            ratedMoviesVec.push_back(tempPair);
            idxMap[this->_movieVec[i]] = i; //save index for future use.
        }
    }
}

/**
 * comparator for sorting.
 */
bool RecommenderSystem::comparePair(const std::pair<string, double>& pair1, const std::pair<string, double>& pair2)
{
    return pair1.second > pair2.second;
}

/**
 * recommends a movie to given user according to CF algorithm.
 * @param userName - recommend movie to this user
 * @param k - algorithm input.
 * @return - recommendation as string.
 */
string RecommenderSystem::recommendByCF(const string &userName, const int k)
{
    if(this->_userRanks.find(userName) == this->_userRanks.end())
    {
        return BAD_USER_ERR;
    }
    vector<std::pair<string, double>> unwatchedRatings;
    for(long unsigned int i = 0; i < this->_movieVec.size(); i++)
    {
        if(this->_userRanks[userName][i] == NORATE) //unwatched.
        {
            double predictedScore = predictMovieScoreForUser(this->_movieVec[i], userName, k);
            std::pair<string, double> tempPair;
            tempPair.first = this->_movieVec[i];
            tempPair.second = predictedScore;
            unwatchedRatings.push_back(tempPair);
        }
    }
    return getBestPrediction(unwatchedRatings);
}

/**
    * get the vector with the best predicted score.
    * @param vec - vector holding name of movie and its predicted rating.
    * @return - the name of the movie.
    */
string RecommenderSystem::getBestPrediction(const vector<std::pair<string, double>>& vec)
{
    string bestScoreMovie;
    double highestScore = 0;
    for(auto &item : vec)
    {
       if(item.second > highestScore)
       {
           highestScore = item.second;
           bestScoreMovie = item.first;
       }
    }
    return bestScoreMovie;
}


int main(int argc, char* argv[])
{
    RecommenderSystem rec;
    rec.loadData(argv[1], argv[2]);
    rec.printData();
    std::cout << rec.recommendByContent("Christopher") << std::endl;
    std::cout << rec.recommendByContent("Brayson") << std::endl;
    std::cout << rec.recommendByContent("Randy") << std::endl;
    std::cout << rec.recommendByContent("Brayson") << std::endl;
    std::cout << rec.recommendByContent("London") << std::endl;

    std::cout << rec.predictMovieScoreForUser("Fargo", "Christopher", 2) << std::endl;
}
