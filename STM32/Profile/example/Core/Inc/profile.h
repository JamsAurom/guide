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

uint64_t timer = 0;

class LogDuration {
public:
	explicit LogDuration(const std::string& msg = "")
		: message(msg + ": ")
		, start(timer)
	{
	}

	~LogDuration() {
		uint64_t finish = timer;
		uint64_t dur = finish - start;
		printf("%s: %i ms\n", message.c_str(), dur);
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
