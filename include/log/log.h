#ifndef LOG_H
#define LOG_H

// Uncomment to enable specific logging
#define DEBUG_LOG_PERFORMANCE

#ifdef DEBUG_LOG_PERFORMANCE
    #include <iostream>
    #define LOG_PERFORMANCE(msg) std::cout << "[Debug][Performance] " << msg << std::endl;
#else
    #define LOG_PERFORMANCE(msg) ((void)0);
#endif

#endif // LOG_H