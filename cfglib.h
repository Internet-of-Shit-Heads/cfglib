#ifndef __CFGLIB_H__
#define __CFGLIB_H__

#include <cryptlib.h>

struct sensor_info {
	uint16_t id;
	at_ac_tuwien_iot1718_N2C_SensorType type;
	uint8_t pin;
	uint8_t degree;
	const float *poly;
} __attribute__((packed));

struct rfnode_config {
	uint64_t address;
	uint32_t room_number;
	uint32_t node_id;
	unsigned int wakeup_interval;
	unsigned int baud_rate;
	uint16_t cepin;
	uint16_t cspin;
	uint8_t channel;
	uint8_t delay;
	uint8_t retransmits;
	const uint8_t auth_key[CRYPTLIB_KEY_SIZE];
	const struct sensor_info *const *sensors; 
} __attribute__((packed));

#endif /* __CFGLIB_H__ */
