// ----------------------------------------------------------------------------
// Callbacks.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Callbacks.h"


namespace callbacks
{
// Callbacks must be non-blocking (avoid 'delay')
//
// modular_server.getParameterValue must be cast to either:
// const char *
// long
// double
// bool
// ArduinoJson::JsonArray &
// ArduinoJson::JsonObject &
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server.getSavedVariableValue type must match the saved variable default type
// modular_server.setSavedVariableValue type must match the saved variable default type

ModularDevice::ModularServer & modular_server = controller.getModularServer();

IndexedContainer<ChannelsPower,constants::INDEXED_CHANNELS_POWER_COUNT_MAX> indexed_channels_power;
IndexedContainer<PulseInfo,constants::INDEXED_PULSES_COUNT_MAX> indexed_pulses;

void setChannelPowerCallback()
{
  long channel = modular_server.getParameterValue(constants::channel_parameter_name);
  long power = modular_server.getParameterValue(constants::power_parameter_name);
  controller.setChannelPower(channel,power);
}

void setChannelOffCallback()
{
  long channel = modular_server.getParameterValue(constants::channel_parameter_name);
  controller.setChannelOff(channel);
}

void setChannelsPowersCallback()
{
  ArduinoJson::JsonArray & powers = modular_server.getParameterValue(constants::powers_parameter_name);
  int channel = 0;
  for (ArduinoJson::JsonArray::iterator it=powers.begin(); it!=powers.end(); ++it)
  {
    long power = *it;
    controller.setChannelPower(channel++,power);
  }
}

void setChannelsOffCallback()
{
  ArduinoJson::JsonArray & channels = modular_server.getParameterValue(constants::channels_parameter_name);
  for (ArduinoJson::JsonArray::iterator it=channels.begin(); it!=channels.end(); ++it)
  {
    long channel = *it;
    controller.setChannelOff(channel);
  }
}

void setAllChannelsPowerCallback()
{
  long power = modular_server.getParameterValue(constants::power_parameter_name);
  for (int channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    controller.setChannelPower(channel,power);
  }
}

void setAllChannelsOffCallback()
{
  for (int channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    controller.setChannelOff(channel);
  }
}

void getChannelsPowersCallback()
{
  modular_server.writeResultKeyToResponse();
  modular_server.beginResponseArray();
  for (int channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    modular_server.writeToResponse(controller.getChannelPower(channel));
  }
  modular_server.endResponseArray();
}

void getChannelCountCallback()
{
  modular_server.writeResultToResponse((int)constants::CHANNEL_COUNT);
}

void addPwmPeriodOnDurationCallback()
{
  if (indexed_channels_power.full())
  {
    return;
  }
  ArduinoJson::JsonArray & channels_array = modular_server.getParameterValue(constants::channels_parameter_name);
  ChannelsPower channels_power;
  channels_power.channels = arrayToChannels(channels_array);
  long power = modular_server.getParameterValue(constants::power_parameter_name);
  channels_power.power = power;
  int index = indexed_channels_power.add(channels_power);
  long period = modular_server.getParameterValue(constants::period_parameter_name);
  long on_duration = modular_server.getParameterValue(constants::on_duration_parameter_name);
  long count = modular_server.getParameterValue(constants::count_parameter_name);
  EventController::event_controller.addPwmUsingDelayPeriodOnDuration(setChannelsOnEventCallback,
                                                                     setChannelsOffEventCallback,
                                                                     constants::delay,
                                                                     period,
                                                                     on_duration,
                                                                     count,
                                                                     index,
                                                                     NULL,
                                                                     removeIndexedChannelCallback);
}

void addPwmFrequencyDutyCycleCallback()
{
  if (indexed_channels_power.full())
  {
    return;
  }
  ArduinoJson::JsonArray & channels_array = modular_server.getParameterValue(constants::channels_parameter_name);
  ChannelsPower channels_power;
  channels_power.channels = arrayToChannels(channels_array);
  long power = modular_server.getParameterValue(constants::power_parameter_name);
  channels_power.power = power;
  int index = indexed_channels_power.add(channels_power);
  double frequency = modular_server.getParameterValue(constants::frequency_parameter_name);
  long duty_cycle = modular_server.getParameterValue(constants::duty_cycle_parameter_name);
  long pwm_duration = modular_server.getParameterValue(constants::pwm_duration_parameter_name);
  uint32_t period = 1000/frequency;
  period = max(period,2);
  uint32_t on_duration = (period*duty_cycle)/100;
  on_duration = constrain(on_duration,1,period-1);
  uint32_t count = pwm_duration/period;
  EventController::event_controller.addPwmUsingDelayPeriodOnDuration(setChannelsOnEventCallback,
                                                                     setChannelsOffEventCallback,
                                                                     constants::delay,
                                                                     period,
                                                                     on_duration,
                                                                     count,
                                                                     index,
                                                                     NULL,
                                                                     removeIndexedChannelCallback);
}

void stopAllPulsesCallback()
{
  EventController::event_controller.removeAllEvents();
  for (int i=0; i<indexed_channels_power.max_size(); ++i)
  {
    if (indexed_channels_power.indexHasValue(i))
    {
      setChannelsOffEventCallback(i);
    }
  }
  indexed_channels_power.clear();
}

void startPwmPeriodOnDurationCallback()
{
  if (indexed_channels_power.full() || indexed_pulses.full())
  {
    modular_server.writeResultToResponse(-1);
    return;
  }
  ArduinoJson::JsonArray & channels_array = modular_server.getParameterValue(constants::channels_parameter_name);
  ChannelsPower channels_power;
  channels_power.channels = arrayToChannels(channels_array);
  long power = modular_server.getParameterValue(constants::power_parameter_name);
  channels_power.power = power;
  int index = indexed_channels_power.add(channels_power);
  long period = modular_server.getParameterValue(constants::period_parameter_name);
  long on_duration = modular_server.getParameterValue(constants::on_duration_parameter_name);
  PulseInfo pulse_info;
  EventController::EventIdPair event_id_pair =
    EventController::event_controller.addInfinitePwmUsingDelayPeriodOnDuration(setChannelsOnEventCallback,
                                                                               setChannelsOffEventCallback,
                                                                               constants::delay,
                                                                               period,
                                                                               on_duration,
                                                                               index);
  pulse_info.event_id_pair = event_id_pair;
  pulse_info.channel_index = index;
  int pulse_wave_index = indexed_pulses.add(pulse_info);
  modular_server.writeResultToResponse(pulse_wave_index);
}

void startPwmFrequencyDutyCycleCallback()
{
  if (indexed_channels_power.full() || indexed_pulses.full())
  {
    modular_server.writeResultToResponse(-1);
    return;
  }
  ArduinoJson::JsonArray & channels_array = modular_server.getParameterValue(constants::channels_parameter_name);
  ChannelsPower channels_power;
  channels_power.channels = arrayToChannels(channels_array);
  long power = modular_server.getParameterValue(constants::power_parameter_name);
  channels_power.power = power;
  int index = indexed_channels_power.add(channels_power);
  double frequency = modular_server.getParameterValue(constants::frequency_parameter_name);
  long duty_cycle = modular_server.getParameterValue(constants::duty_cycle_parameter_name);
  long pwm_duration = modular_server.getParameterValue(constants::pwm_duration_parameter_name);
  uint32_t period = 1000/frequency;
  period = max(period,2);
  uint32_t on_duration = (period*duty_cycle)/100;
  on_duration = constrain(on_duration,1,period-1);
  PulseInfo pulse_info;
  EventController::EventIdPair event_id_pair =
    EventController::event_controller.addInfinitePwmUsingDelayPeriodOnDuration(setChannelsOnEventCallback,
                                                                               setChannelsOffEventCallback,
                                                                               constants::delay,
                                                                               period,
                                                                               on_duration,
                                                                               index);
  pulse_info.event_id_pair = event_id_pair;
  pulse_info.channel_index = index;
  int pulse_wave_index = indexed_pulses.add(pulse_info);
  modular_server.writeResultToResponse(pulse_wave_index);
}

void stopPulseWaveCallback()
{
  long pulse_wave_index = modular_server.getParameterValue(constants::pulse_wave_index_parameter_name);
  PulseInfo & pulse_info = indexed_pulses[pulse_wave_index];
  EventController::event_controller.removeEventPair(pulse_info.event_id_pair);
  setChannelsOffEventCallback(pulse_info.channel_index);
  indexed_channels_power.remove(pulse_info.channel_index);
  indexed_pulses.remove(pulse_wave_index);
}

uint32_t arrayToChannels(ArduinoJson::JsonArray & channels_array)
{
  uint32_t channels = 0;
  uint32_t bit = 1;
  for (ArduinoJson::JsonArray::iterator channels_it=channels_array.begin();
       channels_it != channels_array.end();
       ++channels_it)
  {
    long channel = *channels_it;
    channels |= bit << channel;
  }
  return channels;
}

void setChannelPowerStandaloneCallback()
{
  uint8_t channel = controller.getChannelIntVar();
  uint8_t power = controller.getPowerIntVar();
  controller.setChannelPower(channel,power);
}

void setChannelOffStandaloneCallback()
{
  uint8_t channel = controller.getChannelIntVar();
  controller.setChannelOff(channel);
}

void setAllChannelsPowerStandaloneCallback()
{
  uint8_t power = controller.getPowerIntVar();
  for (int channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    controller.setChannelPower(channel,power);
  }
}

void pwmStandaloneCallback()
{
  uint8_t channel = controller.getChnlIntVar();
  uint32_t channels = 1;
  ChannelsPower channels_power;
  channels_power.channels = channels << channel;
  long period = controller.getPeriodIntVar();
  long on_duration = controller.getOnIntVar();
  long count = controller.getCountIntVar();
  channels_power.power = controller.getPwrIntVar();
  int index = indexed_channels_power.add(channels_power);

  EventController::event_controller.addPwmUsingDelayPeriodOnDuration(setChannelsOnEventCallback,
                                                                     setChannelsOffEventCallback,
                                                                     constants::delay,
                                                                     period,
                                                                     on_duration,
                                                                     count,
                                                                     index,
                                                                     NULL,
                                                                     removeIndexedChannelCallback);
}

void setPwmDefaultsStandaloneCallback()
{
  long period = controller.getPeriodIntVar();
  modular_server.setSavedVariableValue(constants::period_dsp_lbl_str,period);
  long on_duration = controller.getOnIntVar();
  modular_server.setSavedVariableValue(constants::on_dsp_lbl_str,on_duration);
  long count = controller.getCountIntVar();
  modular_server.setSavedVariableValue(constants::count_dsp_lbl_str,count);
  long power = controller.getPwrIntVar();
  modular_server.setSavedVariableValue(constants::pwr_dsp_lbl_str,power);
}

// EventController Callbacks
void removeIndexedChannelCallback(int index)
{
  indexed_channels_power.remove(index);
}

void setChannelsOnEventCallback(int index)
{
  ChannelsPower channels_power = indexed_channels_power[index];
  for (int channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    if ((1<<channel) & channels_power.channels)
    {
      controller.setChannelPower(channel,channels_power.power);
    }
  }
}

void setChannelsOffEventCallback(int index)
{
  ChannelsPower channels_power = indexed_channels_power[index];
  for (int channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    if ((1<<channel) & channels_power.channels)
    {
      controller.setChannelOff(channel);
    }
  }
}

//Interactive Variable Update Callbacks

}
