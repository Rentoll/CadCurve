#ifndef EXAMPLE_H
#define EXAMPLE_H
#include <vector>
#include "Curve.h"

void startExample();
void fillVector(std::vector<std::shared_ptr<crv::Curve>>& curves, const int numberOfCurves = 100000);
void printPointAndDerivative(const std::vector<std::shared_ptr<crv::Curve>>& curves);
void fillVectorWithCircles(const std::vector<std::shared_ptr<crv::Curve>>& curves, std::vector <std::shared_ptr<crv::Curve>>& onlyCircles);
void sortCircles(std::vector<std::shared_ptr<crv::Curve>>& onlyCircles);
#endif

