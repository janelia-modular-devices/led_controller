// ----------------------------------------------------------------------------
// Callbacks.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef CALLBACKS_H
#define CALLBACKS_H
#include "ArduinoJson.h"
#include "EventController.h"
#include "IndexedContainer.h"
#include "ModularServer.h"
#include "Constants.h"
#include "Controller.h"

#include "Streaming.h"

namespace callbacks
{
struct ChannelsPower
{
  uint32_t channels;
  uint8_t power;
};

struct PulseInfo
{
  EventController::EventIdPair event_id_pair;
  int channel_index;
};

void setChannelPowerCallback();

void setChannelOffCallback();

void setChannelsPowersCallback();

void setChannelsOffCallback();

void setAllChannelsPowerCallback();

void setAllChannelsOffCallback();

void getChannelsPowersCallback();

void getChannelCountCallback();

void addPwmPeriodOnDurationCallback();

void addPwmFrequencyDutyCycleCallback();

void stopAllPulsesCallback();

void startPwmPeriodOnDurationCallback();

void startPwmFrequencyDutyCycleCallback();

void stopPulseWaveCallback();

uint32_t arrayToChannels(ArduinoJson::JsonArray& channels_array);


// Standalone Callbacks
void setChannelPowerStandaloneCallback();

void setChannelOffStandaloneCallback();

void setAllChannelsPowerStandaloneCallback();

void pwmStandaloneCallback();

// EventController Callbacks
void removeIndexedChannelCallback(int index);

void setChannelsOnEventCallback(int index);

void setChannelsOffEventCallback(int index);

//Interactive Variable Update Callbacks

}
#endif
