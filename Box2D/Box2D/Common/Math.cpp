/*
* Copyright (c) 2007-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#include <Box2D/Common/Math.h>

using namespace box2d;

void Mat33::GetInverse22(Mat33* M) const
{
	const auto a = ex.x, b = ey.x, c = ex.y, d = ey.y;
	auto det = a * d - b * c;
	if (det != float_t{0})
	{
		det = float_t(1) / det;
	}

	M->ex.x =  det * d;	M->ey.x = -det * b; M->ex.z = float_t{0};
	M->ex.y = -det * c;	M->ey.y =  det * a; M->ey.z = float_t{0};
	M->ez.x = float_t{0}; M->ez.y = float_t{0}; M->ez.z = float_t{0};
}

/// Returns the zero matrix if singular.
void Mat33::GetSymInverse33(Mat33* M) const
{
	auto det = Dot(ex, Cross(ey, ez));
	if (det != float_t{0})
	{
		det = float_t(1) / det;
	}

	const auto a11 = ex.x, a12 = ey.x, a13 = ez.x;
	const auto a22 = ey.y, a23 = ez.y;
	const auto a33 = ez.z;

	M->ex.x = det * (a22 * a33 - a23 * a23);
	M->ex.y = det * (a13 * a23 - a12 * a33);
	M->ex.z = det * (a12 * a23 - a13 * a22);

	M->ey.x = M->ex.y;
	M->ey.y = det * (a11 * a33 - a13 * a13);
	M->ey.z = det * (a13 * a12 - a11 * a23);

	M->ez.x = M->ex.z;
	M->ez.y = M->ey.z;
	M->ez.z = det * (a11 * a22 - a12 * a12);
}