//
//  screen_setup.h
//  yaritori_oneWindow
//
//  Created by Momoha Matsuhashi on 2018/01/19.
//
//

#ifndef screen_setup_h
#define screen_setup_h

//#define DEBUG_MODE_SCREEN

//Length: real length(mm) | input figures on the site
constexpr float DISPLAY_LENGTH_W = 7111.;
constexpr float DISPLAY_LENGTH_H = 4000.;
constexpr float MARGIN_0_LENGTH = 200.;
constexpr float MARGIN_1_LENGTH = 200.;

//display resolution(projector)
constexpr int DISPLAY_WIDTH = 1920;
constexpr int DISPLAY_HEIGHT = 1080;

//Display reslution (master pc)
constexpr int MASTER_WIDTH = 1920;
constexpr int MASTER_HEGHT = 1200;

//unit conversion
constexpr float PixPerMm_W = DISPLAY_WIDTH / DISPLAY_LENGTH_W;
constexpr float PixPerMm_H = DISPLAY_HEIGHT / DISPLAY_LENGTH_H;

//in vsyn
constexpr int MARGIN_0 = MARGIN_0_LENGTH * PixPerMm_W;
constexpr int MARGIN_1 = MARGIN_1_LENGTH * PixPerMm_H;
//constexpr int MARGIN_W = DISPLAY_WIDTH * 0.5;
//constexpr int MARGIN_H = DISPLAY_HEIGHT * 0.5;

constexpr int MARGIN_W = 0;
constexpr int MARGIN_H = 0;

//constexpr int ORIGINAL_HEIGHT = DISPLAY_HEIGHT + MARGIN_H * 2;  //That is 1.0
//constexpr int ORIGINAL_WIDTH = ORIGINAL_HEIGHT * 2.9;
//constexpr int ORIGINAL_WIDTH = DISPLAY_WIDTH * 3 + MARGIN_W * 2 + MARGIN_0 + MARGIN_1;  //ORIGINAL_WIDTH = 4 * DISPLAY_WIDTH
//constexpr int ORIGINAL_HEIGHT = DISPLAY_HEIGHT + MARGIN_H * 2;  //ORIGINAL_HEIGHT = 2 * DISPLAY_HEIGHT.
//constexpr int ORIGINAL_WIDTH = ORIGINAL_HEIGHT * 2.9;

constexpr int ORIGINAL_WIDTH = DISPLAY_WIDTH * 3 + MARGIN_0 * 2. ;
constexpr int ORIGINAL_HEIGHT = DISPLAY_HEIGHT;

constexpr int APP_WIDTH = DISPLAY_WIDTH * 3;
constexpr int APP_HEIGHT = DISPLAY_HEIGHT;

#endif /* screen_setup_h */
