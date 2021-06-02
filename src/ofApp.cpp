#include "ofApp.h"
#include "Misc.h"
#include <random>

void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_ERROR);
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofSetTextureWrap(GL_REPEAT);

    ofBackground(0);
    ofSetCircleResolution(100);

    m_percentages.push_back(27.8f);
    m_percentages.push_back(8.1f);
    m_percentages.push_back(7.03f);
    m_percentages.push_back(4.95f);
    m_percentages.push_back(4.21f);
    m_percentages.push_back(4.04f);
    m_percentages.push_back(3.68f);
    m_percentages.push_back(3.62f);
    m_percentages.push_back(3.23f);
    m_percentages.push_back(3.08f);
    m_percentages.push_back(3.02f);
    m_percentages.push_back(3.02f);
    m_percentages.push_back(2.92f);
    m_percentages.push_back(2.7f);
    m_percentages.push_back(2.66f);
    m_percentages.push_back(2.53f);
    m_percentages.push_back(2.52f);
    m_percentages.push_back(2.50f);
    m_percentages.push_back(2.39f);
    //m_percentages.push_back(2.37f);
   
    //m_percentages.push_back(3.95f);
    //m_percentages.push_back(3.21f);
    //m_percentages.push_back(3.04f);
    //m_percentages.push_back(2.68f);
    //m_percentages.push_back(2.62f);
    //m_percentages.push_back(2.23f);
    //m_percentages.push_back(2.08f);
    //m_percentages.push_back(2.02f);
    //m_percentages.push_back(2.01f);
    //m_percentages.push_back(1.92f);
    //m_percentages.push_back(1.7f);
    //m_percentages.push_back(1.66f);
    //m_percentages.push_back(1.53f);

    // first 4
    //m_props.push_back(Properties{500, 115, 2.9, 13.0, 13.0, 15.0, ofColor(10, 15, 96), ofColor(48, 255, 42)});
    //m_props.push_back(Properties{232, 210, 4.8, 13.0, 13.0, 15, ofColor(1, 24, 6), ofColor(245, 255, 0)});
    //m_props.push_back(Properties{500, 82, 3.1, 13.0, 13.0, 15, ofColor(220, 80, 0), ofColor(255, 150, 38)});
    //m_props.push_back(Properties{500, 82, 4.0, 13.0, 13.0, 15, ofColor(20, 7, 0), ofColor(255, 87, 167)});

    //float maxGrowRadius;
    //float maxCircleSize;
    //float spacing;
    //float sizeMin;
    //float sizeMax;
    //float speed;
    //ofColor color;
    //ofColor stoneCircleColor;

    // final
    m_props.push_back(Properties{382, 382, 2.2, 13.0, 13.0, 6,
                                 ofColor(7, 141, 4), ofColor(169, 37, 104)});
    m_props.push_back(Properties{382, 100, 0.8, 13.0, 13.0, 6.5,
                                 ofColor(50, 61, 255), ofColor(50, 61, 255)});
    m_props.push_back(Properties{382, 382, 2.2, 13.0, 13.0, 6,
                                 ofColor(7, 141, 4), ofColor(49, 81, 189)});
    m_props.push_back(Properties{382, 100, 0.8, 13.0, 13.0, 6.5,
                                 ofColor(169, 14, 57), ofColor(169, 14, 57)});
    m_props.push_back(Properties{382, 100, 0.8, 13.0, 13.0, 6.0,
                                 ofColor(255, 71, 35), ofColor(11, 89, 4)});
    m_props.push_back(Properties{350, 350, 4.5, 13.0, 13.0, 6.0,
                                 ofColor(11, 176, 146), ofColor(30, 37, 10)});
    m_props.push_back(Properties{238, 150, 1.4, 13.0, 13.0, 16.0,
                                 ofColor(42, 7, 255), ofColor(11, 89, 4)});
    m_props.push_back(Properties{382, 382, 2.2, 13.0, 13.0, 6,
                                 ofColor(7, 141, 4), ofColor(169, 37, 104)});
    m_props.push_back(Properties{382, 100, 2.2, 13.0, 13.0, 10,
                                 ofColor(247, 19, 113), ofColor(230, 98, 6)});
    //m_props.push_back(Properties{350, 350, 4.5, 13.0, 13.0, 6.0,
    //                             ofColor(22, 230, 10), ofColor(30, 37, 10)});
    m_props.push_back(Properties{382, 100, 0.8, 13.0, 13.0, 6.0,
                                 ofColor(255, 27, 183), ofColor(11, 89, 4)});
    m_props.push_back(Properties{238, 150, 1.4, 13.0, 13.0, 16.0,
                                 ofColor(91, 19, 28), ofColor(42, 7, 255)});
    m_props.push_back(Properties{382, 382, 2.2, 13.0, 13.0, 6,
                                 ofColor(255, 255, 255), ofColor(16, 132, 13)});
    m_props.push_back(Properties{382, 100, 0.8, 13.0, 13.0, 6.0,
                                 ofColor(166, 4, 255), ofColor(11, 89, 4)});
    m_props.push_back(Properties{382, 100, 2.2, 13.0, 13.0, 10,
                                 ofColor(82, 247, 2), ofColor(230, 98, 6)});
    m_props.push_back(Properties{382, 100, 2.2, 13.0, 13.0, 10,
                                 ofColor(247, 19, 113), ofColor(230, 98, 6)});
    m_props.push_back(Properties{350, 350, 4.5, 13.0, 13.0, 6.0,
                                 ofColor(106, 77, 150), ofColor(187, 134, 24)});
    m_props.push_back(Properties{238, 150, 1.4, 13.0, 13.0, 16.0,
                                 ofColor(253, 6, 39), ofColor(220, 29, 6)});
    m_props.push_back(Properties{382, 100, 0.8, 13.0, 13.0, 6.5,
                                 ofColor(167, 0, 20), ofColor(167, 0, 20)});
    m_props.push_back(Properties{382, 382, 2.2, 13.0, 13.0, 6,
                                 ofColor(7, 141, 4), ofColor(190, 53, 20)});
    m_props.push_back(Properties{382, 100, 2.2, 13.0, 13.0, 10,
                                 ofColor(183, 2, 54), ofColor(50, 61, 255)});

    /*

    // first section
    m_props.push_back(Properties{382, 100, 2.2, 13.0, 13.0, 10, ofColor(183, 2, 54), ofColor(50, 61, 255)});
    m_props.push_back(Properties{382, 100, 2.2, 13.0, 13.0, 10, ofColor(247, 13, 16), ofColor(230, 98, 6)});
    m_props.push_back(Properties{382, 100, 2.2, 13.0, 13.0, 10, ofColor(82, 247, 2), ofColor(230, 98, 6)});
    m_props.push_back(Properties{382, 100, 2.2, 13.0, 13.0, 10, ofColor(247, 19, 113), ofColor(230, 98, 6)});
    //m_props.push_back(Properties{100, 100, 2.2, 13.0, 13.0, 10, ofColor(246, 62, 31), ofColor(255, 146, 59)});

    // second section
    m_props.push_back(Properties{382, 382, 2.2, 13.0, 13.0, 6,  ofColor(7, 141, 4), ofColor(169, 37, 104)});
    m_props.push_back(Properties{382, 382, 2.2, 13.0, 13.0, 6,  ofColor(7, 141, 4), ofColor(190, 53, 20)});
    m_props.push_back(Properties{382, 382, 2.2, 13.0, 13.0, 6,  ofColor(7, 141, 4), ofColor(49, 81, 189)});

    // third section
    m_props.push_back(Properties{382, 100, 0.8, 13.0, 13.0, 6.5, ofColor(50, 61, 255), ofColor(50, 61, 255)});
    m_props.push_back(Properties{382, 100, 0.8, 13.0, 13.0, 6.5, ofColor(169, 14, 57), ofColor(169, 14, 57)});
    m_props.push_back(Properties{382, 100, 0.8, 13.0, 13.0, 6.5, ofColor(167, 0, 20), ofColor(167, 0, 20)});

    // fourth section
    m_props.push_back(Properties{382, 100, 0.8, 13.0, 13.0, 6.0, ofColor(255, 71, 35), ofColor(11, 89, 4)});
    m_props.push_back(Properties{382, 100, 0.8, 13.0, 13.0, 6.0, ofColor(255, 27, 183), ofColor(11, 89, 4)});
    m_props.push_back(Properties{382, 100, 0.8, 13.0, 13.0, 6.0, ofColor(166, 4, 255), ofColor(11, 89, 4)});

    // fifth section
    m_props.push_back(Properties{350, 350, 4.5, 13.0, 13.0, 6.0, ofColor(15, 240, 17), ofColor(22, 230, 10)});

    // sixth section
    m_props.push_back(Properties{350, 350, 4.5, 13.0, 13.0, 6.0, ofColor(11, 176, 146), ofColor(30, 37, 10)});
    m_props.push_back(Properties{350, 350, 4.5, 13.0, 13.0, 6.0, ofColor(22, 230, 10), ofColor(30, 37, 10)});

    //m_props.push_back(Properties{500, 110, 1.5, 10.0, 15.0, 24, ofColor(200, 50, 50), ofColor(0, 255, 70)});
    //m_props.push_back(Properties{500, 110, 1.5, 10.0, 15.0, 24, ofColor(200, 50, 50), ofColor(0, 255, 70)});
    //m_props.push_back(Properties{500, 110, 1.5, 10.0, 15.0, 24, ofColor(200, 50, 50), ofColor(0, 255, 70)});
    //m_props.push_back(Properties{500, 110, 1.5, 10.0, 15.0, 24, ofColor(200, 50, 50), ofColor(0, 255, 70)});
    //m_props.push_back(Properties{500, 110, 1.5, 10.0, 15.0, 24, ofColor(200, 50, 50), ofColor(0, 255, 70)});
    //m_props.push_back(Properties{500, 110, 1.5, 10.0, 15.0, 24, ofColor(200, 50, 50), ofColor(0, 255, 70)});
    //m_props.push_back(Properties{500, 110, 1.5, 10.0, 15.0, 24, ofColor(200, 50, 50), ofColor(0, 255, 70)});
    //m_props.push_back(Properties{500, 110, 1.5, 10.0, 15.0, 24, ofColor(200, 50, 50), ofColor(0, 255, 70)});
    //m_props.push_back(Properties{500, 110, 1.5, 10.0, 15.0, 24, ofColor(200, 50, 50), ofColor(0, 255, 70)});
    //m_props.push_back(Properties{150, 150, 1.0, 10.0, 15.0, 1, ofColor(200, 50, 50), ofColor(0, 255, 70)});
    //m_props.push_back(Properties{150, 150, 1.0, 10.0, 15.0, 1, ofColor(200, 50, 50), ofColor(0, 255, 70)});
    //m_props.push_back(Properties{150, 150, 1.0, 10.0, 15.0, 1, ofColor(200, 50, 50), ofColor(0, 255, 70)});
    //m_props.push_back(Properties{150, 150, 1.0, 10.0, 15.0, 1, ofColor(0, 50, 50), ofColor(0, 255, 70)});

    */

    float sum = 0;
    for (const auto& p : m_percentages)
    {
        sum += p;
    }
    m_percentages.push_back(100.0f - sum);

    gen = std::mt19937(rd());
    d = std::discrete_distribution<>(std::begin(m_percentages), std::end(m_percentages));


    m_drawGui = false;

    gui.setup("", ofxPanelDefaultFilename, 10, 600);
    //gui.add(offsetLeft.setup("offsetLeft", 667, 100, 1000));
    //gui.add(padding.setup("padding", 264, 100, 500));
    //gui.add(offsetTop.setup("offsetTop", 540, 000, 1000));
    gui.add(rock1x.setup("rock1x", 540, 0, 1920));
    gui.add(rock1y.setup("rock1y", 540, 0, 1080));
    gui.add(rock2x.setup("rock2x", 540, 0, 1920));
    gui.add(rock2y.setup("rock2y", 540, 0, 1080));
    gui.add(rock3x.setup("rock3x", 540, 0, 1920));
    gui.add(rock3y.setup("rock3y", 540, 0, 1080));
    gui.add(rock4x.setup("rock4x", 540, 0, 1920));
    gui.add(rock4y.setup("rock4y", 540, 0, 1080));
    gui.add(backgroundColor.setup("backgroundColor", ofColor(53, 127, 12), ofColor(0, 0), ofColor(255, 255)));

    gui.loadFromFile("gui_parameters.json");

    reinit();

    ofSetFullscreen(true);
}

void ofApp::update()
{
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    rocks[0].centroid.x = rock1x;
    rocks[0].centroid.y = rock1y;
    rocks[1].centroid.x = rock2x;
    rocks[1].centroid.y = rock2y;
    rocks[2].centroid.x = rock3x;
    rocks[2].centroid.y = rock3y;
    rocks[3].centroid.x = rock4x;
    rocks[3].centroid.y = rock4y;
    
    for (auto& r : rocks)
    {
        if (ofGetFrameNum() % static_cast<int>(r.speed) == 0)
        {
            auto finished = r.grow();
            if (finished)
            {
                auto rand = d(gen);
                auto prop = m_props[rand];

                for (auto &r2 : rocks) {

                    r2.init(r2.centroid.x, r2.centroid.y);
                    r2.setMaxGrowRad(prop.maxGrowRadius);
                    r2.maxCircleSize = prop.maxCircleSize;
                    r2.growRadIncrease = prop.spacing;
                    r2.setBrushStrokeSizeMin(prop.sizeMin);
                    r2.setBrushStrokeSizeMax(prop.sizeMax);
                    r2.setSelectedColor(prop.color);
                    r2.setStoneCircleBackgroundColor(prop.stoneCircleColor);
                    r2.speed = prop.speed;
                }
                return;
            }
        }
    }
}

void ofApp::draw()
{
    ofBackground(backgroundColor);
    ofPushStyle();
    ofSetColor(255);

    for (auto& r : rocks)
    {
        r.draw(0, 0, 1920, 1080);
    }

    ofPopStyle();
    if (m_drawGui)
    {
        gui.draw();
    }
}

void ofApp::keyPressed(int key)
{
    switch (key)
    {
    case 'g':
        {
            for (auto& r : rocks)
            {
                ofPolyline line;
                line.addVertex(0, 0, 0);
                line.addVertex(1920, 0, 0);
                line.addVertex(0, 1080, 0);
                line.addVertex(1920, 1080, 0);
                r.grow();
            }
        }
        break;
    case 's':
        gui.saveToFile("gui_parameters.json");
        break;
    case 'i':
        {
            ofFileDialogResult result = ofSystemLoadDialog("Load Image");
            if (result.bSuccess)
            {
                string path = result.getPath();
                brushes.loadSingle(path);
                reinit();
            }
            break;
        }
    case 'f':
        ofToggleFullscreen();
        break;
    case 'p':
        m_drawGui = !m_drawGui;
        break;
    }
}

void ofApp::reinit()
{
    rocks.clear();

    brushes.load(31, 1);

    BrushStone s1;
    s1.setBrushCollection(brushes);
    s1.setColorCollection(ColorCollection::getBlackAndWhiteColorCollection());
    ofPoint randomPoint(500, 540);

    s1.init(randomPoint.x, randomPoint.y);
    initSingle(s1, m_props[0]);

    rocks.push_back(s1);

    brushes.clear();
    brushes.load(31, 1);

    BrushStone s2;
    s2.setBrushCollection(brushes);
    s2.setColorCollection(ColorCollection::getBlackAndWhiteColorCollection());
    ofPoint randomPoint2(800, 540);
    s2.init(randomPoint2.x, randomPoint2.y);
    initSingle(s2, m_props[1]);
    rocks.push_back(s2);

    brushes.clear();
    brushes.load(31, 1);

    BrushStone s3;
    s3.setBrushCollection(brushes);
    s3.setColorCollection(ColorCollection::getBlackAndWhiteColorCollection());
    ofPoint randomPoint3(1100, 540);
    s3.init(randomPoint3.x, randomPoint3.y);
    initSingle(s3, m_props[2]);
    rocks.push_back(s3);

    brushes.clear();
    brushes.load(31, 1);

    BrushStone s4;
    s4.setBrushCollection(brushes);
    s4.setColorCollection(ColorCollection::getBlackAndWhiteColorCollection());
    ofPoint randomPoint4(1400, 540);
    s4.init(randomPoint4.x, randomPoint4.y);
    initSingle(s4, m_props[3]);
    rocks.push_back(s4);
}

void ofApp::initSingle(BrushStone& r, Properties prop)
{
    r.init(r.centroid.x, r.centroid.y);
    r.setMaxGrowRad(prop.maxGrowRadius);
    r.maxCircleSize = prop.maxCircleSize;
    r.growRadIncrease = prop.spacing;
    r.setBrushStrokeSizeMin(prop.sizeMin);
    r.setBrushStrokeSizeMax(prop.sizeMax);
    r.setSelectedColor(prop.color);
    r.setStoneCircleBackgroundColor(prop.stoneCircleColor);
    r.speed = prop.speed;
}
