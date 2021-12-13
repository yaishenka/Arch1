//
// Created by wasd on 13.12.2021.
//
#pragma once

#include <iostream>

namespace banks {

struct AccountConditions {
  Percentage debit_percentage;

  Money credit_limit;
  Percentage credit_percentage;

  Percentage deposit_percent;
  Time deadline;
};

}  // namespace banks
