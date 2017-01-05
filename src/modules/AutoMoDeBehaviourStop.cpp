/**
  * @file <src/modules/AutoMoDeBehaviourStop.cpp>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#include "AutoMoDeBehaviourStop.h"


namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourStop::AutoMoDeBehaviourStop() {
		m_strLabel = "Stop";
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourStop::AutoMoDeBehaviourStop(AutoMoDeBehaviourStop* pc_behaviour) {
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

	AutoMoDeBehaviourStop::~AutoMoDeBehaviourStop() {}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourStop* AutoMoDeBehaviourStop::Clone() {
		return new AutoMoDeBehaviourStop(this);
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourStop::ControlStep() {

		m_pcRobotDAO->SetRangeAndBearingMessageToSend(m_bBroadcastStateAndMessage);

		m_pcRobotDAO->SetWheelsVelocity(0,0);
		m_bLocked = false;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourStop::Init() {
		std::map<std::string, Real>::iterator itMes = m_mapParameters.find("brd");
		if (itMes != m_mapParameters.end()) {
			m_bBroadcastStateAndMessage = itMes->second;
		} else {
			LOGERR << "[FATAL] Missing parameter for the following behaviour:" << m_strLabel << std::endl;
			THROW_ARGOSEXCEPTION("Missing Parameter");
		}
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourStop::Reset() {
		m_bOperational = false;
		ResumeStep();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourStop::ResumeStep() {
		m_bOperational = true;
	}
}
