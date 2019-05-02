//
// Created by jsier on 02/05/2019.
//

#ifndef MIRROR_APP_SIZE_H
#define MIRROR_APP_SIZE_H


class Size {
public:
    double w;
    double h;
    bool percentageW;
    bool percentageH;

    Size(double w, double h, bool percentageW = false, bool percentageH = false)
        : w(w), h(h), percentageW(percentageW), percentageH(percentageH)
    {}
};


#endif //MIRROR_APP_SIZE_H
