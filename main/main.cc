/*
 * 阿闯 (Achuang) AI 语音机器人
 * 基于 ESP32-S3 的开源智能语音机器人
 * 
 * 默认音色: 湾湾小何
 * 支持开发板: 70+ 种
 * 
 * Copyright (c) 2024 Achuang AI Team
 * Licensed under MIT License
 */

#include <stdio.h>
#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_system.h>
#include <esp_log.h>
#include <esp_chip_info.h>
#include <esp_flash.h>
#include <esp_app_format.h>

#include "application.h"
#include "settings.h"
#include "ota.h"
#include "system_info.h"

static const char *TAG = "achuang_main";

/**
 * 阿闯 AI 机器人主入口
 * 
 * 功能:
 * - 初始化系统组件 (音频、显示、网络等)
 * - 启动语音识别和对话流程
 * - 处理 OTA 升级
 * - 管理设备状态
 */
void app_main(void) {
    ESP_LOGI(TAG, "=================================================");
    ESP_LOGI(TAG, "  阿闯 AI 语音机器人 v1.0.0");
    ESP_LOGI(TAG, "  Build: %s %s", __DATE__, __TIME__);
    ESP_LOGI(TAG, "  Chip: ESP32-S3");
    ESP_LOGI(TAG, "  Default Voice: 湾湾小何");
    ESP_LOGI(TAG, "=================================================");

    // 打印芯片信息
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    ESP_LOGI(TAG, "CPU cores: %d", chip_info.cores);
    ESP_LOGI(TAG, "WiFi%s%s",
             (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
             (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");
    ESP_LOGI(TAG, "Chip revision: %d", chip_info.revision);
    
    uint32_t flash_size;
    esp_flash_get_size(NULL, &flash_size);
    ESP_LOGI(TAG, "Flash size: %lu MB", flash_size / (1024 * 1024));

    // 初始化应用程序
    Application &app = Application::GetInstance();
    app.Init();
    
    // 启动应用
    app.Start();

    ESP_LOGI(TAG, "阿闯 AI 已启动，等待唤醒词...");
    ESP_LOGI(TAG, "say '你好阿闯' to wake up");
}
