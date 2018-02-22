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

#define GET_DEF_STR(x) x
#ifndef COORDINATOR
#	define CFG_N_SENSORS (sizeof(GET_DEF_STR(CFG_SENSORS)) / sizeof(struct sensor_info *))
#endif

#ifdef DEBUG_HARD_OFF
#	define DO_DEBUG(lvl)	if (0)
#	define DO_DEBUG_AVAIL	if (0)
#else
#	define DO_DEBUG(lvl)	if (GET_DEF_STR(CFG_CURRENT).debug >= (lvl))
#	define DO_DEBUG_AVAIL	if (1)
#endif

#endif /* __CFGLIB_H__ */
