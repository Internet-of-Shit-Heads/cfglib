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

enum debug_level {
	DEBUG_OFF,
	DEBUG_ERRORS,
	DEBUG_NOTICE,
	DEBUG_ALL
};

struct rfnode_config {
	/* operations */
	const struct sensor_info *const *sensors; 
	uint32_t room_number;
	uint32_t node_id;
	unsigned int wakeup_interval;
	/* communications */
	uint64_t address;
	uint8_t channel;
	uint8_t delay;
	uint8_t retransmits;
	/* security */
	const uint8_t auth_key[CRYPTLIB_KEY_SIZE];
	/* hardware */
	uint16_t cepin;
	uint16_t cspin;
	uint16_t rtcpin;
	uint16_t rtcint;
	/* debug */
	unsigned int baud_rate;
	debug_level debug;
} __attribute__((packed));

struct coordinator_config {
	/* operations */
	/* communications */
	uint64_t address;
	uint8_t channel;
	uint8_t delay;
	uint8_t retransmits;
	/* security */
	const uint8_t auth_key[CRYPTLIB_KEY_SIZE];
	/* hardware */
	uint16_t cepin;
	uint16_t cspin;
	/* debug */
	unsigned int baud_rate;
	debug_level debug;
} __attribute__((packed));

#ifdef COORDINATOR
	extern struct coordinator_config current_cfg;
#else
	extern const struct sensor_info *const available_sensors[];
#	define N_SENSORS (sizeof(available_sensors) / sizeof(struct sensor_info *))

	extern struct rfnode_config current_cfg;
#endif

#ifdef DEBUG_HARD_OFF
#	define DO_DEBUG(lvl)	if (0)
#	define DO_DEBUG_AVAIL	if (0)
#else
#	define DO_DEBUG(lvl)	if (current_cfg.debug >= (lvl))
#	define DO_DEBUG_AVAIL	if (1)
#endif

#endif /* __CFGLIB_H__ */
