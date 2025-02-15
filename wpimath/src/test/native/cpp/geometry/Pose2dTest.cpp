// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <cmath>

#include "frc/geometry/Pose2d.h"
#include "gtest/gtest.h"

using namespace frc;

TEST(Pose2dTest, TransformBy) {
  const Pose2d initial{1_m, 2_m, Rotation2d{45_deg}};
  const Transform2d transform{Translation2d{5_m, 0_m}, Rotation2d{5_deg}};

  const auto transformed = initial + transform;

  EXPECT_DOUBLE_EQ(1.0 + 5.0 / std::sqrt(2.0), transformed.X().value());
  EXPECT_DOUBLE_EQ(2.0 + 5.0 / std::sqrt(2.0), transformed.Y().value());
  EXPECT_DOUBLE_EQ(50.0, transformed.Rotation().Degrees().value());
}

TEST(Pose2dTest, RelativeTo) {
  const Pose2d initial{0_m, 0_m, Rotation2d{45_deg}};
  const Pose2d final{5_m, 5_m, Rotation2d{45.0_deg}};

  const auto finalRelativeToInitial = final.RelativeTo(initial);

  EXPECT_DOUBLE_EQ(5.0 * std::sqrt(2.0), finalRelativeToInitial.X().value());
  EXPECT_NEAR(0.0, finalRelativeToInitial.Y().value(), 1e-9);
  EXPECT_DOUBLE_EQ(0.0, finalRelativeToInitial.Rotation().Degrees().value());
}

TEST(Pose2dTest, Equality) {
  const Pose2d a{0_m, 5_m, Rotation2d{43_deg}};
  const Pose2d b{0_m, 5_m, Rotation2d{43_deg}};
  EXPECT_TRUE(a == b);
}

TEST(Pose2dTest, Inequality) {
  const Pose2d a{0_m, 5_m, Rotation2d{43_deg}};
  const Pose2d b{0_m, 5_ft, Rotation2d{43_deg}};
  EXPECT_TRUE(a != b);
}

TEST(Pose2dTest, Minus) {
  const Pose2d initial{0_m, 0_m, Rotation2d{45_deg}};
  const Pose2d final{5_m, 5_m, Rotation2d{45_deg}};

  const auto transform = final - initial;

  EXPECT_DOUBLE_EQ(5.0 * std::sqrt(2.0), transform.X().value());
  EXPECT_NEAR(0.0, transform.Y().value(), 1e-9);
  EXPECT_DOUBLE_EQ(0.0, transform.Rotation().Degrees().value());
}
