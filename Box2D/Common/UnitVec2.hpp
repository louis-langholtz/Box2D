/*
 * Copyright (c) 2017 Louis Langholtz https://github.com/louis-langholtz/Box2D
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#ifndef UnitVec2_hpp
#define UnitVec2_hpp

/// @file
/// Declarations of the UnitVec2 class and free functions associated with it.

#include <Box2D/Common/Settings.hpp>

namespace box2d
{
    /// @brief 2-D unit vector.
    /// @details This is a 2-dimensional directional vector.
    class UnitVec2
    {
    public:
        
        /// @brief Data type used for the coordinate values of this vector.
        using data_type = Real;
        
        /// @brief Gets the right-ward oriented unit vector.
        /// @note This is the value for the 0/4 turned (0 angled) unit vector.
        /// @note This is the reverse perpendicular unit vector of the bottom oriented vector.
        /// @note This is the forward perpendicular unit vector of the top oriented vector.
        static constexpr UnitVec2 GetRight() noexcept
        {
            return UnitVec2{1, 0};
        }
        
        /// @brief Gets the top-ward oriented unit vector.
        /// @note This is the actual value for the 1/4 turned (90 degree angled) unit vector.
        /// @note This is the reverse perpendicular unit vector of the right oriented vector.
        /// @note This is the forward perpendicular unit vector of the left oriented vector.
        static constexpr UnitVec2 GetTop() noexcept
        {
            return UnitVec2{0, 1};
        }
        
        /// @brief Gets the left-ward oriented unit vector.
        /// @note This is the actual value for the 2/4 turned (180 degree angled) unit vector.
        /// @note This is the reverse perpendicular unit vector of the top oriented vector.
        /// @note This is the forward perpendicular unit vector of the bottom oriented vector.
        static constexpr UnitVec2 GetLeft() noexcept
        {
            return UnitVec2{-1, 0};
        }

        /// @brief Gets the bottom-ward oriented unit vector.
        /// @note This is the actual value for the 3/4 turned (270 degree angled) unit vector.
        /// @note This is the reverse perpendicular unit vector of the left oriented vector.
        /// @note This is the forward perpendicular unit vector of the right oriented vector.
        static constexpr UnitVec2 GetBottom() noexcept
        {
            return UnitVec2{0, -1};
        }
        
        /// @brief Gets the non-oriented unit vector.
        static constexpr UnitVec2 GetZero() noexcept
        {
            return UnitVec2{0, 0};
        }
        
        static constexpr UnitVec2 GetDefaultFallback() noexcept
        {
            return UnitVec2{};
        }
        
        static UnitVec2 Get(const Real x, const Real y, Real& magnitude,
                            const UnitVec2 fallback = GetDefaultFallback());

        constexpr UnitVec2() noexcept
        {
            // Intentionally empty.
        }
        
        /// @brief Gets the given angled unit vector.
        ///
        /// @note For angles that are meant to be at exact multiples of the quarter turn,
        ///   better accuracy will be had by using one of the four oriented unit
        ///   vector returning methods - for the right, top, left, bottom orientations.
        ///
        explicit UnitVec2(const Angle angle) noexcept;
        
        constexpr auto GetX() const noexcept
        {
            return m_x;
        }
        
        constexpr auto GetY() const noexcept
        {
            return m_y;
        }
        
        constexpr auto cos() const noexcept
        {
            return m_x;
        }
        
        constexpr auto sin() const noexcept
        {
            return m_y;
        }

        constexpr inline UnitVec2 FlipXY() const noexcept
        {
            return UnitVec2{-GetX(), -GetY()};
        }
        
        constexpr inline UnitVec2 FlipX() const noexcept
        {
            return UnitVec2{-GetX(), GetY()};
        }
        
        constexpr inline UnitVec2 FlipY() const noexcept
        {
            return UnitVec2{GetX(), -GetY()};
        }
        
        constexpr inline UnitVec2 Rotate(UnitVec2 amount) const noexcept
        {
            return UnitVec2{
                GetX() * amount.GetX() - GetY() * amount.GetY(),
                GetY() * amount.GetX() + GetX() * amount.GetY()
            };
        }
        
        /// @brief Gets a vector counter-clockwise (reverse-clockwise) perpendicular to this vector.
        /// @details This returns the unit vector (-y, x).
        /// @return A counter-clockwise 90-degree rotation of this vector.
        /// @sa GetFwdPerpendicular.
        constexpr inline UnitVec2 GetRevPerpendicular() const noexcept
        {
            // See http://mathworld.wolfram.com/PerpendicularVector.html
            return UnitVec2{-m_y, m_x};
        }
        
        /// @brief Gets a vector clockwise (forward-clockwise) perpendicular to this vector.
        /// @details This returns the unit vector (y, -x).
        /// @return A clockwise 90-degree rotation of this vector.
        /// @sa GetRevPerpendicular.
        constexpr inline UnitVec2 GetFwdPerpendicular() const noexcept
        {
            // See http://mathworld.wolfram.com/PerpendicularVector.html
            return UnitVec2{m_y, -m_x};
        }
        
        constexpr inline UnitVec2 operator- () const noexcept
        {
            return UnitVec2{-m_x, -m_y};
        }

        constexpr inline UnitVec2 operator+ () const noexcept
        {
            return UnitVec2{+m_x, +m_y};
        }
        
        constexpr inline UnitVec2 Absolute() const noexcept
        {
            return UnitVec2{std::abs(m_x), std::abs(m_y)};
        }
        
    private:
        constexpr UnitVec2(data_type x, data_type y) noexcept:
            m_x{x}, m_y{y}
        {
            // Intentionally empty.
        }
        
        data_type m_x = GetInvalid<data_type>();
        data_type m_y = GetInvalid<data_type>();
    };
    
    /// Get the x-axis
    constexpr inline UnitVec2 GetXAxis(UnitVec2 rot) noexcept
    {
        return rot;
    }
    
    /// Get the u-axis ("u"??? is that a typo??? Anyway, this is the reverse perpendicular vector of rot as a directional vector)
    constexpr inline UnitVec2 GetYAxis(UnitVec2 rot) noexcept
    {
        return rot.GetRevPerpendicular();
    }

    constexpr inline bool operator == (const UnitVec2 a, const UnitVec2 b) noexcept
    {
        return (a.GetX() == b.GetX()) && (a.GetY() == b.GetY());
    }
    
    constexpr inline bool operator != (const UnitVec2 a, const UnitVec2 b) noexcept
    {
        return (a.GetX() != b.GetX()) || (a.GetY() != b.GetY());
    }

    /// Gets a vector counter-clockwise (reverse-clockwise) perpendicular to the given vector.
    /// @details This takes a vector of form (x, y) and returns the vector (-y, x).
    /// @param vector Vector to return a counter-clockwise perpendicular equivalent for.
    /// @return A counter-clockwise 90-degree rotation of the given vector.
    /// @sa GetFwdPerpendicular.
    constexpr inline UnitVec2 GetRevPerpendicular(const UnitVec2 vector) noexcept
    {
        return vector.GetRevPerpendicular();
    }
    
    /// Gets a vector clockwise (forward-clockwise) perpendicular to the given vector.
    /// @details This takes a vector of form (x, y) and returns the vector (y, -x).
    /// @param vector Vector to return a clockwise perpendicular equivalent for.
    /// @return A clockwise 90-degree rotation of the given vector.
    /// @sa GetRevPerpendicular.
    constexpr inline UnitVec2 GetFwdPerpendicular(const UnitVec2 vector) noexcept
    {
        return vector.GetFwdPerpendicular();
    }

    /// Rotates a vector by a given angle.
    constexpr inline UnitVec2 Rotate(const UnitVec2 vector, const UnitVec2& angle) noexcept
    {
        return vector.Rotate(angle);
    }
    
    /// Inverse rotate a vector
    constexpr inline UnitVec2 InverseRotate(const UnitVec2 vector, const UnitVec2& angle) noexcept
    {
        return vector.Rotate(angle.FlipY());
    }

    constexpr inline UnitVec2::data_type GetX(const UnitVec2 value)
    {
        return value.GetX();
    }
    
    constexpr inline UnitVec2::data_type GetY(const UnitVec2 value)
    {
        return value.GetY();
    }
    
    template <>
    constexpr UnitVec2 GetInvalid() noexcept
    {
        return UnitVec2{};
    }
    
    template <>
    constexpr inline bool IsValid(const UnitVec2& value) noexcept
    {
        return IsValid(GetX(value)) && IsValid(GetY(value)) && (value != UnitVec2::GetZero());
    }
    
}

#endif /* UnitVec2_hpp */
