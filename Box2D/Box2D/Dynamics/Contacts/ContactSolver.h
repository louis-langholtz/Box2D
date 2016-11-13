/*
 * Original work Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
 * Modified work Copyright (c) 2016 Louis Langholtz https://github.com/louis-langholtz/Box2D
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

#ifndef B2_CONTACT_SOLVER_H
#define B2_CONTACT_SOLVER_H

#include <Box2D/Common/Math.h>
#include <Box2D/Common/Span.hpp>

namespace box2d {

	class VelocityConstraint;
	class PositionConstraint;
	
	struct PositionSolution
	{
		Position pos_a;
		Position pos_b;
		float_t min_separation;
	};

	inline PositionSolution operator+ (PositionSolution lhs, PositionSolution rhs)
	{
		return PositionSolution{lhs.pos_a + rhs.pos_a, lhs.pos_b + rhs.pos_b, lhs.min_separation + rhs.min_separation};
	}

	inline PositionSolution operator- (PositionSolution lhs, PositionSolution rhs)
	{
		return PositionSolution{lhs.pos_a - rhs.pos_a, lhs.pos_b - rhs.pos_b, lhs.min_separation - rhs.min_separation};
	}

	/// Constraint solver configuration data.
	/// @detail
	/// Defines how a constraint solver should resolve a given constraint.
	/// @sa SolvePositionConstraint.
	struct ConstraintSolverConf
	{
		/// Resolution rate.
		/// @detail
		/// Defines the percentage of the overlap that should get resolved in a single solver call.
		/// Value greater than zero and less than or equal to one.
		/// @note Recommended values are: <code>Baumgarte</code> or <code>ToiBaumgarte</code>.
		float_t resolution_rate = Baumgarte;

		/// Linear slop.
		/// @note The negative of this amount is the maximum amount of separation to create.
		/// @note Recommended value: <code>LinearSlop</code>.
		float_t linearSlop = LinearSlop;

		/// Angular slop.
		/// @note Recommended value: <code>AngularSlop</code>.
		float_t angularSlop = AngularSlop;

		/// Maximum linear correction.
		/// @detail
		/// Maximum amount of overlap to resolve in a single solver call.
		/// @note Recommended value: <code>MaxLinearCorrection</code>.
		float_t maxLinearCorrection = MaxLinearCorrection;
	};

	/// Solves the given position constraint.
	/// @detail
	/// This pushes apart the two given positions for every point in the contact position constraint
	/// and returns the minimum separation value from the position solver manifold for each point.
	/// @sa http://allenchou.net/2013/12/game-physics-resolution-contact-constraints/
	/// @return Minimum separation distance of the position constraint's manifold points
	///   (prior to "solving").
	PositionSolution SolvePositionConstraint(const PositionConstraint& pc,
											 Position positionA, bool moveA,
											 Position positionB, bool moveB,
											 ConstraintSolverConf conf);
	
	inline ConstraintSolverConf GetDefaultPositionSolverConf()
	{
		return ConstraintSolverConf{Baumgarte, LinearSlop, MaxLinearCorrection};
	}
	
	/// Solves the given position constraints.
	/// @detail This updates positions (and nothing else) by calling the position constraint solving function.
	/// @note Can't expect the returned minimum separation to be greater than or equal to
	///  ConstraintSolverConf.max_separation because code won't push the separation above this
	///   amount to begin with.
	/// @return Minimum separation.
	/// @sa MinSeparationThreshold.
	/// @sa Solve.
	float_t SolvePositionConstraints(Span<const PositionConstraint> positionConstraints,
									 Span<Position> positions,
									 ConstraintSolverConf conf = GetDefaultPositionSolverConf());
	
	inline ConstraintSolverConf GetDefaultToiPositionSolverConf()
	{
		return ConstraintSolverConf{ToiBaumgarte, LinearSlop, MaxLinearCorrection};
	}

	/// Solves the given position constraints.
	/// @detail This updates positions (and nothing else) for the two bodies identified by the
	///   given indexes by calling the position constraint solving function.
	/// @param indexA Index within the island of body A.
	/// @param indexB Index within the island of body B.
	/// @note Can't expect the returned minimum separation to be greater than or equal to
	///  ConstraintSolverConf.max_separation because code won't push the separation above this
	///   amount to begin with.
	/// @return Minimum separation.
	float_t SolvePositionConstraints(Span<const PositionConstraint> positionConstraints,
									 Span<Position> positions,
									 island_count_t indexA, island_count_t indexB,
									 ConstraintSolverConf conf = GetDefaultToiPositionSolverConf());

	/// Solves the velocity constraint.
	/// @detail This updates the tangent and normal impulses of the velocity constraint points of the given velocity
	///   constraint and updates the given velocities.
	/// @pre The velocity constraint must have a valid normal, a valid tangent,
	///   valid point relative positions, and valid velocity biases.
	void SolveVelocityConstraint(VelocityConstraint& vc, Velocity& velA, Velocity& velB);
	
} // namespace box2d

#endif

