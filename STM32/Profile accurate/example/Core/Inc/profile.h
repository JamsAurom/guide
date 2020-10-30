/*
 * profile.h
 *
 *  Created on: Oct 21, 2020
 *      Author: maksi
 */

#ifndef INC_PROFILE_H_
#define INC_PROFILE_H_

#pragma once

#include <stdio.h>

#include <stm32f4xx_it.h>
#include <optional>
#include <string>

#define    DWT_CYCCNT    *(volatile unsigned long *)0xE0001004
#define    DWT_CONTROL   *(volatile unsigned long *)0xE0001000
#define    SCB_DEMCR     *(volatile unsigned long *)0xE000EDFC

class LogDuration {
public:
	explicit LogDuration(const std::string& msg = "")
		: message(msg + ": ")
	{
		SCB_DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;// разрешаем использовать DWT
		DWT_CONTROL|= DWT_CTRL_CYCCNTENA_Msk; // включаем счётчик
		start = DWT_CYCCNT;// обнуляем счётчик
	}

	~LogDuration() {
		uint64_t finish = DWT_CYCCNT;
		uint64_t dur = finish - start - 1;
		printf("%sticks: %i\n", message.c_str(), dur);
	}
private:
	std::string message;
	uint64_t start;
};

#ifndef UNIQ_ID
  #define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
  #define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)
#endif

#define LOG_DURATION(message) \
  LogDuration UNIQ_ID(__LINE__){message};

#endif /* INC_PROFILE_H_ */
