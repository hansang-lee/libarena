#include "camera/lucid/config.hpp"
#include "camera/exception.h"

#include <arpa/inet.h>

namespace camera {
namespace lucid {

namespace {
template<typename T>
void setParameter(Config* config, const char* node, const T value) {
    try {
        GenApi::INodeMap* node_map = config->findNodeMap_(node);
        Arena::SetNodeValue<T>(node_map, GenICam::gcstring(node), value);
    } catch (const GenICam::GenericException& e) {
        if (std::string(node) != "PixelFormat") {
            throw exception::InvalidConfigValue(e.what());
        }
    }
}

template<typename T>
T getParameter(Config* config, const char* node) {
    T result{};
    try {
        GenApi::INodeMap* node_map = config->findNodeMap_(node);
        result                     = Arena::GetNodeValue<T>(node_map, GenICam::gcstring(node));
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
    : arena_system_(system)
    , arena_device_(device) {}

Config::~Config() {}

void Config::setActionCommandExecuteTime(const int64_t value) {
    setParameter<int64_t>(this, "ActionCommandExecuteTime", value);
}

int64_t Config::getActionCommandExecuteTime() const {
    return getParameter<int64_t>(const_cast<Config*>(this), "ActionCommandExecuteTime");
}

void Config::setActionDeviceKey(const int64_t value) {
    setParameter<int64_t>(this, "ActionDeviceKey", value);
}

int64_t Config::getActionDeviceKey() const {
    return getParameter<int64_t>(const_cast<Config*>(this), "ActionDeviceKey");
}

void Config::setActionGroupKey(const int64_t value) {
    setParameter<int64_t>(this, "ActionGroupKey", value);
}

int64_t Config::getActionGroupKey() const {
    return getParameter<int64_t>(const_cast<Config*>(this), "ActionGroupKey");
}

void Config::setActionGroupMask(const int64_t value) {
    setParameter<int64_t>(this, "ActionGroupMask", value);
}

int64_t Config::getActionGroupMask() const {
    return getParameter<int64_t>(const_cast<Config*>(this), "ActionGroupMask");
}

void Config::setActionSelector(const int64_t value) {
    setParameter<int64_t>(this, "ActionSelector", value);
}

int64_t Config::getActionSelector() const {
    return getParameter<int64_t>(const_cast<Config*>(this), "ActionSelector");
}

void Config::setActionUnconditionalMode(const char* value) {
    setParameter<GenICam::gcstring>(this, "ActionUnconditionalMode", static_cast<GenICam::gcstring>(value));
}

std::string Config::getActionUnconditionalMode() const {
    return std::string(getParameter<GenICam::gcstring>(const_cast<Config*>(this), "ActionUnconditionalMode").c_str());
}

int64_t Config::getActionQueueSize() const {
    return getParameter<int64_t>(const_cast<Config*>(this), "ActionQueueSize");
}

void Config::setAcquisitionFrameRate(const double value) {
    setParameter<double>(this, "AcquisitionFrameRate", value);
}

double Config::getAcquisitionFrameRate() const {
    return getParameter<double>(const_cast<Config*>(this), "AcquisitionFrameRate");
}

void Config::setAcquisitionFrameRateEnable(const bool value) {
    setParameter<bool>(this, "AcquisitionFrameRateEnable", value);
}

bool Config::getAcquisitionFrameRateEnable() const {
    return getParameter<bool>(const_cast<Config*>(this), "AcquisitionFrameRateEnable");
}

void Config::setAcquisitionMode(const char* value) {
    setParameter<GenICam::gcstring>(this, "AcquisitionMode", static_cast<GenICam::gcstring>(value));
}

std::string Config::getAcquisitionMode() const {
    return std::string(getParameter<GenICam::gcstring>(const_cast<Config*>(this), "AcquisitionMode").c_str());
}

void Config::setAcquisitionStartMode(const char* value) {
    setParameter<GenICam::gcstring>(this, "AcquisitionStartMode", static_cast<GenICam::gcstring>(value));
}

std::string Config::getAcquisitionStartMode() const {
    return std::string(getParameter<GenICam::gcstring>(const_cast<Config*>(this), "AcquisitionStartMode").c_str());
}

void Config::setBinningHorizontal(const int64_t value) {
    setParameter<int64_t>(this, "BinningHorizontal", value);
}

int64_t Config::getBinningHorizontal() const {
    return getParameter<int64_t>(const_cast<Config*>(this), "BinningHorizontal");
}

void Config::setBinningHorizontalMode(const char* value) {
    setParameter<GenICam::gcstring>(this, "BinningHorizontalMode", static_cast<GenICam::gcstring>(value));
}

std::string Config::getBinningHorizontalMode() const {
    return std::string(getParameter<GenICam::gcstring>(const_cast<Config*>(this), "BinningHorizontalMode").c_str());
}

void Config::setBinningSelector(const char* value) {
    setParameter<GenICam::gcstring>(this, "BinningSelector", static_cast<GenICam::gcstring>(value));
}

std::string Config::getBinningSelector() const {
    return std::string(getParameter<GenICam::gcstring>(const_cast<Config*>(this), "BinningSelector").c_str());
}

void Config::setBinningVertical(const int64_t value) {
    setParameter<int64_t>(this, "BinningVertical", value);
}

int64_t Config::getBinningVertical() const {
    return getParameter<int64_t>(const_cast<Config*>(this), "BinningVertical");
}

void Config::setBinningVerticalMode(const char* value) {
    setParameter<GenICam::gcstring>(this, "BinningVerticalMode", static_cast<GenICam::gcstring>(value));
}

std::string Config::getBinningVerticalMode() const {
    return std::string(getParameter<GenICam::gcstring>(const_cast<Config*>(this), "BinningVerticalMode").c_str());
}

void Config::setConversionGain(const char* value) {
    setParameter<GenICam::gcstring>(this, "ConversionGain", static_cast<GenICam::gcstring>(value));
}

std::string Config::getConversionGain() const {
    return std::string(getParameter<GenICam::gcstring>(const_cast<Config*>(this), "ConversionGain").c_str());
}

std::string Config::getDeviceAccessStatus() const {
    return std::string(getParameter<GenICam::gcstring>(const_cast<Config*>(this), "DeviceAccessStatus").c_str());
}

double Config::getDeviceTemperature() const {
    return getParameter<double>(const_cast<Config*>(this), "DeviceTemperature");
}

void Config::setExposureAuto(const char* value) {
    setParameter<GenICam::gcstring>(this, "ExposureAuto", static_cast<GenICam::gcstring>(value));
}

std::string Config::getExposureAuto() const {
    return std::string(getParameter<GenICam::gcstring>(const_cast<Config*>(this), "ExposureAuto").c_str());
}

void Config::setExposureAutoLimitAuto(const char* value) {
    setParameter<GenICam::gcstring>(this, "ExposureAutoLimitAuto", static_cast<GenICam::gcstring>(value));
}

[[nodiscard]] std::string Config::getExposureAutoLimitAuto() const {
    return std::string(getParameter<GenICam::gcstring>(const_cast<Config*>(this), "ExposureAutoLimitAuto").c_str());
}

void Config::setExposureAutoLowerLimit(const double value) {
    setParameter<double>(this, "ExposureAutoLowerLimit", value);
}

[[nodiscard]] double Config::getExposureAutoLowerLimit() const {
    return getParameter<double>(const_cast<Config*>(this), "ExposureAutoLowerLimit");
}

void Config::setExposureAutoUpperLimit(const double value) {
    setParameter<double>(this, "ExposureAutoUpperLimit", value);
}

[[nodiscard]] double Config::getExposureAutoUpperLimit() const {
    return getParameter<double>(const_cast<Config*>(this), "ExposureAutoUpperLimit");
}

void Config::setExposureTime(const double value) {
    setParameter<double>(this, "ExposureTime", value);
}

[[nodiscard]] double Config::getExposureTime() const {
    return getParameter<double>(const_cast<Config*>(this), "ExposureTime");
}

void Config::setGainAuto(const char* value) {
    setParameter<GenICam::gcstring>(this, "GainAuto", static_cast<GenICam::gcstring>(value));
}

std::string Config::getGainAuto() const {
    return std::string(getParameter<GenICam::gcstring>(const_cast<Config*>(this), "GainAuto").c_str());
}

void Config::setGevCurrentIPConfigurationDHCP(const bool value) {
    setParameter<bool>(this, "GevCurrentIPConfigurationDHCP", value);
}

bool Config::getGevCurrentIPConfigurationDHCP() const {
    return getParameter<bool>(const_cast<Config*>(this), "GevCurrentIPConfigurationDHCP");
}

bool Config::getGevCurrentIPConfigurationLLA() const {
    return getParameter<bool>(const_cast<Config*>(this), "GevCurrentIPConfigurationLLA");
}

void Config::setGevCurrentIPConfigurationPersistentIP(const bool value) {
    setParameter<bool>(this, "GevCurrentIPConfigurationPersistentIP", value);
}

bool Config::getGevCurrentIPConfigurationPersistentIP() const {
    return getParameter<bool>(const_cast<Config*>(this), "GevCurrentIPConfigurationPersistentIP");
}

void Config::setGevPersistentIPAddress(const char* value) {
    setParameter<int64_t>(this, "GevPersistentIPAddress", toIntIPAddress(std::string(value)));
}

int64_t Config::getGevPersistentIPAddress() const {
    return getParameter<int64_t>(const_cast<Config*>(this), "GevPersistentIPAddress");
}

std::string Config::getGevPersistentIPAddressStr() const {
    return toStrIPAddress(getParameter<int64_t>(const_cast<Config*>(this), "GevPersistentIPAddress"));
}

void Config::setGevPersistentSubnetMask(const char* value) {
    setParameter<int64_t>(this, "GevPersistentSubnetMask", toIntIPAddress(std::string(value)));
}

int64_t Config::getGevPersistentSubnetMask() const {
    return getParameter<int64_t>(const_cast<Config*>(this), "GevPersistentSubnetMask");
}

std::string Config::getGevPersistentSubnetMaskStr() const {
    return toStrIPAddress(getParameter<int64_t>(const_cast<Config*>(this), "GevPersistentSubnetMask"));
}

void Config::setGevPersistentARPConflictDetectionEnable(const bool value) {
    setParameter<bool>(this, "GevPersistentARPConflictDetectionEnable", value);
}

void Config::setGevMCDA(const int64_t value) {
    setParameter<int64_t>(this, "GevMCDA", value);
}

void Config::setGevMCDA(const char* value) {
    setParameter<int64_t>(this, "GevMCDA", toIntIPAddress(std::string(value)));
}

int64_t Config::getGevMCDA() const {
    return getParameter<int64_t>(const_cast<Config*>(this), "GevMCDA");
}

std::string Config::getGevMCDAStr() const {
    return toStrIPAddress(getParameter<int64_t>(const_cast<Config*>(this), "GevMCDA"));
}

void Config::setGevSCDA(const int64_t value) {
    setParameter<int64_t>(this, "GevSCDA", value);
}

void Config::setGevSCDA(const char* value) {
    setParameter<int64_t>(this, "GevSCDA", toIntIPAddress(value));
}

int64_t Config::getGevSCDA() const {
    return getParameter<int64_t>(const_cast<Config*>(this), "GevSCDA");
}

std::string Config::getGevSCDAStr() const {
    return toStrIPAddress(getParameter<int64_t>(const_cast<Config*>(this), "GevSCDA"));
}

void Config::setGevSCPSPacketSize(const int64_t value) {
    setParameter<int64_t>(this, "GevSCPSPacketSize", value);
}

int64_t Config::getGevSCPSPacketSize() const {
    return getParameter<int64_t>(const_cast<Config*>(this), "GevSCPSPacketSize");
}

void Config::setHeight(const int64_t value) {
    setParameter<int64_t>(this, "Height", value);
}

int64_t Config::getHeight() const {
    return getParameter<int64_t>(const_cast<Config*>(this), "Height");
}

int64_t Config::getHeightMax() const {
    return getParameter<int64_t>(const_cast<Config*>(this), "HeightMax");
}

void Config::setPixelFormat(const char* value) {
    setParameter<GenICam::gcstring>(this, "PixelFormat", static_cast<GenICam::gcstring>(value));
}

std::string Config::getPixelFormat() const {
    return std::string(getParameter<GenICam::gcstring>(const_cast<Config*>(this), "PixelFormat").c_str());
}

void Config::setPtpEnable(const bool value) {
    setParameter<bool>(this, "PtpEnable", value);
}

bool Config::getPtpEnable() const {
    return getParameter<bool>(const_cast<Config*>(this), "PtpEnable");
}

void Config::setPtpSlaveOnly(const bool value) {
    setParameter<bool>(this, "PtpSlaveOnly", value);
}

bool Config::getPtpSlaveOnly() const {
    return getParameter<bool>(const_cast<Config*>(this), "PtpSlaveOnly");
}

std::string Config::getPtpStatus() const {
    return std::string(getParameter<GenICam::gcstring>(const_cast<Config*>(this), "PtpStatus").c_str());
}

void Config::setReverseX(const bool value) {
    setParameter<bool>(this, "ReverseX", value);
}

bool Config::getReverseX() const {
    return getParameter<bool>(const_cast<Config*>(this), "ReverseX");
}

void Config::setReverseY(const bool value) {
    setParameter<bool>(this, "ReverseY", value);
}

bool Config::getReverseY() const {
    return getParameter<bool>(const_cast<Config*>(this), "ReverseY");
}

[[nodiscard]] double Config::getScan3dCoordinateOffset() const {
    return getParameter<double>(const_cast<Config*>(this), "Scan3dCoordinateOffset");
}

[[nodiscard]] double Config::getScan3dCoordinateScale() const {
    return getParameter<double>(const_cast<Config*>(this), "Scan3dCoordinateScale");
}

void Config::setScan3dCoordinateSelector(const char* value) {
    setParameter<GenICam::gcstring>(this, "Scan3dCoordinateSelector", static_cast<GenICam::gcstring>(value));
}

std::string Config::getScan3dCoordinateSelector() const {
    return std::string(getParameter<GenICam::gcstring>(const_cast<Config*>(this), "Scan3dCoordinateSelector").c_str());
}

void Config::setScan3dModeSelector(const char* value) {
    setParameter<GenICam::gcstring>(this, "Scan3dModeSelector", static_cast<GenICam::gcstring>(value));
}

std::string Config::getScan3dModeSelector() const {
    return std::string(getParameter<GenICam::gcstring>(const_cast<Config*>(this), "Scan3dModeSelector").c_str());
}

void Config::setStreamAutoNegotiatePacketSize(const bool value) {
    setParameter<bool>(this, "StreamAutoNegotiatePacketSize", value);
}

bool Config::getStreamAutoNegotiatePacketSize() const {
    return getParameter<bool>(const_cast<Config*>(this), "StreamAutoNegotiatePacketSize");
}

void Config::setStreamBufferHandlingMode(const char* value) {
    setParameter<GenICam::gcstring>(this, "StreamBufferHandlingMode", static_cast<GenICam::gcstring>(value));
}

std::string Config::getStreamBufferHandlingMode() const {
    return std::string(getParameter<GenICam::gcstring>(const_cast<Config*>(this), "StreamBufferHandlingMode").c_str());
}

int64_t Config::getStreamLostFrameCount() const {
    return getParameter<int64_t>(const_cast<Config*>(this), "StreamLostFrameCount");
}

int64_t Config::getStreamMissedPacketCount() const {
    return getParameter<int64_t>(const_cast<Config*>(this), "StreamMissedPacketCount");
}

void Config::setStreamMulticastEnable(const bool value) {
    setParameter<bool>(this, "StreamMulticastEnable", value);
}

bool Config::getStreamMulticastEnable() const {
    return getParameter<bool>(const_cast<Config*>(this), "StreamMulticastEnable");
}

void Config::setStreamPacketResendEnable(const bool value) {
    setParameter<bool>(this, "StreamPacketResendEnable", value);
}

bool Config::getStreamPacketResendEnable() const {
    return getParameter<bool>(const_cast<Config*>(this), "StreamPacketResendEnable");
}

void Config::setTargetBrightness(const int64_t value) {
    setParameter<int64_t>(this, "TargetBrightness", static_cast<int64_t>(value));
}

int64_t Config::getTargetBrightness() const {
    return getParameter<int64_t>(const_cast<Config*>(this), "TargetBrightness");
}

void Config::setTransferControlMode(const char* value) {
    setParameter<GenICam::gcstring>(this, "TransferControlMode", static_cast<GenICam::gcstring>(value));
}

std::string Config::getTransferControlMode() const {
    return std::string(getParameter<GenICam::gcstring>(const_cast<Config*>(this), "TransferControlMode").c_str());
}

void Config::setTransferOperationMode(const char* value) {
    setParameter<GenICam::gcstring>(this, "TransferOperationMode", static_cast<GenICam::gcstring>(value));
}

std::string Config::getTransferOperationMode() const {
    return std::string(getParameter<GenICam::gcstring>(const_cast<Config*>(this), "TransferOperationMode").c_str());
}

void Config::setTransferSelector(const char* value) {
    setParameter<GenICam::gcstring>(this, "TransferSelector", static_cast<GenICam::gcstring>(value));
}

std::string Config::getTransferSelector() const {
    return std::string(getParameter<GenICam::gcstring>(const_cast<Config*>(this), "TransferSelector").c_str());
}

void Config::setTriggerActivation(const char* value) {
    setParameter<GenICam::gcstring>(this, "TriggerActivation", static_cast<GenICam::gcstring>(value));
}

std::string Config::getTriggerActivation() const {
    return std::string(getParameter<GenICam::gcstring>(const_cast<Config*>(this), "TriggerActivation").c_str());
}

bool Config::getTriggerArmed() const {
    return getParameter<bool>(const_cast<Config*>(this), "TriggerArmed");
}

void Config::setTriggerDelay(const double value) {
    setParameter<double>(this, "TriggerDelay", value);
}

double Config::getTriggerDelay() const {
    return getParameter<double>(const_cast<Config*>(this), "TriggerDelay");
}

void Config::setTriggerLatency(const char* value) {
    setParameter<GenICam::gcstring>(this, "TriggerLatency", static_cast<GenICam::gcstring>(value));
}

std::string Config::getTriggerLatency() const {
    return std::string(getParameter<GenICam::gcstring>(const_cast<Config*>(this), "TriggerLatency").c_str());
}

void Config::setTriggerMode(const char* value) {
    setParameter<GenICam::gcstring>(this, "TriggerMode", static_cast<GenICam::gcstring>(value));
}

std::string Config::getTriggerMode() const {
    return std::string(getParameter<GenICam::gcstring>(const_cast<Config*>(this), "TriggerMode").c_str());
}

void Config::setTriggerOverlap(const char* value) {
    setParameter<GenICam::gcstring>(this, "TriggerOverlap", static_cast<GenICam::gcstring>(value));
}

std::string Config::getTriggerOverlap() const {
    return std::string(getParameter<GenICam::gcstring>(const_cast<Config*>(this), "TriggerOverlap").c_str());
}

void Config::setTriggerSelector(const char* value) {
    setParameter<GenICam::gcstring>(this, "TriggerSelector", static_cast<GenICam::gcstring>(value));
}

std::string Config::getTriggerSelector() const {
    return std::string(getParameter<GenICam::gcstring>(const_cast<Config*>(this), "TriggerSelector").c_str());
}

void Config::setTriggerSource(const char* value) {
    setParameter<GenICam::gcstring>(this, "TriggerSource", static_cast<GenICam::gcstring>(value));
}

std::string Config::getTriggerSource() const {
    return std::string(getParameter<GenICam::gcstring>(const_cast<Config*>(this), "TriggerSource").c_str());
}

void Config::setWidth(const int64_t value) {
    setParameter<int64_t>(this, "Width", value);
}

int64_t Config::getWidth() const {
    return getParameter<int64_t>(const_cast<Config*>(this), "Width");
}

int64_t Config::getWidthMax() const {
    return getParameter<int64_t>(const_cast<Config*>(this), "WidthMax");
}

GenApi::INodeMap* Config::findNodeMap_(const char* node) {
    auto it = node_map_cache_.find(node);
    if (it != node_map_cache_.end()) {
        return it->second;
    }

    GenApi::INodeMap* node_map = nullptr;
    GenICam::gcstring node_name(node);

    if (arena_device_->GetNodeMap()->GetNode(node_name) != nullptr) {
        node_map = arena_device_->GetNodeMap();
    } else if (arena_device_->GetTLStreamNodeMap()->GetNode(node_name) != nullptr) {
        node_map = arena_device_->GetTLStreamNodeMap();
    } else if (arena_system_->GetTLSystemNodeMap()->GetNode(node_name) != nullptr) {
        node_map = arena_system_->GetTLSystemNodeMap();
    } else if (arena_device_->GetTLDeviceNodeMap()->GetNode(node_name) != nullptr) {
        node_map = arena_device_->GetTLDeviceNodeMap();
    }

    if (node_map) {
        node_map_cache_[node] = node_map;
    }
    return node_map;
}

}  // namespace lucid
}  // namespace camera
