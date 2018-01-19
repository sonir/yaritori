//
//  animation_setup.hpp
//  yaritori
//
//  Created by Hana on 2018/01/19.
//
//

#ifndef animation_setup_h
#define animation_setup_h

//Constant Values
constexpr float M_2XPI = M_PI * 2.0;

constexpr float SIZE_FIX = 0.5;

//Modulation on each node
constexpr float STEP_MAX = M_2XPI * 6.0f;
constexpr float STEP_MIN = M_2XPI * 4.0f;

constexpr float TREMOR_RATIO = 0.18f;//180119 MODIFIED BY 137 //0.12f;
constexpr float STAY_RATIO = 1.0 - TREMOR_RATIO;
constexpr float MOV_FIX = 0.008;

//Size modulation
constexpr float SIZE_MOD_STRENGTH = 0.12;
constexpr float SIZE_MOD_FLOOR = 1.0 - SIZE_MOD_STRENGTH;
constexpr float SIZE_MOD_STEP = 0.04;

//constexpr float dx = 0.0166f;
constexpr float easing = 0.05;

#endif /* animation_setup_h */
