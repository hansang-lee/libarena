#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include <ArenaApi.h>

#include "camera/image.h"
#include "camera/lucid/types.h"

namespace camera {

/**
 * @brief General device configuration parameters.
 *
 */
struct DeviceParameters {
    /**
     * @brief A 32-bit unique identifier for each camera.
     *      Action Command uses the Device Key to find the correct camera for trigger.
     *      Provides the device key that allows the device to check the validity of action commands.
     * @param value
     * @note default is 1.
     */
    int64_t action_device_key = 0x00000001;

    /**
     * @brief A 32-bit value. Several cameras can be assigned the same Group Key.
     *      Action Command uses the Group Key to find the correct group of cameras for trigger.
     *      Provides the key that the device will use to validate the action on reception of the action protocol message.
     * @param value
     * @note default is 1.
     */
    int64_t action_group_key = 0x00000001;

    /**
     * @brief All cameras are assigned a Device Key and Group Key.
     *      The Group Mask is used to mask the Group Key so only a subgroup of cameras can be triggered.
     *      Provides the mask that the device will use to validate the action on reception of the action protocol message.
     * @param value
     * @note default is 1.
     */
    int64_t action_group_mask = 0x00000001;

    /**
     * @brief Selects to which Action Signal further Action settings apply.
     * @param value
     * @note default is 0.
     */
    int64_t action_selector = 0;

    /**
     * @brief Enables the unconditional action command mode where action commands are processed even when the primary control channel is closed.
     * @param value "On" / "Off"
     * @note default is "On".
     */
    std::string action_unconditional_mode = "On";

    /**
     * @brief Count of frames processed per second.
     * @param value (0, X]
     * @note default value is 0, which indicates increasing the frame rate upto the maximal value determined by the system.
     */
    double acquisition_frame_rate = 0.0;

    /**
     * @brief Acquisition mode of the device.
     * @param value ["Continuous" / "SingleFrame" / "MultiFrame"]. Continuous acquires images continuously. SingleFrame acquires 1 image before stopping acquisition. MultiFrame acquires a specified number of images before stopping acquisition.
     * @note default is "Continuous".
     */
    std::string acquisition_mode = "Continuous";

    /**
     * @brief Acquisition start mode of the device.
     * @param value [in] "Normal" / "LowLatency"
     * @note default is "Normal".
     */
    std::string acquisition_start_mode = "Normal";

    /**
     * @brief Ratio to combine adjacent pixels in the horizontal direction into a single binned pixel. This is a technique in digital imaging where adjacent pixels in the horizontal direction are combined to form a single "binned" pixel. It could result in increased sensitivity and reduced noise, but with a lower resolution in the horizontal dimension.
     * Ratio to combine adjacent pixels in the horizontal direction into a single binned pixel.
     * this is a technique in digital imaging where adjacent pixels in the horizontal direction are combined to form a single "binned" pixel.
     * it results in increased sensitivity and reduced noise, but with a lower resolution in the horizontal dimension.
     * @param value integer only
     * @note default is 1.
     *
     */
    int64_t binning_horizontal = 1;

    /**
     * @brief Logics for combining the horizontal pixels together.
     * @param value ["Sum" / "Average"] Sum is when multiple pixels combine to form 1 pixel by summing pixels and this method could result in brighter images. Average is when multiple pixels combine to form 1 pixel by averaging pixels and this method could result in less noisy images.
     * @note default is "Average".
     */
    std::string binning_horizontal_mode = "Average";

    /**
     * @brief Binning engine controlled by the BinningHorizontal and BinningVertical features (Binning feature is not supported for formats with color processed, such as BGR8 and RGB8).
     * @param value ["Digital" / "Sensor"] Digitals is binning performed on the FPGA and Sensor is binning performed on the sensor. To enable binning feature, please select "Digital".
     * @note default is "Digital".
     */
    std::string binning_selector = "Digital";

    /**
     * @brief Ratio to combine adjacent pixels in the vertical direction into a single binned pixel. This is a technique in digital imaging where adjacent pixels in the vertical direction are combined to form a single "binned" pixel. It could result in increased sensitivity and reduced noise, but with a lower resolution in the vertical dimension.
     * Ratio to combine adjacent pixels in the vertical direction into a single binned pixel.
     * this is a technique in digital imaging where adjacent pixels in the vertical direction are combined to form a single "binned" pixel.
     * it results in increased sensitivity and reduced noise, but with a lower resolution in the vertical dimension.
     * @param value integer only
     * @note default value is 1.
     */
    int64_t binning_vertical = 1;

    /**
     * @brief Logics for combining the vertically pixels together.
     * @param value ["Sum" / "Average"]
     * @details
     * "Sum" is when multiple pixels combine to form 1 pixel by summing pixels. This method will result in brighter images.
     * "Average" is when multiple pixels combine to form 1 pixel by averaging pixels. This method can result in less noisy images.
     * @note default is "Average".
     */
    std::string binning_vertical_mode = "Average";

    /**
     * @brief
     * @param  value ["Low" / "High"]
     * @note default is "High".
     */
    std::string conversion_gain = "High";

    /**
     * @brief Enable auto exposure time adjustment.
     * @param value "Continuous" / "Off"
     * @note default is "Continuous"
     */
    std::string exposure_auto = "Continuous";

    /**
     * @brief
     * @param value "Continuous" / "Off"
     * @note default is "Continuous"
     */
    std::string exposure_auto_limit_auto = "Continuous";

    /**
     * @brief Least value for exposure time which could reach to under auto-exposure condition.
     * @param value [20.56, (1,000,000 / frame rate)]
     * @note default is 0.
     */
    double exposure_auto_lower_limit = 20.56;

    /**
     * @brief Largest value for exposure time which could reach to under auto-exposure condition.
     * @param value [20.56, (1,000,000 / frame rate)]
     * @note default is 0.
     */
    double exposure_auto_upper_limit = 25000.0;

    /**
     * @brief Fixed exposure time.
     * @param value []
     * @note default is 500.0.
     * @warning exposure time can only be configured when exposure auto feature is diabled.
     */
    double exposure_time = 500.0;

    /**
     * @brief Mode for automatic gain balancing between the sensor color channels or taps.
     * The gain coefficients of each channel or tap are adjusted so they are matched.
     * @param value "Continuous" / "Off"
     * @note default is "Continuous".
     */
    std::string gain_auto = "Continuous";

    /**
     * @brief Controls whether the dhcp ip configuration scheme is activated on the given logical link.
     * @param value true / false
     * @note default is true.
     */
    bool gev_current_ip_configuration_dhcp = true;

    /**
     * @brief Controls whether the persistent ip configuration scheme is activated on the given logical link.
     * @param value true / false
     * @note default is false.
     */
    bool persistent_ip_enable = false;

    /**
     * @brief Controls the destination IP address of the selected stream channel to which a GVSP transmitter must send data stream or the destination IP address from which a GVSP receiver may receive data stream.
     * @param value ipv4
     * @note default destination ip is determined automatically by host which handshakes with devices.
     * If the multicast mode is activated, the destination ip must be in the range of [224.0.0.0, 239.255.255.255].
     */
    std::string gev_scda = "0.0.0.0";

    /**
     * @brief Height of the image (in pixels).
     * @param value (0, X]
     * @note default is 0, which indicates increasing the width upto the maximal value determined by the system.
     */
    int64_t height = 0;

    /**
     * @brief Image pixel format.
     * @param value "Mono8" / "Mono10" / "Mono10p" / "Mono10Packed" / "Mono12" / "Mono12p" / "Mono12Packed" / "Mono16" / "BayerRG8" / "BayerRG10" / "BayerRG10p" / "BayerRG10Packed" / "BayerRG12" / "BayerRG12p" / "BayerRG12Packed" / "BayerRG16" / "RGB8" / "BGR8" / "YCbCr8" / "YCbCr8_CbYCr" / "YUV422_8" / "YUV422_8_UYVY" / "YCbCr411_8" / "YUV411_8_UYYVYY".
     * @note default is BayerRG8.
     */
    std::string pixel_format = "BayerRG8";

    /**
     * @brief Enable the Precision Time Protocol (PTP).
     * @param value true / false
     * @note default is true.
     */
    bool ptp_enable = true;

    /**
     * @brief Enable slave only operation of the PTP.
     * @param value true / false
     * @note default is true.
     */
    bool ptp_slave_only = true;

    /**
     * @brief Horizontally flips the image sent by the device.
     * @param value true / false
     * @note default is false.
     */
    bool reverse_x = false;

    /**
     * @brief Vertically flips the image sent by the device.
     * @param value true / false
     * @note default is false.
     */
    bool reverse_y = false;

    /**
     * @brief Max packet size will be determined by system automatically and applied to the device before streaming begins.
     * @param value true / false
     * @note default is true.
     */
    bool stream_auto_negotiate_packet_size = true;

    /**
     * @brief Mode for handling image buffers.
     * @param value "OldestFirst" / "OldestFirstOverwrite" / "NewestOnly"
     * @note default is "OldestFirst".
     */
    std::string stream_buffer_handling_mode = "OldestFirst";

    /**
     * @brief Enable to stream packets in multicast mode.
     * @param value true / false
     * @note default is false.
     */
    bool stream_multicast_enable = false;

    /**
     * @brief Enable to re-transmit packet if fails.
     * @param value true / false
     * @note default is true.
     */
    bool stream_packet_resend_enable = true;

    /**
     * @brief Pixel value that camera will try to reach by automatically adjusting the exposure time and gain values.
     * @param value [0, 255]
     * @note default is 60.
     */
    int64_t target_brightness = 60;

    /**
     * @brief Control mode for starting streaming of data blocks (images) out of the device.
     * @param value "Basic" / "Automatic" / "UserControlled"
     * @note default is "UserControlled"
     */
    std::string transfer_control_mode = "UserControlled";

    /**
     * @brief
     * @param value "Continuous" / "MultiBlock"
     * @note default is "Continuous".
     */
    std::string transfer_operation_mode = "Continuous";

    /**
     * @brief
     * @param value "RisingEdge" / "FallingEdge" / "AnyEdge"
     * @note default is "RisingEdge"
     */
    std::string trigger_activation = "RisingEdge";

    /**
     * @brief
     * @param value [0, X] in microseconds
     * @note default is "0.0"
     */
    double trigger_delay = 0.0;

    /**
     * @brief
     * @param value "Off" / "OneLine"
     * @note default is "Off"
     */
    std::string trigger_latency = "Off";

    /**
     * @brief Activate trigger mode.
     * @param value "On" / "Off"
     * @note default is "Off".
     */
    std::string trigger_mode = "Off";

    /**
     * @brief
     * @param value "Off" / "ReadOut" / "PreviousFrame"
     * @note default is "Off"
     */
    std::string trigger_overlap = "Off";

    /**
     * @brief Trigger type of the device.
     * @param value [in] "AcquisitionStart" / "FrameStart" / "FrameBurstStart" / "ExposureActive" / "LineStart"
     * @note default is "FrameStart".
     */
    std::string trigger_selector = "FrameStart";

    /**
     * @brief Trigger mode of the device. The feature is only activated when trigger mode is enabled.
     * @param value "Software" / "Line[0:8]" / "Action0" / "Encoder0"
     * @note default is "Action0".
     */
    std::string trigger_source = "Action0";

    /**
     * @brief Width of the image (in pixels).
     * @param value (0, X]
     * @note default is 0, which indicates increasing the width upto the maximal value determined by the system.
     */
    int64_t width = 0;
};

/**
 * @brief General device information.
 *
 */
struct DeviceInfo {
    DeviceType  device_type           = DeviceType::UNDEFINED;
    std::string device_version        = "";
    std::string model                 = "";
    std::string serial                = "";
    std::string vendor                = "";
    std::string mac                   = "";
    std::string ipv4                  = "";
    std::string subnet_mask           = "";
    std::string gateway               = "";
    double      rate                  = 0.0;
    int         max_width             = 0;
    int         max_height            = 0;
    bool        dhcp_enabled          = false;
    bool        persistent_ip_enabled = false;
    bool        lla_enabled           = false;
};

/**
 * @brief General camera device class.
 *
 */
class IDevice {
   public:
    virtual ~IDevice() = default;

    /**
     * @brief Sets configuration parameters for device.
     * @param param [in]
     *
     */
    virtual void config(const DeviceParameters& param) = 0;

    /**
     * @brief Opens device. devices must be opened before IDevice::stream().
     *
     */
    virtual void open() = 0;

    /**
     * @brief Releases and cleans up internal memory of device.
     *
     */
    virtual void release() = 0;

    /**
     * @brief Causes device to begin streaming image data. The stream must be stopped using IDevice::stop(), when no longer needed.
     *
     * @param num_buffer [in] Number of internal buffers to use in acquisition engine.
     */
    virtual void stream(const std::size_t num_buffer = 5UL) = 0;

    /**
     * @brief Stops device from streaming image data and cleans up stream. The stream must be stopped when streaming is no longer needed.
     *
     */
    virtual void stop() = 0;

    virtual bool isConnected() = 0;

    virtual bool isAvailable() = 0;

    /**
     * @brief Returns the device information.
     *
     * @return DeviceInfo
     */
    [[nodiscard]] virtual const DeviceInfo& info() const { return info_; }

    /**
     * @brief Captures an image in form of `camera::IImage`.
     *
     * @return
     */
    [[nodiscard]] virtual std::shared_ptr<IImage> capture(const int64_t timeout_ms = 1000UL) = 0;

    virtual void configurePersistentIpAddress(const std::string& ipv4, const std::string& subnet) = 0;

   protected:
    DeviceInfo info_;
};

}  // namespace camera
