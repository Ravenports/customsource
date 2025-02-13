DEF[PORTVERSION]=	7.87.0
DEF[SOVERSION]=		4.8.0
DEF[DOCS]=		FAQ INSTALL KNOWN_BUGS MAIL-ETIQUETTE THANKS TODO options-in-versions
# MANUAL
# ----------------------------------------------------------------------------

NAMEBASE=		flatcurl
VERSION=		${PORTVERSION}
KEYWORDS=		ftp net www
VARIANTS=		std
SDESC[std]=		Tool and library for transferring data with URLs
HOMEPAGE=		https://curl.haxx.se/
CONTACT=		nobody

DOWNLOAD_GROUPS=	main
SITES[main]=		http://curl.haxx.se/download/
DISTFILE[1]=		curl-${PORTVERSION}.tar.xz:main

SPKGS[std]=		set primary manpages examples docs

OPTIONS_AVAILABLE=	none
OPTIONS_STANDARD=	none

LICENSE=		MIT:primary
LICENSE_FILE=		MIT:{{WRKSRC}}/COPYING
LICENSE_SCHEME=		solo

RUN_DEPENDS=		nss:caroot:std
BUILD_DEPENDS=		libressl:single:static
# BUILDRUN_DEPENDS=	libnghttp2:single:std

FPC_EQUIVALENT=		ftp/curl

USES=			cpe perl:build pkgconfig shebangfix cmake
CMAKE_ARGS=		-DBUILD_SHARED_LIBS:BOOL=OFF
			-DCURL_DISABLE_IMAP:BOOL=ON
			-DCURL_DISABLE_POP3:BOOL=ON
			-DCURL_DISABLE_SMTP:BOOL=ON
			-DCURL_CA_BUNDLE:STRING="{{LOCALBASE}}/share/certs/ca-root-nss.crt"
			-DUSE_NGHTTP2:BOOL=OFF
			-DENABLE_IPV6:BOOL=ON

# LDFLAGS=		-L{{LOCALBASE}}/libressl/lib
# CPPFLAGS=		-I{{LOCALBASE}}/libressl/include
CPE_VENDOR=		haxx
CPE_PRODUCT=		libcurl
SHEBANG_FILES=		*/*.pl
SOVERSION=		${SOVERSION}
DISTNAME=		curl-${PORTVERSION}
