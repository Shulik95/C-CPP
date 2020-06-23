
// ------------------------------ includes ------------------------------
#include "RecommenderSystem.h"
// -------------------------- const definitions -------------------------
#define SUCCESS 0
#define FAIL -1
#define NORATE 0

const string FILE_ERR_MSG = "Unable to open file ";
// ------------------------------- methods ------------------------------

/**
 *
 * @param moviesAttributesFilePath
 * @param userRanksFilePath
 * @return
 */
int RecommenderSystem::loadData(const string &moviesAttributesFilePath, const string &userRanksFilePath)
{
    _parser(moviesAttributesFilePath);
}

/**
 * loads movieFeatures map and movieVec.
 * @param path  - path to file of movies and rankings.
 */
int RecommenderSystem::_parser(const string &path)
{
    std::ifstream is;
    is.open(path);
    if(!is.is_open())
    {
        std::cout << FILE_ERR_MSG << path << std::endl;
        return FAIL;
    }
    std::string line;
    while(std::getline(is, line))
    {
        string movieName = line.substr(0, line.find_first_of(' '));
        line = line.substr(line.find_first_of(" \t") + 1); //remove movie name.
        vector<double> ratingVec;

    }
    return 0;
}

/**
 * breaks line according to spaces and inserts to data struct, assumes movie name was removed.
 * @param line - line to parse.
 */
void RecommenderSystem::_parseLine(const string &line, vector<double> &vec)
{
    std::istringstream iss(line);
    do
    {
        string tempWord;
        iss >> tempWord;
        if(!tempWord.empty())
        {
            tempWord == "NA" ? vec.push_back(NORATE) : vec.push_back(std::stod(tempWord));
        }
    } while(iss);
}

void RecommenderSystem::printData()
{

}

int main(int argc, char* argv[])
{
    RecommenderSystem rec;
    rec.loadData(argv[1], argv[2]);
    rec

}
