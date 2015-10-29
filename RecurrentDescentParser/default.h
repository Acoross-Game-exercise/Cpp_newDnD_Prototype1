#pragma once

#define DEF_CON(TypeName) \
	TypeName() = default;

#define NO_COPY(TypeName) \
  TypeName(const TypeName&) = delete;   \
  void operator=(const TypeName&) = delete;

#define ASSERT(cond)\
if (!(cond))\
{printf("assertion error line %d, file(%s)\n", \
	__LINE__, __FILE__);}