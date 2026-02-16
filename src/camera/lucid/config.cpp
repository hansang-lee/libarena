#include "camera/lucid/config.hpp"
#include "camera/exception.h"

#include <arpa/inet.h>

namespace camera {
namespace lucid {

namespace {
template<typename T>
void setParameter(Arena::ISystem* system, Arena::IDevice* device, const char* node, const T value) {
    try {
        GenApi::INodeMap* node_map(nullptr);
        if (device->GetNodeMap()->GetNode(GenICam::gcstring(node)) != nullptr) {
            node_map = device->GetNodeMap();
        } else if (device->GetTLStreamNodeMap()->GetNode(GenICam::gcstring(node)) != nullptr) {
            node_map = device->GetTLStreamNodeMap();
        } else if (system->GetTLSystemNodeMap()->GetNode(GenICam::gcstring(node)) != nullptr) {
            node_map = system->GetTLSystemNodeMap();
        } else if (device->GetTLDeviceNodeMap()->GetNode(GenICam::gcstring(node)) != nullptr) {
            node_map = device->GetTLDeviceNodeMap();
        }
        Arena::SetNodeValue<T>(node_map, GenICam::gcstring(node), value);
    } catch (const GenICam::GenericException& e) {
        if (std::string(node) != "PixelFormat") {
            throw exception::InvalidConfigValue(e.what());
        }
    }
}

template<typename T>
T getParameter(Arena::ISystem* system, Arena::IDevice* device, const char* node) {
    T result{};
    try {
        GenApi::INodeMap* node_map(nullptr);
        if (device->GetNodeMap()->GetNode(GenICam::gcstring(node)) != nullptr) {
            node_map = device->GetNodeMap();
        } else if (device->GetTLStreamNodeMap()->GetNode(GenICam::gcstring(node)) != nullptr) {
            node_map = device->GetTLStreamNodeMap();
        } else if (system->GetTLSystemNodeMap()->GetNode(GenICam::gcstring(node)) != nullptr) {
            node_map = system->GetTLSystemNodeMap();
        } else if (device->GetTLDeviceNodeMap()->GetNode(GenICam::gcstring(node)) != nullptr) {
            node_map = device->GetTLDeviceNodeMap();
        }
        result = Arena::GetNodeValue<T>(node_map, GenICam::gcstring(node));
    } catch (const GenICam::GenericException& e) {
        if (std::string(node) != "PixelFormat") {
            throw exception::InvalidConfigValue(e.what());
        }
    }
    return result;
}

/**
 * @brief Converts IP address from integer to string.
 *
 * @param ip_address [in] Desired ip address to convert.
 *
 * @return Invalid if returned value is empty.
 */
std::string toStrIPAddress(const int64_t ip_address) {
    std::ostringstream oss;
    oss << ((ip_address >> 24) & 0xff) << "." << ((ip_address >> 16) & 0xff) << "." << ((ip_address >> 8) & 0xff) << "."
        << (ip_address & 0xff);
    return oss.str();
}

/**
 * @brief Converts IP address from string to integer.
 *
 * @param ip_address [in] Desired ip address to convert.
 *
 * @return Invalid if returned value is smaller than 0.
 */
int64_t toIntIPAddress(const std::string& ip_address) {
    struct in_addr ip_addr;
    return (inet_aton(ip_address.c_str(), &ip_addr) == 0) ? (-1) : ntohl(ip_addr.s_addr);
}
}  // namespace

Config::Config(Arena::ISystem* system, Arena::IDevice* device)
    : system_(system)
    , device_(device) {}

Config::~Config() {}

void Config::setActionCommandExecuteTime(const int64_t value) {
    setParameter<int64_t>(system_, device_, "ActionCommandExecuteTime", value);
}

int64_t Config::getActionCommandExecuteTime() const {
    return getParameter<int64_t>(system_, device_, "ActionCommandExecuteTime");
}

void Config::setActionDeviceKey(const int64_t value) {
    setParameter<int64_t>(system_, device_, "ActionDeviceKey", value);
}

int64_t Config::getActionDeviceKey() const {
    return getParameter<int64_t>(system_, device_, "ActionDeviceKey");
}

void Config::setActionGroupKey(const int64_t value) {
    setParameter<int64_t>(system_, device_, "ActionGroupKey", value);
}

int64_t Config::getActionGroupKey() const {
    return getParameter<int64_t>(system_, device_, "ActionGroupKey");
}

void Config::setActionGroupMask(const int64_t value) {
    setParameter<int64_t>(system_, device_, "ActionGroupMask", value);
}

int64_t Config::getActionGroupMask() const {
    return getParameter<int64_t>(system_, device_, "ActionGroupMask");
}

void Config::setActionSelector(const int64_t value) {
    setParameter<int64_t>(system_, device_, "ActionSelector", value);
}

int64_t Config::getActionSelector() const {
    return getParameter<int64_t>(system_, device_, "ActionSelector");
}

void Config::setActionUnconditionalMode(const char* value) {
    setParameter<GenICam::gcstring>(system_, device_, "ActionUnconditionalMode", static_cast<GenICam::gcstring>(value));
}

std::string Config::getActionUnconditionalMode() const {
    return std::string(getParameter<GenICam::gcstring>(system_, device_, "ActionUnconditionalMode").c_str());
}

int64_t Config::getActionQueueSize() const {
    return getParameter<int64_t>(system_, device_, "ActionQueueSize");
}

void Config::setAcquisitionFrameRate(const double value) {
    setParameter<double>(system_, device_, "AcquisitionFrameRate", value);
}

double Config::getAcquisitionFrameRate() const {
    return getParameter<double>(system_, device_, "AcquisitionFrameRate");
}

void Config::setAcquisitionFrameRateEnable(const bool value) {
    setParameter<bool>(system_, device_, "AcquisitionFrameRateEnable", value);
}

bool Config::getAcquisitionFrameRateEnable() const {
    return getParameter<bool>(system_, device_, "AcquisitionFrameRateEnable");
}

void Config::setAcquisitionMode(const char* value) {
    setParameter<GenICam::gcstring>(system_, device_, "AcquisitionMode", static_cast<GenICam::gcstring>(value));
}

std::string Config::getAcquisitionMode() const {
    return std::string(getParameter<GenICam::gcstring>(system_, device_, "AcquisitionMode").c_str());
}

void Config::setAcquisitionStartMode(const char* value) {
    setParameter<GenICam::gcstring>(system_, device_, "AcquisitionStartMode", static_cast<GenICam::gcstring>(value));
}

std::string Config::getAcquisitionStartMode() const {
    return std::string(getParameter<GenICam::gcstring>(system_, device_, "AcquisitionStartMode").c_str());
}

void Config::setBinningHorizontal(const int64_t value) {
    setParameter<int64_t>(system_, device_, "BinningHorizontal", value);
}

int64_t Config::getBinningHorizontal() const {
    return getParameter<int64_t>(system_, device_, "BinningHorizontal");
}

void Config::setBinningHorizontalMode(const char* value) {
    setParameter<GenICam::gcstring>(system_, device_, "BinningHorizontalMode", static_cast<GenICam::gcstring>(value));
}

std::string Config::getBinningHorizontalMode() const {
    return std::string(getParameter<GenICam::gcstring>(system_, device_, "BinningHorizontalMode").c_str());
}

void Config::setBinningSelector(const char* value) {
    setParameter<GenICam::gcstring>(system_, device_, "BinningSelector", static_cast<GenICam::gcstring>(value));
}

std::string Config::getBinningSelector() const {
    return std::string(getParameter<GenICam::gcstring>(system_, device_, "BinningSelector").c_str());
}

void Config::setBinningVertical(const int64_t value) {
    setParameter<int64_t>(system_, device_, "BinningVertical", value);
}

int64_t Config::getBinningVertical() const {
    return getParameter<int64_t>(system_, device_, "BinningVertical");
}

void Config::setBinningVerticalMode(const char* value) {
    setParameter<GenICam::gcstring>(system_, device_, "BinningVerticalMode", static_cast<GenICam::gcstring>(value));
}

std::string Config::getBinningVerticalMode() const {
    return std::string(getParameter<GenICam::gcstring>(system_, device_, "BinningVerticalMode").c_str());
}

void Config::setConversionGain(const char* value) {
    setParameter<GenICam::gcstring>(system_, device_, "ConversionGain", static_cast<GenICam::gcstring>(value));
}

std::string Config::getConversionGain() const {
    return std::string(getParameter<GenICam::gcstring>(system_, device_, "ConversionGain").c_str());
}

std::string Config::getDeviceAccessStatus() const {
    return std::string(getParameter<GenICam::gcstring>(system_, device_, "DeviceAccessStatus").c_str());
}

double Config::getDeviceTemperature() const {
    return getParameter<double>(system_, device_, "DeviceTemperature");
}

void Config::setExposureAuto(const char* value) {
    setParameter<GenICam::gcstring>(system_, device_, "ExposureAuto", static_cast<GenICam::gcstring>(value));
}

std::string Config::getExposureAuto() const {
    return std::string(getParameter<GenICam::gcstring>(system_, device_, "ExposureAuto").c_str());
}

void Config::setExposureAutoLimitAuto(const char* value) {
    setParameter<GenICam::gcstring>(system_, device_, "ExposureAutoLimitAuto", static_cast<GenICam::gcstring>(value));
}

[[nodiscard]] std::string Config::getExposureAutoLimitAuto() const {
    return std::string(getParameter<GenICam::gcstring>(system_, device_, "ExposureAutoLimitAuto").c_str());
}

void Config::setExposureAutoLowerLimit(const double value) {
    setParameter<double>(system_, device_, "ExposureAutoLowerLimit", value);
}

[[nodiscard]] double Config::getExposureAutoLowerLimit() const {
    return getParameter<double>(system_, device_, "ExposureAutoLowerLimit");
}

void Config::setExposureAutoUpperLimit(const double value) {
    setParameter<double>(system_, device_, "ExposureAutoUpperLimit", value);
}

[[nodiscard]] double Config::getExposureAutoUpperLimit() const {
    return getParameter<double>(system_, device_, "ExposureAutoUpperLimit");
}

void Config::setExposureTime(const double value) {
    setParameter<double>(system_, device_, "ExposureTime", value);
}

[[nodiscard]] double Config::getExposureTime() const {
    return getParameter<double>(system_, device_, "ExposureTime");
}

void Config::setGainAuto(const char* value) {
    setParameter<GenICam::gcstring>(system_, device_, "GainAuto", static_cast<GenICam::gcstring>(value));
}

std::string Config::getGainAuto() const {
    return std::string(getParameter<GenICam::gcstring>(system_, device_, "GainAuto").c_str());
}

void Config::setGevCurrentIPConfigurationDHCP(const bool value) {
    setParameter<bool>(system_, device_, "GevCurrentIPConfigurationDHCP", value);
}

bool Config::getGevCurrentIPConfigurationDHCP() const {
    return getParameter<bool>(system_, device_, "GevCurrentIPConfigurationDHCP");
}

bool Config::getGevCurrentIPConfigurationLLA() const {
    return getParameter<bool>(system_, device_, "GevCurrentIPConfigurationLLA");
}

void Config::setGevCurrentIPConfigurationPersistentIP(const bool value) {
    setParameter<bool>(system_, device_, "GevCurrentIPConfigurationPersistentIP", value);
}

bool Config::getGevCurrentIPConfigurationPersistentIP() const {
    return getParameter<bool>(system_, device_, "GevCurrentIPConfigurationPersistentIP");
}

void Config::setGevPersistentIPAddress(const char* value) {
    setParameter<int64_t>(system_, device_, "GevPersistentIPAddress", toIntIPAddress(std::string(value)));
}

int64_t Config::getGevPersistentIPAddress() const {
    return getParameter<int64_t>(system_, device_, "GevPersistentIPAddress");
}

std::string Config::getGevPersistentIPAddressStr() const {
    return toStrIPAddress(getParameter<int64_t>(system_, device_, "GevPersistentIPAddress"));
}

void Config::setGevPersistentSubnetMask(const char* value) {
    setParameter<int64_t>(system_, device_, "GevPersistentSubnetMask", toIntIPAddress(std::string(value)));
}

int64_t Config::getGevPersistentSubnetMask() const {
    return getParameter<int64_t>(system_, device_, "GevPersistentSubnetMask");
}

std::string Config::getGevPersistentSubnetMaskStr() const {
    return toStrIPAddress(getParameter<int64_t>(system_, device_, "GevPersistentSubnetMask"));
}

void Config::setGevPersistentARPConflictDetectionEnable(const bool value) {
    setParameter<bool>(system_, device_, "GevPersistentARPConflictDetectionEnable", value);
}

void Config::setGevMCDA(const int64_t value) {
    setParameter<int64_t>(system_, device_, "GevMCDA", value);
}

void Config::setGevMCDA(const char* value) {
    setParameter<int64_t>(system_, device_, "GevMCDA", toIntIPAddress(std::string(value)));
}

int64_t Config::getGevMCDA() const {
    return getParameter<int64_t>(system_, device_, "GevMCDA");
}

std::string Config::getGevMCDAStr() const {
    return toStrIPAddress(getParameter<int64_t>(system_, device_, "GevMCDA"));
}

void Config::setGevSCDA(const int64_t value) {
    setParameter<int64_t>(system_, device_, "GevSCDA", value);
}

void Config::setGevSCDA(const char* value) {
    setParameter<int64_t>(system_, device_, "GevSCDA", toIntIPAddress(value));
}

int64_t Config::getGevSCDA() const {
    return getParameter<int64_t>(system_, device_, "GevSCDA");
}

std::string Config::getGevSCDAStr() const {
    return toStrIPAddress(getParameter<int64_t>(system_, device_, "GevSCDA"));
}

void Config::setGevSCPSPacketSize(const int64_t value) {
    setParameter<int64_t>(system_, device_, "GevSCPSPacketSize", value);
}

int64_t Config::getGevSCPSPacketSize() const {
    return getParameter<int64_t>(system_, device_, "GevSCPSPacketSize");
}

void Config::setHeight(const int64_t value) {
    setParameter<int64_t>(system_, device_, "Height", value);
}

int64_t Config::getHeight() const {
    return getParameter<int64_t>(system_, device_, "Height");
}

int64_t Config::getHeightMax() const {
    return getParameter<int64_t>(system_, device_, "HeightMax");
}

void Config::setPixelFormat(const char* value) {
    setParameter<GenICam::gcstring>(system_, device_, "PixelFormat", static_cast<GenICam::gcstring>(value));
}

std::string Config::getPixelFormat() const {
    return std::string(getParameter<GenICam::gcstring>(system_, device_, "PixelFormat").c_str());
}

void Config::setPtpEnable(const bool value) {
    setParameter<bool>(system_, device_, "PtpEnable", value);
}

bool Config::getPtpEnable() const {
    return getParameter<bool>(system_, device_, "PtpEnable");
}

void Config::setPtpSlaveOnly(const bool value) {
    setParameter<bool>(system_, device_, "PtpSlaveOnly", value);
}

bool Config::getPtpSlaveOnly() const {
    return getParameter<bool>(system_, device_, "PtpSlaveOnly");
}

std::string Config::getPtpStatus() const {
    return std::string(getParameter<GenICam::gcstring>(system_, device_, "PtpStatus").c_str());
}

void Config::setReverseX(const bool value) {
    setParameter<bool>(system_, device_, "ReverseX", value);
}

bool Config::getReverseX() const {
    return getParameter<bool>(system_, device_, "ReverseX");
}

void Config::setReverseY(const bool value) {
    setParameter<bool>(system_, device_, "ReverseY", value);
}

bool Config::getReverseY() const {
    return getParameter<bool>(system_, device_, "ReverseY");
}

[[nodiscard]] double Config::getScan3dCoordinateOffset() const {
    return getParameter<double>(system_, device_, "Scan3dCoordinateOffset");
}

[[nodiscard]] double Config::getScan3dCoordinateScale() const {
    return getParameter<double>(system_, device_, "Scan3dCoordinateScale");
}

void Config::setScan3dCoordinateSelector(const char* value) {
    setParameter<GenICam::gcstring>(system_, device_, "Scan3dCoordinateSelector",
                                    static_cast<GenICam::gcstring>(value));
}

std::string Config::getScan3dCoordinateSelector() const {
    return std::string(getParameter<GenICam::gcstring>(system_, device_, "Scan3dCoordinateSelector").c_str());
}

void Config::setScan3dModeSelector(const char* value) {
    setParameter<GenICam::gcstring>(system_, device_, "Scan3dModeSelector", static_cast<GenICam::gcstring>(value));
}

std::string Config::getScan3dModeSelector() const {
    return std::string(getParameter<GenICam::gcstring>(system_, device_, "Scan3dModeSelector").c_str());
}

void Config::setStreamAutoNegotiatePacketSize(const bool value) {
    setParameter<bool>(system_, device_, "StreamAutoNegotiatePacketSize", value);
}

bool Config::getStreamAutoNegotiatePacketSize() const {
    return getParameter<bool>(system_, device_, "StreamAutoNegotiatePacketSize");
}

void Config::setStreamBufferHandlingMode(const char* value) {
    setParameter<GenICam::gcstring>(system_, device_, "StreamBufferHandlingMode",
                                    static_cast<GenICam::gcstring>(value));
}

std::string Config::getStreamBufferHandlingMode() const {
    return std::string(getParameter<GenICam::gcstring>(system_, device_, "StreamBufferHandlingMode").c_str());
}

int64_t Config::getStreamLostFrameCount() const {
    return getParameter<int64_t>(system_, device_, "StreamLostFrameCount");
}

int64_t Config::getStreamMissedPacketCount() const {
    return getParameter<int64_t>(system_, device_, "StreamMissedPacketCount");
}

void Config::setStreamMulticastEnable(const bool value) {
    setParameter<bool>(system_, device_, "StreamMulticastEnable", value);
}

bool Config::getStreamMulticastEnable() const {
    return getParameter<bool>(system_, device_, "StreamMulticastEnable");
}

void Config::setStreamPacketResendEnable(const bool value) {
    setParameter<bool>(system_, device_, "StreamPacketResendEnable", value);
}

bool Config::getStreamPacketResendEnable() const {
    return getParameter<bool>(system_, device_, "StreamPacketResendEnable");
}

void Config::setTargetBrightness(const int64_t value) {
    setParameter<int64_t>(system_, device_, "TargetBrightness", static_cast<int64_t>(value));
}

int64_t Config::getTargetBrightness() const {
    return getParameter<int64_t>(system_, device_, "TargetBrightness");
}

void Config::setTransferControlMode(const char* value) {
    setParameter<GenICam::gcstring>(system_, device_, "TransferControlMode", static_cast<GenICam::gcstring>(value));
}

std::string Config::getTransferControlMode() const {
    return std::string(getParameter<GenICam::gcstring>(system_, device_, "TransferControlMode").c_str());
}

void Config::setTransferOperationMode(const char* value) {
    setParameter<GenICam::gcstring>(system_, device_, "TransferOperationMode", static_cast<GenICam::gcstring>(value));
}

std::string Config::getTransferOperationMode() const {
    return std::string(getParameter<GenICam::gcstring>(system_, device_, "TransferOperationMode").c_str());
}

void Config::setTransferSelector(const char* value) {
    setParameter<GenICam::gcstring>(system_, device_, "TransferSelector", static_cast<GenICam::gcstring>(value));
}

std::string Config::getTransferSelector() const {
    return std::string(getParameter<GenICam::gcstring>(system_, device_, "TransferSelector").c_str());
}

void Config::setTriggerActivation(const char* value) {
    setParameter<GenICam::gcstring>(system_, device_, "TriggerActivation", static_cast<GenICam::gcstring>(value));
}

std::string Config::getTriggerActivation() const {
    return std::string(getParameter<GenICam::gcstring>(system_, device_, "TriggerActivation").c_str());
}

bool Config::getTriggerArmed() const {
    return getParameter<bool>(system_, device_, "TriggerArmed");
}

void Config::setTriggerDelay(const double value) {
    setParameter<double>(system_, device_, "TriggerDelay", value);
}

double Config::getTriggerDelay() const {
    return getParameter<double>(system_, device_, "TriggerDelay");
}

void Config::setTriggerLatency(const char* value) {
    setParameter<GenICam::gcstring>(system_, device_, "TriggerLatency", static_cast<GenICam::gcstring>(value));
}

std::string Config::getTriggerLatency() const {
    return std::string(getParameter<GenICam::gcstring>(system_, device_, "TriggerLatency").c_str());
}

void Config::setTriggerMode(const char* value) {
    setParameter<GenICam::gcstring>(system_, device_, "TriggerMode", static_cast<GenICam::gcstring>(value));
}

std::string Config::getTriggerMode() const {
    return std::string(getParameter<GenICam::gcstring>(system_, device_, "TriggerMode").c_str());
}

void Config::setTriggerOverlap(const char* value) {
    setParameter<GenICam::gcstring>(system_, device_, "TriggerOverlap", static_cast<GenICam::gcstring>(value));
}

std::string Config::getTriggerOverlap() const {
    return std::string(getParameter<GenICam::gcstring>(system_, device_, "TriggerOverlap").c_str());
}

void Config::setTriggerSelector(const char* value) {
    setParameter<GenICam::gcstring>(system_, device_, "TriggerSelector", static_cast<GenICam::gcstring>(value));
}

std::string Config::getTriggerSelector() const {
    return std::string(getParameter<GenICam::gcstring>(system_, device_, "TriggerSelector").c_str());
}

void Config::setTriggerSource(const char* value) {
    setParameter<GenICam::gcstring>(system_, device_, "TriggerSource", static_cast<GenICam::gcstring>(value));
}

std::string Config::getTriggerSource() const {
    return std::string(getParameter<GenICam::gcstring>(system_, device_, "TriggerSource").c_str());
}

void Config::setWidth(const int64_t value) {
    setParameter<int64_t>(system_, device_, "Width", value);
}

int64_t Config::getWidth() const {
    return getParameter<int64_t>(system_, device_, "Width");
}

int64_t Config::getWidthMax() const {
    return getParameter<int64_t>(system_, device_, "WidthMax");
}

}  // namespace lucid
}  // namespace camera
