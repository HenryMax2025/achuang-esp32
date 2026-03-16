/*
 * 阿闯 (Achuang) 应用主逻辑
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>
#include <string>
#include <functional>

/**
 * 设备状态枚举
 */
enum class DeviceState {
    kIdle = 0,           // 空闲状态
    kListening = 1,     // 监听中
    kSpeaking = 2,      // 说话中
    kThinking = 3,       // AI 处理中
    kUpgrading = 4,     // 升级中
    kError = 5           // 错误状态
};

/**
 * 音频通道类型
 */
enum class AudioChannel {
    kMic = 0,           // 麦克风输入
    kSpeaker = 1        // 扬声器输出
};

/**
 * 应用主类
 * 负责管理整个设备的运行逻辑
 */
class Application {
public:
    /**
     * 获取单例实例
     */
    static Application& GetInstance();

    /**
     * 初始化应用
     */
    void Init();

    /**
     * 启动应用
     */
    void Start();

    /**
     * 停止应用
     */
    void Stop();

    /**
     * 获取当前状态
     */
    DeviceState GetState() const;

    /**
     * 设置状态
     */
    void SetState(DeviceState state);

    /**
     * 处理语音输入
     */
    void OnAudioInput(const uint8_t* data, size_t len);

    /**
     * 播放 TTS 语音
     */
    void PlayTTS(const std::string& text);

    /**
     * 设置 TTS 音色
     * @param voice 音色名称，如 "湾湾小何"
     */
    void SetVoice(const std::string& voice);

    /**
     * 获取当前 TTS 音色
     */
    std::string GetVoice() const;

    /**
     * 唤醒词检测回调
     */
    void OnWakeWordDetected();

    /**
     * 语音结束回调
     */
    void OnSpeechEnd();

    /**
     * AI 响应回调
     */
    void OnAIResponse(const std::string& response);

    /**
     * 错误回调
     */
    void OnError(const std::string& error);

private:
    Application() = default;
    ~Application() = default;
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    class Impl;
    std::unique_ptr<Impl> impl_;
};

#endif // APPLICATION_H
