
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

const string FILE_ERR_MSG = "Unable to open file ";
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


int main(int argc, char* argv[])
{
    RecommenderSystem rec;
    rec.loadData(argv[1], argv[2]);
    rec.printData();
}
