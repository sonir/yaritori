//
//  animation_setup.hpp
//  yaritori
//
//  Created by Hana on 2018/01/19.
//
//

#ifndef animation_setup_h
#define animation_setup_h


/////////////////// AGENT ///////////////////

//Constant Values
constexpr float M_2XPI = M_PI * 2.0;

//Modulation on each node
constexpr float STEP_MAX = M_2XPI * 6.0f;
constexpr float STEP_MIN = M_2XPI * 4.0f;

constexpr float TREMOR_RATIO = 0.12f;
constexpr float STAY_RATIO = 1.0 - TREMOR_RATIO;
constexpr float MOV_FIX = 0.008;

//Size modulation
constexpr float SIZE_MOD_STRENGTH = 0.12;
constexpr float SIZE_MOD_FLOOR = 1.0 - SIZE_MOD_STRENGTH;
constexpr float SIZE_MOD_STEP = 0.04;

//constexpr float dx = 0.0166f;
constexpr float easing = 0.05;



/////////////////// WAVEFORM ///////////////////

static constexpr float cycle = 1. * 1000.;   //msec
static constexpr float maxR = 0.01;    //Max amplitude
static const int TURN_NUM = 15;  //num of feature points



/////////////////// Ripple ///////////////////
constexpr float RIPPLE_ALPHA_FIX_BLACK = 0.3;
constexpr float RIPPLE_ALPHA_FIX_WHITE = 0.7;
static constexpr float r_Min = 0.15;
static constexpr float r_Max = 0.17;

static constexpr float durMin = 0.5;
static constexpr float durMax = 1.2;

static constexpr float lagMin = 0.1;
static constexpr float lagMax = 0.25;

static constexpr float sp_noiseMin = 1.5;
static constexpr float sp_noiseMax = 1.7;



#endif /* animation_setup_h */
