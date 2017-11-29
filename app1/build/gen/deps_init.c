#include <stdbool.h>
#include <stdio.h>

#include "common/cs_dbg.h"

#include "fw/src/mgos_app.h"


extern bool mgos_adc_init(void);
extern bool mgos_i2c_init(void);
extern bool mgos_atca_init(void);
extern bool mgos_ca_bundle_init(void);
extern bool mgos_mqtt_init(void);
extern bool mgos_aws_init(void);
extern bool mgos_bt_common_init(void);
extern bool mgos_bt_service_config_init(void);
extern bool mgos_bt_service_debug_init(void);
extern bool mgos_ethernet_init(void);
extern bool mgos_wifi_init(void);
extern bool mgos_http_server_init(void);
extern bool mgos_rpc_common_init(void);
extern bool mgos_dash_init(void);
extern bool mgos_dns_sd_init(void);
extern bool mgos_esp32_touchpad_init(void);
extern bool mgos_gcp_init(void);
extern bool mgos_mjs_init(void);
extern bool mgos_ota_http_client_init(void);
extern bool mgos_ota_aws_shadow_init(void);
extern bool mgos_ota_http_server_init(void);
extern bool mgos_pppos_init(void);
extern bool mgos_pwm_init(void);
extern bool mgos_rpc_gatts_init(void);
extern bool mgos_rpc_loopback_init(void);
extern bool mgos_rpc_mqtt_init(void);
extern bool mgos_rpc_service_atca_init(void);
extern bool mgos_rpc_service_config_init(void);
extern bool mgos_rpc_service_fs_init(void);
extern bool mgos_rpc_service_gpio_init(void);
extern bool mgos_rpc_service_i2c_init(void);
extern bool mgos_rpc_service_ota_init(void);
extern bool mgos_rpc_service_wifi_init(void);
extern bool mgos_rpc_uart_init(void);
extern bool mgos_spi_init(void);
extern bool mgos_vfs_dev_spi_flash_init(void);
extern bool mgos_js_demo_bundle_init(void);

static const struct lib_descr {
  const char *title;
  bool (*init)(void);
} descrs[] = {

  // "adc". deps: [ ]
  {
    .title = "adc",
    .init = mgos_adc_init,
  },

  // "i2c". deps: [ ]
  {
    .title = "i2c",
    .init = mgos_i2c_init,
  },

  // "atca". deps: [ "i2c" ]
  {
    .title = "atca",
    .init = mgos_atca_init,
  },

  // "ca_bundle". deps: [ ]
  {
    .title = "ca_bundle",
    .init = mgos_ca_bundle_init,
  },

  // "mqtt". deps: [ ]
  {
    .title = "mqtt",
    .init = mgos_mqtt_init,
  },

  // "aws". deps: [ "ca-bundle" "mqtt" ]
  {
    .title = "aws",
    .init = mgos_aws_init,
  },

  // "bt_common". deps: [ ]
  {
    .title = "bt_common",
    .init = mgos_bt_common_init,
  },

  // "bt_service_config". deps: [ "bt-common" ]
  {
    .title = "bt_service_config",
    .init = mgos_bt_service_config_init,
  },

  // "bt_service_debug". deps: [ "bt-common" ]
  {
    .title = "bt_service_debug",
    .init = mgos_bt_service_debug_init,
  },

  // "ethernet". deps: [ ]
  {
    .title = "ethernet",
    .init = mgos_ethernet_init,
  },

  // "wifi". deps: [ ]
  {
    .title = "wifi",
    .init = mgos_wifi_init,
  },

  // "http_server". deps: [ "atca" "ethernet" "wifi" ]
  {
    .title = "http_server",
    .init = mgos_http_server_init,
  },

  // "rpc_common". deps: [ "http-server" ]
  {
    .title = "rpc_common",
    .init = mgos_rpc_common_init,
  },

  // "dash". deps: [ "rpc-common" ]
  {
    .title = "dash",
    .init = mgos_dash_init,
  },

  // "dns_sd". deps: [ "http-server" ]
  {
    .title = "dns_sd",
    .init = mgos_dns_sd_init,
  },

  // "esp32_touchpad". deps: [ ]
  {
    .title = "esp32_touchpad",
    .init = mgos_esp32_touchpad_init,
  },

  // "gcp". deps: [ "ca-bundle" "mqtt" ]
  {
    .title = "gcp",
    .init = mgos_gcp_init,
  },

  // "mjs". deps: [ ]
  {
    .title = "mjs",
    .init = mgos_mjs_init,
  },

  // "ota_http_client". deps: [ ]
  {
    .title = "ota_http_client",
    .init = mgos_ota_http_client_init,
  },

  // "ota_aws_shadow". deps: [ "aws" "ota-http-client" ]
  {
    .title = "ota_aws_shadow",
    .init = mgos_ota_aws_shadow_init,
  },

  // "ota_http_server". deps: [ "http-server" "ota-http-client" ]
  {
    .title = "ota_http_server",
    .init = mgos_ota_http_server_init,
  },

  // "pppos". deps: [ ]
  {
    .title = "pppos",
    .init = mgos_pppos_init,
  },

  // "pwm". deps: [ ]
  {
    .title = "pwm",
    .init = mgos_pwm_init,
  },

  // "rpc_gatts". deps: [ "bt-common" "rpc-common" ]
  {
    .title = "rpc_gatts",
    .init = mgos_rpc_gatts_init,
  },

  // "rpc_loopback". deps: [ "rpc-common" ]
  {
    .title = "rpc_loopback",
    .init = mgos_rpc_loopback_init,
  },

  // "rpc_mqtt". deps: [ "mqtt" "rpc-common" ]
  {
    .title = "rpc_mqtt",
    .init = mgos_rpc_mqtt_init,
  },

  // "rpc_service_atca". deps: [ "atca" "rpc-common" ]
  {
    .title = "rpc_service_atca",
    .init = mgos_rpc_service_atca_init,
  },

  // "rpc_service_config". deps: [ "rpc-common" ]
  {
    .title = "rpc_service_config",
    .init = mgos_rpc_service_config_init,
  },

  // "rpc_service_fs". deps: [ "rpc-common" ]
  {
    .title = "rpc_service_fs",
    .init = mgos_rpc_service_fs_init,
  },

  // "rpc_service_gpio". deps: [ "rpc-common" ]
  {
    .title = "rpc_service_gpio",
    .init = mgos_rpc_service_gpio_init,
  },

  // "rpc_service_i2c". deps: [ "i2c" "rpc-common" ]
  {
    .title = "rpc_service_i2c",
    .init = mgos_rpc_service_i2c_init,
  },

  // "rpc_service_ota". deps: [ "ota-http-client" "rpc-common" ]
  {
    .title = "rpc_service_ota",
    .init = mgos_rpc_service_ota_init,
  },

  // "rpc_service_wifi". deps: [ "rpc-common" "wifi" ]
  {
    .title = "rpc_service_wifi",
    .init = mgos_rpc_service_wifi_init,
  },

  // "rpc_uart". deps: [ "rpc-common" ]
  {
    .title = "rpc_uart",
    .init = mgos_rpc_uart_init,
  },

  // "spi". deps: [ ]
  {
    .title = "spi",
    .init = mgos_spi_init,
  },

  // "vfs_dev_spi_flash". deps: [ "spi" ]
  {
    .title = "vfs_dev_spi_flash",
    .init = mgos_vfs_dev_spi_flash_init,
  },

  // "js_demo_bundle". deps: [ "adc" "atca" "aws" "bt-service-config" "bt-service-debug" "ca-bundle" "dash" "dns-sd" "esp32-touchpad" "ethernet" "gcp" "http-server" "i2c" "mjs" "ota-aws-shadow" "ota-http-client" "ota-http-server" "pppos" "pwm" "rpc-gatts" "rpc-loopback" "rpc-mqtt" "rpc-service-atca" "rpc-service-config" "rpc-service-fs" "rpc-service-gpio" "rpc-service-i2c" "rpc-service-ota" "rpc-service-wifi" "rpc-uart" "spi" "vfs-dev-spi-flash" "wifi" ]
  {
    .title = "js_demo_bundle",
    .init = mgos_js_demo_bundle_init,
  },

};

bool mgos_deps_init(void) {
  size_t i;
  for (i = 0; i < sizeof(descrs) / sizeof(struct lib_descr); i++) {
    LOG(LL_DEBUG, ("init %s...", descrs[i].title));
    if (!descrs[i].init()) {
      LOG(LL_ERROR, ("%s init failed", descrs[i].title));
      return false;
    }
  }

  return true;
}
