#pragma once
#include <string>
#include <list>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <chrono>
#include <algorithm>

struct brickNamesStruct;
struct testData;
brickNamesStruct getBricks(std::string);
void westWall(const std::unordered_map<std::string, std::string>, std::list<std::string>&);
void eastWall(const std::unordered_map<std::string, std::string>, std::list<std::string>&);
std::list<std::string>output(std::string);
void viewOutput(std::list<std::string>&);
std::list<testData> getTestData();