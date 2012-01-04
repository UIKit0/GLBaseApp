#ifndef NX_LOGGING_LOGGING_H_
#define NX_LOGGING_LOGGING_H_

// Boost Log
#define BOOST_LOG_USE_WCHAR_T
#pragma warning(push)
#pragma warning(disable: 4100)
#pragma warning(disable: 4244)
#pragma warning(disable: 4251)
#pragma warning(disable: 4634)
#pragma warning(disable: 4714)
#pragma warning(disable: 4996)
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#define _AFX_SECURE_NO_WARNINGS
#include <boost/ref.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/barrier.hpp>
#include <boost/log/common.hpp>
#include <boost/log/filters.hpp>
#include <boost/log/formatters.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/utility/empty_deleter.hpp>
#include <boost/log/utility/record_ordering.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/basic_attribute_value.hpp>
#undef _AFX_SECURE_NO_WARNINGS
#undef _CRT_NONSTDC_NO_WARNINGS
#undef _CRT_SECURE_NO_WARNINGS
#pragma warning(pop)

namespace nx
{
namespace logging
{
// ********** HRESULT **********

extern void _HResultStr(std::ios_base& os, HRESULT args);

inline std::_Smanip<HRESULT> __cdecl HResultStr(HRESULT args)
{
    return (std::_Smanip<HRESULT>(&_HResultStr, args));
}


/**
 * Loggerの初期化.
 * @param[in] logFileName ログファイル名
 */
extern void InitLogger(const wchar_t* logFileName);
}
}

enum SEVERITY_LEVEL {
    SEVERITY_LEVEL_DEBUG_L3,
    SEVERITY_LEVEL_DEBUG_L2,
    SEVERITY_LEVEL_DEBUG,
    SEVERITY_LEVEL_INFO,
    SEVERITY_LEVEL_WARN,
    SEVERITY_LEVEL_ERROR,
    SEVERITY_LEVEL_FATAL
};

#define LOG(sev) BOOST_LOG_SEV(get_logger(),sev) << __FUNCTION__ << L"(" << __LINE__ << L") - "
#define LOG_HRESULT(sev, hr) BOOST_LOG_SEV(get_logger(),sev) << __FUNCTION__ << L"(" << __LINE__ << L") - " << L"HRESULT = " << nx::logging::HResultStr(hr) << L", "
#define LOG_ENTER(sev) BOOST_LOG_SEV(get_logger(),sev) << __FUNCTION__ << L"(" << __LINE__ << L") <ENTER> - "
#define LOG_LEAVE(sev) BOOST_LOG_SEV(get_logger(),sev) << __FUNCTION__ << L"(" << __LINE__ << L") <LEAVE> - "
#define LOG_LEAVE_HRESULT(sev, hr) BOOST_LOG_SEV(get_logger(),sev) << __FUNCTION__ << L"(" << __LINE__ << L") <LEAVE> - " << L"HRESULT = " << nx::logging::HResultStr(hr)
#define LOG_RESOURCE(level, resource)\
    LOG(level) << L"[RESOURCE] " << #resource << L"(" << typeid(resource).name() << L") = " << std::hex << resource << std::dec

#if defined(DEBUG) || defined(_DEBUG)

#define NXLOG_DEBUG3(args) BOOST_LOG_SEV(get_logger(),SEVERITY_LEVEL_DEBUG_L3) << __FUNCTION__ << L"(" << __LINE__ << L") - " << args
#define NXLOG_DEBUG2(args) BOOST_LOG_SEV(get_logger(),SEVERITY_LEVEL_DEBUG_L2) << __FUNCTION__ << L"(" << __LINE__ << L") - " << args
#define NXLOG_DEBUG(args) BOOST_LOG_SEV(get_logger(),SEVERITY_LEVEL_DEBUG) << __FUNCTION__ << L"(" << __LINE__ << L") - " << args
#define NXLOG_INFO(args) BOOST_LOG_SEV(get_logger(),SEVERITY_LEVEL_INFO) << __FUNCTION__ << L"(" << __LINE__ << L") - " << args
#define NXLOG_WARN(args) BOOST_LOG_SEV(get_logger(),SEVERITY_LEVEL_WARN) << __FUNCTION__ << L"(" << __LINE__ << L") - " << args
#define NXLOG_ERROR(args) BOOST_LOG_SEV(get_logger(),SEVERITY_LEVEL_ERROR) << __FUNCTION__ << L"(" << __LINE__ << L") - " << args
#define NXLOG_FATAL(args) BOOST_LOG_SEV(get_logger(),SEVERITY_LEVEL_FATAL) << __FUNCTION__ << L"(" << __LINE__ << L") - " << args
#define NXLOG_ENTER(args) BOOST_LOG_SEV(get_logger(),SEVERITY_LEVEL_DEBUG) << __FUNCTION__ << L"(" << __LINE__ << L") <ENTER> - " << args
#define NXLOG_LEAVE(args) BOOST_LOG_SEV(get_logger(),SEVERITY_LEVEL_DEBUG) << __FUNCTION__ << L"(" << __LINE__ << L") <LEAVE> - " << args
#define NXLOG_LEAVE_HRESULT(hr, args) BOOST_LOG_SEV(get_logger(),SEVERITY_LEVEL_DEBUG) << __FUNCTION__ << L"(" << __LINE__ << L") <LEAVE> - " << L"HRESULT = " << nx::logging::HResultStr(hr) << args

#else

#define NXLOG_DEBUG3(args) ;
#define NXLOG_DEBUG2(args) ;
#define NXLOG_DEBUG(args) ;
#define NXLOG_INFO(args) BOOST_LOG_SEV(get_logger(),SEVERITY_LEVEL_INFO) << __FUNCTION__ << L"(" << __LINE__ << L") - " << args
#define NXLOG_WARN(args) BOOST_LOG_SEV(get_logger(),SEVERITY_LEVEL_WARN) << __FUNCTION__ << L"(" << __LINE__ << L") - " << args
#define NXLOG_ERROR(args) BOOST_LOG_SEV(get_logger(),SEVERITY_LEVEL_ERROR) << __FUNCTION__ << L"(" << __LINE__ << L") - " << args
#define NXLOG_FATAL(args) BOOST_LOG_SEV(get_logger(),SEVERITY_LEVEL_FATAL) << __FUNCTION__ << L"(" << __LINE__ << L") - " << args
#define NXLOG_ENTER(args) ;
#define NXLOG_LEAVE(args) ;
#define NXLOG_LEAVE_HRESULT(hr, args) ;

#endif

inline std::wostream& operator<< (std::wostream& strm, SEVERITY_LEVEL const& val)
{
    switch (val) {
    case SEVERITY_LEVEL_DEBUG_L3:
        strm << L"DDD";
        break;
    case SEVERITY_LEVEL_DEBUG_L2:
        strm << L"DD";
        break;
    case SEVERITY_LEVEL_DEBUG:
        strm << L'D';
        break;
    case SEVERITY_LEVEL_INFO:
        strm << L'I';
        break;
    case SEVERITY_LEVEL_WARN:
        strm << L'W';
        break;
    case SEVERITY_LEVEL_ERROR:
        strm << L'E';
        break;
    case SEVERITY_LEVEL_FATAL:
        strm << L'F';
        break;
    }
    return strm;
}

BOOST_LOG_DECLARE_GLOBAL_LOGGER(logger, boost::log::sources::wseverity_logger< SEVERITY_LEVEL >);

#endif // NX_LOGGING_LOGGING_H_
