/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef LOG_OUTPUT_H
#define LOG_OUTPUT_H

#include <logging/log_msg.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Log output API
 * @defgroup log_output Log output API
 * @ingroup logger
 * @{
 */

/** @brief Flag forcing ANSI escape code colors, red (errors), yellow
 *         (warnings).
 */
#define LOG_OUTPUT_FLAG_COLORS                  (1 << 0)

/** @brief Flag forcing timestamp formatting. */
#define LOG_OUTPUT_FLAG_FORMAT_TIMESTAMP        (1 << 1)

/**
 * @brief Prototype of the function processing output data.
 *
 * @param data Data.
 * @param length Data length.
 * @param ctx  User context.
 *
 * @return Number of bytes processed.
 */
typedef int (*log_output_func_t)(u8_t *buf, size_t size, void *ctx);

/* @brief Control block structure for log_output instance.  */
struct log_output_control_block {
	size_t offset;
	void *ctx;
};

/** @brief Log_output instance structure. */
struct log_output {
	log_output_func_t func;
	struct log_output_control_block *control_block;
	u8_t *buf;
	size_t size;
};

/** @brief Create log_output instance.
 *
 * @param _name Instance name.
 * @param _func Function for processing output data.
 * @param _buf  Pointer to the output buffer.
 * @param _size Size of the output buffer.
 */
#define LOG_OUTPUT_DEFINE(_name, _func, _buf, _size)			\
	static struct log_output_control_block _name##_control_block;	\
	static const struct log_output _name = {			\
		.func = _func,						\
		.control_block = &_name##_control_block,		\
		.buf = _buf,						\
		.size = _size,						\
	}

/** @brief Process log messages to readable strings.
 *
 * Function is using provided context with the buffer and output function to
 * process formatted string and output the data.
 *
 * @param log_output Pointer to the log output instance.
 * @param msg Log message.
 * @param flags Optional flags.
 */
void log_output_msg_process(const struct log_output *log_output,
			    struct log_msg *msg,
			    u32_t flags);

/** @brief Flush output buffer.
 *
 * @param log_output Pointer to the log output instance.
 */
void log_output_flush(const struct log_output *log_output);

/** @brief Function for setting user context passed to the output function.
 *
 * @param log_output	Pointer to the log output instance.
 * @param ctx		User context.
 */
static inline void log_output_ctx_set(const struct log_output *log_output,
				      void *ctx)
{
	log_output->control_block->ctx = ctx;
}


/** @brief Set timestamp frequency.
 *
 * @param freq Frequency in Hz.
 */
void log_output_timestamp_freq_set(u32_t freq);

/**
 * @}
 */


#ifdef __cplusplus
}
#endif

#endif /* LOG_OUTPUT_H */
