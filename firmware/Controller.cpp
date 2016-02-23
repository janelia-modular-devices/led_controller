// ----------------------------------------------------------------------------
// Controller.cpp
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Controller.h"

Controller::Controller() :
  standalone_interface_(Standalone::StandaloneInterface(constants::standalone_configuration))
{
}

void Controller::setup()
{
  EventController::event_controller.setup();

  // Pin Setup
  for (int channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    pinMode(constants::enable_pins[channel],OUTPUT);
    setChannelOff(channel);
  }

  // Device Info
  modular_server_.setName(constants::device_name);
  modular_server_.setModelNumber(constants::model_number);
  modular_server_.setFirmwareVersion(constants::firmware_major,constants::firmware_minor,constants::firmware_patch);

  // Add Server Streams
  modular_server_.addServerStream(Serial);

  // Set Storage
  modular_server_.setSavedVariableStorage(saved_variables_);
  modular_server_.setParameterStorage(parameters_);
  modular_server_.setMethodStorage(methods_);

  // Saved Variables
  modular_server_.createSavedVariable(constants::period_dsp_lbl_str,constants::display_period_default);
  modular_server_.createSavedVariable(constants::on_dsp_lbl_str,constants::display_on_default);
  modular_server_.createSavedVariable(constants::pwr_dsp_lbl_str,constants::display_power_default);
  modular_server_.createSavedVariable(constants::count_dsp_lbl_str,constants::display_count_default);

  // Parameters
  ModularDevice::Parameter& channel_parameter = modular_server_.createParameter(constants::channel_parameter_name);
  channel_parameter.setRange(0,constants::CHANNEL_COUNT-1);

  ModularDevice::Parameter& channels_parameter = modular_server_.createParameter(constants::channels_parameter_name);
  channels_parameter.setTypeArray();
  channels_parameter.setRange(0,constants::CHANNEL_COUNT-1);

  ModularDevice::Parameter& power_parameter = modular_server_.createParameter(constants::power_parameter_name);
  power_parameter.setRange(constants::power_min,constants::power_max);
  power_parameter.setUnits(constants::power_units_name);

  ModularDevice::Parameter& powers_parameter = modular_server_.createParameter(constants::powers_parameter_name);
  powers_parameter.setTypeArray();
  powers_parameter.setRange(constants::power_min,constants::power_max);

  ModularDevice::Parameter& on_duration_parameter = modular_server_.createParameter(constants::on_duration_parameter_name);
  on_duration_parameter.setRange(constants::duration_min,constants::duration_max);
  on_duration_parameter.setUnits(constants::duration_units_name);

  ModularDevice::Parameter& period_parameter = modular_server_.createParameter(constants::period_parameter_name);
  period_parameter.setRange(constants::duration_min,constants::duration_max);
  period_parameter.setUnits(constants::duration_units_name);

  ModularDevice::Parameter& count_parameter = modular_server_.createParameter(constants::count_parameter_name);
  count_parameter.setRange(constants::duration_min,constants::duration_max);

  ModularDevice::Parameter& frequency_parameter = modular_server_.createParameter(constants::frequency_parameter_name);
  frequency_parameter.setRange(constants::frequency_min,constants::frequency_max);
  frequency_parameter.setUnits(constants::frequency_units_name);

  ModularDevice::Parameter& duty_cycle_parameter = modular_server_.createParameter(constants::duty_cycle_parameter_name);
  duty_cycle_parameter.setRange(constants::duty_cycle_min,constants::duty_cycle_max);
  duty_cycle_parameter.setUnits(constants::duty_cycle_units_name);

  ModularDevice::Parameter& pwm_duration_parameter = modular_server_.createParameter(constants::pwm_duration_parameter_name);
  pwm_duration_parameter.setRange(constants::duration_min,constants::duration_max);
  pwm_duration_parameter.setUnits(constants::duration_units_name);

  ModularDevice::Parameter& pulse_wave_index_parameter = modular_server_.createParameter(constants::pulse_wave_index_parameter_name);
  pulse_wave_index_parameter.setRange((int)0,(constants::INDEXED_PULSES_COUNT_MAX-1));

  // Methods
  ModularDevice::Method& set_channel_power_method = modular_server_.createMethod(constants::set_channel_power_method_name);
  set_channel_power_method.attachCallback(callbacks::setChannelPowerCallback);
  set_channel_power_method.addParameter(channel_parameter);
  set_channel_power_method.addParameter(power_parameter);

  ModularDevice::Method& set_channel_off_method = modular_server_.createMethod(constants::set_channel_off_method_name);
  set_channel_off_method.attachCallback(callbacks::setChannelOffCallback);
  set_channel_off_method.addParameter(channel_parameter);

  ModularDevice::Method& set_channels_powers_method = modular_server_.createMethod(constants::set_channels_powers_method_name);
  set_channels_powers_method.attachCallback(callbacks::setChannelsPowersCallback);
  set_channels_powers_method.addParameter(powers_parameter);

  ModularDevice::Method& set_channels_off_method = modular_server_.createMethod(constants::set_channels_off_method_name);
  set_channels_off_method.attachCallback(callbacks::setChannelsOffCallback);
  set_channels_off_method.addParameter(channels_parameter);

  ModularDevice::Method& set_all_channels_power_method = modular_server_.createMethod(constants::set_all_channels_power_method_name);
  set_all_channels_power_method.attachCallback(callbacks::setAllChannelsPowerCallback);
  set_all_channels_power_method.addParameter(power_parameter);

  ModularDevice::Method& set_all_channels_off_method = modular_server_.createMethod(constants::set_all_channels_off_method_name);
  set_all_channels_off_method.attachCallback(callbacks::setAllChannelsOffCallback);

  ModularDevice::Method& get_channels_powers_method = modular_server_.createMethod(constants::get_channels_powers_method_name);
  get_channels_powers_method.attachCallback(callbacks::getChannelsPowersCallback);
  get_channels_powers_method.setReturnTypeArray();

  ModularDevice::Method& get_channel_count_method = modular_server_.createMethod(constants::get_channel_count_method_name);
  get_channel_count_method.attachCallback(callbacks::getChannelCountCallback);
  get_channel_count_method.setReturnTypeLong();

  ModularDevice::Method& add_pwm_period_on_duration_method = modular_server_.createMethod(constants::add_pwm_period_on_duration_method_name);
  add_pwm_period_on_duration_method.attachCallback(callbacks::addPwmPeriodOnDurationCallback);
  add_pwm_period_on_duration_method.addParameter(channels_parameter);
  add_pwm_period_on_duration_method.addParameter(power_parameter);
  add_pwm_period_on_duration_method.addParameter(period_parameter);
  add_pwm_period_on_duration_method.addParameter(on_duration_parameter);
  add_pwm_period_on_duration_method.addParameter(count_parameter);

  ModularDevice::Method& add_pwm_frequency_duty_cycle_method = modular_server_.createMethod(constants::add_pwm_frequency_duty_cycle_method_name);
  add_pwm_frequency_duty_cycle_method.attachCallback(callbacks::addPwmFrequencyDutyCycleCallback);
  add_pwm_frequency_duty_cycle_method.addParameter(channels_parameter);
  add_pwm_frequency_duty_cycle_method.addParameter(power_parameter);
  add_pwm_frequency_duty_cycle_method.addParameter(frequency_parameter);
  add_pwm_frequency_duty_cycle_method.addParameter(duty_cycle_parameter);
  add_pwm_frequency_duty_cycle_method.addParameter(pwm_duration_parameter);

  ModularDevice::Method& stop_all_pulses_method = modular_server_.createMethod(constants::stop_all_pulses_method_name);
  stop_all_pulses_method.attachCallback(callbacks::stopAllPulsesCallback);

  ModularDevice::Method& start_pwm_period_on_duration_method = modular_server_.createMethod(constants::start_pwm_period_on_duration_method_name);
  start_pwm_period_on_duration_method.attachCallback(callbacks::startPwmPeriodOnDurationCallback);
  start_pwm_period_on_duration_method.addParameter(channels_parameter);
  start_pwm_period_on_duration_method.addParameter(power_parameter);
  start_pwm_period_on_duration_method.addParameter(period_parameter);
  start_pwm_period_on_duration_method.addParameter(on_duration_parameter);

  ModularDevice::Method& start_pwm_frequency_duty_cycle_method = modular_server_.createMethod(constants::start_pwm_frequency_duty_cycle_method_name);
  start_pwm_frequency_duty_cycle_method.attachCallback(callbacks::startPwmFrequencyDutyCycleCallback);
  start_pwm_frequency_duty_cycle_method.addParameter(channels_parameter);
  start_pwm_frequency_duty_cycle_method.addParameter(power_parameter);
  start_pwm_frequency_duty_cycle_method.addParameter(frequency_parameter);
  start_pwm_frequency_duty_cycle_method.addParameter(duty_cycle_parameter);

  ModularDevice::Method& stop_pulse_wave_method = modular_server_.createMethod(constants::stop_pulse_wave_method_name);
  stop_pulse_wave_method.attachCallback(callbacks::stopPulseWaveCallback);
  stop_pulse_wave_method.addParameter(pulse_wave_index_parameter);

  // Setup Streams
  Serial.begin(constants::baudrate);

  // Start Modular Device Server
  modular_server_.startServer();

  // Standalone Interface

  // Set Storage
  standalone_interface_.setDisplayLabelStorage(display_labels_);
  standalone_interface_.setDisplayVariableStorage(display_variables_);
  standalone_interface_.setInteractiveVariableStorage(interactive_variables_);

  // Setup
  standalone_interface_.setup(constants::frame_name_array);

  // Display Labels
  Standalone::DisplayLabel& channel_dsp_lbl = standalone_interface_.createDisplayLabel();
  channel_dsp_lbl.setDisplayPosition(constants::dsp_lbl_display_position);
  channel_dsp_lbl.setConstantString(constants::channel_parameter_name);
  channel_dsp_lbl.setRightJustify();

  Standalone::DisplayLabel& power_dsp_lbl = standalone_interface_.createDisplayLabel();
  power_dsp_lbl.setDisplayPosition(constants::dsp_lbl_display_position_2);
  power_dsp_lbl.setConstantString(constants::power_parameter_name);
  power_dsp_lbl.setRightJustify();

  Standalone::DisplayLabel& inc_dsp_lbl = standalone_interface_.createDisplayLabel();
  inc_dsp_lbl.setDisplayPosition(constants::inc_dsp_lbl_display_position);
  inc_dsp_lbl.setConstantString(constants::inc_dsp_lbl_str);

  Standalone::DisplayLabel& chnl_dsp_lbl = standalone_interface_.createDisplayLabel();
  chnl_dsp_lbl.setDisplayPosition(constants::chnl_dsp_lbl_display_position);
  chnl_dsp_lbl.setConstantString(constants::chnl_dsp_lbl_str);

  Standalone::DisplayLabel& pwr_dsp_lbl = standalone_interface_.createDisplayLabel();
  pwr_dsp_lbl.setDisplayPosition(constants::pwr_dsp_lbl_display_position);
  pwr_dsp_lbl.setConstantString(constants::pwr_dsp_lbl_str);

  Standalone::DisplayLabel& period_dsp_lbl = standalone_interface_.createDisplayLabel();
  period_dsp_lbl.setDisplayPosition(constants::period_dsp_lbl_display_position);
  period_dsp_lbl.setConstantString(constants::period_dsp_lbl_str);

  Standalone::DisplayLabel& on_dsp_lbl = standalone_interface_.createDisplayLabel();
  on_dsp_lbl.setDisplayPosition(constants::on_dsp_lbl_display_position);
  on_dsp_lbl.setConstantString(constants::on_dsp_lbl_str);

  Standalone::DisplayLabel& count_dsp_lbl = standalone_interface_.createDisplayLabel();
  count_dsp_lbl.setDisplayPosition(constants::count_dsp_lbl_display_position);
  count_dsp_lbl.setConstantString(constants::count_dsp_lbl_str);

  // Display Variables

  // Interactive Variables
  channel_int_var_ptr_ = &(standalone_interface_.createInteractiveVariable());
  channel_int_var_ptr_->setDisplayPosition(constants::int_var_display_position);
  channel_int_var_ptr_->setRange(0,constants::CHANNEL_COUNT-1);
  channel_int_var_ptr_->trimDisplayWidthUsingRange();

  power_int_var_ptr_ = &(standalone_interface_.createInteractiveVariable());
  power_int_var_ptr_->setDisplayPosition(constants::int_var_display_position_2);
  power_int_var_ptr_->setRange(constants::power_min,constants::power_max);
  power_int_var_ptr_->trimDisplayWidthUsingRange();
  power_int_var_ptr_->setValue(constants::display_power_default);

  Standalone::InteractiveVariable& inc_int_var = standalone_interface_.createIncrementVariable(constants::inc_width_max);
  inc_int_var.setDisplayPosition(constants::inc_int_var_display_position);

  chnl_int_var_ptr_ = &(standalone_interface_.createInteractiveVariable());
  chnl_int_var_ptr_->setDisplayPosition(constants::chnl_int_var_display_position);
  chnl_int_var_ptr_->setRange(0,constants::CHANNEL_COUNT-1);
  chnl_int_var_ptr_->trimDisplayWidthUsingRange();

  pwr_int_var_ptr_ = &(standalone_interface_.createInteractiveVariable());
  pwr_int_var_ptr_->setDisplayPosition(constants::pwr_int_var_display_position);
  pwr_int_var_ptr_->setRange(constants::power_min,constants::power_max);
  pwr_int_var_ptr_->trimDisplayWidthUsingRange();
  long pwr_default;
  modular_server_.getSavedVariableValue(constants::pwr_dsp_lbl_str,pwr_default);
  pwr_int_var_ptr_->setValue(pwr_default);

  period_int_var_ptr_ = &(standalone_interface_.createInteractiveVariable());
  period_int_var_ptr_->setDisplayPosition(constants::period_int_var_display_position);
  period_int_var_ptr_->setRange(constants::display_period_min,constants::display_period_max);
  period_int_var_ptr_->trimDisplayWidthUsingRange();
  long period_default;
  modular_server_.getSavedVariableValue(constants::period_dsp_lbl_str,period_default);
  period_int_var_ptr_->setValue(period_default);

  on_int_var_ptr_ = &(standalone_interface_.createInteractiveVariable());
  on_int_var_ptr_->setDisplayPosition(constants::on_int_var_display_position);
  on_int_var_ptr_->setRange(constants::display_on_min,constants::display_on_max);
  on_int_var_ptr_->trimDisplayWidthUsingRange();
  long on_default;
  modular_server_.getSavedVariableValue(constants::on_dsp_lbl_str,on_default);
  on_int_var_ptr_->setValue(on_default);

  count_int_var_ptr_ = &(standalone_interface_.createInteractiveVariable());
  count_int_var_ptr_->setDisplayPosition(constants::count_int_var_display_position);
  count_int_var_ptr_->setRange(constants::display_count_min,constants::display_count_max);
  count_int_var_ptr_->trimDisplayWidthUsingRange();
  long count_default;
  modular_server_.getSavedVariableValue(constants::count_dsp_lbl_str,count_default);
  count_int_var_ptr_->setValue(count_default);

  // All Frames

  // Frame 0
  int frame = 0;
  channel_dsp_lbl.addToFrame(frame);
  channel_int_var_ptr_->addToFrame(frame);
  power_dsp_lbl.addToFrame(frame);
  power_int_var_ptr_->addToFrame(frame);
  standalone_interface_.attachCallbackToFrame(callbacks::setChannelPowerStandaloneCallback,frame);

  // Frame 1
  frame = 1;
  channel_dsp_lbl.addToFrame(frame);
  channel_int_var_ptr_->addToFrame(frame);
  standalone_interface_.attachCallbackToFrame(callbacks::setChannelOffStandaloneCallback,frame);

  // Frame 2
  frame = 2;
  power_dsp_lbl.addToFrame(frame);
  power_int_var_ptr_->addToFrame(frame);
  standalone_interface_.attachCallbackToFrame(callbacks::setAllChannelsPowerStandaloneCallback,frame);

  // Frame 3
  frame = 3;
  standalone_interface_.attachCallbackToFrame(callbacks::setAllChannelsOffCallback,frame);

  // Frame 4
  frame = 4;
  inc_dsp_lbl.addToFrame(frame);
  inc_int_var.addToFrame(frame);
  chnl_dsp_lbl.addToFrame(frame);
  chnl_int_var_ptr_->addToFrame(frame);
  pwr_dsp_lbl.addToFrame(frame);
  pwr_int_var_ptr_->addToFrame(frame);
  period_dsp_lbl.addToFrame(frame);
  period_int_var_ptr_->addToFrame(frame);
  on_dsp_lbl.addToFrame(frame);
  on_int_var_ptr_->addToFrame(frame);
  count_dsp_lbl.addToFrame(frame);
  count_int_var_ptr_->addToFrame(frame);
  standalone_interface_.attachCallbackToFrame(callbacks::pwmStandaloneCallback,frame);

  // Frame 5
  frame = 5;
  standalone_interface_.attachCallbackToFrame(callbacks::stopAllPulsesCallback,frame);

  // Frame 6
  frame = 6;
  inc_dsp_lbl.addToFrame(frame);
  inc_int_var.addToFrame(frame);
  pwr_dsp_lbl.addToFrame(frame);
  pwr_int_var_ptr_->addToFrame(frame);
  period_dsp_lbl.addToFrame(frame);
  period_int_var_ptr_->addToFrame(frame);
  on_dsp_lbl.addToFrame(frame);
  on_int_var_ptr_->addToFrame(frame);
  count_dsp_lbl.addToFrame(frame);
  count_int_var_ptr_->addToFrame(frame);
  standalone_interface_.attachCallbackToFrame(callbacks::setPwmDefaultsStandaloneCallback,frame);

  // Enable Standalone Interface
  standalone_interface_.enable();
}

void Controller::update()
{
  modular_server_.handleServerRequests();
  standalone_interface_.update();
}

ModularDevice::ModularServer& Controller::getModularServer()
{
  return modular_server_;
}

void Controller::enableChannel(uint8_t channel)
{
  digitalWrite(constants::enable_pins[channel],HIGH);
}

void Controller::disableChannel(uint8_t channel)
{
  digitalWrite(constants::enable_pins[channel],LOW);
}

void Controller::setChannelPower(uint8_t channel, uint8_t power)
{
  int analog_out = map(power,
                       constants::power_min,
                       constants::power_max,
                       constants::analog_out_max,
                       constants::analog_out_min);
  analogWrite(constants::pwm_pins[channel],analog_out);
  enableChannel(channel);
  powers_[channel] = power;
}

void Controller::setChannelOff(uint8_t channel)
{
  disableChannel(channel);
  powers_[channel] = 0;
}

uint8_t Controller::getChannelPower(uint8_t channel)
{
  return powers_[channel];
}

uint8_t Controller::getChannelIntVar()
{
  return channel_int_var_ptr_->getValue();
}

uint8_t Controller::getPowerIntVar()
{
  return power_int_var_ptr_->getValue();
}

uint8_t Controller::getChnlIntVar()
{
  return chnl_int_var_ptr_->getValue();
}

uint8_t Controller::getPwrIntVar()
{
  return pwr_int_var_ptr_->getValue();
}

long Controller::getPeriodIntVar()
{
  return period_int_var_ptr_->getValue();
}

void Controller::setPeriodIntVar(long value)
{
  period_int_var_ptr_->setValue(value);
}

long Controller::getOnIntVar()
{
  return on_int_var_ptr_->getValue();
}

void Controller::setOnIntVar(long value)
{
  on_int_var_ptr_->setValue(value);
}

void Controller::setOnIntVarMax(long value)
{
  if (value <= constants::display_on_max)
  {
    on_int_var_ptr_->setRange(constants::display_on_min,value);
  }
}

long Controller::getCountIntVar()
{
  return count_int_var_ptr_->getValue();
}

void Controller::setCountIntVar(long value)
{
  count_int_var_ptr_->setValue(value);
}

void Controller::setCountIntVarMax(long value)
{
  if (value <= constants::display_count_max)
  {
    count_int_var_ptr_->setRange(constants::display_count_min,value);
  }
}

Controller controller;
