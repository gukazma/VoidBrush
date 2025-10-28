#pragma once

#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include <memory>

// 初始化日志系统（可选：支持控制台 + 文件）
inline void init_logger()
{
    // 创建控制台 sink
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::trace);

    // 创建文件 sink（可选）
    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/app.log", 1024 * 1024 * 5, 3);
    file_sink->set_level(spdlog::level::info);

    // 合并 sinks
    spdlog::logger logger("multi_sink", {console_sink, file_sink});
    auto multi_logger = std::make_shared<spdlog::logger>(logger);
    multi_logger->set_level(spdlog::level::trace);
    multi_logger->flush_on(spdlog::level::warn); // 警告及以上立即刷新

    // 注册为默认 logger
    spdlog::set_default_logger(multi_logger);
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] [%@] %v");
}

// 宏封装：便于使用和未来替换
#define LOG_TRACE(...) SPDLOG_TRACE(__VA_ARGS__)
#define LOG_DEBUG(...) SPDLOG_DEBUG(__VA_ARGS__)
#define LOG_INFO(...) SPDLOG_INFO(__VA_ARGS__)
#define LOG_WARN(...) SPDLOG_WARN(__VA_ARGS__)
#define LOG_ERROR(...) SPDLOG_ERROR(__VA_ARGS__)
#define LOG_CRITICAL(...) SPDLOG_CRITICAL(__VA_ARGS__)