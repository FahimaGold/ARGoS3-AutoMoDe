/**
  * @file <src/modules/AutoMoDeBehaviourRepulsion.cpp>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#include "AutoMoDeBehaviourRepulsion.h"


namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourRepulsion::AutoMoDeBehaviourRepulsion() {
		m_strLabel = "Repulsion";
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourRepulsion::AutoMoDeBehaviourRepulsion(AutoMoDeBehaviourRepulsion* pc_behaviour) {
		m_strLabel = pc_behaviour->GetLabel();
		m_bLocked = pc_behaviour->IsLocked();
		m_bOperational = pc_behaviour->IsOperational();
		m_unIndex = pc_behaviour->GetIndex();
		m_unIdentifier = pc_behaviour->GetIdentifier();
		m_mapParameters = pc_behaviour->GetParameters();
		Init();
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourRepulsion::~AutoMoDeBehaviourRepulsion() {}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourRepulsion* AutoMoDeBehaviourRepulsion::Clone() {
		return new AutoMoDeBehaviourRepulsion(this);
	}

	/****************************************/
	/****************************************/


	void AutoMoDeBehaviourRepulsion::ControlStep() {
		CVector2 sRabVector(0,CRadians::ZERO);
		CCI_EPuckRangeAndBearingSensor::SReceivedPacket cRabReading = m_pcRobotDAO->GetNeighborsCenterOfMass();

		if (cRabReading.Range > 0.0f) {
			sRabVector = CVector2(cRabReading.Range, cRabReading.Bearing);
		}

		if (sRabVector.Length() < 0.1) {
			sRabVector = CVector2(1.0, CRadians::ZERO);
		}

		m_pcRobotDAO->SetWheelsVelocity(ComputeWheelsVelocityFromVector(-sRabVector));

		m_bLocked = false;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourRepulsion::Init() {
		std::map<std::string, Real>::iterator it;

		// Repulsion parameter not needed anymore
		// = m_mapParameters.find("rep");
		// if (it != m_mapParameters.end()) {
		// 	m_unRepulsionParameter = it->second;
		// } else {
		// 	LOGERR << "[FATAL] Missing parameter for the following behaviour:" << m_strLabel << std::endl;
		// 	THROW_ARGOSEXCEPTION("Missing Parameter");
		// }

		// Success probability
		it = m_mapParameters.find("p");
		if (it != m_mapParameters.end()) {
			m_fSuccessProbabilityParameter = it->second;
		} else {
			LOGERR << "[FATAL] Missing probability parameter for the following behaviour:" << m_strLabel << std::endl;
			THROW_ARGOSEXCEPTION("Missing Parameter");
		}
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourRepulsion::Reset() {
		m_bOperational = false;
		ResumeStep();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourRepulsion::ResumeStep() {
		m_bOperational = true;
	}

	/****************************************/
	/****************************************/

	bool AutoMoDeBehaviourRepulsion::Succeeded() {
		return EvaluateBernoulliProbability(m_fSuccessProbabilityParameter);
	}

	/****************************************/
	/****************************************/

	bool AutoMoDeBehaviourRepulsion::Failed() {
		return ObstacleInFront();
	}
}
