// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace constants
{
const unsigned int baudrate = 9600;

const unsigned int model_number = 1160;

// Use semantic versioning http://semver.org/
const unsigned char firmware_major = 0;
const unsigned char firmware_minor = 1;
const unsigned char firmware_patch = 0;

const Standalone::Configuration standalone_configuration =
  {Serial3, // display_serial
   18, // enc_a_pin
   2, // enc_b_pin
   19, // enc_btn_pin
   4, // enc_btn_int
   21, // btn_pin
   2, // btn_int
   20, // switch_pin
   3, // switch_int
   22, // lights_pin
   300 // update_period
  };

const int pwm_pins[CHANNEL_COUNT] = {10,9,8,7};
const int enable_pins[CHANNEL_COUNT] = {52,50,48,46};

const uint8_t power_min = 0;
const uint8_t power_max = 100;

const int analog_out_min = 0;
const int analog_out_max = 255;

const uint32_t duration_min = 1;
const uint32_t duration_max = 0x7FFFFFFF;

const float frequency_min = 0.00001;
const float frequency_max = 500.0;

const uint8_t duty_cycle_min = 1;
const uint8_t duty_cycle_max = 99;

const int delay = 100;

const uint8_t dsp_lbl_display_position = 48;
const uint8_t int_var_display_position = 51;

const uint8_t dsp_lbl_display_position_2 = 68;
const uint8_t int_var_display_position_2 = 71;

const uint8_t inc_dsp_lbl_display_position = 11;
const uint8_t inc_int_var_display_position = 15;
const uint8_t chnl_dsp_lbl_display_position = 33;
const uint8_t chnl_int_var_display_position = 38;
const uint8_t pwr_dsp_lbl_display_position = 53;
const uint8_t pwr_int_var_display_position = 57;

const uint8_t period_dsp_lbl_display_position = 20;
const uint8_t on_dsp_lbl_display_position = 40;
const uint8_t count_dsp_lbl_display_position = 60;

const uint8_t period_int_var_display_position = 27;
const uint8_t on_int_var_display_position = 47;
const uint8_t count_int_var_display_position = 67;

const int inc_width_max = 5;
const long display_period_min = 2;
const long display_period_max = 100000;
const long display_period_default = 1000;
const long display_on_min = 1;
const long display_on_max = display_period_max-1;
const long display_on_default = display_period_default/2;
const long display_count_min = 1;
const long display_count_max = 1000;
const long display_count_default = 10;
const long display_power_default = 50;

CONSTANT_STRING(inc_dsp_lbl_str,"inc");
CONSTANT_STRING(chnl_dsp_lbl_str,"chnl");
CONSTANT_STRING(pwr_dsp_lbl_str,"pwr");

CONSTANT_STRING(period_dsp_lbl_str,"period");
CONSTANT_STRING(on_dsp_lbl_str,"on_dur");
CONSTANT_STRING(count_dsp_lbl_str,"count");

CONSTANT_STRING(device_name,"led_controller");

CONSTANT_STRING(duration_units_name,"ms");
CONSTANT_STRING(frequency_units_name,"Hz");
CONSTANT_STRING(duty_cycle_units_name,"%");
CONSTANT_STRING(power_units_name,"%");

CONSTANT_STRING(channels_parameter_name,"channels");
CONSTANT_STRING(channel_parameter_name,"channel");
CONSTANT_STRING(power_parameter_name,"power");
CONSTANT_STRING(powers_parameter_name,"powers");
CONSTANT_STRING(state_parameter_name,"state");
CONSTANT_STRING(on_duration_parameter_name,"on_duration");
CONSTANT_STRING(period_parameter_name,"period");
CONSTANT_STRING(count_parameter_name,"count");
CONSTANT_STRING(frequency_parameter_name,"frequency");
CONSTANT_STRING(duty_cycle_parameter_name,"duty_cycle");
CONSTANT_STRING(pwm_duration_parameter_name,"pwm_duration");
CONSTANT_STRING(pulse_wave_index_parameter_name,"pulse_wave_index");

CONSTANT_STRING(set_channel_power_method_name,"setChannelPower");
CONSTANT_STRING(set_channel_off_method_name,"setChannelOff");
CONSTANT_STRING(set_channels_powers_method_name,"setChannelsPowers");
CONSTANT_STRING(set_channels_off_method_name,"setChannelsOff");
CONSTANT_STRING(set_all_channels_power_method_name,"setAllChannelsPower");
CONSTANT_STRING(set_all_channels_off_method_name,"setAllChannelsOff");
CONSTANT_STRING(get_channels_powers_method_name,"getChannelsPowers");
CONSTANT_STRING(get_channel_count_method_name,"getChannelCount");
CONSTANT_STRING(add_pwm_period_on_duration_method_name,"addPwmPeriodOnDuration");
CONSTANT_STRING(add_pwm_frequency_duty_cycle_method_name,"addPwmFrequencyDutyCycle");
CONSTANT_STRING(stop_all_pulses_method_name,"stopAllPulses");
CONSTANT_STRING(start_pwm_period_on_duration_method_name,"startPwmPeriodOnDuration");
CONSTANT_STRING(start_pwm_frequency_duty_cycle_method_name,"startPwmFrequencyDutyCycle");
CONSTANT_STRING(stop_pulse_wave_method_name,"stopPulseWave");

CONSTANT_STRING(pwm_method_name,"pwm");
CONSTANT_STRING(set_pwm_defaults_method_name,"defaults");
const ConstantString frame_name_array[] =
  {
    set_channel_power_method_name,
    set_channel_off_method_name,
    set_all_channels_power_method_name,
    set_all_channels_off_method_name,
    pwm_method_name,
    stop_all_pulses_method_name,
    set_pwm_defaults_method_name,
  };
}
