#ifndef VT_EXPORT_INCLUDE_H
#define VT_EXPORT_INCLUDE_H

#include <boost/config.hpp>

#ifdef VulkanTrainingEngine_EXPORTS
#   define LIB_INTERFACE BOOST_SYMBOL_EXPORT
#else
#   define LIB_INTERFACE BOOST_SYMBOL_IMPORT
#endif

#endif
