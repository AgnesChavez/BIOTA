#pragma once

#include "ofMain.h"

class BrushCollection
{
public:
    BrushCollection();
    ~BrushCollection();

    void clear();

    ofFbo getRandomBrush();
    ofImage& getCircleBrush();
    ofImage& getOwnBrush1();
    ofFbo getBrushById(int id);

    void load(int offset = 0, int count = 25);
    void loadSingle(std::string path);

private:
    std::vector<ofFbo> fboBrushes;
    std::vector<ofImage> brushes;
    ofImage circleBrush, ownBrush1;
};
