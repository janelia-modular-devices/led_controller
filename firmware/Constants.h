// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "ConstantVariable.h"


namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{SAVED_VARIABLE_COUNT_MAX=1};
enum{PARAMETER_COUNT_MAX=13};
enum{METHOD_COUNT_MAX=20};

enum{DISPLAY_LABEL_COUNT_MAX=10};
enum{DISPLAY_VARIABLE_COUNT_MAX=1};
enum{INTERACTIVE_VARIABLE_COUNT_MAX=10};
enum {FRAME_COUNT=7};

enum {CHANNEL_COUNT=4};
enum {STATE_COUNT=16};
enum {INDEXED_CHANNELS_COUNT_MAX=8};
enum {INDEXED_PULSES_COUNT_MAX=4};

extern const unsigned int baudrate;

extern const unsigned int model_number;

extern const unsigned char firmware_major;
extern const unsigned char firmware_minor;
extern const unsigned char firmware_patch;

extern HardwareSerial& display_serial;

extern const int enc_a_pin;
extern const int enc_b_pin;
extern const int enc_btn_pin;
extern const int enc_btn_int;
extern const int btn_pin;
extern const int btn_int;
extern const int lights_pin;
extern const int standalone_update_period;

extern const int pwm_pins[CHANNEL_COUNT];
extern const int enable_pins[CHANNEL_COUNT];

extern const int power_min;
extern const int power_max;
extern const int display_power_default;

extern const int analog_out_min;
extern const int analog_out_max;

extern const uint32_t duration_min;
extern const uint32_t duration_max;

extern const float frequency_min;
extern const float frequency_max;

extern const uint8_t duty_cycle_min;
extern const uint8_t duty_cycle_max;
extern const uint8_t display_duty_cycle_default;

extern const uint32_t states_array_default[STATE_COUNT];

extern const uint8_t dsp_lbl_display_position;
extern const uint8_t int_var_display_position;

extern const uint8_t dsp_lbl_display_position_2;
extern const uint8_t int_var_display_position_2;

extern const uint8_t inc_dsp_lbl_display_position;
extern const uint8_t inc_int_var_display_position;
extern const uint8_t c_dsp_lbl_display_position;
extern const uint8_t c_int_var_display_position;

extern const uint8_t period_dsp_lbl_display_position;
extern const uint8_t on_dsp_lbl_display_position;
extern const uint8_t count_dsp_lbl_display_position;
extern const uint8_t frequency_dsp_lbl_display_position;
extern const uint8_t pwm_duty_dsp_lbl_display_position;
extern const uint8_t pwm_dur_dsp_lbl_display_position;

extern const uint8_t period_int_var_display_position;
extern const uint8_t on_int_var_display_position;
extern const uint8_t count_int_var_display_position;
extern const uint8_t frequency_int_var_display_position;
extern const uint8_t pwm_duty_int_var_display_position;
extern const uint8_t pwm_dur_int_var_display_position;

extern const int display_period_min;
extern const int display_period_max;
extern const int display_period_default;
extern const int display_on_min;
extern const int display_on_max;
extern const int display_on_default;
extern const int display_count_min;
extern const int display_count_max;
extern const int display_count_default;
extern const int display_frequency_min;
extern const int display_frequency_max;
extern const int display_frequency_default;
extern const int display_dur_max;
extern const int display_dur_default;

extern ConstantString inc_dsp_lbl_str;
extern ConstantString c_dsp_lbl_str;

extern ConstantString period_dsp_lbl_str;
extern ConstantString on_dsp_lbl_str;
extern ConstantString count_dsp_lbl_str;
extern ConstantString frequency_dsp_lbl_str;

extern ConstantString device_name;

extern ConstantString duration_units_name;
extern ConstantString frequency_units_name;
extern ConstantString duty_cycle_units_name;
extern ConstantString power_units_name;

extern ConstantString channels_parameter_name;
extern ConstantString channel_parameter_name;
extern ConstantString power_parameter_name;
extern ConstantString powers_parameter_name;
extern ConstantString state_parameter_name;
extern ConstantString delay_parameter_name;
extern ConstantString on_duration_parameter_name;
extern ConstantString period_parameter_name;
extern ConstantString count_parameter_name;
extern ConstantString frequency_parameter_name;
extern ConstantString duty_cycle_parameter_name;
extern ConstantString pwm_duration_parameter_name;
extern ConstantString pulse_wave_index_parameter_name;

extern ConstantString execute_standalone_callback_method_name;
extern ConstantString set_channel_power_method_name;
extern ConstantString set_channel_off_method_name;
extern ConstantString set_channels_on_method_name;
extern ConstantString set_channels_off_method_name;
extern ConstantString set_all_channels_on_method_name;
extern ConstantString set_all_channels_off_method_name;
extern ConstantString get_channels_on_method_name;
extern ConstantString get_channels_off_method_name;
extern ConstantString get_channel_count_method_name;
extern ConstantString save_state_method_name;
extern ConstantString recall_state_method_name;
extern ConstantString get_saved_states_method_name;
extern ConstantString add_pulse_centered_method_name;
extern ConstantString add_pwm_period_on_duration_method_name;
extern ConstantString add_pwm_frequency_duty_cycle_method_name;
extern ConstantString stop_all_pulses_method_name;
extern ConstantString start_pwm_period_on_duration_method_name;
extern ConstantString start_pwm_frequency_duty_cycle_method_name;
extern ConstantString stop_pulse_wave_method_name;

extern ConstantString pwm_state_method_name;
extern ConstantString states_name;
extern const ConstantString frame_name_array[FRAME_COUNT];
}
#endif
