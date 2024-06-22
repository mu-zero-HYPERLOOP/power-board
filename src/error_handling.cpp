#include "canzero/canzero.h"
#include "error_handling.hpp"

pdu_12v_command error_handling::approve(pdu_12v_command cmd) {
  if (canzero_get_error_any_short() == error_flag_ERROR) {
    // affected channel is already off anyway
    return pdu_12v_command_TELEMETRY;
  }
  if (canzero_get_error_heartbeat_miss() == error_flag_ERROR) {
    // with only telemetry on nothing too bad can happen right?
    return pdu_12v_command_TELEMETRY;
  }

  if (canzero_get_error_level_mcu_temperature() == error_level_ERROR) {
    return pdu_12v_command_STOP;
  }

  return cmd;
}