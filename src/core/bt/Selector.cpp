/*
 * @file <src/core/bt/Selector.cpp>
 *
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 *
 * @package ARGoS3-AutoMoDe-BT
 *
 * @license MIT License
 */

#include "Selector.h"

namespace argos {

  /****************************************/
  /****************************************/

	Selector::Selector() {
    m_strLabel = "Selector";
  }

  /****************************************/
	/****************************************/

  Selector::~Selector() {}

  /****************************************/
  /****************************************/


	Selector::Selector(Selector* pc_behaviour) {
	}

	/****************************************/
	/****************************************/

	Selector* Selector::Clone() {
		return new Selector(this);
	}

  /****************************************/
  /****************************************/

  const std::string Selector::GetDOTDescription() {
    return "Selector";
  }

	/****************************************/
  /****************************************/

  Node::ReturnState Selector::Tick() {
    return SUCCESS;
  }

  /****************************************/
  /****************************************/

  void Selector::AddCondition(AutoMoDeCondition* pc_condition) {
    m_vecConditions.push_back(pc_condition);
  }

  /****************************************/
  /****************************************/

  void Selector::AddAction(AutoMoDeBehaviour* pc_action) {
    m_vecActions.push_back(pc_action);
  }

}
