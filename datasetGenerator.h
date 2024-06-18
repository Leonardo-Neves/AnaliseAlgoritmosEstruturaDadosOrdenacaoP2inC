#ifndef DATASETGENERATOR_H
#define DATASETGENERATOR_H

#include <vector>

class DatasetGenerator {
public:
    DatasetGenerator();
    
    std::vector<int> generateOrdered(int length);
    std::vector<int> generateOrderedInverse(int length);
    std::vector<int> generateAlmostOrdered(int length);
    std::vector<int> generateRandom(int length);
    std::vector<int> generateRandomWithRepeats(int length);

private:
};

#endif // DATASETGENERATOR_H