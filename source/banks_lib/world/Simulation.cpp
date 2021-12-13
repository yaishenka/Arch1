//
// Created by wasd on 13.12.2021.
//

#include "Simulation.hpp"

#include <iostream>
#include <string>

#include <banks_lib/types/utils.hpp>

using namespace banks;

Simulation::Simulation(ITimeService::Ptr time_service, ILogger::Ptr logger)
    : IWorld(time_service, logger), output_(std::cout), input_(std::cin) {
}

bool Simulation::ProcessEvents(size_t step) {
  output_ << "START OF STEP: " << std::to_string(step) << "\n";

  std::string token;
  while (true) {
    input_ >> token;

    if (token == "actor") {
      ProcessActor();
    } else if (token == "new") {
      ProcessNew();
    } else if (token == "now") {
      ProcessNow();
    } else if (token == "end") {
      return ProcessEnd();
    } else if (token == "finish") {
      ProcessFinish();
    }
  }
}

void Simulation::MakeStep() {
  for (auto bank : banks_) {
    bank->Step();
  }
}

void Simulation::ProcessNew() {
  std::string token;
  input_ >> token;

  if (token == "bank") {
    output_ << "[creating new bank]\n";
    output_
        << "enter:\n debit %\n credit limit and %\n deposit % and deadline\n";

    AccountConditions conditions;
    input_ >> conditions;

    AddBank(conditions);

    output_ << "bank " << banks_.size() - 1 << " created\n";
  } else if (token == "bot") {
    output_ << "[creating new bot]\n";

    std::string name;
    std::string surname;
    std::optional<std::string> address;
    std::optional<std::string> passport;

    output_ << "enter name and surname\n";
    input_ >> name >> surname;

    while (!address || !passport) {
      output_ << "add passport or address? no/p/a\n";
      input_ >> token;

      if (token == "no") {
        break;
      } else if (token == "p") {
        std::string passport_str;
        input_ >> passport_str;

        passport = std::move(passport_str);
      } else if (token == "a") {
        std::string address_str;
        input_ >> address_str;

        address = std::move(address_str);
      }
    }

    AddBot(UserInfo{std::move(name), std::move(surname), std::move(address),
                    std::move(passport)});

    output_ << "bot " << users_.size() - 1 << " created\n";
  } else if (token == "user") {
    output_ << "[unsupported]"
            << "\n";
  }
}

void Simulation::ProcessNow() {
  output_ << "[now] " << time_service_->Now() << "\n";
}

bool Simulation::ProcessEnd() {
  output_ << "END OF STEP\n" << std::endl;

  bool status = time_service_->Tick();
  if (status) {
    MakeStep();
  }

  return status;
}

void Simulation::ProcessActor() {
  size_t actor_index = 0;
  input_ >> actor_index;
  if (actor_index >= users_.size()) {
    output_ << "no such actor\n";

    return;
  }

  output_ << "ACTOR " << actor_index << " started\n";

  users_[actor_index]->Step();

  output_ << "ACTOR " << actor_index << " stopped\n";
}

void Simulation::ProcessFinish() {
  exit(0);
}
