#include <SYCL/device_selector.h>
#include <CL/sycl.hpp>
#include <string>

using namespace std;
using namespace cl::sycl;

unique_ptr<device_selector*> getDeviceSelector(const std::string& Vendor, unique_ptr<device_selector*> selector){

    if(Vendor == "AMD"){
        selector = std::make_unique<device_selector*>(new amd_selector);
    }
    else if(Vendor == "Intel"){
        selector = std::make_unique<device_selector*>(new intel_selector);
    }
    else if(Vendor == "Arm"){
        selector = std::make_unique<device_selector*>(new arm_selector);
    }
    else if(Vendor == "GPU"){
        selector = std::make_unique<device_selector*>(new gpu_selector);
    }
    else if(Vendor == "CPU"){
        selector = std::make_unique<device_selector*>(new cpu_selector);
    }
    else if(Vendor == "Host"){
        selector = std::make_unique<device_selector*>(new host_selector);
    } else{
        selector = std::make_unique<device_selector*>(new default_selector);
    }

    return selector;
}