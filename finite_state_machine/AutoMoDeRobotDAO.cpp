/*
 * File: AutoMoDeRobotDAO.cpp
 *
 */


#include "AutoMoDeRobotDAO.h"

namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeRobotDAO::AutoMoDeRobotDAO() {
		m_pcRng = CRandom::CreateRNG("argos");
		m_pcRabMessageBuffer = new AutoMoDeRabBuffer();
		m_pcRabMessageBuffer->SetTimeLife(2);
		m_fMaxVelocity = 10;
		m_fLeftWheelVelocity = 0;
		m_fRightWheelVelocity = 0;
	}

	/****************************************/
	/****************************************/

	AutoMoDeRobotDAO::~AutoMoDeRobotDAO() {}

	/****************************************/
	/****************************************/

	CCI_EPuckProximitySensor::TReadings AutoMoDeRobotDAO::GetProximityInput() const {
		return m_sProximityInput;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeRobotDAO::SetProximityInput(CCI_EPuckProximitySensor::TReadings s_prox_input) {
		m_sProximityInput = s_prox_input;
	}

	/****************************************/
	/****************************************/

	CCI_EPuckLightSensor::TReadings AutoMoDeRobotDAO::GetLightInput() const{
		return m_sLightInput;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeRobotDAO::SetLightInput(CCI_EPuckLightSensor::TReadings s_light_input) {
		m_sLightInput = s_light_input;
	}

	/****************************************/
	/****************************************/

	CCI_EPuckGroundSensor::SReadings AutoMoDeRobotDAO::GetGroundInput() const{
		return m_sGroundInput;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeRobotDAO::SetGroundInput(CCI_EPuckGroundSensor::SReadings s_ground_input) {
		m_sGroundInput = s_ground_input;
	}

	/****************************************/
	/****************************************/

	const UInt8& AutoMoDeRobotDAO::GetNumberNeighbors() const {
		return m_unNumberNeighbors;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeRobotDAO::SetNumberNeighbors(const UInt8& un_number_neighbors){
		m_unNumberNeighbors = un_number_neighbors;
	}

	/****************************************/
	/****************************************/

	std::vector<CCI_EPuckRangeAndBearingSensor::SReceivedPacket*> AutoMoDeRobotDAO::GetRangeAndBearingMessages() const {
		return m_pcRabMessageBuffer->GetMessages();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeRobotDAO::SetRangeAndBearingMessages(CCI_EPuckRangeAndBearingSensor::TPackets s_packets) {
		std::map<UInt32, CCI_EPuckRangeAndBearingSensor::SReceivedPacket*> mapRemainingMessages;
		std::map<UInt32, CCI_EPuckRangeAndBearingSensor::SReceivedPacket*>::iterator mapIt;
		CCI_EPuckRangeAndBearingSensor::TPackets::iterator it;
		m_unNumberNeighbors = 0;
		for (it = s_packets.begin(); it < s_packets.end(); ++it) {
			if ((*it)->Data[0] != m_unRobotIdentifier) {
				mapRemainingMessages[(*it)->Data[0]] = (*it);
			}
		}
		for (mapIt = mapRemainingMessages.begin(); mapIt != mapRemainingMessages.end(); ++mapIt) {
			m_pcRabMessageBuffer->AddMessage((*mapIt).second);
			m_unNumberNeighbors += 1;
		}
		m_pcRabMessageBuffer->Update();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeRobotDAO::SetWheelsVelocity(const Real& un_left_velocity, const Real& un_right_velocity) {
		m_fLeftWheelVelocity = un_left_velocity;
		m_fRightWheelVelocity = un_right_velocity;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeRobotDAO::SetWheelsVelocity(const CVector2& c_velocity_vector) {
		m_fLeftWheelVelocity = c_velocity_vector.GetX();
		m_fRightWheelVelocity = c_velocity_vector.GetY();
	}

	/****************************************/
	/****************************************/

	const Real& AutoMoDeRobotDAO::GetRightWheelVelocity() const {
		return m_fRightWheelVelocity;
	}

	/****************************************/
	/****************************************/

	const Real& AutoMoDeRobotDAO::GetLeftWheelVelocity() const {
		return m_fLeftWheelVelocity;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeRobotDAO::Reset() {
		m_fLeftWheelVelocity = 0;
		m_fRightWheelVelocity = 0;
		m_pcRabMessageBuffer->Reset();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeRobotDAO::SetRobotIdentifier(const UInt32& un_robot_id) {
		m_unRobotIdentifier = un_robot_id;
	}

	/****************************************/
	/****************************************/

	const UInt32& AutoMoDeRobotDAO::GetRobotIdentifier() const{
		return m_unRobotIdentifier;
	}

	/****************************************/
	/****************************************/

	CRandom::CRNG* AutoMoDeRobotDAO::GetRandomNumberGenerator() const {
		return m_pcRng;
	}

	/****************************************/
	/****************************************/

	const Real& AutoMoDeRobotDAO::GetMaxVelocity() const{
		return m_fMaxVelocity;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeRobotDAO::DisplayRabBufferContent() {
		//LOG << " Epuck " << m_unRobotIdentifier << std::endl;
		//m_pcRabMessageBuffer->DisplayContent();
	}
}
