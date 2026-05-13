#pragma once
#ifndef TEXTURES_H
#define TEXTURES_H

#include <fstream>
#include <string>
#include <vector>

using namespace std;
class Textures 
{
public:
    void read(string path);
    void print();

private:
    string line;
    vector<string> tamagotchi;
};


#endif