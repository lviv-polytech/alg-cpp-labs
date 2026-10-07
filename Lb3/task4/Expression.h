#pragma once

namespace Task4::Expression {
    /// <summary>
    /// Represents the parameters for checking whether a given 2D point lies within
    /// the target shaded region.
    /// </summary>
    struct Params {
        const double x;
        const double y;
        const double R;

        /// <summary>
        /// Initializes a new instance of the Params structure.
        /// </summary>
        /// <param name="x">The x-coordinate of the point.</param>
        /// <param name="y">The y-coordinate of the point.</param>
        /// <param name="R">The radius parameter R defining the geometry of the region (must be strictly positive).</param>
        Params(const double x, const double y, const double R) : x(x), y(y), R(R) {}
    };

    /// <summary>
    /// Determines whether the point (x, y) falls inside or on the boundary of the shaded area.
    ///
    /// Mathematical description:
    /// The shaded region is symmetric about the origin and consists of two parts:
    /// 1. Second quadrant (top-left region):
    ///    - Horizontal bounds: -R &lt;= x &lt;= 0
    ///    - Vertical bounds: y &gt;= 0
    ///    - Bounded by the circle arc centered at (-R, 0) with radius R:
    ///      (x + R)^2 + y^2 &lt;= R^2
    /// 2. Fourth quadrant (bottom-right region):
    ///    - Horizontal bounds: 0 &lt;= x &lt;= R
    ///    - Vertical bounds: y &lt;= 0
    ///    - Bounded by the circle arc centered at (R, 0) with radius R:
    ///      (x - R)^2 + y^2 &lt;= R^2
    /// </summary>
    /// <param name="params">The point coordinates and radius parameter.</param>
    /// <returns>True if the point is inside or on the boundary of the shaded region, false otherwise.</returns>
    /// <exception cref="std::invalid_argument">Thrown if R is non-positive or not a finite number.</exception>
    bool isInside(const Params& params);

    /// <summary>
    /// Direct overload taking coordinates and radius as separate arguments.
    /// </summary>
    /// <param name="x">The x-coordinate of the point.</param>
    /// <param name="y">The y-coordinate of the point.</param>
    /// <param name="R">The radius parameter R (must be positive and finite).</param>
    /// <returns>True if the point lies inside or on the boundary; false otherwise.</returns>
    /// <exception cref="std::invalid_argument">Thrown if R is non-positive or not a finite number.</exception>
    bool isInside(double x, double y, double R);
}
