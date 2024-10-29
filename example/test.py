import sys
import mxLogPy as mxLog
import time


def manual_test():
    # 获取 LogManager 单例实例
    logger = mxLog.LogManager.getInstance()
    # 设置文件追加器
    logger.setFileAppender("logAuto.txt")
    # 设置控制台追加器
    logger.setConsoleAppender()

    logger.setOutBufferSize(10)
    logger.setBufferSize(10)
    # 测试消息
    logger.log("Info", mxLog.LogLevel.Info)
    logger.log("Debug", mxLog.LogLevel.Debug)
    logger.log("Info", mxLog.LogLevel.Info)
    logger.log("Warning", mxLog.LogLevel.Warning)
    logger.log("Error", mxLog.LogLevel.Error)
    logger.log("Fatal", mxLog.LogLevel.Fatal)
    logger.clearConsoleBuffer()
    time.sleep(1)


def benchMark():
    # 获取 LogManager 单例实例
    logger = mxLog.LogManager.getInstance()

    # 设置文件追加器
    logger.setFileAppender("benchmark.txt")
    # 设置控制台追加器
    logger.setConsoleAppender()

    # 设置输出缓冲区大小
    logger.setOutBufferSize(1000)

    # 记录开始时间
    start = time.time()

    # 进行十万次 info 输入
    for i in range(20000):
        logger.log("Info :" + str(i), mxLog.LogLevel.Info)
        logger.log("Debug :" + str(i), mxLog.LogLevel.Debug)
        logger.log("Warning :" + str(i), mxLog.LogLevel.Warning)
        logger.log("Error :" + str(i), mxLog.LogLevel.Error)
        logger.log("Fatal :" + str(i), mxLog.LogLevel.Fatal)
        if i == 20000:
            logger.clearConsoleBuffer()

    # 记录结束时间
    end = time.time()

    # 计算耗时
    elapsed_time = end - start

    # 记录耗时到日志
    logger.log(f"Elapsed time: {elapsed_time:.6f} seconds", mxLog.LogLevel.Info)


if __name__ == "__main__":
    manual_test()
    # benchMark()
