/*
 * Copyright (c) 2017 Louis Langholtz https://github.com/louis-langholtz/Box2D
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

#include "gtest/gtest.h"
#include <Box2D/Common/Math.hpp>

using namespace box2d;

TEST(Sweep, ByteSizeIs_36_or_72)
{
    switch (sizeof(Real))
    {
        case  4: EXPECT_EQ(sizeof(Sweep), std::size_t(36)); break;
        case  8: EXPECT_EQ(sizeof(Sweep), std::size_t(72)); break;
        case 16: EXPECT_EQ(sizeof(Sweep), std::size_t(144)); break;
        default: FAIL(); break;
    }
}

TEST(Sweep, ConstructorSetsPos0and1) {
    const auto pos = Position{Length2D{Real(-0.4) * Meter, Real(2.34) * Meter}, Real{3.14f} * Radian};
    Sweep sweep{pos};
    EXPECT_EQ(pos, sweep.pos0);
    EXPECT_EQ(pos, sweep.pos1);
}

TEST(Sweep, ResetSetsAlpha0to0) {
    const auto pos = Position{Length2D{Real(-0.4) * Meter, Real(2.34) * Meter}, Real{3.14f} * Radian};
    Sweep sweep{pos, pos, Length2D(0, 0), Real(0.6)};
    EXPECT_NE(Real{0}, sweep.GetAlpha0());
    sweep.ResetAlpha0();
    EXPECT_EQ(Real{0}, sweep.GetAlpha0());    
}

TEST(Sweep, GetPosition) {
    const auto pos0 = Position{Length2D{Real(-0.4) * Meter, Real(+2.34) * Meter}, Real{3.14f} * Radian};
    const auto pos1 = Position{Length2D{Real(+0.4) * Meter, Real(-2.34) * Meter}, -Real{3.14f} * Radian};
    Sweep sweep{pos0, pos1, Length2D(0, 0), Real(0.6)};
    EXPECT_EQ(pos0, GetPosition(sweep.pos0, sweep.pos1, 0));
    EXPECT_EQ(pos1, GetPosition(sweep.pos0, sweep.pos1, 1));
}

TEST(Sweep, Advance) {
    const auto pos0 = Position{Length2D{Real(-0.4) * Meter, Real(+2.34) * Meter}, Real{3.14f} * Radian};
    const auto pos1 = Position{Length2D{Real(+0.4) * Meter, Real(-2.34) * Meter}, -Real{3.14f} * Radian};
    
    Sweep sweep{pos0, pos1, Length2D(0, 0), 0};
    EXPECT_EQ(Real{0}, sweep.GetAlpha0());
    
    sweep.Advance0(0);
    EXPECT_EQ(Real{0}, sweep.GetAlpha0());
    EXPECT_EQ(pos0, sweep.pos0);
    EXPECT_EQ(pos1, sweep.pos1);
    
    sweep.Advance0(Real{1}/Real{2});
    EXPECT_EQ(Real{1}/Real{2}, sweep.GetAlpha0());
    EXPECT_EQ(pos1, sweep.pos1);
    EXPECT_EQ((Position{Length2D(0, 0), Angle{0}}), sweep.pos0);

    sweep.Advance0(0);
    EXPECT_EQ(Real{0}, sweep.GetAlpha0());
    EXPECT_EQ(pos0, sweep.pos0);
    EXPECT_EQ(pos1, sweep.pos1);
}

TEST(Sweep, GetAnglesNormalized)
{
    const auto sweep0 = Sweep{
        Position{Length2D(0, 0), Angle{0}},
        Position{Length2D(0, 0), Angle{0}}
    };
    EXPECT_EQ(GetAnglesNormalized(sweep0).pos0.angular, Angle{0});
    EXPECT_EQ(GetAnglesNormalized(sweep0).pos1.angular, Angle{0});

    const auto sweep1 = Sweep{
        Position{Length2D(0, 0), Angle{Real{90.0f} * Degree}},
        Position{Length2D(0, 0), Angle{Real{90.0f} * Degree}}
    };
    EXPECT_NEAR(double(Real{GetAnglesNormalized(sweep1).pos0.angular / Angle{Real(1) * Degree}}),
                double( 90), 0.03);
    EXPECT_NEAR(double(Real{GetAnglesNormalized(sweep1).pos1.angular / Angle{Real(1) * Degree}}),
                double( 90), 0.03);

    const auto sweep2 = Sweep{
        Position{Length2D(0, 0), Angle{Real{180.0f} * Degree}},
        Position{Length2D(0, 0), Angle{Real{180.0f} * Degree}}
    };
    EXPECT_NEAR(double(Real{GetAnglesNormalized(sweep2).pos0.angular / Angle{Real(1) * Degree}}),
                double(180), 0.03);
    EXPECT_NEAR(double(Real{GetAnglesNormalized(sweep2).pos1.angular / Angle{Real(1) * Degree}}),
                double(180), 0.03);

    const auto sweep3 = Sweep{
        Position{Length2D(0, 0), Angle{Real{270.0f} * Degree}},
        Position{Length2D(0, 0), Angle{Real{270.0f} * Degree}}
    };
    EXPECT_NEAR(double(Real{GetAnglesNormalized(sweep3).pos0.angular / Angle{Real(1) * Degree}}),
                double(270), 0.03);
    EXPECT_NEAR(double(Real{GetAnglesNormalized(sweep3).pos1.angular / Angle{Real(1) * Degree}}),
                       double(270), 0.03);

    const auto sweep4 = Sweep{
        Position{Length2D(0, 0), Angle{Real{361.0f} * Degree}},
        Position{Length2D(0, 0), Angle{Real{361.0f} * Degree}}
    };
    EXPECT_NEAR(double(Real{GetAnglesNormalized(sweep4).pos0.angular / Angle{Real(1) * Degree}}),
                double(1), 0.001);
    EXPECT_NEAR(double(Real{GetAnglesNormalized(sweep4).pos1.angular / Angle{Real(1) * Degree}}),
                double(1), 0.001);

    const auto sweep5 = Sweep{
        Position{Length2D(0, 0), Angle{Real{722.0f} * Degree}},
        Position{Length2D(0, 0), Angle{Real{722.0f} * Degree}}
    };
    EXPECT_NEAR(double(Real{GetAnglesNormalized(sweep5).pos0.angular / Angle{Real(1) * Degree}}),
                double(2), 0.002);
    EXPECT_NEAR(double(Real{GetAnglesNormalized(sweep5).pos1.angular / Angle{Real(1) * Degree}}),
                double(2), 0.002);

    const auto sweep6 = Sweep{
        Position{Length2D(0, 0), Angle{Real{726.0f} * Degree}},
        Position{Length2D(0, 0), Angle{Real{90.0f} * Degree}}
    };
    EXPECT_NEAR(double(Real{GetAnglesNormalized(sweep6).pos0.angular / Angle{Real(1) * Degree}}),
                double(6), 0.03);
    EXPECT_NEAR(double(Real{GetAnglesNormalized(sweep6).pos1.angular / Angle{Real(1) * Degree}}),
                double(-630), 0.03);
    
    const auto sweep7 = Sweep{
        Position{Length2D(0, 0), Angle{-Real{90.0f} * Degree}},
        Position{Length2D(0, 0), Angle{-Real{90.0f} * Degree}}
    };
    EXPECT_NEAR(double(Real{GetAnglesNormalized(sweep7).pos0.angular / Angle{Real(1) * Degree}}),
                double( -90), 0.03);
    EXPECT_NEAR(double(Real{GetAnglesNormalized(sweep7).pos1.angular / Angle{Real(1) * Degree}}),
                double( -90), 0.03);
}
