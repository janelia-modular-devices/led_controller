// ----------------------------------------------------------------------------
// Controller.h
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "PowerSwitch.h"
#include "ModularServer.h"
#include "StandaloneInterface.h"
#include "EventController.h"
#include "Constants.h"
#include "Callbacks.h"

class Controller
{
public:
  Controller();
  void setup();
  void update();
  ModularDevice::ModularServer & getModularServer();

  void enableChannel(uint8_t channel);
  void disableChannel(uint8_t channel);
  void setChannelPower(uint8_t channel, uint8_t power);
  void setChannelOff(uint8_t channel);
  uint8_t getChannelPower(uint8_t channel);
  uint8_t getChannelIntVar();
  uint8_t getPowerIntVar();
  uint8_t getChnlIntVar();
  uint8_t getPwrIntVar();
  long getPeriodIntVar();
  void setPeriodIntVar(long value);
  long getOnIntVar();
  void setOnIntVar(long value);
  void setOnIntVarMax(long value);
  long getCountIntVar();
  void setCountIntVar(long value);
  void setCountIntVarMax(long value);
private:
  ModularDevice::ModularServer modular_server_;
  SavedVariable saved_variables_[constants::SAVED_VARIABLE_COUNT_MAX];
  ModularDevice::Parameter parameters_[constants::PARAMETER_COUNT_MAX];
  ModularDevice::Method methods_[constants::METHOD_COUNT_MAX];

  Standalone::StandaloneInterface standalone_interface_;
  Standalone::DisplayLabel display_labels_[constants::DISPLAY_LABEL_COUNT_MAX];
  Standalone::DisplayVariable display_variables_[constants::DISPLAY_VARIABLE_COUNT_MAX];
  Standalone::InteractiveVariable interactive_variables_[constants::INTERACTIVE_VARIABLE_COUNT_MAX];

  Standalone::InteractiveVariable * channel_int_var_ptr_;
  Standalone::InteractiveVariable * power_int_var_ptr_;

  Standalone::InteractiveVariable * chnl_int_var_ptr_;
  Standalone::InteractiveVariable * pwr_int_var_ptr_;
  Standalone::InteractiveVariable * period_int_var_ptr_;
  Standalone::InteractiveVariable * on_int_var_ptr_;
  Standalone::InteractiveVariable * count_int_var_ptr_;

  uint8_t powers_[constants::CHANNEL_COUNT];
};

extern Controller controller;

#endif
