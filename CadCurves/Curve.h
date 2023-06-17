#ifndef CURVE_H
#define CURVE_H
#include <stdexcept>
#include <iostream>
#include <cmath>

namespace crv {
	/// PI, which is used in calculations in this library
	const double PI = 3.14;
	/**
	 * \brief 3D Point with x, y and z coordinates
	 */
	struct Point {
		/// x coordinate
        double x;
		/// y coordinate
        double y;
		/// z coordinate
        double z;

        /**
         * \brief Default constructor, all coordinates equal to zero
         * 
         */
        Point() : x{ 0 }, y{ 0 }, z{ 0 } {}

        /**
         * \brief Point constructor
         * 
         * \param _x x coordinate
         * \param _y y coordinate
         * \param _z z coordinate
         */
        Point(double _x, double _y, double _z) : x{ _x }, y{ _y }, z{ _z } {}

        friend std::ostream& operator<<(std::ostream& os, const Point& rhs) {
            os << "{" << rhs.x << ", " << rhs.y << ", " << rhs.z << "}";
            return os;
        }
	};
	/**
	 * @brief An abstract class of all curves 
	 */
	class Curve {

	protected:
		/// Curve radius
		double radius; 
	public:
		/**
		 * \brief Basic curve constructor
		 * \throw std::invalid_argument Radius must be > 0
		 * \param radi curve radius (must be > 0)
		 */
		Curve(double radi) : radius{ radi } {
			if (radi <= 0) throw std::invalid_argument("Radius must be > 0");
		}
		Curve() = delete;
		/**
		 * \brief Get curve radius 
		 * \return Curve radius
		 */
		double getRadius() { return radius; };

		/**
		 * \brief Calculates a 3D point per parameter t along the curve
		 * 
		 * \param t Parameter in radians to find coordinates
		 * \return Point at parameter t
		 */
		virtual Point findPoint(const double t) = 0;

		/**
		 * \brief Calculates a 3D vector per parameter t along the curve 
		 * \param t Parameter in radians
		 * \return Point which contains an answer
		 */
		virtual Point derivative(const double t) = 0;

		virtual ~Curve() {}
	};

	/**
	 * \brief Curve that represents a Circle
	 */
	class Circle : public Curve {
	public:
		/**
		 * \brief Circle constructor
		 * \throw std::invalid_argument Radius must be > 0
		 * \param radi Circle radius (must be > 0)
		 */
		Circle(double radi) : Curve(radi) {}

		Circle() = delete;

		/**
		 * \brief Calculates a 3D point per parameter t along the Circle
		 * \param t Parameter in radians which using to find coordinates
		 * \return Point at parameter t
		 */
		Point findPoint(const double t) override {
			return Point{ radius * cos(t), radius * sin(t) , 0 };
		}

		/**
		 * \brief Calculates a 3D vector per parameter t along the Circle
		 * \param t Parameter in radians
		 * \return Point which contains an answer
		 */
		Point derivative(const double t) override {
			return Point{ -1 * radius * sin(t) , radius * cos(t), 0 };
		}
	};


	/**
	 * \brief Curve that represents an Ellipse
	 */
	class Ellipse : public Curve {
	private:
		/// Second radius of Ellipse
		double secondRadius;
	public:
		/**
		 * \brief Ellipse constructor
		 * \throw std::invalid_argument Radius must be > 0
		 * \param firstRadi First radius of Ellipse (should be > 0)
		 * \param secondRadi Second radius of Ellipse (should be > 0)
		 */
		Ellipse(double firstRadi, double secondRadi) : Curve(firstRadi), secondRadius{ secondRadi } {
			if (secondRadi <= 0) throw std::invalid_argument("Second radius must be > 0");
		}

		/**
		 * \brief Calculates a 3D point per parameter t along the Ellipse
		 * \param t Parameter in radians which using to find coordinates
		 * \return Point at parameter t
		 */
		Point findPoint(const double t) override {
			return Point{ radius * cos(t), secondRadius * sin(t) , 0 };
		}

		/**
		 * \brief Calculates a 3D vector per parameter t along the Ellipse
		 * \param t Parameter in radians
		 * \return Point which contains an answer
		 */
		Point derivative(const double t) override {
			return Point{ -1 * radius * sin(t) , secondRadius * cos(t) , 0 };
		}

		/**
		 * \brief Get both ellipse radii
		 *
		 * \return pair of radii
		 */
		std::pair<double, double> getRadius() {
			return std::pair<double, double>(radius, secondRadius);
		}
	};

	/**
 * \brief Curve that represents Helix
 */
	class Helix : public Curve {
	private:
		/// Helix step
		double step;
	public:
		/**
		 * \brief Helix constructor
		 * \throw std::invalid_argument Radius must be > 0
		 * \throw std::invalid_argument Step must be > 0
		 * \param radi Radius of helix
		 * \param _step Step of helix
		 */
		Helix(double radi, double _step) : Curve(radi), step{ _step } {
			if (_step <= 0) throw std::invalid_argument("Step of helix must be > 0");
		}

		/**
		 * \brief Calculates a 3D point per parameter t along the Helix
		 * \param t Parameter in radians which using to find coordinates
		 * \return Point at parameter t
		 */
		Point findPoint(const double t) override {
			return Point{ radius * cos(t), radius * sin(t), step / (2 * PI) * t };
		}

		/**
		 * \brief Calculates a 3D vector per parameter t along the Helix
		 * \param t Parameter in radians
		 * \return Point which contains an answer
		 */
		Point derivative(const double t) override {
			return Point{ -1 * radius * sin(t) , radius * cos(t), step / (2 * PI) };
		}
	};
}
#endif
