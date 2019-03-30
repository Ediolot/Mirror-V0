#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

const char* AUDIO_OGG_FILE = "../files/file_example_OOG_1MG.ogg";
const char* FONT_TTF = "../files/commanders.ttf";
const int VIDEO_FRAME_MS_WAIT = 10;
const int VIDEO_FRAMES = 300;

std::string allegroVersion();
int allegroStart();
int allegroAudio();
int opencvToAllegroImg();

int main(int argc, char** argv) {
    std::cout << "OpenCV Version: " << CV_VERSION << std::endl;
    std::cout << "Allegro Version: " << allegroVersion() << std::endl;

    std::cout << "Starting allegro...\n" << std::flush;
    std::cout << (allegroStart() == 0 ? "OK" : "FAIL") << std::endl;

    //std::cout << "Playing audio...\n" << std::flush;
    //std::cout << (allegroAudio() == 0 ? "OK" : "FAIL") << std::endl;

    std::cout << "Capturing mic...\n" << std::flush;
    std::cout << "Not implemented" << std::endl;

    std::cout << "Capturing video...\n" << std::flush;
    std::cout << (opencvToAllegroImg() == 0 ? "OK" : "FAIL") << std::endl;

    return 0;
}

std::string allegroVersion() {
    uint32_t version = al_get_allegro_version();
    int major    = version >> 24;
    int minor    = (version >> 16) & 255;
    int revision = (version >> 8) & 255;
    int release  = version & 255;

    return std::to_string(major)    + "." +
           std::to_string(minor)    + "." +
           std::to_string(revision) + "." +
           std::to_string(release);
}

int allegroStart() {

    if (!al_init()) {
        std::cout << "Failed to initialize allegro!" << std::endl;
        return -1;
    }

    if(!al_install_audio()){
        fprintf(stderr, "failed to initialize audio!\n");
        return -1;
    }

    if(!al_init_acodec_addon()){
        fprintf(stderr, "failed to initialize audio codecs!\n");
        return -1;
    }

    if (!al_reserve_samples(1)){
        fprintf(stderr, "failed to reserve samples!\n");
        return -1;
    }

    al_init_font_addon();
    al_init_ttf_addon();

    return 0;
}

int allegroAudio() {
    ALLEGRO_SAMPLE *sample = al_load_sample(AUDIO_OGG_FILE);

    if (!sample){
        std::cout << "Audio clip sample '" << AUDIO_OGG_FILE << "' not loaded!" << std::endl;
        return -1;
    }

    al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, nullptr);
    al_rest(3.0);
    al_destroy_sample(sample);
    return 0;
}

int opencvToAllegroImg() {
    const int W = 640;
    const int H = 480;
    cv::VideoCapture capture;
    cv::Mat image = cv::Mat::zeros(H, W, CV_8UC1); // Rows Cols

    al_set_new_bitmap_format(ALLEGRO_PIXEL_FORMAT_RGB_888);
    ALLEGRO_BITMAP *alImage = al_create_bitmap(W, H); // Width Height
    ALLEGRO_DISPLAY *display = al_create_display(W, H);
    ALLEGRO_FONT *font = al_load_ttf_font(FONT_TTF, 10, ALLEGRO_TTF_MONOCHROME );

    if (!font){
        return -1;
    }

    if (!alImage || !display) {
        return -1;
    }

    capture.open(0);
    if (!capture.isOpened()) {
        return -1;
    }

    for(int i = 0; i < VIDEO_FRAMES; ++i)
    {
        capture >> image;

        if (!image.empty()) {
            ALLEGRO_LOCKED_REGION *region = al_lock_bitmap(alImage, ALLEGRO_PIXEL_FORMAT_RGB_888, ALLEGRO_LOCK_WRITEONLY);
            memcpy(region->data, image.data, H * W * 3);
            al_unlock_bitmap(alImage);
        }
        cv::waitKey(VIDEO_FRAME_MS_WAIT);

        al_clear_to_color(al_map_rgb(0,0,0));
        //al_draw_bitmap(alImage,0,0,0);
        al_draw_text(font, al_map_rgb(255,255,255), 100, 100, ALLEGRO_ALIGN_CENTRE, "Your Text Here!");
        al_flip_display();
        al_rest(10.0);
    }
    al_destroy_display(display);
    al_destroy_bitmap(alImage);
    capture.release();
    return 0;
}