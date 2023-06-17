#include "Example.h"
#include <random>
#include <iostream>
#include <omp.h>

void startExample() {
	// Populate a container
	std::vector<std::shared_ptr<crv::Curve>> curves;
	fillVector(curves, 100);

	//Print coordinates of points and derivatives of all curves
	printPointAndDerivative(curves);

	//Populates second container only with circles
	std::vector <std::shared_ptr<crv::Curve>> onlyCircles;
	fillVectorWithCircles(curves, onlyCircles);

	//Sort circles
	sortCircles(onlyCircles);

	//sum circles radii with OpenMP
	double circlesRadiSum = 0;
	#pragma omp parallel for reducton (+:circlesRadiSum)
	for (int i = 0; i < onlyCircles.size(); i++) {
		circlesRadiSum += onlyCircles[i]->getRadius();
	}
	std::cout << "Sum of circles radii = " << circlesRadiSum << std::endl;
}

void fillVector(std::vector<std::shared_ptr<crv::Curve>>& curves, const int numberOfCurves)  {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> distCurvesType(0, 2);
	std::uniform_int_distribution<int> distCurvesRadi(1, 100);

	for (int i = 0; i < numberOfCurves; i++) {
		switch (distCurvesType(mt)) {
		case 0:
			curves.push_back(std::make_shared<crv::Circle>(distCurvesRadi(mt)));
			break;
		case 1:
			curves.push_back(std::make_shared<crv::Ellipse>(distCurvesRadi(mt), distCurvesRadi(mt)));
			break;
		case 2:
			curves.push_back(std::make_shared<crv::Helix>(distCurvesRadi(mt), distCurvesRadi(mt)));
			break;
		default:
			break;
		}
	}
}

void printPointAndDerivative(const std::vector<std::shared_ptr<crv::Curve>>& curves) {
	double t = crv::PI / 4;
	for (auto const& curve : curves) {
		std::cout << typeid(*curve).name();
		std::cout << " Point at t = " << curve->findPoint(t) << " derivative  = " << curve->derivative(t) << std::endl;
	}
}

void fillVectorWithCircles(const std::vector<std::shared_ptr<crv::Curve>>& curves, std::vector<std::shared_ptr<crv::Curve>>& onlyCircles) {
	for (auto& curve : curves) {
		if (auto circle = std::dynamic_pointer_cast<crv::Circle>(curve)) {
			onlyCircles.push_back(circle);
		}
	}
}

void sortCircles(std::vector<std::shared_ptr<crv::Curve>>& onlyCircles) {
	std::sort(onlyCircles.begin(), onlyCircles.end(), [](const auto& lhs, const auto& rhs) {
		return lhs->getRadius() < rhs->getRadius();
		});
	std::cout << "Sorted Circles:" << std::endl;
	for (auto& circle : onlyCircles) {
		std::cout << circle->getRadius() << " ";
	}
	std::cout << std::endl;
}


