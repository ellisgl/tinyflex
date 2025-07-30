#pragma once
#include <string>
#include <fstream>
#include <iostream>

struct Config {
    u_int16_t PORT        = 0;
    u_int64_t SAMPLE_RATE = 0;
    u_int16_t BITRATE     = 0;
    int8_t    AMPLITUDE   = 0;
    u_int32_t FREQ_DEV    = 0;
    u_int8_t  TX_GAIN     = 0;
};

inline bool load_config(const std::string& filename, Config& cfg) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open configuration file: " << filename << std::endl;
        return false;
    }
    std::string line;
    while (std::getline(file, line)) {
        auto comment = line.find('#');
        if (comment != std::string::npos) {
            line = line.substr(0, comment);
        }
        size_t eq = line.find('=');
        if (eq == std::string::npos) {
            continue;
        }

        std::string key = line.substr(0, eq);
        std::string val = line.substr(eq + 1);
        key.erase(0, key.find_first_not_of(" \t"));
        key.erase(key.find_last_not_of(" \t") + 1);
        val.erase(0, val.find_first_not_of(" \t"));
        val.erase(val.find_last_not_of(" \t") + 1);

        if (key == "PORT") {
            try {
                cfg.PORT = std::stoul(val);
            } catch (...) {
                std::cerr << "Invalid PORT value: " << val << std::endl;
                return false;
            }
        }
        else if (key == "SAMPLE_RATE") {
            try {
                cfg.SAMPLE_RATE = std::stoull(val);
            } catch (...) {
                std::cerr << "Invalid SAMPLE_RATE value: " << val << std::endl;
                return false;
            }
        }
        else if (key == "BITRATE") {
            try {
                cfg.BITRATE = std::stoul(val);
            } catch (...) {
                std::cerr << "Invalid BITRATE value: " << val << std::endl;
                return false;
            }
        }
        else if (key == "AMPLITUDE") {
            try {
                cfg.AMPLITUDE = static_cast<int8_t>(std::stoi(val));
            } catch (...) {
                std::cerr << "Invalid AMPLITUDE value: " << val << std::endl;
                return false;
            }
        }
        else if (key == "FREQ_DEV") {
            try {
                cfg.FREQ_DEV = std::stoul(val);
            } catch (...) {
                std::cerr << "Invalid FREQ_DEV value: " << val << std::endl;
                return false;
            }
        }
        else if (key == "TX_GAIN") {
            try {
                cfg.TX_GAIN = static_cast<uint8_t>(std::stoi(val));
            } catch (...) {
                std::cerr << "Invalid TX_GAIN value: " << val << std::endl;
                return false;
            }
        }
        else {
            std::cerr << "Unknown configuration key: " << key << std::endl;
            return false;
        }
    }

    return true;
}
