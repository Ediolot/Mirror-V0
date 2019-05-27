#include <iostream>
#include <opencv2/core.hpp>
#include "utils/Utils.h"
#include "App.h"
#include <typeinfo>

int main(int argc, char** argv) {
    std::cout << "OpenCV Version: " << CV_VERSION << std::endl;
    std::cout << "Allegro Version: " << Utils::allegroVersion() << std::endl;

    App app;
    app.run();

    //weather stuff
    std::string url_weather = "http://api.openweathermap.org/data/2.5/weather?id=3128760&appid=c4aeec5a95e4ef1db4c115086f5eeb5a&units=metric";
    nlohmann::json weather = Utils::requestJSON(url_weather);
    std::string weather_description = weather["weather"][0]["description"];
    std::string weather_image = weather["weather"][0]["main"];
    //std::cout <<  weather_description << std::endl;
    auto temperature = weather["main"]["temp"];
    if(weather_image.compare("clear sky") || weather_image.compare("few clouds")){
        //usar imagen sun.png
    }else if(weather_image.compare("scattered clouds") || weather_image.compare("broken clouds")){
        //usar imagen coulds.png
    }else if(weather_image.compare("shower rain") || weather_image.compare("rain")){
        //usar rainy.png
    }else if(weather_image.compare("thunderstorm") || weather_image.compare("snow")){
        //usar snow-alt.png
    }


    //reddit stuff
    std::string url_reddit = "https://www.reddit.com/r/worldnews/top/.json?limit=5";
    nlohmann::json reddit = Utils::requestJSON(url_reddit);
    std::vector<std::string> reddit_titles;
    std::vector<int> reddit_comments;
    for(int a = 0; a <= 4; a++) {
        reddit_titles.push_back(reddit["data"]["children"][a]["data"]["title"]);
        reddit_comments.push_back(reddit["data"]["children"][a]["data"]["num_comments"]);
    }

    for(int a = 0; a <= 4; a++) {
        std::cout <<  reddit_comments[a] << std::endl;
    }


    return 0;
}