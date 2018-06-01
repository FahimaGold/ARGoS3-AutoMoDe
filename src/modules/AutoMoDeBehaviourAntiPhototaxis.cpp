/**
  * @file <src/modules/AutoMoDeBehaviourAntiPhototaxis.cpp>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#include "AutoMoDeBehaviourAntiPhototaxis.h"


namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourAntiPhototaxis::AutoMoDeBehaviourAntiPhototaxis() {
		m_strLabel = "Anti-Phototaxis";
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourAntiPhototaxis::AutoMoDeBehaviourAntiPhototaxis(AutoMoDeBehaviourAntiPhototaxis* pc_behaviour) {
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

	AutoMoDeBehaviourAntiPhototaxis::~AutoMoDeBehaviourAntiPhototaxis() {}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourAntiPhototaxis* AutoMoDeBehaviourAntiPhototaxis::Clone() {
		return new AutoMoDeBehaviourAntiPhototaxis(this);
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourAntiPhototaxis::ControlStep() {
		CVector2 sLightVector(0,CRadians::ZERO);
		CCI_EPuckLightSensor::SReading cLightReading = m_pcRobotDAO->GetLightReading();

		sLightVector = CVector2(cLightReading.Value, cLightReading.Angle);

	// LOG << cLightReading.Value << " " << cLightReading.Angle << std::endl;
	// LOG << sLightVector << std::endl;

		if (sLightVector.Length() < 0.1) {
			sLightVector = CVector2(1.0, CRadians::ZERO);
		}

		m_pcRobotDAO->SetWheelsVelocity(ComputeWheelsVelocityFromVector(-sLightVector));

		m_bLocked = false;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourAntiPhototaxis::Init() {}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourAntiPhototaxis::Reset() {
		m_bOperational = false;
		ResumeStep();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourAntiPhototaxis::ResumeStep() {
		m_bOperational = true;
	}

	/****************************************/
	/****************************************/

	bool AutoMoDeBehaviourAntiPhototaxis::Succeeded() {
		return EvaluateBernoulliProbability(m_fSuccessProbabilityParameter);
	}

	/****************************************/
	/****************************************/

	bool AutoMoDeBehaviourAntiPhototaxis::Failed() {
		return (ObstacleInFront() || !LightPerceived());
	}
}
