#pragma once

// TODO order
// TODO currently later bind will overwrite the previous function without any kind of warning
// might be confusing why some functions are not working (been overwritten)
#define BIND_DISPLAY \
->Bind<GL::CALLBACK_FUNC::DISPLAY>([&]() \
{

#define BIND_KEYBOARD(key, x, y) \
->Bind<GL::CALLBACK_FUNC::KEYBOARD>([&](unsigned char key, int x, int y) \
{

#define BIND_MOUSE(button, state, x, y) \
->Bind<GL::CALLBACK_FUNC::MOUSE>([&](int button, int state, int x, int y) \
{

#define BIND_IDLE \
->Bind<GL::CALLBACK_FUNC::IDLE>([&]() \
{

#define BIND_MOTION(x, y) \
->Bind<GL::CALLBACK_FUNC::MOTION>([&](int x, int y) \
{

#define BIND_PASSIVE_MOTION(x, y) \
->Bind<GL::CALLBACK_FUNC::PASSIVEMOTION>([&](int x, int y) \
{

#define BIND_INIT \
->Bind<GL::CALLBACK_FUNC::INIT>([&]() \
{

#define BIND_UPDATE \
->Bind<GL::CALLBACK_FUNC::UPDATE>([&]() \
{

#define END_BIND })