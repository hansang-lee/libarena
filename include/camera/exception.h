#pragma once

#include <exception>
#include <iostream>
#include <string>

namespace camera {
namespace exception {

class GenericException: public std::exception {
   private:
    std::string message = "";

   public:
    explicit GenericException(const std::string& msg = "")
        : message(msg) {}

    [[nodiscard]] const char* what() const noexcept override { return message.c_str(); }
};

class DevicecNotAccesible: public std::exception {
   public:
    [[nodiscard]] const char* what() const noexcept override { return "Device is being used"; }
};

class DeviceNotFound: public std::exception {
   public:
    [[nodiscard]] const char* what() const noexcept override { return "Device not found"; }
};

class DeviceNotConnected: public std::exception {
   public:
    [[nodiscard]] const char* what() const noexcept override { return "Device not connected"; }
};

class UnknownModel: public std::exception {
   public:
    [[nodiscard]] const char* what() const noexcept override { return "Unknown Model"; }
};

class InvalidConfigValue: public std::exception {
   private:
    std::string message = "";

   public:
    explicit InvalidConfigValue(const std::string& msg = "")
        : message(msg) {}

    [[nodiscard]] const char* what() const noexcept override { return message.c_str(); }
};

class Timeout: public std::exception {
   public:
    [[nodiscard]] const char* what() const noexcept override {
        return "TimeoutException - Packets have not been delivered within a specific time duration";
    }
};

}  // namespace exception
}  // namespace camera
