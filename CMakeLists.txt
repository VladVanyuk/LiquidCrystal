# Virtual base class for LiquidCrystal and LiquidCrystal_I2C libraries
# https://github.com/VladVanyuk/LiquidCrystal
# MIT License

cmake_minimum_required(VERSION 3.5)

idf_component_register(SRCS "LiquidCrystal_Base.cpp" "LiquidCrystal.cpp" "LiquidCrystal_I2C.cpp"
                       INCLUDE_DIRS "."
                       REQUIRES arduino)

project(LiquidCrystal)