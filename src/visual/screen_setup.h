//
//  screen_setup.h
//  yaritori_oneWindow
//
//  Created by Momoha Matsuhashi on 2018/01/19.
//
//

#ifndef screen_setup_h
#define screen_setup_h

//Length: real length(mm) | input figures on the site
constexpr float DISPLAY_LENGTH_W = 7111.;
constexpr float DISPLAY_LENGTH_H = 4000.;
constexpr float SCREEN_LENGHT_W = 4000.;
constexpr float SCREEN_LENGTH_H = 4000.;
constexpr float MARGIN_LENGTH = 200.;
constexpr float ORIGIN_0_LENGTH_W = 0.;
constexpr float ORIGIN_1_LENGTH_W = 0.;
constexpr float ORIGIN_2_LENGTH_W = 0.;

//display resolution(projector)
constexpr int DISPLAY_WIDTH = 480;//1920;
constexpr int DISPLAY_HEIGHT = 270;//1080;

//Display reslution (master pc)
constexpr int MASTER_WIDTH = 1920;
constexpr int MASTER_HEGHT = 1200;

//unit conversion
constexpr float PixPerMm_W = DISPLAY_WIDTH / DISPLAY_LENGTH_W;
constexpr float PixPerMm_H = DISPLAY_HEIGHT / DISPLAY_LENGTH_H;

//in vsyn
constexpr int MARGIN = MARGIN_LENGTH * PixPerMm_W;

constexpr int SCREEN_WIDTH = SCREEN_LENGHT_W * PixPerMm_W;
constexpr int SCREEN_HEIGHT = SCREEN_LENGTH_H * PixPerMm_H;

constexpr int VSYN_WIDTH = SCREEN_WIDTH * 3 + MARGIN * 4;
constexpr int VSYN_HEIGHT = SCREEN_HEIGHT + MARGIN * 2;  //That is 1.0

constexpr int APP_WIDTH = DISPLAY_WIDTH * 3;
constexpr int APP_HEIGHT = DISPLAY_HEIGHT;

constexpr int ORIGIN_0_W = ORIGIN_0_LENGTH_W * PixPerMm_W;
constexpr int ORIGIN_1_W = ORIGIN_1_LENGTH_W * PixPerMm_W;
constexpr int ORIGIN_2_W = ORIGIN_2_LENGTH_W * PixPerMm_W;

#endif /* screen_setup_h */
