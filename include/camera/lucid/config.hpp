#pragma once

#include <ArenaApi.h>

#include <cstdint>
#include <string>

namespace camera {
namespace lucid {

/* Guide */
//<! https://www.1stvision.com/cameras/Lucid-Vision-Labs/Helio2-Technical-Reference/html/CategoryDoc.html !>

class Config {
   public:
    Config(Arena::ISystem* system, Arena::IDevice* device);
    ~Config();

    /**
     * @brief Time when the device will execute the command.
     * @param value [in]
     */
    void setActionCommandExecuteTime(const int64_t value);

    /**
     * @brief Gets the currently configured value of action-command-time.
     * @return int64_t
     */
    [[nodiscard]] int64_t getActionCommandExecuteTime() const;

    /**
     * @brief Provides the key that the device will use to validate the action on reception of the action protocol message.
     * @param value [in]
     */
    void setActionDeviceKey(const int64_t value);

    /**
     * @brief Gets the currently configured value of action-device-key.
     * @return int64_t
     */
    [[nodiscard]] int64_t getActionDeviceKey() const;

    /**
     * @brief Provides the key that the device will use to validate the action on reception of the action protocol message.
     * @param value [in]
     */
    void setActionGroupKey(const int64_t value);

    /**
     * @brief Gets the currently configured value of action-group-key.
     * @return int64_t
     */
    [[nodiscard]] int64_t getActionGroupKey() const;

    /**
     * @brief Provides the mask that the device will use to validate the action on reception of the action protocol message.
     * @param value [in]
     */
    void setActionGroupMask(const int64_t value);

    /**
     * @brief Gets the currently configured value of action-group-mask.
     * @return int64_t
     */
    [[nodiscard]] int64_t getActionGroupMask() const;

    /**
     * @brief Selects to which Action Signal further Action settings apply.
     * @param value [in]
     */
    void setActionSelector(const int64_t value);

    /**
     * @brief Gets the currently configured state of action-selector.
     * @return
     */
    [[nodiscard]] int64_t getActionSelector() const;

    /**
     * @brief Enables the unconditional action command mode where action commands are processed even when the primary control channel is closed.
     * It allows a camera to accept action from an application without write access.
     * The device key, group key, and group mask must match similar settings in the system's TL node map.
     * @param value [in] "On" / "Off"
     */
    void setActionUnconditionalMode(const char* value);

    /**
     * @brief Gets the currently configured state of action-unconditional-mode.
     * @return "On" / "Off"
     */
    [[nodiscard]] std::string getActionUnconditionalMode() const;

    /**
     * @brief Indicates the size of the scheduled action command queue.
     * @return
     */
    [[nodiscard]] int64_t getActionQueueSize() const;

    /**
     * @brief Controls the acquisition rate (in Hertz) at which the frames are captured.
     * @param value [in] (0, x) the maximum frame rate depends on product.
     */
    void setAcquisitionFrameRate(const double value);

    /**
     * @brief Gets the currently configured value of frame-rate.
     * @return (0, x)
     */
    [[nodiscard]] double getAcquisitionFrameRate() const;

    /**
     * @brief Controls if the AcquisitionFrameRate feature is writable and used to control the acquisition rate.
     * @param value [in] true / false
     */
    void setAcquisitionFrameRateEnable(const bool value);

    /**
     * @brief Gets the currently configured state of frame-rate enablement.
     * @return true / false
     */
    [[nodiscard]] bool getAcquisitionFrameRateEnable() const;

    /**
     * @brief Specifies the acquisition mode of the current device. It helps determine the number of frames to acquire during each acquisition sequence.
     * @param value [in] "Continuous" / "SingleFrame" / "MultiFrame"
     */
    void setAcquisitionMode(const char* value);

    /**
     * @brief Gets the currently configured state of acquisition-mode.
     * @return "Continuous" / "SingleFrame" / "MultiFrame"
     */
    [[nodiscard]] std::string getAcquisitionMode() const;

    /**
     * @brief Specifies the acquisition start mode.
     * @param value [in] "Normal" / "LowLatency"
     */
    void setAcquisitionStartMode(const char* value);

    /**
     * @brief Gets the currently configured state of acquisition-start-mode.
     * @return "Normal" / "LowLatency"
     */
    [[nodiscard]] std::string getAcquisitionStartMode() const;

    /**
     * @brief Number of horizontal pixels to combine together.
     * This reduces the horizontal resolution (width) of the image.
     * A value of 1 indicates that no horizontal binning is performed by the camera.
     * (Binning is not supported in in color processed pixel formats like BGR8 and RGB8)
     * @details https://support.thinklucid.com/knowledgebase/binning-and-decimation-on-lucid-cameras/?gclid=EAIaIQobChMIhojWovfk_AIVVMFMAh3jeApuEAAYASAAEgLdf_D_BwE
     * @param value [in] (0, x)
     */
    void setBinningHorizontal(const int64_t value);

    /**
     * @brief Gets the currently configured horizontal-binning ratio.
     * @return (0, x)
     */
    [[nodiscard]] int64_t getBinningHorizontal() const;

    /**
     * @brief Selects how to combine the horizontal pixels together.
     * (Binning is not supported in in color processed pixel formats like BGR8 and RGB8)
     * @details https://support.thinklucid.com/knowledgebase/binning-and-decimation-on-lucid-cameras/?gclid=EAIaIQobChMIhojWovfk_AIVVMFMAh3jeApuEAAYASAAEgLdf_D_BwE
     * @param value [in] "Sum" (is when multiple pixels combine to form 1 pixel by summing pixels. This method will result in brighter images)
     *                    / "Average" (is when multiple pixels combine to form 1 pixel by averaging pixels. This method can result in less noisy images)
     */
    void setBinningHorizontalMode(const char* value);

    /**
     * @brief Gets the currently configured state of binning-horizontal-mode.
     * @return "Sum" / "Average"
     */
    [[nodiscard]] std::string getBinningHorizontalMode() const;

    /**
     * @brief Selects which binning engine is controlled by the BinningHorizontal and BinningVertical features.
     * (Binning is not supported in in color processed pixel formats like BGR8 and RGB8)
     * @details https://support.thinklucid.com/knowledgebase/binning-and-decimation-on-lucid-cameras/?gclid=EAIaIQobChMIhojWovfk_AIVVMFMAh3jeApuEAAYASAAEgLdf_D_BwE
     * @param value [in] "Digital" (is binning performed on the FPGA)
     *                    / "Sensor" (is binning performed on the sensor)
     */
    void setBinningSelector(const char* value);

    /**
     * @brief Gets the currently configured state of binning-selector.
     * @return "Digital" / "Sensor"
     */
    [[nodiscard]] std::string getBinningSelector() const;

    /**
     * @brief Number of vertical pixels to combine together.
     * This reduces the vertical resolution (height) of the image.
     * A value of 1 indicates that no vertical binning is performed by the camera.
     * (Binning is not supported in in color processed pixel formats like BGR8 and RGB8)
     * @details https://support.thinklucid.com/knowledgebase/binning-and-decimation-on-lucid-cameras/?gclid=EAIaIQobChMIhojWovfk_AIVVMFMAh3jeApuEAAYASAAEgLdf_D_BwE
     * @param value [in] (0, x)
     */
    void setBinningVertical(const int64_t value);

    /**
     * @brief Gets the currently configured vertical-binning ratio.
     * @return (0, x)
     */
    [[nodiscard]] int64_t getBinningVertical() const;

    /**
     * @brief Selects how to combine the vertical pixels together.
     * (Binning is not supported in in color processed pixel formats like BGR8 and RGB8)
     * @details https://support.thinklucid.com/knowledgebase/binning-and-decimation-on-lucid-cameras/?gclid=EAIaIQobChMIhojWovfk_AIVVMFMAh3jeApuEAAYASAAEgLdf_D_BwE
     * @param value [in] "Sum" / "Average"
     */
    void setBinningVerticalMode(const char* value);

    /**
     * @brief Gets the currently configured state of binning-vertical-mode.
     * @return "Sum" / "Average"
     */
    [[nodiscard]] std::string getBinningVerticalMode() const;

    /**
     * @brief
     * @param value [in] "High" / "Low"
     * @warning only supports `helios` camera.
     */
    void setConversionGain(const char* value);

    /**
     * @brief.
     * @warning only supports `helios` camera.
     * @return "High" / "Low"
     */
    [[nodiscard]] std::string getConversionGain() const;

    /**
     * @brief
     * @return
     */
    [[nodiscard]] std::string getDeviceAccessStatus() const;

    /**
     * @brief Retrieves the device temperature in degree Celsius.
     * @param value [in] [1, 30] (experimentally recommended)
     */
    [[nodiscard]] double getDeviceTemperature() const;

    /**
     * @brief Sets the automatic exposure mode.
     * @param value [in] "Continuous" / "Off"
     */
    void setExposureAuto(const char* value);

    /**
     * @brief Gets the currently configured state of auto-exposure feature.
     * @return "Continuous" / "Off"
     */
    [[nodiscard]] std::string getExposureAuto() const;

    /**
     * @brief Enables or disables to limit exposure time automatically.
     * @param value [in] "Continuous" / "Off"
     */
    void setExposureAutoLimitAuto(const char* value);

    /**
     * @brief Gets the currently configured state of auto-exposure time limit feature.
     * @return "Continuous" / "Off"
     */
    [[nodiscard]] std::string getExposureAutoLimitAuto() const;

    /**
     * @brief Sets the upper limit of exposure time. the maximal exposure time is determined by its current frame-rate.
     * @param value [in] [20.56, (1000000 / currently configured frame-rate)]
     */
    void setExposureAutoLowerLimit(const double value);

    /**
     * @brief Gets the currently configured lower limit of exposure time.
     * @return [20.56, (1000000 / currently configured frame-rate)]
     */
    [[nodiscard]] double getExposureAutoLowerLimit() const;

    /**
     * @brief Sets the upper limit of exposure time. the maximal exposure time is determined by its current frame-rate.
     * @param value [in] [20.56, (1000000 / currently configured frame-rate)]
     */
    void setExposureAutoUpperLimit(const double value);

    /**
     * @brief Gets the currently configured lower limit of exposure time.
     * @return [20.56, (1000000 / currently configured frame-rate)]
     */
    [[nodiscard]] double getExposureAutoUpperLimit() const;

    /**
     * @brief Sets exposure time.
     * @param value [in]
     */
    void setExposureTime(const double value);

    /**
     * @brief Gets exposure time.
     * @return
     */
    [[nodiscard]] double getExposureTime() const;

    /**
     * @brief Sets the automatic gain control mode.
     * @param value [in] "Continuous" / "Off"
     */
    void setGainAuto(const char* value);

    /**
     * @brief Gets the currently configured state of auto-gain feature.
     * @return "Continuous" / "Off"
     */
    [[nodiscard]] std::string getGainAuto() const;

    /**
     * @brief Controls whether the DHCP IP configuration scheme is activated on the given logical link.
     * @param value [in] true / false
     */
    void setGevCurrentIPConfigurationDHCP(const bool value);

    /**
     * @brief Gets the currently configured state of DHCP enablement.
     * @return true / false
     */
    [[nodiscard]] bool getGevCurrentIPConfigurationDHCP() const;

    /**
     * @brief Controls whether the Link Local Address IP configuration scheme is activated on the given logical link.
     * This parameter is always enabled as default, not changable.
     */
    [[nodiscard]] bool getGevCurrentIPConfigurationLLA() const;

    /**
     * @brief Controls whether the Persistent IP configuration scheme is activated on the given logical link.
     * @param value [in] true / false
     */
    void setGevCurrentIPConfigurationPersistentIP(const bool value);

    /**
     * @brief Gets the currently configured state of persistent-ip-configuration enablement.
     * @return true / false
     */
    [[nodiscard]] bool getGevCurrentIPConfigurationPersistentIP() const;

    /**
     * @brief Sets a specific IPv4 address.
     * @param value [in] "XXX.XXX.XXX.XXX"
     */
    void setGevPersistentIPAddress(const char* value);

    /**
     * @brief Gets the persistent IPv4 address.
     * @return
     */
    [[nodiscard]] int64_t getGevPersistentIPAddress() const;

    /**
     * @brief Gets the persistent IPv4 address as string.
     * @return "XXX.XXX.XXX.XXX"
     */
    [[nodiscard]] std::string getGevPersistentIPAddressStr() const;

    /**
     * @brief Sets a specific subnet mask.
     * @param value [in] "XXX.XXX.XXX.XXX"
     */
    void setGevPersistentSubnetMask(const char* value);

    /**
     * @brief Gets the persistent subnet mask.
     * @return
     */
    [[nodiscard]] int64_t getGevPersistentSubnetMask() const;

    /**
     * @brief Gets the persistent subnet mask as string.
     * @return "XXX.XXX.XXX.XXX"
     */
    [[nodiscard]] std::string getGevPersistentSubnetMaskStr() const;

    /**
     * @brief Enabling/disabling ARP conflict detection.
     * @param
     */
    void setGevPersistentARPConflictDetectionEnable(const bool value);

    /**
     * @brief Controls the destination IP address for the message channel.
     * @param value [in]
     */
    void setGevMCDA(const int64_t value);

    /**
     * @brief Controls the destination IP address for the message channel.
     * @param value [in]
     */
    void setGevMCDA(const char* value);

    /**
     * @brief Gets the currently configured value of message-channel-destination-address.
     * @return
     */
    [[nodiscard]] int64_t getGevMCDA() const;

    /**
     * @brief Gets the currently configured value of message-channel-destination-address.
     * @return
     */
    [[nodiscard]] std::string getGevMCDAStr() const;

    /**
     * @brief Controls the destination IP address of the selected stream channel to which a GVSP transmitter must send data stream or the destination IP address from which a GVSP receiver may receive data stream.
     * @param value [in]
     */
    void setGevSCDA(const int64_t value);

    /**
     * @brief Controls the destination IP address of the selected stream channel to which a GVSP transmitter must send data stream or the destination IP address from which a GVSP receiver may receive data stream.
     * @param value [in]
     */
    void setGevSCDA(const char* value);

    /**
     * @brief Gets the currently configured value of stream-channel-destination-address.
     * @return
     */
    [[nodiscard]] int64_t getGevSCDA() const;

    /**
     * @brief Gets the currently configured value of stream-channel-destination-address.
     * @return
     */
    [[nodiscard]] std::string getGevSCDAStr() const;

    /**
     * @brief
     * @param value [in]
     */
    void setGevSCPSPacketSize(const int64_t value);

    /**
     * @brief
     * @return
     */
    [[nodiscard]] int64_t getGevSCPSPacketSize() const;

    /**
     * @brief Sets height of the image provided by the device in pixels.
     * @param value [in] desired height.
     */
    void setHeight(const int64_t value);

    /**
     * @brief Gets the currently configured height.
     * @return (0, x)
     */
    [[nodiscard]] int64_t getHeight() const;

    /**
     * @brief Gets the maximally configurable height.
     * @return
     */
    [[nodiscard]] int64_t getHeightMax() const;

    /**
     * @brief Sets format of the pixels provided by the device.
     * @param value [in] "Mono8" / "Mono10" / "Mono10p" / "Mono10Packed" / "Mono12" / "Mono12p" / "Mono12Packed" / "Mono16" / "BayerRG8" / "BayerRG10" / "BayerRG10p" / "BayerRG10Packed" / "BayerRG12" / "BayerRG12p" / "BayerRG12Packed" / "BayerRG16" / "RGB8" / "BGR8" / "YCbCr8" / "YCbCr8_CbYCr" / "YUV422_8" / "YUV422_8_UYVY" / "YCbCr411_8" / "YUV411_8_UYYVYY"
     */
    void setPixelFormat(const char* value);

    /**
     * @brief Gets the currently configured pixel format.
     * @return "Mono8" / "Mono10" / "Mono10p" / "Mono10Packed" / "Mono12" / "Mono12p" / "Mono12Packed" / "Mono16" / "BayerRG8" / "BayerRG10" / "BayerRG10p" / "BayerRG10Packed" / "BayerRG12" / "BayerRG12p" / "BayerRG12Packed" / "BayerRG16" / "RGB8" / "BGR8" / "YCbCr8" / "YCbCr8_CbYCr" / "YUV422_8" / "YUV422_8_UYVY" / "YCbCr411_8" / "YUV411_8_UYYVYY"
     */
    [[nodiscard]] std::string getPixelFormat() const;

    /**
     * @brief Enables the Precision Time Protocol (PTP).
     * @param value [in] true / false
     */
    void setPtpEnable(const bool value);

    /**
     * @brief Gets the currently configured state of ptp enablement.
     * @return true / false
     */
    [[nodiscard]] bool getPtpEnable() const;

    /**
     * @brief Enables slave only operation of the PTP.
     * @param value [in] true / false
     */
    void setPtpSlaveOnly(const bool value);

    /**
     * @brief Gets the currently configured state of ptp-slave-only enablement.
     * @return true / false
     */
    [[nodiscard]] bool getPtpSlaveOnly() const;

    /**
     * @brief Returns the latched state of the PTP clock.
     */
    [[nodiscard]] std::string getPtpStatus() const;

    /**
     * @brief Flips horizontally the image sent by the device.
     * @param value [in]
     */
    void setReverseX(const bool value);

    /**
     * @brief Gets if image is configured as fliped horizontally.
     * @param value [in]
     */
    [[nodiscard]] bool getReverseX() const;

    /**
     * @brief Flips vertically the image sent by the device.
     * @param value [in]
     */
    void setReverseY(const bool value);

    /**
     * @brief Gets if image is configured as fliped vertically.
     * @param value [in]
     */
    [[nodiscard]] bool getReverseY() const;

    /**
     * @brief
     * @return
     */
    [[nodiscard]] double getScan3dCoordinateOffset() const;

    /**
     * @brief
     * @return
     */
    [[nodiscard]] double getScan3dCoordinateScale() const;

    /**
     * @brief
     * @param value [in] "CoordinateA" / "CoordinateB" / "CoordinateC"
     */
    void setScan3dCoordinateSelector(const char* value);

    /**
     * @brief
     * @return "CoordinateA" / "CoordinateB" / "CoordinateC"
     */
    [[nodiscard]] std::string getScan3dCoordinateSelector() const;

    /**
     * @brief
     * @param value [in] "Processed" / "Raw"
     * @warning only supports `helios` camera.
     */
    void setScan3dModeSelector(const char* value);

    /**
     * @brief
     * @warning only supports `helios` camera.
     * @return "Processed" / "Raw"
     */
    [[nodiscard]] std::string getScan3dModeSelector() const;

    /**
     * @brief Controls whether the max packet size will be determined and applied to the device before streaming begins.
     * @param value [in] true / false
     */
    void setStreamAutoNegotiatePacketSize(const bool value);

    /**
     * @brief Gets the currently configured state of stream-auto-negotiate-packet-size enablement.
     * @return true / false
     */
    [[nodiscard]] bool getStreamAutoNegotiatePacketSize() const;
    /**
     * @brief Available buffer handling modes of this data stream.
     * @details https://www.flir.com/support-center/iis/machine-vision/application-note/understanding-buffer-handling/
     * @param value [in] "OldestFirst" / "OldestFirstOverwrite" / "NewestOnly"
     */
    void setStreamBufferHandlingMode(const char* value);

    /**
     * @brief Gets the currently configured state of stream-buffer-handling-mode.
     * @return "OldestFirst" / "OldestFirstOverwrite" / "NewestOnly"
     */
    [[nodiscard]] std::string getStreamBufferHandlingMode() const;

    /**
     * @brief Gets the accumulated number of lost frames in total.
     * @return >=0
     */
    [[nodiscard]] int64_t getStreamLostFrameCount() const;

    /**
     * @brief Gets the accumulated number of missed packets in total.
     * @return >=0
     */
    [[nodiscard]] int64_t getStreamMissedPacketCount() const;

    /**
     * @brief Controls whether the device will stream in multicast or unicast mode.
     * @param value [in] true / false
     */
    void setStreamMulticastEnable(const bool value);

    /**
     * @brief Gets the currently configured state of multicast enablement.
     * @return true / false
     */
    [[nodiscard]] bool getStreamMulticastEnable() const;

    /**
     * @brief Controls the On/Off status of packet resend.
     * @param value [in] true / false
     */
    void setStreamPacketResendEnable(const bool value);

    /**
     * @brief Gets the currently configured state of stream-packet-resend-enable enablement.
     * @return true / false
     */
    [[nodiscard]] bool getStreamPacketResendEnable() const;

    /**
     * @brief Sets the target brightness in 8-bit.
     * @param value [in] [0, 255]
     */
    void setTargetBrightness(const int64_t value);

    /**
     * @brief Gets the currently configured value of target-brightness.
     * @return [0, 255]
     */
    [[nodiscard]] int64_t getTargetBrightness() const;

    /**
     * @brief Selects the control method for the transfers.
     * @param value [in] "Basic" / "Automatic" / "UserControlled"
     */
    void setTransferControlMode(const char* value);

    /**
     * @brief Gets the currently configured state of transfer-control-mode.
     * @return "Basic" / "Automatic" / "UserControlled"
     */
    [[nodiscard]] std::string getTransferControlMode() const;

    /**
     * @brief Sets the operation mode of transfer.
     * @param value [in] "Continuous" / "MultiBlock"
     */
    void setTransferOperationMode(const char* value);

    /**
     * @brief Gets the currently configured state of transfer-operation-mode.
     * @return "Continuous" / "MultiBlock"
     */
    [[nodiscard]] std::string getTransferOperationMode() const;

    /**
     * @brief Selects which stream transfers are currently controlled by the selected transfer features.
     * @param value [in] "Stream0"
     */
    void setTransferSelector(const char* value);

    /**
     * @brief
     * @return "Stream0"
     */
    [[nodiscard]] std::string getTransferSelector() const;

    /**
     * @brief Selects the activation mode of the trigger to start the timer.
     * @param value [in] "RisingEdge" / "FallingEdge" / "AnyEdge"
     */
    void setTriggerActivation(const char* value);

    /**
     * @brief Gets the currently configured state of trigger-activation.
     * @return "RisingEdge" / "FallingEdge" / "AnyEdge"
     */
    [[nodiscard]] std::string getTriggerActivation() const;

    /**
     * @brief Gets whether the trigger is armed.
     * If the trigger is not armed, triggers will be ignored.
     * @return true / false
     */
    [[nodiscard]] bool getTriggerArmed() const;

    /**
     * @brief
     * @param value [in]
     */
    void setTriggerDelay(const double value);

    /**
     * @brief
     * @return
     */
    [[nodiscard]] double getTriggerDelay() const;

    /**
     * @brief Enables low latency trigger mode.
     * @param value [in] "Off" / "OneLine"
     * @warning To use this feature, TriggerOverlap parameter must be set with "Off".
     */
    void setTriggerLatency(const char* value);

    /**
     * @brief Gets the currently configured state of trigger-latency.
     * @return "Off" / "OneLine"
     */
    [[nodiscard]] std::string getTriggerLatency() const;

    /**
     * @brief Controls the On/Off status of the current trigger.
     * @param value [in] "On" / "Off"
     */
    void setTriggerMode(const char* value);

    /**
     * @brief Gets the currently configured state of trigger-mode.
     * @return "On" / "Off"
     */
    [[nodiscard]] std::string getTriggerMode() const;

    /**
     * @brief Specifies the tpye of trigger overlap permitted with the previous frame or line.
     * This defines when a valid trigger will be accepted (or latched) for a new frame or a new line.
     * @param value [in] "Off" / "ReadOut" / "PreviousFrame"
     */
    void setTriggerOverlap(const char* value);

    /**
     * @brief Gets the currently configured trigger-overlap.
     * @return "Off" / "ReadOut" / "PreviousFrame"
     */
    [[nodiscard]] std::string getTriggerOverlap() const;

    /**
     * @brief Selects the specific trigger type to configure.
     * @param value [in] "AcquisitionStart" / "FrameStart" / "FrameBurstStart" / "ExposureActive" / "LineStart"
     */
    void setTriggerSelector(const char* value);

    /**
     * @brief Gets the currently configured state of trigger-selector.
     * @return "AcquisitionStart" / "FrameStart" / "FrameBurstStart" / "ExposureActive"
     */
    [[nodiscard]] std::string getTriggerSelector() const;

    /**
     * @brief Specifies the source of the trigger. It can be a software internal signal of a physical input hardware signal.
     * @param value [in] "Software" / "Line0" / "Line2" / "Line3" / "Action0"
     */
    void setTriggerSource(const char* value);

    /**
     * @brief Gets the currently configured state of trggier-source.
     * @return "Software" / "Line0" / "Line2" / "Line3" / "Action0"
     */
    [[nodiscard]] std::string getTriggerSource() const;

    /**
     * @brief Sets width of the image provided by the device in pixels.
     * @param value [in] desired width.
     */
    void setWidth(const int64_t value);

    /**
     * @brief Gets the currently configured width.
     * @return (0, x)
     */
    [[nodiscard]] int64_t getWidth() const;

    /**
     * @brief Gets the maximally configurable width.
     * @return
     */
    [[nodiscard]] int64_t getWidthMax() const;

   private:
    Arena::ISystem* system_;
    Arena::IDevice* device_;
};

}  // namespace lucid
}  // namespace camera
