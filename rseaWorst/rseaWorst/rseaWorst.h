#pragma once
#include <string>
#include <list>
#include <map>
#include <fstream>
#include <iostream>

struct brickNamesStruct;
brickNamesStruct getBricks(std::string);
void westWall(const std::map<std::string, std::string>, std::list<std::string>&);
void eastWall(const std::map<std::string, std::string>, std::list<std::string>&);
std::list<std::string>output(std::string);
void viewOutput(std::list<std::string>&);
