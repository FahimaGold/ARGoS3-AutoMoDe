/*
 * File: AutoMoDeConditionBlackFloor.cpp
 *
 */

 #include "AutoMoDeConditionBlackFloor.h"

 namespace argos {

	AutoMoDeConditionBlackFloor::AutoMoDeConditionBlackFloor() {
		m_strLabel = "BlackFloor";
	}

	AutoMoDeConditionBlackFloor::~AutoMoDeConditionBlackFloor() {}

	AutoMoDeConditionBlackFloor::AutoMoDeConditionBlackFloor(AutoMoDeConditionBlackFloor* pc_condition) {
		m_strLabel = pc_condition->GetLabel();
		m_unIndex = pc_condition->GetIndex();
		m_unIdentifier = pc_condition->GetIndex();
		m_unFromBehaviourIndex = pc_condition->GetOrigin();
		m_unToBehaviourIndex = pc_condition->GetExtremity();
		m_mapParameters = pc_condition->GetParameters();
        Init();
	}

    void AutoMoDeConditionBlackFloor::Init() {
        m_fGroundThreshold = 0; //TODO : definir le paramètre
        if (m_mapParameters.find("p") != m_mapParameters.end()) {
			m_fProbability = m_mapParameters.find("p")->second;
		} else {
			THROW_ARGOSEXCEPTION("Missing Parameter: black floor");
		}
     }

	AutoMoDeConditionBlackFloor* AutoMoDeConditionBlackFloor::Clone() {
		return new AutoMoDeConditionBlackFloor(*this);
	}

	bool AutoMoDeConditionBlackFloor::Verify() {
        CCI_EPuckGroundSensor::SReadings readings = m_pcRobotDAO->GetGroundInput();

       if (readings.Left <= m_fGroundThreshold || readings.Center <= m_fGroundThreshold || readings.Right <= m_fGroundThreshold) {
            return EvaluateBernoulliProbability(m_fProbability);
        }
        else {
            return false;
        }
	}

	void AutoMoDeConditionBlackFloor::Reset() {

	}

 }
