# Install script for directory: /Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mbedtls" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/aes.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/aria.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/asn1.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/asn1write.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/base64.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/bignum.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/block_cipher.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/build_info.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/camellia.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/ccm.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/chacha20.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/chachapoly.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/check_config.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/cipher.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/cmac.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/compat-2.x.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/config_adjust_legacy_crypto.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/config_adjust_legacy_from_psa.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/config_adjust_psa_from_legacy.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/config_adjust_psa_superset_legacy.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/config_adjust_ssl.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/config_adjust_x509.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/config_psa.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/constant_time.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/ctr_drbg.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/debug.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/des.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/dhm.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/ecdh.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/ecdsa.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/ecjpake.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/ecp.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/entropy.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/error.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/gcm.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/hkdf.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/hmac_drbg.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/lms.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/mbedtls_config.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/md.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/md5.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/memory_buffer_alloc.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/net_sockets.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/nist_kw.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/oid.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/pem.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/pk.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/pkcs12.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/pkcs5.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/pkcs7.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/platform.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/platform_time.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/platform_util.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/poly1305.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/private_access.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/psa_util.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/ripemd160.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/rsa.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/sha1.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/sha256.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/sha3.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/sha512.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/ssl.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/ssl_cache.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/ssl_ciphersuites.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/ssl_cookie.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/ssl_ticket.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/threading.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/threading_alt.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/timing.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/version.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/x509.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/x509_crl.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/x509_crt.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/mbedtls/x509_csr.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/psa" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/psa/build_info.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/psa/crypto.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/psa/crypto_adjust_auto_enabled.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/psa/crypto_adjust_config_dependencies.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/psa/crypto_adjust_config_key_pair_types.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/psa/crypto_adjust_config_synonyms.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/psa/crypto_builtin_composites.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/psa/crypto_builtin_key_derivation.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/psa/crypto_builtin_primitives.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/psa/crypto_compat.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/psa/crypto_config.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/psa/crypto_driver_common.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/psa/crypto_driver_contexts_composites.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/psa/crypto_driver_contexts_key_derivation.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/psa/crypto_driver_contexts_primitives.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/psa/crypto_extra.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/psa/crypto_legacy.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/psa/crypto_platform.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/psa/crypto_se_driver.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/psa/crypto_sizes.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/psa/crypto_struct.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/psa/crypto_types.h"
    "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-src/include/psa/crypto_values.h"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/Users/salabdoulaye/Documents/cmput_350/project/CMPUT-350-Project-2/build/_deps/mbedtls-build/include/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
