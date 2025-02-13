GN_BOOTSTRAP_FLAGS=	--no-clean --no-rebuild --skip-generate-buildfiles

GN_ARGS+=	clang_use_chrome_plugins=false \
		enable_backup_ref_ptr_support=false \
		enable_hangout_services_extension=true \
		enable_log_error_not_reached=true \
		enable_nacl=false \
		enable_remoting=false \
		enable_widevine=true \
		fatal_linker_warnings=false \
		icu_use_data_file=false \
		is_clang=true \
		optimize_webui=true \
		toolkit_views=true \
		treat_warnings_as_errors=false \
		use_allocator_shim=false \
		use_aura=true \
		use_custom_libcxx=true \
		use_custom_libunwind=true \
		use_lld=true \
		use_partition_alloc=true \
		use_partition_alloc_as_malloc=false \
		use_sysroot=false \
		use_system_freetype=false \
		use_system_harfbuzz=true \
		use_system_libffi=true \
		use_system_libjpeg=true \
		use_udev=false \
		use_kerberos=true \
		extra_cxxflags="${CXXFLAGS} ${PINCLUDES}" \
		extra_ldflags="${LDFLAGS}" \
		ffmpeg_branding="${FFMPEG_BRAND}"

# possible future options
GN_ARGS+=	use_alsa=false
GN_ARGS+=	use_thin_lto=false
GN_ARGS+=	use_pulseaudio=false

.if "${BUILDTYPE}" == "Debug"
WANTSPACE=	"21 GB"
GN_ARGS+=	is_debug=true
GN_ARGS+=	is_component_build=false
GN_ARGS+=	symbol_level=1
GN_BOOTSTRAP_FLAGS+=	--debug
MAKE_ARGS+=	-C out/Debug
.else
GN_ARGS+=	blink_symbol_level=0
GN_ARGS+=	is_debug=false
GN_ARGS+=	is_official_build=true
GN_ARGS+=	symbol_level=0
WANTSPACE=	"14 GB"
MAKE_ARGS+=	-C out/Release
.endif 

FFMPEG_BDIR=	${WRKSRC}/build.${FFMPEG_TARGET}.${OPSYS:tl}/${FFMPEG_BRAND}
FFMPEG_CDIR=	${WRKSRC}/third_party/ffmpeg/chromium/config/${FFMPEG_BRAND}/${OPSYS:tl}/${FFMPEG_TARGET}
FFMPEG_TARGET=	x64

# rust
RUSTC_VERSION!=	rustc -V 2>/dev/null || true
MAKE_ENV+=	RUSTC_BOOTSTRAP=1
GN_ARGS+=	enable_rust=true \
		rust_sysroot_absolute="${LOCALBASE}" \
		rustc_version="${RUSTC_VERSION}"

# FreeBSD Chromium Api Key
# Set up Google API keys, see http://www.chromium.org/developers/how-tos/api-keys .
# Note: these are for FreeBSD use ONLY. For your own distribution,
# please get your own set of keys.
GN_ARGS+=	google_api_key="AIzaSyBsp9n41JLW8jCokwn7vhoaMejDFRd1mp8"
