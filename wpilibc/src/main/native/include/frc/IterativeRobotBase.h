// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <units/time.h>

#include "frc/RobotBase.h"
#include "frc/Watchdog.h"

namespace frc {

/**
 * IterativeRobotBase implements a specific type of robot program framework,
 * extending the RobotBase class.
 *
 * The IterativeRobotBase class does not implement StartCompetition(), so it
 * should not be used by teams directly.
 *
 * This class provides the following functions which are called by the main
 * loop, StartCompetition(), at the appropriate times:
 *
 * RobotInit() -- provide for initialization at robot power-on
 *
 * Init() functions -- each of the following functions is called once when the
 * appropriate mode is entered:
 *
 * \li DisabledInit() -- called each and every time disabled is entered from
 *   another mode
 * \li AutonomousInit() -- called each and every time autonomous is entered from
 *   another mode
 * \li TeleopInit() -- called each and every time teleop is entered from another
 *   mode
 * \li TestInit() -- called each and every time test is entered from another
 *   mode
 *
 * Periodic() functions -- each of these functions is called on an interval:
 *
 * \li RobotPeriodic()
 * \li DisabledPeriodic()
 * \li AutonomousPeriodic()
 * \li TeleopPeriodic()
 * \li TestPeriodic()
 *
 * Exit() functions -- each of the following functions is called once when the
 * appropriate mode is exited:
 *
 * \li DisabledExit() -- called each and every time disabled is exited
 * \li AutonomousExit() -- called each and every time autonomous is exited
 * \li TeleopExit() -- called each and every time teleop is exited
 * \li TestExit() -- called each and every time test is exited
 */
class IterativeRobotBase : public RobotBase {
 public:
  /**
   * Robot-wide initialization code should go here.
   *
   * Users should override this method for default Robot-wide initialization
   * which will be called when the robot is first powered on. It will be called
   * exactly one time.
   *
   * Warning: the Driver Station "Robot Code" light and FMS "Robot Ready"
   * indicators will be off until RobotInit() exits. Code in RobotInit() that
   * waits for enable will cause the robot to never indicate that the code is
   * ready, causing the robot to be bypassed in a match.
   */
  virtual void RobotInit();

  /**
   * Robot-wide simulation initialization code should go here.
   *
   * Users should override this method for default Robot-wide simulation
   * related initialization which will be called when the robot is first
   * started. It will be called exactly one time after RobotInit is called
   * only when the robot is in simulation.
   */
  virtual void SimulationInit();

  /**
   * Initialization code for disabled mode should go here.
   *
   * Users should override this method for initialization code which will be
   * called each time
   * the robot enters disabled mode.
   */
  virtual void DisabledInit();

  /**
   * Initialization code for autonomous mode should go here.
   *
   * Users should override this method for initialization code which will be
   * called each time the robot enters autonomous mode.
   */
  virtual void AutonomousInit();

  /**
   * Initialization code for teleop mode should go here.
   *
   * Users should override this method for initialization code which will be
   * called each time the robot enters teleop mode.
   */
  virtual void TeleopInit();

  /**
   * Initialization code for test mode should go here.
   *
   * Users should override this method for initialization code which will be
   * called each time the robot enters test mode.
   */
  virtual void TestInit();

  /**
   * Periodic code for all modes should go here.
   *
   * This function is called each time a new packet is received from the driver
   * station.
   */
  virtual void RobotPeriodic();

  /**
   * Periodic simulation code should go here.
   *
   * This function is called in a simulated robot after user code executes.
   */
  virtual void SimulationPeriodic();

  /**
   * Periodic code for disabled mode should go here.
   *
   * Users should override this method for code which will be called each time a
   * new packet is received from the driver station and the robot is in disabled
   * mode.
   */
  virtual void DisabledPeriodic();

  /**
   * Periodic code for autonomous mode should go here.
   *
   * Users should override this method for code which will be called each time a
   * new packet is received from the driver station and the robot is in
   * autonomous mode.
   */
  virtual void AutonomousPeriodic();

  /**
   * Periodic code for teleop mode should go here.
   *
   * Users should override this method for code which will be called each time a
   * new packet is received from the driver station and the robot is in teleop
   * mode.
   */
  virtual void TeleopPeriodic();

  /**
   * Periodic code for test mode should go here.
   *
   * Users should override this method for code which will be called each time a
   * new packet is received from the driver station and the robot is in test
   * mode.
   */
  virtual void TestPeriodic();

  /**
   * Exit code for disabled mode should go here.
   *
   * Users should override this method for code which will be called each time
   * the robot exits disabled mode.
   */
  virtual void DisabledExit();

  /**
   * Exit code for autonomous mode should go here.
   *
   * Users should override this method for code which will be called each time
   * the robot exits autonomous mode.
   */
  virtual void AutonomousExit();

  /**
   * Exit code for teleop mode should go here.
   *
   * Users should override this method for code which will be called each time
   * the robot exits teleop mode.
   */
  virtual void TeleopExit();

  /**
   * Exit code for test mode should go here.
   *
   * Users should override this method for code which will be called each time
   * the robot exits test mode.
   */
  virtual void TestExit();

  /**
   * Enables or disables flushing NetworkTables every loop iteration.
   * By default, this is disabled.
   *
   * @param enabled True to enable, false to disable
   */
  void SetNetworkTablesFlushEnabled(bool enabled);

  /**
   * Gets time period between calls to Periodic() functions.
   */
  units::second_t GetPeriod() const;

  /**
   * Constructor for IterativeRobotBase.
   *
   * @param period Period.
   */
  explicit IterativeRobotBase(units::second_t period);

  ~IterativeRobotBase() override = default;

 protected:
  IterativeRobotBase(IterativeRobotBase&&) = default;
  IterativeRobotBase& operator=(IterativeRobotBase&&) = default;

  void LoopFunc();

 private:
  enum class Mode { kNone, kDisabled, kAutonomous, kTeleop, kTest };

  Mode m_lastMode = Mode::kNone;
  units::second_t m_period;
  Watchdog m_watchdog;
  bool m_ntFlushEnabled = false;

  void PrintLoopOverrunMessage();
};

}  // namespace frc
