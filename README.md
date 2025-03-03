# ConsloleTranslate
My console translater for movie watching in Linux.

## Dependencies
Before compiling file you need to install:
  - libcurl4-openssl-dev - for Curl;
  - nlohmann-json3-dev - for parse json;

## Installation on Ubuntu
  sudo apt update && sudo apt install libcurl4-openssl-dev nlohmann-json3-dev

## To compile project, use:
  g++ main.cpp -o Translate -lcurl -std=c++17;

