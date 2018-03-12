/*
 * @file <src/core/AutoMoDeController.cpp>
 *
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 *
 * @package ARGoS3-AutoMoDe
 *
 * @license MIT License
 */

#include "AutoMoDeController.h"

namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeController::AutoMoDeController() {
		m_pcRobotState = new AutoMoDeRobotDAO();
		m_unTimeStep = 0;
		m_strFsmConfiguration = "";
		m_bMaintainHistory = false;
		m_bPrintReadableFsm = false;
		m_strHistoryFolder = "./";
		m_bFiniteStateMachineGiven = false;
	}

	/****************************************/
	/****************************************/

	AutoMoDeController::~AutoMoDeController() {
		delete m_pcRobotState;
		delete m_pcFsmBuilder;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeController::Init(TConfigurationNode& t_node) {
		// Parsing parameters
		try {
			GetNodeAttributeOrDefault(t_node, "fsm-config", m_strFsmConfiguration, m_strFsmConfiguration);
			GetNodeAttributeOrDefault(t_node, "history", m_bMaintainHistory, m_bMaintainHistory);
			GetNodeAttributeOrDefault(t_node, "hist-folder", m_strHistoryFolder, m_strHistoryFolder);
			GetNodeAttributeOrDefault(t_node, "readable", m_bPrintReadableFsm, m_bPrintReadableFsm);
		} catch (CARGoSException& ex) {
			THROW_ARGOSEXCEPTION_NESTED("Error parsing <params>", ex);
		}

		m_unRobotID = atoi(GetId().substr(5, 6).c_str());
		m_pcRobotState->SetRobotIdentifier(m_unRobotID);

		/*
		 * If a FSM configuration is given as parameter of the experiment file, create a FSM from it
		 */
		if (m_strFsmConfiguration.compare("") != 0 && !m_bFiniteStateMachineGiven) {
			m_pcFsmBuilder = new AutoMoDeFsmBuilder();
			SetFiniteStateMachine(m_pcFsmBuilder->BuildFiniteStateMachine(m_strFsmConfiguration));
			if (m_bMaintainHistory) {
				m_pcFiniteStateMachine->SetHistoryFolder(m_strHistoryFolder);
				m_pcFiniteStateMachine->MaintainHistory();
			}
			if (m_bPrintReadableFsm) {
				std::cout << "Finite State Machine description: " << std::endl;
				std::cout << m_pcFiniteStateMachine->GetReadableFormat() << std::endl;
			}
		} else {
			LOGERR << "Warning: No finite state machine configuration found in .argos" << std::endl;
		}

		/*
		 *  Initializing default sensors and actuators
		 */
		try{
			 m_pcProximitySensor = GetSensor<CCI_EPuckProximitySensor>("epuck_proximity");
			 m_pcLightSensor = GetSensor<CCI_EPuckLightSensor>("epuck_light");
			 m_pcGroundSensor = GetSensor<CCI_EPuckGroundSensor>("epuck_ground");
			 m_pcCameraSensor = GetSensor<CCI_EPuckOmnidirectionalCameraSensor>("epuck_omnidirectional_camera");
		} catch (CARGoSException ex) {
			LOGERR<<"Error while initializing a Sensor!\n";
		}

		try{
			m_pcWheelsActuator = GetActuator<CCI_EPuckWheelsActuator>("epuck_wheels");
			m_pcLEDsActuator = GetActuator<CCI_EPuckRGBLEDsActuator>("epuck_rgb_leds");
		} catch (CARGoSException ex) {
			LOGERR<<"Error while initializing an Actuator!\n";
		}

	}


	/****************************************/
	/****************************************/

	void AutoMoDeController::ControlStep() {
		/*
		 * 1. Update RobotDAO
		 */
		if(m_pcRabSensor != NULL){
			const CCI_EPuckRangeAndBearingSensor::TPackets& packets = m_pcRabSensor->GetPackets();
			//m_pcRobotState->SetNumberNeighbors(packets.size());
			m_pcRobotState->SetRangeAndBearingMessages(packets);
		}
		if (m_pcGroundSensor != NULL) {
			const CCI_EPuckGroundSensor::SReadings& readings = m_pcGroundSensor->GetReadings();
			m_pcRobotState->SetGroundInput(readings);
		}
		if (m_pcLightSensor != NULL) {
			const CCI_EPuckLightSensor::TReadings& readings = m_pcLightSensor->GetReadings();
			m_pcRobotState->SetLightInput(readings);
		}
		if (m_pcProximitySensor != NULL) {
			const CCI_EPuckProximitySensor::TReadings& readings = m_pcProximitySensor->GetReadings();
			m_pcRobotState->SetProximityInput(readings);
		}

		/*
		 * 2. Execute step of FSM
		 */
		m_pcFiniteStateMachine->ControlStep();

		/*
		 * 3. Update Actuators
		 */
		if (m_pcWheelsActuator != NULL) {
			m_pcWheelsActuator->SetLinearVelocity(m_pcRobotState->GetLeftWheelVelocity(),m_pcRobotState->GetRightWheelVelocity());
		}

		/*
		 * 4. Update variables and sensors
		 */
		if (m_pcRabSensor != NULL) {
			m_pcRabSensor->ClearPackets();
		}
		m_unTimeStep++;

	}

	/****************************************/
	/****************************************/

	void AutoMoDeController::Destroy() {}

	/****************************************/
	/****************************************/

	void AutoMoDeController::Reset() {
		m_pcFiniteStateMachine->Reset();
		m_pcRobotState->Reset();
		InitializeActuation();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeController::SetFiniteStateMachine(AutoMoDeFiniteStateMachine* pc_finite_state_machine) {
		m_pcFiniteStateMachine = pc_finite_state_machine;
		m_pcFiniteStateMachine->SetRobotDAO(m_pcRobotState);
		m_pcFiniteStateMachine->Init();
		m_bFiniteStateMachineGiven = true;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeController::InitializeActuation() {
		if (m_pcRabActuator != NULL) {
			UInt8 data[4];
			data[0] = m_unRobotID;
			data[1] = 0;
			data[2] = 0;
			data[3] = 0;
			m_pcRabActuator->SetData(data);
		}
	}

	/****************************************/
	/****************************************/

	void AutoMoDeController::InitializeHardwareModules() {
		UInt32 unIndexRabSensor = m_pcFiniteStateMachine->GetIndexRabSensor();
		switch(unIndexRabSensor) {
			case 0:
				LOG << "RabSensor -> 1" << std::endl;
				m_pcRabSensor	= GetSensor<CCI_EPuckRangeAndBearingSensor>("epuck_range_and_bearing_salman_sen1");
				break;
			case 1:
				LOG << "RabSensor -> 2" << std::endl;
				m_pcRabSensor	= GetSensor<CCI_EPuckRangeAndBearingSensor>("epuck_range_and_bearing_salman_sen2");
				break;
			case 2:
				LOG << "RabSensor -> 3" << std::endl;
				m_pcRabSensor	= GetSensor<CCI_EPuckRangeAndBearingSensor>("epuck_range_and_bearing_salman_sen3");
				break;
			case 3:
				LOG << "RabSensor -> 4" << std::endl;
				m_pcRabSensor	= GetSensor<CCI_EPuckRangeAndBearingSensor>("epuck_range_and_bearing_salman_sen4");
				break;
			case 4:
				LOG << "RabSensor -> 5" << std::endl;
				m_pcRabSensor	= GetSensor<CCI_EPuckRangeAndBearingSensor>("epuck_range_and_bearing_salman_sen5");
				break;
			case 5:
				LOG << "RabSensor -> 6" << std::endl;
				m_pcRabSensor	= GetSensor<CCI_EPuckRangeAndBearingSensor>("epuck_range_and_bearing_salman_sen6");
				break;

		}

		UInt32 unIndexRabActuator = m_pcFiniteStateMachine->GetIndexRabActuator();
		switch(unIndexRabActuator) {
			case 0:
				LOG << "RabAct -> 1" << std::endl;
				m_pcRabActuator = GetActuator<CCI_EPuckRangeAndBearingActuator>("epuck_range_and_bearing_salman_act1");
				break;
			case 1:
				LOG << "RabAct -> 2" << std::endl;
				m_pcRabActuator = GetActuator<CCI_EPuckRangeAndBearingActuator>("epuck_range_and_bearing_salman_act2");
				break;
		}

		InitializeActuation();
	}


	REGISTER_CONTROLLER(AutoMoDeController, "automode_controller");
}
