#ifndef CONFIG_H
#define CONFIG_H

#ifndef PACKAGE_VERSION
#error "PACKAGE_VERSION is not defined."
#endif

#ifndef PACKAGE_NAME
#error "PACKAGE_NAME is not defined."
#endif

#ifndef PACKAGE_AUTHOR_NAME
#error "PACKAGE_AUTHOR_NAME is not defined."
#endif

#define QD__AUTHOR            "Thomas Quémard"
#define QD__VERSION           "0.1"
#define QD__VERSION_MAJOR     "0"
#define QD__VERSION_MINOR     "1"
#define QD__VM__KEEP_STATS    1

// -------------------------
// NAMESPACES
// -------------------------
#ifndef NS_ROOT
#define NS_ROOT qd
#endif

#ifndef NS_TYPE
#define NS_TYPE t
#endif

#ifndef NS_VM
#define NS_VM vm
#endif

#ifndef NS_UTIL
#define NS_UTIL util
#endif

// # NODIA_ALLOW_UNICODE
#endif


