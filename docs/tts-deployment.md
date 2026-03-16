# 阿闯 TTS 语音服务器部署指南

本文档介绍如何自建 TTS 语音合成服务器，支持多种开源 TTS 引擎。

## TTS 方案对比

| 方案 | 延迟 | 音色克隆 | 情感控制 | 推荐场景 |
|------|------|----------|----------|----------|
| **CosyVoice** | 150ms | ✅ | ✅ | 实时交互 🥇 |
| **F5-TTS** | 200ms | ✅ | ❌ | 直播配音 |
| **GPT-SoVITS** | 500ms | ✅✅ | ⚠️ | 角色定制 |
| **Fish-Speech** | 300ms | ✅ | ❌ | 多语言 |

## 推荐方案：CosyVoice 部署

### 1. Docker 部署 (推荐)

```bash
# 拉取镜像
docker pull icicle137/cosyvoice:latest

# 启动服务
docker run -d -p 5000:5000 \
  --name cosyvoice \
  -v ./models:/root/.cache/models \
  icicle137/cosyvoice:latest

# 测试 API
curl -X POST http://localhost:5000/tts \
  -H "Content-Type: application/json" \
  -d '{
    "text": "你好，我是阿闯",
    "voice": "湾湾小何",
    "speed": 1.0,
    "pitch": 0
  }'
```

### 2. Docker Compose 部署

创建 `docker-compose.yml`:

```yaml
version: '3.8'

services:
  cosyvoice:
    image: icicle137/cosyvoice:latest
    container_name: achuang-cosyvoice
    ports:
      - "5000:5000"
    volumes:
      - ./data:/data
      - ./models:/root/.cache/models
    environment:
      - TZ=Asia/Shanghai
    restart: unless-stopped
    deploy:
      resources:
        reservations:
          devices:
            - driver: nvidia
              count: 1
              capabilities: [gpu]
```

启动服务：

```bash
docker-compose up -d
```

### 3. API 接口说明

#### TTS 语音合成

```bash
POST /tts
Content-Type: application/json

# 请求
{
  "text": "你好，我是阿闯",      # 要合成的内容
  "voice": "湾湾小何",          # 音色选择
  "speed": 1.0,                # 语速 0.5-2.0
  "pitch": 0                   # 音调 -12-12
}

# 响应 (audio/wav 或 audio/mp3)
返回二进制音频数据
```

#### 可用音色列表

```bash
GET /voices

# 响应
{
  "voices": [
    {"id": "湾湾小何", "name": "湾湾小何", "gender": "male", "language": "zh-CN"},
    {"id": "台湾女友", "name": "台湾女友", "gender": "female", "language": "zh-CN"},
    {"id": "高冷御姐", "name": "高冷御姐", "gender": "female", "language": "zh-CN"},
    {"id": "京腔侃爷", "name": "京腔侃爷", "gender": "male", "language": "zh-CN"},
    {"id": "四川小妹", "name": "四川小妹", "gender": "female", "language": "zh-CN"},
    {"id": "温柔小姐姐", "name": "温柔小姐姐", "gender": "female", "language": "zh-CN"},
    {"id": "调皮小妹", "name": "调皮小妹", "gender": "female", "language": "zh-CN"},
    {"id": "暴躁老哥", "name": "暴躁老哥", "gender": "male", "language": "zh-CN"},
    {"id": "专业播音", "name": "专业播音", "gender": "male", "language": "zh-CN"},
    {"id": "稚嫩童声", "name": "稚嫩童声", "gender": "child", "language": "zh-CN"}
  ]
}
```

#### 流式 TTS (推荐用于实时对话)

```bash
POST /tts/stream
Content-Type: application/json

# 请求
{
  "text": "你好，我是阿闯",
  "voice": "湾湾小何"
}

# 响应 (流式返回 audio/pcm)
返回 PCM 音频流
```

### 4. 与 ESP32 固件集成

在固件 `menuconfig` 中配置：

```
Achuang Configuration
├── Server URL
│   └── http://your-server-ip:8000
├── TTS Engine
│   └── CosyVoice (HTTP API)
└── Default Voice
    └── 湾湾小何
```

## 备选方案：F5-TTS

### 部署

```bash
docker pull f5tts/f5tts:latest
docker run -d -p 5001:5000 f5tts/f5tts:latest

# API 调用
curl -X POST http://localhost:5001/tts \
  -d "text=你好，我是阿闯&voice=湾湾小何"
```

## 硬件要求

| 方案 | GPU | 显存 | 内存 |
|------|-----|------|------|
| CosyVoice | RTX 3060+ | 8GB | 16GB |
| F5-TTS | RTX 3060+ | 6GB | 12GB |
| GPT-SoVITS | RTX 4090 | 24GB | 32GB |

## 常见问题

### Q: 如何实现低延迟？
A: 使用流式 TTS (Streaming TTS)，首包延迟可控制在 150ms 以内

### Q: 如何定制自己的声音？
A: 
1. 录制 10-30 秒音频
2. 使用 CosyVoice 的克隆功能
3. 获取 voice_id 并配置到固件

### Q: 支持离线部署吗？
A: 
- CosyVoice 支持离线模式
- 也可以使用 Piper TTS (完全离线)

## 参考链接

- [CosyVoice GitHub](https://github.com/FunAudioLLM/CosyVoice)
- [F5-TTS GitHub](https://github.com/SWivid/F5-TTS)
- [GPT-SoVITS GitHub](https://github.com/RVC-Project/GPT-SoVITS)
