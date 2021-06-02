#pragma once

#include "BrushStone.h"
#include "ofMain.h"
#include "ofxGui.h"
#include <random>

class ofApp : public ofBaseApp
{
    struct Properties
    {
        float maxGrowRadius;
        float maxCircleSize;
        float spacing;
        float sizeMin;
        float sizeMax;
        float speed;
        ofColor color;
        ofColor stoneCircleColor;
    };

public:
    void setup() override;
    void update() override;
    void draw() override;

    void keyPressed(int key);

    void reinit();

private:
    std::vector<BrushStone> rocks;
    BrushCollection brushes;

    void initSingle(BrushStone& stone, Properties props);

    bool m_drawGui;

    ofxPanel gui;
    ofxColorSlider backgroundColor;
    ofxFloatSlider offsetLeft, padding, offsetTop;

    ofxFloatSlider rock1x, rock1y, rock2x, rock2y, rock3x, rock3y, rock4x, rock4y;

    std::vector<float> m_percentages;
    std::vector<Properties> m_props;
    std::random_device rd;
    std::mt19937 gen;
    std::discrete_distribution<> d;
};
