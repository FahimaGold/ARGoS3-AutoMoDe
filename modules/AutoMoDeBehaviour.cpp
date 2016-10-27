/*
 * File: AutoMoDeBehaviour.cpp
 *
 */

#include "AutoMoDeBehaviour.h"


namespace argos {

	/****************************************/
	/****************************************/

	const bool AutoMoDeBehaviour::IsLocked() {
		return m_bLocked;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviour::SetIndex(UInt8 un_index) {
		m_unIndex = un_index;
	}

	/****************************************/
	/****************************************/

	const UInt8 AutoMoDeBehaviour::GetIndex() {
		return m_unIndex;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviour::SetIdentifier(UInt8 un_id) {
		m_unIdentifier = un_id;
	}

	/****************************************/
	/****************************************/

	const UInt8 AutoMoDeBehaviour::GetIdentifier(){
		return m_unIdentifier;
	}

	/****************************************/
	/****************************************/

	const std::string AutoMoDeBehaviour::GetUrlDescription() {
		std::stringstream ss;
		ss << m_strLabel;
		if (!m_mapParameters.empty()) {
			std::map<std::string, Real>::iterator it;
			for (it = m_mapParameters.begin(); it != m_mapParameters.end(); it++) {
				ss << "\\n" << it->first << "=" << it->second ;
			}
		}
		return ss.str();
	}

	/****************************************/
	/****************************************/

	CVector2 AutoMoDeBehaviour::ComputeWheelsVelocityFromVector(CVector2 c_vector_to_follow) {
		Real fLeftVelocity = 0;
		Real fRightVelocity = 0;
		CRange<CRadians> cRightHemisphere(CRadians::PI, CRadians::TWO_PI);
		CRange<CRadians> cLeftHemisphere(CRadians::ZERO, CRadians::PI);
		CRadians cNormalizedVectorToFollow = c_vector_to_follow.Angle().UnsignedNormalize();
		
		// Compute relative wheel velocity
		if (c_vector_to_follow.GetX() != 0 || c_vector_to_follow.GetY() != 0) {
			if (cLeftHemisphere.WithinMinBoundExcludedMaxBoundExcluded(cNormalizedVectorToFollow)) {
				fRightVelocity = 1;
			} else {
				fRightVelocity = Max<Real>(-0.5f, Cos(cNormalizedVectorToFollow));
			}
			
			if (cRightHemisphere.WithinMinBoundExcludedMaxBoundExcluded(cNormalizedVectorToFollow)) {
				fLeftVelocity = 1;
			} else {
				fLeftVelocity = Max<Real>(-0.5f, Cos(cNormalizedVectorToFollow));
			}
		}
		
		// Transform relative velocity according to max velocity allowed 
		Real fVelocityFactor = m_pcRobotDAO->GetMaxVelocity() / Max<Real>(std::abs(fRightVelocity), std::abs(fLeftVelocity));
		CVector2 cWheelsVelocity = CVector2(fVelocityFactor * fLeftVelocity, fVelocityFactor * fRightVelocity);
		
		return cWheelsVelocity;
	}

	/****************************************/
	/****************************************/

	CVector2 AutoMoDeBehaviour::SumProximityReadings(CCI_EPuckProximitySensor::TReadings s_prox) {
		CVector2 cSum(0, 0);
		for (UInt8 i = 0; i < s_prox.size(); i++) {
			cSum += CVector2(s_prox[i].Value, s_prox[i].Angle);
		}
		return cSum;
	}

	/****************************************/
	/****************************************/

	CVector2 AutoMoDeBehaviour::ParseLight(CVector2 c_light) {
		LOG << "ParseLight: Todo" << std::endl;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviour::AddParameter(std::string str_identifier, Real f_value) {
		m_mapParameters.insert(std::pair<std::string, Real>(str_identifier, f_value));
	}

	/****************************************/
	/****************************************/

	const bool AutoMoDeBehaviour::IsOperational() {
		return m_bOperational;
	}

	/****************************************/
	/****************************************/

	const std::string AutoMoDeBehaviour::GetLabel() {
		return m_strLabel;
	}

	/****************************************/
	/****************************************/

	const std::map<std::string, Real> AutoMoDeBehaviour::GetParameters() {
		return m_mapParameters;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviour::SetRobotDAO(AutoMoDeRobotDAO* pc_robot_dao) {
		m_pcRobotDAO = pc_robot_dao;
	}

}
