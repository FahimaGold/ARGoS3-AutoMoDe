/**
  * @file AutoMoDeRabBuffer.cpp
  */

#include "AutoMoDeRabBuffer.h"

namespace argos {

  /****************************************/
  /****************************************/

  AutoMoDeRabBuffer::AutoMoDeRabBuffer() {
    m_unCurrentTime = 0;
  }

  /****************************************/
  /****************************************/

  AutoMoDeRabBuffer::~AutoMoDeRabBuffer() {}

  /****************************************/
  /****************************************/

  void AutoMoDeRabBuffer::SetTimeLife(UInt32 un_max_time_to_live) {
    m_unMaxTimeToLive = un_max_time_to_live;

  }

  /****************************************/
  /****************************************/

  void AutoMoDeRabBuffer::Update() {
    m_unCurrentTime += 1;
    for (UInt32 i = 0; i < m_vecBufferElements.size(); i++) {
      if (m_vecBufferElements.at(i).second < (m_unCurrentTime - m_unMaxTimeToLive)) {
        m_vecBufferElements.erase(m_vecBufferElements.begin() + i);
      }
    }
  }

  /****************************************/
  /****************************************/

  void AutoMoDeRabBuffer::AddMessage(CCI_EPuckRangeAndBearingSensor::SReceivedPacket* c_packet, UInt32 un_timestamp) {
    m_vecBufferElements.push_back(std::make_pair(*c_packet, un_timestamp));
  }

  /****************************************/
	/****************************************/

  void AutoMoDeRabBuffer::AddMessage(CCI_EPuckRangeAndBearingSensor::SReceivedPacket* c_packet) {
    m_vecBufferElements.push_back(std::make_pair(*c_packet, m_unCurrentTime));
  }

  /****************************************/
	/****************************************/

  //std::vector<CCI_EPuckRangeAndBearingSensor::SReceivedPacket> AutoMoDeRabBuffer::GetMessages(UInt32 un_current_time, UInt32 un_offset);

  /****************************************/
  /****************************************/

  std::vector<CCI_EPuckRangeAndBearingSensor::SReceivedPacket*> AutoMoDeRabBuffer::GetMessages() {
    std::vector<CCI_EPuckRangeAndBearingSensor::SReceivedPacket*> vecRabMessages;
    std::vector<std::pair<CCI_EPuckRangeAndBearingSensor::SReceivedPacket, UInt32> >::iterator it;
    for (it = m_vecBufferElements.begin(); it != m_vecBufferElements.end(); it++) {
      vecRabMessages.push_back(&(*it).first);
    }
    return vecRabMessages;
  }

  /****************************************/
  /****************************************/

  void AutoMoDeRabBuffer::DisplayContent() {
    LOG << "--------------------------" << std::endl;
    for (UInt32 i = 0; i < m_vecBufferElements.size(); i++) {
      LOG << (m_vecBufferElements.at(i).first).Range << " " << (m_vecBufferElements.at(i).first).Data[0] << " " << m_vecBufferElements.at(i).second << std::endl;
    }
  }

  /****************************************/
  /****************************************/

  UInt32 AutoMoDeRabBuffer::GetSize() {
    return m_vecBufferElements.size();
  }
  
  /****************************************/
  /****************************************/

  void AutoMoDeRabBuffer::Reset() {
    m_vecBufferElements.clear();
    m_unCurrentTime = 0;
  }

}
