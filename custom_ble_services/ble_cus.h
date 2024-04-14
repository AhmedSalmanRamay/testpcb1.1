#ifndef BLE_CUS_H__
#define BLE_CUS_H__

#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"
#include "sdk_common.h"

#define BLE_CUS_BLE_OBSERVER_PRIO  2

#define BLE_CUS_DEF(_name)                                                                          \
static ble_cus_t _name;                                                                             \
NRF_SDH_BLE_OBSERVER(_name ## _obs,                                                                 \
                     BLE_HRS_BLE_OBSERVER_PRIO,                                                     \
                     ble_cus_on_ble_evt, &_name)





#define CUSTOM_SERVICE_UUID_BASE         {0xBC, 0x8A, 0xBF, 0x45, 0xCA, 0x05, 0x50, 0xBA, \
                                          0x40, 0x42, 0xB0, 0x00, 0xC9, 0xAD, 0x64, 0xF3}

#define CUSTOM_SERVICE_UUID               0x1812
#define CUSTOM_VALUE_CHAR_UUID            0x2A22
																					

typedef enum
{
    BLE_CUS_EVT_NOTIFICATION_ENABLED,                            
    BLE_CUS_EVT_NOTIFICATION_DISABLED,                             
    BLE_CUS_EVT_DISCONNECTED,
    BLE_CUS_EVT_CONNECTED
} ble_cus_evt_type_t;

/**@brief Custom Service event. */
typedef struct
{
    ble_cus_evt_type_t evt_type;                                  /**< Type of event. */
} ble_cus_evt_t;


typedef struct ble_cus_s ble_cus_t;


typedef void (*ble_cus_evt_handler_t) (ble_cus_t * p_bas, ble_cus_evt_t * p_evt);

typedef struct
{
    ble_cus_evt_handler_t         evt_handler;                    
    uint8_t                       initial_custom_value;           
    ble_srv_cccd_security_mode_t  custom_value_char_attr_md;    
} ble_cus_init_t;


struct ble_cus_s
{
    ble_cus_evt_handler_t         evt_handler;                   
    uint16_t                      service_handle;                 
    ble_gatts_char_handles_t      custom_value_handles;           
    uint16_t                      conn_handle;                   
    uint8_t                       uuid_type; 
};


uint32_t ble_cus_init(ble_cus_t * p_cus, const ble_cus_init_t * p_cus_init);


void ble_cus_on_ble_evt( ble_evt_t const * p_ble_evt, void * p_context);



uint32_t ble_cus_custom_value_update(ble_cus_t * p_cus, uint8_t custom_value);

#endif 
