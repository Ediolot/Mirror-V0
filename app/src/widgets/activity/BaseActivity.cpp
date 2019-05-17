//
// Created by jsier on 17/05/2019.
//

#include <iostream>
#include "../../external/tinyxml2/tinyxml2.h"
#include "BaseActivity.h"
#include "../WidgetFactory.h"

using namespace tinyxml2;

BaseActivity::BaseActivity(const std::string &xmlView)
    : BaseWidget(xmlView)
{
    std::cout << "Created activity: " << xmlView << std::endl;
}

BaseActivity::~BaseActivity() {
    ;
}
