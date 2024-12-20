#pragma once

#include "vector.h"

typedef const char *ec_string;

ec_vector ec_string_split(ec_string string, char divider);

ec_string ec_string_trim(ec_string string);
