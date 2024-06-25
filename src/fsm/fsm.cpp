#include "fsm/fsm.hpp"
#include "canzero/canzero.h"
#include "fsm/error_handling.hpp"
#include "firmware/pdu12.hpp"



void fsm::begin() {
  canzero_set_state(pdu_12v_state_CHANNELS_OFF);
  canzero_set_command(pdu_12v_command_TELEMETRY);
  canzero_set_sdc_status(sdc_status_OPEN);
}


void fsm::update() {
  pdu_12v_command cmd = error_handling::approve(canzero_get_command());
  switch (cmd) {

  case pdu_12v_command_NONE:
  case pdu_12v_command_START:
    canzero_set_state(pdu_12v_state_CHANNELS_ON);
    if (canzero_get_error_any_short() == error_flag_OK && 
        canzero_get_error_heartbeat_miss() == error_flag_OK) {
      pdu12::set_sdc(true);
      canzero_set_sdc_status(sdc_status_CLOSED);
    } else {
      pdu12::set_sdc(false);
      canzero_set_sdc_status(sdc_status_OPEN);
    }
    break;
  case pdu_12v_command_STOP:
    canzero_set_state(pdu_12v_state_CHANNELS_OFF);
    pdu12::set_sdc(false);
    canzero_set_sdc_status(sdc_status_OPEN);
    break;
  case pdu_12v_command_TELEMETRY:
    canzero_set_state(pdu_12v_state_CHANNELS_TELEMETRY);
    if (canzero_get_error_any_short() == error_flag_OK && 
        canzero_get_error_heartbeat_miss() == error_flag_OK) {
      pdu12::set_sdc(true);
      canzero_set_sdc_status(sdc_status_CLOSED);
    } else {
      pdu12::set_sdc(false);
      canzero_set_sdc_status(sdc_status_OPEN);
    }
    break;
  }
}