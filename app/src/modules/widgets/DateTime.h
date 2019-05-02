//
// Created by jsier on 02/05/2019.
//

#ifndef MIRROR_APP_DATETIME_H
#define MIRROR_APP_DATETIME_H


#include "Widget.h"
#include "components/Text.h"

class DateTime : public Widget {
    Text date;
    Text time;

public:
    DateTime();
    void draw() override;
    void update() override;

private:
    void setDateTime(std::string &date, std::string &time);
};


#endif //MIRROR_APP_DATETIME_H
