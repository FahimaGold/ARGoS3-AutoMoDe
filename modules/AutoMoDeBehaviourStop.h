/*
 * File: AutoMoDeBehaviourStop.h
 *
 */

#ifndef AUTOMODE_BEHAVIOUR_STOP_H
#define AUTOMODE_BEHAVIOUR_STOP_H

#include "AutoMoDeBehaviour.h"

namespace argos {
	class AutoMoDeBehaviourStop: public AutoMoDeBehaviour {
		public:
			AutoMoDeBehaviourStop();
			AutoMoDeBehaviourStop(AutoMoDeBehaviourStop* pc_behaviour);
			virtual ~AutoMoDeBehaviourStop();

			virtual void ControlStep();
			virtual void Reset();
			virtual void ResumeStep();
			virtual void Init();


			virtual AutoMoDeBehaviourStop* Clone();
	};
}


#endif
