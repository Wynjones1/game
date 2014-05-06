#include "config.h"

Config::Config()
: width(800)
, height(500)
, aspect((float) width / height)
, fov(45.0f)
{}

Config::Config(int argc, char **argv)
{}

Config g_config;
