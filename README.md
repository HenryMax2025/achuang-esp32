# 阿闯 (Achuang) AI 语音机器人

[![GitHub stars](https://img.shields.io/github/stars/achuang-ai/achuang-esp32?style=flat)](https://github.com/achuang-ai/achuang-esp32/stargazers)
[![GitHub forks](https://img.shields.io/github/forks/achuang-ai/achuang-esp32?style=flat)](https://github.com/achuang-ai/achuang-esp32/network)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![ESP-IDF](https://img.shields.io/badge/ESP--IDF-v5.4%2B-blue)](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/)

[English](./README_en.md) | [中文](./README.md)

## 项目介绍

阿闯 (Achuang) 是一款基于 ESP32-S3 开发的开源智能语音机器人，源自 [小智 AI](https://github.com/78/xiaozhi-esp32) 开源项目并进行重构优化。集成了语音唤醒、AI 对话、设备控制和多协议通信功能。

### 核心特性

- 🎙️ **离线语音唤醒** - 支持"你好阿闯"等唤醒词，<200ms 响应
- 🧠 **AI 对话** - 流式 ASR + LLM + TTS 架构
- 🏠 **IoT 控制** - 集成 MCP/MQTT 协议，支持智能家居控制
- 🎵 **多音色 TTS** - 支持 10+ 种角色语音，包括默认的湾湾小何
- 📺 **显示反馈** - OLED/LCD 显示屏，支持表情显示
- 🌐 **多协议支持** - WebSocket / MQTT+UDP 双协议
- 🔄 **OTA 升级** - 远程更新固件
- 🌍 **多语言** - 支持中文、英文、日文等 40+ 语言

### 与原项目对比

| 特性 | 小智 (原) | 阿闯 (新) |
|------|-----------|-----------|
| 默认服务器 | xiaozhi.me | **可自建 + 官方** |
| 默认音色 | 湾湾小何 | 湾湾小何 (不变) |
| TTS 方案 | 商业 API | **自建开源 TTS** |
| 开发板 | 70+ 种 | 70+ 种 (全部支持) |
| License | MIT | MIT |

---

## 硬件支持

### 主力开发板 (ESP32-S3)

| 开发板 | 配置名称 | 说明 |
|--------|----------|------|
| 立创·实战派 ESP32-S3 | `BOARD_TYPE_LICHUANG_DEV_S3` | 🥇 面包板首选 |
| ESP32-S3-BOX3 | `BOARD_TYPE_ESP_BOX_3` | 乐鑫官方 |
| M5Stack CoreS3 | `BOARD_TYPE_M5STACK_CORE_S3` | 带显示屏 |
| AtomS3 + Echo Base | `BOARD_TYPE_M5STACK_ATOM_S3_ECHO_BASE` | 轻量方案 |
| Waveshare AMOLED | `BOARD_TYPE_WAVESHARE_ESP32_S3_TOUCH_AMOLED_1_8` | 1.8寸 AMOLED |
| LILYGO T-Circle-S3 | `BOARD_TYPE_LILYGO_T_CIRCLE_S3` | 圆形设计 |
| SenseCAP Watcher | `BOARD_TYPE_SEEED_STUDIO_SENSECAP_WATCHER` | IP66 防护 |
| 面包板方案 | `BOARD_TYPE_BREAD_COMPACT_WIFI` | 低成本 DIY |

### 完整支持列表

项目支持 **70+ 种** ESP32 开发板，详见 [开发板列表](./docs/supported-boards.md)。

---

## TTS 语音系统

### 角色音色列表

| 角色名称 | 音色特点 | 状态 |
|----------|----------|------|
| **湾湾小何** | 台湾男生，温柔清晰 | ✅ 默认 |
| 台湾女友 | 甜美可爱 | ✅ |
| 高冷御姐 | 御姐音 | ✅ |
| 京腔侃爷 | 北京口音 | ✅ |
| 四川小妹 | 四川话 | ✅ |
| 温柔小姐姐 | 柔声细语 | ✅ |
| 调皮小妹 | 古灵精怪 | ✅ |
| 暴躁老哥 | 大嗓门 | ✅ |
| 专业播音 | 新闻主播 | ✅ |
| 稚嫩童声 | 小朋友 | ✅ |

### TTS 技术方案

#### 推荐开源方案

| 方案 | 特点 | 推荐场景 |
|------|------|----------|
| **CosyVoice** | 阿里开源，流式低延迟 150ms，支持情感控制 | 🥇 实时交互 |
| **F5-TTS** | 推理速度快 (RTF=0.15)，商用友好 | 直播配音 |
| **GPT-SoVITS** | 5 秒样本即可克隆 | 快速定制 |
| **Fish-Speech** | 多语言支持强 | 国际播报 |

#### 部署方式

```bash
# 推荐：CosyVoice 一键部署
docker run -d -p 5000:5000 -v ./data:/data \
  icicle137/cosyvoice:latest

# API 调用示例
curl -X POST http://localhost:5000/tts \
  -H "Content-Type: application/json" \
  -d '{"text": "你好，我是阿闯", "voice": "湾湾小何"}'
```

详见 [TTS 服务器部署指南](./docs/tts-deployment.md)

---

## 快速开始

### 方式一：使用预编译固件 (推荐新手)

1. 下载预编译固件：从 [Release](https://github.com/achuang-ai/achuang-esp32/releases) 下载
2. 使用 ESP32 烧录工具刷入
3. 配网：访问设备热点 `Achuang-Config`，配置 Wi-Fi
4. 开始使用："你好阿闯" 唤醒

### 方式二：源码编译 (适合开发者)

#### 开发环境

```bash
# 1. 安装 ESP-IDF (v5.4+)
./install.sh esp32s3

# 2. 激活环境
source ./export.sh

# 3. 克隆项目
git clone https://github.com/achuang-ai/achuang-esp32.git
cd achuang-esp32

# 4. 配置项目
idf.py set-target esp32s3
idf.py menuconfig

# 5. 编译
idf.py build
```

#### menuconfig 配置说明

```
Achuang Assistant Configuration:
├── OTA Server URL
│   └── https://api.achuang.ai/ota/   # 或自定义服务器
├── Board Type
│   └── 立创·实战派 ESP32-S3          # 选择开发板
├── Flash Assets
│   ├── Default Assets               # 默认资源
│   ├── Custom Assets                # 自定义资源
│   └── Expression Assets            # 表情资源
└── Default Language
    └── 中文简体
```

#### 烧录与调试

```bash
# 烧录固件
idf.py -p /dev/ttyUSB0 flash

# 串口监控
idf.py -p /dev/ttyUSB0 monitor
```

---

## 服务器部署

### 方案一：官方服务器

固件默认连接阿闯官方服务器，注册账号即可使用。

### 方案二：自建服务器

```yaml
# docker-compose.yml
services:
  achuang-server:
    image: achuang-ai/server:latest
    ports:
      - "8000:8000"    # WebSocket
      - "8003:8003"    # HTTP API
    environment:
      - ASR_MODEL=funasr
      - LLM_PROVIDER=qwen
      - TTS_ENGINE=cosyvoice
    volumes:
      - ./data:/data

  cosyvoice:
    image: icicle137/cosyvoice:latest
    ports:
      - "5000:5000"
```

详见 [自建服务器指南](./docs/server-deployment.md)

---

## 项目结构

```
achuang-esp32/
├── README.md                 # 项目说明
├── LICENSE                  # MIT 协议
├── CMakeLists.txt           # 构建配置
├── sdkconfig.defaults       # ESP-IDF 默认配置
├── docs/                    # 文档
│   ├── websocket.md         # WebSocket 通信协议
│   ├── mqtt-udp.md         # MQTT+UDP 协议
│   ├── mcp-protocol.md     # MCP 协议
│   ├── tts-deployment.md   # TTS 部署指南
│   └── server-deployment.md # 服务器部署
├── main/                   # 主程序
│   ├── main.cc            # 入口
│   ├── application.cc/h   # 应用逻辑
│   ├── device_state_machine.cc/h  # 状态机
│   ├── settings.cc/h      # 配置管理
│   ├── ota.cc/h          # OTA 升级
│   ├── mcp_server.cc/h   # MCP 服务器
│   ├── protocols/        # 通信协议
│   │   ├── websocket_protocol.cc/h
│   │   └── mqtt_protocol.cc/h
│   ├── boards/           # 开发板配置 (70+)
│   └── assets/          # 资源文件
├── partitions/           # 分区表
└── scripts/             # 工具脚本
```

---

## 开发指南

- [自定义开发板](./docs/custom-board.md)
- [通信协议](./docs/websocket.md)
- [MCP 物联网控制](./docs/mcp-usage.md)
- [TTS 部署](./docs/tts-deployment.md)

---

## 相关资源

### 自建服务器参考项目

- [xinnan-tech/achuang-esp32-server](https://github.com/xinnan-tech/achuang-esp32-server) Python 服务器
- [joey-zhou/achuang-esp32-server-java](https://github.com/joey-zhou/achuang-esp32-server-java) Java 服务器

### TTS 开源项目

- [CosyVoice](https://github.com/FunAudioLLM/CosyVoice) 阿里开源语音合成
- [F5-TTS](https://github.com/SWivid/F5-TTS) 快速语音合成
- [GPT-SoVITS](https://github.com/RVC-Project/GPT-SoVITS) 语音克隆

---

## 许可证

本项目基于 MIT 许可证开源，允许免费使用、修改和商业应用。

---

## 交流与支持

- 📮 问题反馈：[GitHub Issues](https://github.com/achuang-ai/achuang-esp32/issues)
- 💬 讨论交流：[Discord](https://discord.gg/achuang)
- 📖 文档中心：[achuang.ai](https://achuang.ai/docs)

---

## Star History

[![Star History Chart](https://api.star-history.com/svg?repos=achuang-ai/achuang-esp32&type=Date)](https://star-history.com/#achuang-ai/achuang-esp32&Date)
