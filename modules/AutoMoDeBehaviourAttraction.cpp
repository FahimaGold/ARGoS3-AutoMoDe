/*
 * File: AutoMoDeBehaviourAttraction.cpp
 *
 */

#include "AutoMoDeBehaviourAttraction.h"


namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourAttraction::AutoMoDeBehaviourAttraction() {
		m_strLabel = "Attraction";
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourAttraction::AutoMoDeBehaviourAttraction(AutoMoDeBehaviourAttraction* pc_behaviour) {
		m_strLabel = pc_behaviour->GetLabel();
		m_bLocked = pc_behaviour->IsLocked();
		m_bOperational = pc_behaviour->IsOperational();
		m_unIndex = pc_behaviour->GetIndex();
		m_unIdentifier = pc_behaviour->GetIdentifier();
		m_mapParameters = pc_behaviour->GetParameters();
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourAttraction::~AutoMoDeBehaviourAttraction() {}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourAttraction* AutoMoDeBehaviourAttraction::Clone() {
		return new AutoMoDeBehaviourAttraction(*this);
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourAttraction::ControlStep() {
		CCI_EPuckRangeAndBearingSensor::TPackets sLastPackets = m_pcRobotDAO->GetRangeAndBearingMessages();
	 	CCI_EPuckRangeAndBearingSensor::TPackets::iterator it;
		CVector2 sRabVectorSum(0,CRadians::ZERO);
		CVector2 sProxVectorSum(0,CRadians::ZERO);
		CVector2 sResultVector(0,CRadians::ZERO);

		for (it = sLastPackets.begin(); it != sLastPackets.end(); it++) {
			if ((*it)->Data[0] != (UInt8) m_pcRobotDAO->GetRobotIdentifier()) {
				sRabVectorSum += CVector2(m_unAttractionParameter / ((*it)->Range + 1),(*it)->Bearing.SignedNormalize());
			}
		}

		sProxVectorSum = SumProximityReadings(m_pcRobotDAO->GetProximityInput());
		sResultVector = sRabVectorSum - 6*sProxVectorSum;

		if (sResultVector.Length() < 0.1) {
			sResultVector = CVector2(1, CRadians::ZERO);
		}
	
		m_pcRobotDAO->SetWheelsVelocity(ComputeWheelsVelocityFromVector(sResultVector));

		m_bLocked = false;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourAttraction::Init() {
		std::map<std::string, Real>::iterator it = m_mapParameters.find("att");
		if (it != m_mapParameters.end()) {
			m_unAttractionParameter = it->second;
		} else {
			LOGERR << "[FATAL] Missing parameter for the following behaviour:" << m_strLabel << std::endl;
			THROW_ARGOSEXCEPTION("Missing Parameter");
		}
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourAttraction::Reset() {
		m_bOperational = false;
		ResumeStep();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourAttraction::ResumeStep() {
		m_bOperational = true;
	}
}
