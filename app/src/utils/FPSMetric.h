//
// Created by jsier on 16/05/2019.
//

#ifndef MIRROR_APP_FPSMETRIC_H
#define MIRROR_APP_FPSMETRIC_H


class FPSMetric {
    double start;
    double end;
    double elapsed;
    int frames;
    int fps;

    double FPS_UPDATE_S = 1.0;

public:
    FPSMetric() = default;
    virtual ~FPSMetric() = default;

    void init();
    void measure();
    int value();
    void draw() const;
};


#endif //MIRROR_APP_FPSMETRIC_H
