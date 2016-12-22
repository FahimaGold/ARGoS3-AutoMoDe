/**
 * @file AutoMoDeRobotDAO.h
 *
 * @brief This class represents the status of the robot.
 * It contains the input variables (the sensor inputs) and
 * the output variables (the values for the wheel actuators),
 * as well as the setters and getters to access them.
 *
 * Only one object of this class should be instanciated, and
 * is to be used as a brigde between the AutoMoDeController and
 * the AutoMoDeFiniteStateMachine classes. In AutoMoDeController,
 * the variables of the object shall be updated at each time step.
 * The different modules of the  AutoMoDeFiniteStateMachine will
 * then use the input variables and update the output variables
 * accordingly.
 */


#ifndef AUTOMODE_ROBOT_DAO_H
#define AUTOMODE_ROBOT_DAO_H

#include <vector>
#include <argos3/core/utility/math/rng.h>
#include <argos3/core/utility/math/vector2.h>
#include <argos3/core/utility/logging/argos_log.h>
#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_wheels_actuator.h>
#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_range_and_bearing_sensor.h>
#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_range_and_bearing_actuator.h>
#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_rgb_leds_actuator.h>
#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_proximity_sensor.h>
#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_light_sensor.h>
#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_ground_sensor.h>
#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_omnidirectional_camera_sensor.h>

#include "AutoMoDeRabBuffer.h"

namespace argos {
	class AutoMoDeRobotDAO {
		public:
			/*
			 *  Class constructor.
       */
			AutoMoDeRobotDAO();

			/*
			 * Class destructor.
       */
			virtual ~AutoMoDeRobotDAO();

			/*
			 * Getter for the proximity input.
			 */
			CCI_EPuckProximitySensor::TReadings GetProximityInput() const;

			/*
			 * Setter for the proximity input.
			 */
			void SetProximityInput(CCI_EPuckProximitySensor::TReadings s_prox_input);

			/*
			 * Getter for the light input.
			 */
			CCI_EPuckLightSensor::TReadings GetLightInput() const;

			/*
			 * Setter for the light input.
			 */
			void SetLightInput(CCI_EPuckLightSensor::TReadings s_light_input);

			/*
			 * Getter for the ground input.
			 */
			CCI_EPuckGroundSensor::SReadings GetGroundInput() const;

			/*
			 * Setter for the ground input.
			 */
			void SetGroundInput(CCI_EPuckGroundSensor::SReadings s_ground_input);

			/*
			 * Getter for the number of surrounding robots.
			 */
			const UInt8& GetNumberNeighbors() const;

			/*
			 * Setter for the number of surrounding robots.
			 */
			void SetNumberNeighbors(const UInt8& un_number_neighbors);

			/*
			 * Getter for the range-and-bearing input.
			 */
			std::vector<CCI_EPuckRangeAndBearingSensor::SReceivedPacket*> GetRangeAndBearingMessages() ;

			/*
			 * Setter for the range-and-bearing input.
			 */
			void SetRangeAndBearingMessages(CCI_EPuckRangeAndBearingSensor::TPackets s_packets);

			/*
			 * Setter for the wheels velocity.
			 */
			void SetWheelsVelocity(const Real& un_left_velocity, const Real& un_right_velocity);

			/*
			 * Setter for the wheels velocity.
			 */
			void SetWheelsVelocity(const CVector2& c_velocity_vector);

			/*
			 * Getter for the right wheel velocity.
			 */
			const Real& GetRightWheelVelocity() const;

			/*
			 * Getter for the left wheel velocity.
			 */
			const Real& GetLeftWheelVelocity() const;

			/*
			 * Setter for the robot idientifier.
			 */
			void SetRobotIdentifier(const UInt32& un_robot_id);

			/*
			 * Getter for the robot identifier.
			 */
			const UInt32& GetRobotIdentifier() const;

			/*
			 * Reset the output variables and clears range-and-bearing message buffer.
			 */
			void Reset();

			/*
			 * Getter for the maximal wheels velocity.
			 */
			const Real& GetMaxVelocity() const;

			/*
			 * Getter for the random number generetor.
			 */
			CRandom::CRNG* GetRandomNumberGenerator() const;

		private:
			/*
			 * The proximity sensors input.
			 */
			CCI_EPuckProximitySensor::TReadings m_sProximityInput;

			/*
			 * The light sensors input.
			 */
			CCI_EPuckLightSensor::TReadings m_sLightInput;

			/*
			 * The ground sensors input.
			 */
			CCI_EPuckGroundSensor::SReadings m_sGroundInput;

			/*
			 * The number of surrounding robots.
			 */
			UInt8 m_unNumberNeighbors;

			/*
			 * The left wheel velocity (output variable).
			 */
			Real m_fLeftWheelVelocity;

			/*
			 * The right wheel velocity (output variable).
			 */
			Real m_fRightWheelVelocity;

			/*
			 * The maximal wheels velocity.
			 */
			Real m_fMaxVelocity;

			/*
			 * The robot identifier.
			 */
			UInt32 m_unRobotIdentifier;

			/*
			 * Pointer to the random number generator.
			 */
			CRandom::CRNG* m_pcRng;

			/*
			 * Pointer to the range-and-bearing messages buffer.
			 */
			AutoMoDeRabBuffer m_pcRabMessageBuffer;
	};
}


#endif
